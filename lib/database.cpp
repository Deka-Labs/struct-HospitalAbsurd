#include "database.hpp"

Database::Database()
    : m_patients()
    , m_doctors()
    , m_referrals() {
}

Database::~Database() = default;

StatusCodes Database::loadData(const char* fileName) {
    DataFile m_file;

    auto openCode = m_file.open(fileName, true);
    if (openCode != StatusCode_OK)
        return openCode;

    while (!m_file.atEOF()) {
        DataObject obj;
        auto       code = m_file.ReadNextObject(obj);
        switch (code) {
            case StatusCode_File_NoObject:
                continue;
            case StatusCode_OK:
                break;
            default:
                return code;
        };

        if (obj.getType() == "patient") {
            Patient pat;
            if (!pat.fromDataObject(obj))
                return StatusCode_InvalidObject;
            auto codeAdd = m_patients.addPatient(pat);
            if (codeAdd != StatusCode_OK)
                return codeAdd;
        } else if (obj.getType() == "referral") {
            Referral ref;
            if (!ref.fromDataObject(obj))
                return StatusCode_InvalidObject;
            if (!m_referrals.addReferral(ref))
                return StatusCode_UNKNOWN;
        } else if (obj.getType() == "doctor") {
            Doctor doc;
            if (!doc.fromDataObject(obj))
                return StatusCode_InvalidObject;
            auto codeAdd = m_doctors.add(doc);
            if (codeAdd != StatusCode_OK)
                return codeAdd;
        } else {
            return StatusCode_InvalidObject;
        }
    }
    return StatusCode_OK;
}

void Database::saveTo(const char* fileName) {
    DataFile m_file;

    if (m_file.open(fileName, false) != StatusCode_OK)
        return;

    // Adding patients
    auto registedKeys = m_patients.m_registredKeys;
    auto sizePatients = registedKeys.size();
    for (unsigned pos = 0; pos < sizePatients; pos++) {
        Patient pat;
        if (m_patients.get(registedKeys[pos], &pat)) {
            DataObject obj = pat.toDataObject();
            m_file.insertObject(obj);
        }
    }

    // Adding doctors
    auto doctors     = m_doctors.m_listToDisplay;
    auto sizeDoctors = doctors.size();
    for (unsigned pos = 0; pos < sizeDoctors; pos++) {
        try {
            Doctor     doc = m_doctors.find(doctors[pos].key());
            DataObject obj = doc.toDataObject();
            m_file.insertObject(obj);
        } catch (...) {
            ;
        }
    }

    // Adding referrals
    auto referrals     = m_referrals.m_list;
    auto sizeReferrals = referrals.size();
    for (unsigned pos = 0; pos < sizeReferrals; pos++) {
        const Referral& ref = referrals.at(pos);
        DataObject      obj = ref.toDataObject();
        m_file.insertObject(obj);
    }
}

StatusCodes Database::addPatient(const Patient& newPat) {
    return m_patients.addPatient(newPat);
}

void Database::delPatinet(const PatientHashKey& patientKey) {
    auto list = m_referrals.getConnectedToPatient(patientKey);

    for (unsigned pos = 0; pos < list.size(); pos++) {
        m_referrals.removeReferral(list.at(pos));
    }
    m_patients.delPatient(patientKey);
}

void Database::delAllPatients() {
    m_patients.delAll();
}

StatusCodes Database::addDoctor(const Doctor& newDoc) {
    return m_doctors.add(newDoc);
}

void Database::delDoctor(const QString& docKey) {
    auto list = m_referrals.getConnectedToDoctor(docKey);

    for (unsigned pos = 0; pos < list.size(); pos++) {
        m_referrals.removeReferral(list.at(pos));
    }

    m_doctors.remove(docKey);
}

void Database::delAllDoctors() {
    m_doctors.removeAll();
}

StatusCodes Database::addReferral(const Referral& newRef) {
    auto docName = newRef.doctorFullname();
    auto patID   = newRef.regID();

    if (!m_patients.getPatient(PatientHashKey(patID)))
        return StatusCode_InvalidObject;
    Doctor doc;
    if (!m_doctors.getDoctor(docName, &doc))
        return StatusCode_InvalidObject;

    auto list = m_referrals.getConnectedToDoctor(doc.fullname());

    for (unsigned pos = 0; pos < list.size(); pos++) {
        if (list.at(pos).date() == newRef.date() && list.at(pos).time() == newRef.time())
            return StatusCode_AlreadyExist;
    }

    m_referrals.addReferral(newRef);
    return StatusCode_OK;
}

void Database::delReferral(const Referral& ref) {
    m_referrals.removeReferral(ref);
}

void Database::delAllReferrals() {
    m_referrals.removeAll();
}
