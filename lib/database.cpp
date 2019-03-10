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
            if (!m_patients.addPatient(pat))
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
        if (m_patients.getPatient(registedKeys[pos], &pat)) {
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
