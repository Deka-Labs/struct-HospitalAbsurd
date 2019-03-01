#include "dataobject.hpp"

DataObject::DataObject(const QString& type)
    : m_type(type)
    , m_attributes()
{
}

DataObject::DataObject(const DataObject& other)
    : m_type(other.m_type)
    , m_attributes(other.m_attributes)
{
}

void DataObject::setType(const QString& type)
{
    m_type = type;
}
QString DataObject::getType() const
{
    return m_type;
}

void DataObject::setValue(const QString& name, const QString& value)
{
    unsigned pos = 0;
    if (containsAttribute(name, pos)) {
        m_attributes[pos].value = value;
    } else {
        info new_info;
        new_info.name = name;
        new_info.value = value;
        m_attributes.push_back(new_info);
    }
}

bool DataObject::getValue(const QString& name, QString& out_value) const
{
    unsigned pos = 0;
    if (containsAttribute(name, pos)) {
        out_value = static_cast<const QString&>(m_attributes.at(pos).value); //Не позволяем менять значения внутри this
        return true;
    }
    return false;
}

bool DataObject::containsAttribute(const QString& name, unsigned& out_pos) const
{
    for (unsigned pos = 0; pos < m_attributes.size(); pos++) {
        if (m_attributes.at(pos).name == name) {
            out_pos = pos;
            return true;
        }
    }
    return false;
}

void DataObject::delAttribute(const QString& name)
{
    unsigned pos = 0;
    if (containsAttribute(name, pos)) {
        m_attributes.remove(pos);
    }
}
