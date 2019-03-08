#ifndef REFERRAL_HPP
#define REFERRAL_HPP

#include "doctor.hpp"
#include "patient.hpp"

#include <QString>

#define MAX_DATE_STRING_SIZE 10
#define DATE_STRING_PATTERN "dd.dd.dddd"
#define MAX_TIME_STRING_SIZE 5
#define TIME_STRING_PATTERN "dd:dd"

class Referral {
private:
    QString m_regID;
    QString m_doctorFullname;
    QString m_date;
    QString m_time;

public:
    Referral();
    Referral(const Referral& other);
    ~Referral();

    //Setters and getters
    QString regID() const;
    bool setRegID(const QString& regID);
    QString doctorFullname() const;
    bool setDoctorFullname(const QString& doctorFullname);
    QString date() const;
    bool setDate(const QString& date);
    QString time() const;
    bool setTime(const QString& time);
};

#endif // REFERRAL_HPP
