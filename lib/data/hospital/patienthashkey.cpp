#include "patienthashkey.hpp"

#include "utils.hpp"

#include <utility>

QString PatientHashKey::key() const {
    return m_key;
}

PatientHashKey::PatientHashKey(QString key)
    : m_key(std::move(key)) {
}

unsigned PatientHashKey::hash() const {
    if (!validateKey())
        throw std::runtime_error("Invalid key");

    std::string str = m_key.toStdString();

    str = str.substr(3, 6);

    unsigned hash = std::stoul(str);
    hash %= MAX_PATIENTS;

    return hash;
}

unsigned PatientHashKey::dopHash() const {
    std::string str = m_key.toStdString();

    unsigned hash = 0;
    hash += unsigned(str[0] - '0');
    hash += unsigned(str[1] - '0') * 10U;
    hash %= MAX_PATIENT_HASH_STEP;
    hash += 1;

    return hash;
}

bool PatientHashKey::validateKey() const {
    return TemplateValidate(PATIENT_REGID_TEMPLATE, m_key);
}

bool PatientHashKey::operator==(const IHashKey& key) const {
    const auto& other = dynamic_cast<const PatientHashKey&>(key);
    return m_key == other.m_key;
}
