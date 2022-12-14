#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "file/datafile.hpp"
#include "file/dataobject.hpp"
#include "models/doctorbintree.hpp"
#include "models/patienthashtable.hpp"
#include "models/referrallist.hpp"

class Database {
  private:
    PatientHashTable m_patients;
    DoctorBinTree    m_doctors;
    ReferralList     m_referrals;

  public:
    Database();
    Database(const Database&) = delete;
    ~Database();

    StatusCodes loadData(const char* fileName);
    void        saveTo(const char* fileName);

    PatientHashTable& getPatientsModel() {
        return m_patients;
    }
    DoctorBinTree& getDoctorsModel() {
        return m_doctors;
    }
    ReferralList& getReferralsModel() {
        return m_referrals;
    }

    StatusCodes addPatient(const Patient& newPat);
    void        delPatinet(const PatientHashKey& patientKey);
    void        delAllPatients();

    StatusCodes addDoctor(const Doctor& newDoc);
    void        delDoctor(const QString& docKey);
    void        delAllDoctors();

    StatusCodes addReferral(const Referral& newRef);
    void        delReferral(const Referral& ref);
    void        delAllReferrals();
};

#endif // DATABASE_HPP
