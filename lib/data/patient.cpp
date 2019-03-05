#include "patient.hpp"
#include "utils.hpp"
#include <stdexcept>

Patient::Patient()
    : m_regID("00-000000")
    , m_fullName("Unnamed")
    , m_yearOfBirth(0)
    , m_address("-")
    , m_workPlace("-")
{
}

Patient::Patient(const Patient& other)
    : m_regID(other.regID())
    , m_fullName(other.fullName())
    , m_yearOfBirth(other.yearOfBirth())
    , m_address(other.address())
    , m_workPlace(other.workPlace())
{
}

Patient::~Patient()
{
}

QString Patient::regID() const
{
    return m_regID;
}

bool Patient::setRegID(const QString& regID)
{
    if (regID.size() > MAX_PATIENT_REGID_STRING_SIZE)
        return false;

    if (!TemplateValidate(PATIENT_REGID_TEMPLATE, regID))
        return false;

    m_regID = regID;
    return true;
}

QString Patient::fullName() const
{
    return m_fullName;
}

bool Patient::setFullName(const QString& fullName)
{
    if (fullName.size() > MAX_PATIENT_FULLNAME_STRING_SIZE)
        return false;
    m_fullName = fullName;
    return true;
}

unsigned Patient::yearOfBirth() const
{
    return m_yearOfBirth;
}

bool Patient::setYearOfBirth(const unsigned& yearOfBirth)
{
    if (yearOfBirth > MAX_PATIENT_YEAR)
        return false;
    m_yearOfBirth = yearOfBirth;
    return true;
}

QString Patient::address() const
{
    return m_address;
}

bool Patient::setAddress(const QString& address)
{
    if (address.size() > MAX_PATIENT_ADDRESS_STRING_SIZE)
        return false;
    m_address = address;
    return true;
}

QString Patient::workPlace() const
{
    return m_workPlace;
}

bool Patient::setWorkPlace(const QString& workPlace)
{
    if (workPlace.size() > MAX_PATIENT_WORKPLACE_STRING_SIZE)
        return false;
    m_workPlace = workPlace;
    return true;
}

bool Patient::operator==(const Patient& other)
{
    if (m_regID == other.regID() && m_fullName == other.fullName() && m_yearOfBirth == other.yearOfBirth() && m_address == other.address() && m_workPlace == other.workPlace()) {
        return true;
    }
    return false;
}

bool Patient::operator!=(const Patient& other)
{
    return !(*this == other);
}

DataObject Patient::toDataObject() const
{
    DataObject out;
    out.setType("patient");
    out.setValue("regid", m_regID);
    out.setValue("fullname", m_fullName);
    out.setValue("year", QString("%1").arg(m_yearOfBirth));
    out.setValue("address", m_address);
    out.setValue("workplace", m_workPlace);
    return out;
}

bool Patient::fromDataObject(const DataObject& object)
{
    QString new_regID, new_fullname, new_yearText, new_address, new_workplace;

    if (object.getType() != "patient")
        return false;

    if (!object.getValue("regid", new_regID))
        return false;

    if (!object.getValue("fullname", new_fullname))
        return false;

    if (!object.getValue("year", new_yearText))
        return false;
    bool ok = false;
    unsigned new_yearOfBirth = new_yearText.toUInt(&ok);
    if (!ok)
        return false;

    if (!object.getValue("address", new_address))
        return false;

    if (!object.getValue("workplace", new_workplace))
        return false;

    if (!setRegID(new_regID))
        return false;
    if (!setFullName(new_fullname))
        return false;
    if (!setYearOfBirth(new_yearOfBirth))
        return false;
    if (!setAddress(new_address))
        return false;
    if (!setWorkPlace(new_workplace))
        return false;

    return true;
}
