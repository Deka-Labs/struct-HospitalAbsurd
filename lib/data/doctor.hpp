#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include "file/dataobject.hpp"
#include <QString>

#define MAX_DOCTOR_FULLNAME_STRING_SIZE 25
#define MAX_DOCTOR_POST_STRING_SIZE 100
#define MAX_DOCTOR_CABINET 99999
#define MAX_DOCTOR_SCHEDULE_STRING_SIZE 100

class Doctor {
private:
    QString m_fullname;
    QString m_post;
    unsigned m_cabinet;
    QString m_schedule;

public:
    Doctor();
    Doctor(const Doctor& other);
    ~Doctor();

    //Data
    DataObject toDataObject() const;
    bool fromDataObject(const DataObject& object);

    //Set & Get
    QString fullname() const;
    bool setFullname(const QString& fullname);
    QString post() const;
    bool setPost(const QString& post);
    unsigned cabinet() const;
    bool setCabinet(const unsigned& cabinet);
    QString schedule() const;
    bool setSchedule(const QString& schedule);

    QString key() const { return fullname(); }

    //operators
    bool operator==(const Doctor& other) const;
    bool operator!=(const Doctor& other) const;
};

#endif // DOCTOR_HPP
