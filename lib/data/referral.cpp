#include "referral.hpp"
#include "utils.hpp"

Referral::Referral()
    : m_regID("00-000000")
    , m_doctorFullname("")
    , m_date("00.00.0000")
    , m_time("00:00")
{
}

Referral::Referral(const Referral& other)
    : m_regID(other.regID())
    , m_doctorFullname(other.doctorFullname())
    , m_date(other.date())
    , m_time(other.time())
{
}

Referral::~Referral()
{
}

QString Referral::regID() const
{
    return m_regID;
}

bool Referral::setRegID(const QString& regID)
{
    if (regID.size() > MAX_PATIENT_REGID_STRING_SIZE)
        return false;

    if (!TemplateValidate(PATIENT_REGID_TEMPLATE, regID))
        return false;

    m_regID = regID;
    return true;
}

QString Referral::doctorFullname() const
{
    return m_doctorFullname;
}

bool Referral::setDoctorFullname(const QString& doctorFullname)
{
    if (doctorFullname.size() > MAX_DOCTOR_FULLNAME_STRING_SIZE)
        return false;

    m_doctorFullname = doctorFullname;
    return true;
}

QString Referral::date() const
{
    return m_date;
}

bool Referral::setDate(const QString& date)
{
    if (date.size() > MAX_DATE_STRING_SIZE)
        return false;

    if (!TemplateValidate(DATE_STRING_PATTERN, date))
        return false;
    m_date = date;

    return true;
}

QString Referral::time() const
{
    return m_time;
}

bool Referral::setTime(const QString& time)
{
    if (time.size() > MAX_TIME_STRING_SIZE)
        return false;

    if (!TemplateValidate(TIME_STRING_PATTERN, time))
        return false;
    m_time = time;

    return true;
}
