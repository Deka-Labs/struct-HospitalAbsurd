#ifndef PATIENTHASHKEY_HPP
#define PATIENTHASHKEY_HPP

#include "data/dataprocessingclasses/hashtable.hpp"

#include <QString>

#define MAX_PATIENTS 100
#define MAX_PATIENT_REGID_STRING_SIZE 9
#define MIN_PATIENT_REGID_STRING_SIZE 9
#define MAX_PATIENT_FULLNAME_STRING_SIZE 100
#define MIN_PATIENT_FULLNAME_STRING_SIZE 5
#define MAX_PATIENT_ADDRESS_STRING_SIZE 50
#define MIN_PATIENT_ADDRESS_STRING_SIZE 5
#define MAX_PATIENT_WORKPLACE_STRING_SIZE 300
#define MIN_PATIENT_WORKPLACE_STRING_SIZE 3
#define MAX_PATIENT_YEAR 9999
#define MIN_PATIENT_YEAR 0
#define PATIENT_REGID_TEMPLATE "dd-dddddd"
#define MAX_PATIENT_HASH_STEP 5

class PatientHashKey : public IHashKey {
    QString m_key;

  public:
    explicit PatientHashKey(QString key = "");

    unsigned hash() const;
    unsigned dopHash() const;
    bool     validateKey() const;

    bool    operator==(const IHashKey& key) const;
    QString key() const;
};

#endif // PATIENTHASHKEY_HPP
