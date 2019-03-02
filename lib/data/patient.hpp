#ifndef PATIENT_HPP
#define PATIENT_HPP

#include "../file/dataobject.hpp"
#include <QString>

#define MAX_PATIENT_REGID_STRING_SIZE 9
#define MAX_PATIENT_FULLNAME_STRING_SIZE 100
#define MAX_PATIENT_ADDRESS_STRING_SIZE 50
#define MAX_PATIENT_WORKPLACE_STRING_SIZE 300
#define MAX_PATIENT_YEAR 9999
#define PATIENT_REGID_TEMPLATE "dd-dddddd"

class PatientHashTable;

class Patient {
private:
    QString m_regID;
    QString m_fullName;
    unsigned m_yearOfBirth;
    QString m_address;
    QString m_workPlace;

public:
    Patient();
    Patient(const Patient& other);
    ~Patient();

    DataObject toDataObject() const;
    bool fromDataObject(const DataObject& object);

    //Getters and setters
    QString regID() const;
    bool setRegID(const QString& regID);
    QString fullName() const;
    bool setFullName(const QString& fullName);
    unsigned yearOfBirth() const;
    bool setYearOfBirth(const unsigned& yearOfBirth);
    QString address() const;
    bool setAddress(const QString& address);
    QString workPlace() const;
    bool setWorkPlace(const QString& workPlace);

    bool operator==(const Patient& other);
    bool operator!=(const Patient& other);

    friend class PatientHashTable;
};
#endif // PATIENT_HPP
