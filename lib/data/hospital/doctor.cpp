#include "doctor.hpp"
#include "utils.hpp"

Doctor::Doctor()
    : m_fullname("")
    , m_post("")
    , m_cabinet(0)
    , m_schedule("")
{
}

Doctor::Doctor(const Doctor& other)
    : m_fullname(other.fullname())
    , m_post(other.post())
    , m_cabinet(other.cabinet())
    , m_schedule(other.schedule())
{
}

Doctor::~Doctor()
{
}

DataObject Doctor::toDataObject() const
{
    DataObject out;
    out.setType("doctor");
    out.setValue("fullname", m_fullname);
    out.setValue("post", m_post);
    out.setValue("cabinet", QString("%1").arg(m_cabinet));
    out.setValue("schedule", m_schedule);

    return out;
}

bool Doctor::fromDataObject(const DataObject& object)
{
    QString new_fullname, new_post, new_cabinet, new_schedule;

    if (object.getType() != "doctor")
        return false;

    if (!object.getValue("fullname", new_fullname))
        return false;
    if (!object.getValue("post", new_post))
        return false;
    if (!object.getValue("cabinet", new_cabinet))
        return false;
    if (!object.getValue("schedule", new_schedule))
        return false;

    bool ok = false;
    unsigned cabNumber = new_cabinet.toUInt(&ok);
    if (!ok)
        return false;

    if (!setFullname(new_fullname))
        return false;
    if (!setPost(new_post))
        return false;
    if (!setCabinet(cabNumber))
        return false;
    if (!setSchedule(new_schedule))
        return false;

    return true;
}

QString Doctor::fullname() const
{
    return m_fullname;
}

bool Doctor::setFullname(const QString& fullname)
{
    if (fullname.size() > MAX_DOCTOR_FULLNAME_STRING_SIZE)
        return false;
    if (haveRestrictedChars(fullname))
        return false;

    m_fullname = fullname;
    return true;
}

QString Doctor::post() const
{
    return m_post;
}

bool Doctor::setPost(const QString& post)
{
    if (post.size() > MAX_DOCTOR_POST_STRING_SIZE)
        return false;
    if (haveRestrictedChars(post))
        return false;

    m_post = post;
    return true;
}

unsigned Doctor::cabinet() const
{
    return m_cabinet;
}

bool Doctor::setCabinet(const unsigned& cabinet)
{
    if (cabinet > MAX_DOCTOR_CABINET)
        return false;
    m_cabinet = cabinet;
    return true;
}

QString Doctor::schedule() const
{
    return m_schedule;
}

bool Doctor::setSchedule(const QString& schedule)
{
    if (schedule.size() > MAX_DOCTOR_SCHEDULE_STRING_SIZE)
        return false;
    if (haveRestrictedChars(schedule))
        return false;

    m_schedule = schedule;
    return true;
}

bool Doctor::operator==(const Doctor& other) const
{
    return m_fullname == other.fullname();
}

bool Doctor::operator!=(const Doctor& other) const
{
    return !(m_fullname == other.fullname());
}

bool Doctor::operator<(const Doctor& other) const
{
    return m_fullname < other.m_fullname;
}

bool Doctor::operator>(const Doctor& other) const
{
    return !(*this < other) && (*this != other);
}

bool Doctor::operator<=(const Doctor& other) const
{
    return *this < other || *this == other;
}

bool Doctor::operator>=(const Doctor& other) const
{
    return *this > other || *this == other;
}
