#ifndef PATIENT_HPP
#define PATIENT_HPP

#include "file/dataobject.hpp"
#include "patienthashkey.hpp"

#include <QString>

class PatientHashTable;

class Patient {
  private:
    QString  m_regID;
    QString  m_fullName;
    unsigned m_yearOfBirth;
    QString  m_address;
    QString  m_workPlace;

  public:
    Patient();
    Patient(const Patient& other);
    ~Patient();

    DataObject toDataObject() const;
    bool       fromDataObject(const DataObject& object);

    // Getters and setters
    QString  regID() const;
    bool     setRegID(const QString& regID);
    QString  fullName() const;
    bool     setFullName(const QString& fullName);
    unsigned yearOfBirth() const;
    bool     setYearOfBirth(const unsigned& yearOfBirth);
    QString  address() const;
    bool     setAddress(const QString& address);
    QString  workPlace() const;
    bool     setWorkPlace(const QString& workPlace);

    bool operator==(const Patient& other);
    bool operator!=(const Patient& other);

    PatientHashKey key() const {
        return PatientHashKey(m_regID);
    }

    friend class PatientHashTable;
};
#endif // PATIENT_HPP
