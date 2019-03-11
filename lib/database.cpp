#include "database.hpp"

Database::Database()
    : m_patients()
    , m_doctors()
    , m_referrals()
{
}

Database::~Database()
{
}

bool Database::loadData(const char* fileName)
{
    DataFile m_file;

    if (!m_file.open(fileName, true))
        return false;

    while (!m_file.atEOF()) {
        DataObject obj;
        if (!m_file.ReadNextObject(obj))
            continue;

        if (obj.getType() == "patient") {
            Patient pat;
            if (!pat.fromDataObject(obj))
                return false;
            if (!m_patients.m_hashTable.add(pat))
                return false;
        } else if (obj.getType() == "referral") {
            Referral ref;
            if (!ref.fromDataObject(obj))
                return false;
            if (!m_referrals.addReferral(ref))
                return false;
        } else if (obj.getType() == "doctor") {
            Doctor doc;
            if (!doc.fromDataObject(obj))
                return false;
            if (!m_doctors.addDoctor(doc))
                return false;
        } else {
            return false;
        }
    }
    return true;
}

void Database::saveTo(const char* fileName)
{
    DataFile m_file;

    if (!m_file.open(fileName, false))
        return;

    //Adding patients
    auto registedKeys = m_patients.m_registredKeys;
    auto sizePatients = registedKeys.size();
    for (unsigned pos = 0; pos < sizePatients; pos++) {
        Patient pat;
        if (m_patients.m_hashTable.get(registedKeys[pos], &pat)) {
            DataObject obj = pat.toDataObject();
            m_file.insertObject(obj);
        }
    }

    //Adding doctors
    auto doctors = m_doctors.m_listToDisplay;
    auto sizeDoctors = doctors.size();
    for (unsigned pos = 0; pos < sizeDoctors; pos++) {
        try {
            Doctor doc = m_doctors.m_binTree.find(doctors[pos].key());
            DataObject obj = doc.toDataObject();
            m_file.insertObject(obj);
        } catch (...) {
            ;
        }
    }

    //Adding referrals
    auto referrals = m_referrals.m_list;
    auto sizeReferrals = referrals.size();
    for (unsigned pos = 0; pos < sizeReferrals; pos++) {
        Referral ref = referrals.at(pos);
        DataObject obj = ref.toDataObject();
        m_file.insertObject(obj);
    }
}

bool Database::addPatient(const Patient& newPat)
{
    return m_patients.m_hashTable.add(newPat);
}

void Database::delPatinet(const PatientHashKey& patientKey)
{
    m_patients.m_hashTable.del(patientKey);
    fixConnections();
}

bool Database::addDoctor(const Doctor& newDoc)
{
    return m_doctors.addDoctor(newDoc);
}

void Database::delDoctor(const QString& docKey)
{
    m_doctors.removeDoctor(docKey);
    fixConnections();
}

bool Database::addReferral(const Referral& newRef)
{
    auto docName = newRef.doctorFullname();
    auto patID = newRef.regID();

    if (!m_patients.m_hashTable.get(PatientHashKey(patID)))
        return false;
    if (!m_doctors.getDoctor(docName))
        return false;

    m_referrals.addReferral(newRef);
    return true;
}

void Database::delReferral(const Referral& ref)
{
    m_referrals.removeReferral(ref);
}

void Database::fixConnections()
{
    for (unsigned i = 0; i < m_referrals.m_list.size(); i++) {
        auto ref = m_referrals.m_list[i];
        if (!m_patients.m_hashTable.get(PatientHashKey(ref.regID()))) {
            delReferral(ref);
            continue;
        }
        if (!m_doctors.getDoctor(ref.doctorFullname())) {
            delReferral(ref);
            continue;
        }
    }
}
