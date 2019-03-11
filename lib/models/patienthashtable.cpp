#include "patienthashtable.hpp"
#include "../utils.hpp"
#include <string>

PatientHashTable::PatientHashTable(QObject* parent)
    : QAbstractTableModel(parent)
    , m_hashTable(MAX_PATIENTS)
{
}

PatientHashTable::~PatientHashTable()
{
}

QVariant PatientHashTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            switch (section) {
            case 0:
                return "Рег. номер";
            case 1:
                return "ФИО";
            case 2:
                return "Год рождения";
            case 3:
                return "Адрес";
            case 4:
                return "Место работы";
            default:
                return "ERROR";
            }
        }
    }
    return QVariant();
}

QVariant PatientHashTable::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        auto regid = m_registredKeys.at(static_cast<unsigned>(index.row()));
        Patient patient;
        if (!m_hashTable.get(regid, &patient))
            return QVariant();
        switch (index.column()) {
        case 0:
            return patient.regID();
        case 1:
            return patient.fullName();
        case 2:
            return patient.yearOfBirth();
        case 3:
            return patient.address();
        case 4:
            return patient.workPlace();
        default:
            return "ERROR";
        }
    }

    return QVariant();
}

int PatientHashTable::rowCount(const QModelIndex& parent) const
{
    (void)parent;
    return static_cast<int>(m_registredKeys.size());
}

int PatientHashTable::columnCount(const QModelIndex& parent) const
{
    (void)parent;
    //Номер, Имя, год рождения, адрес, место работы - 5 столбцов
    return 5;
}

Patient PatientHashTable::getPatient(const QModelIndex& index) const
{
    if (!index.isValid())
        throw std::runtime_error("Wrong index in PatientHashTable::getPatient");

    auto key = m_registredKeys.at(static_cast<unsigned>(index.row()));
    Patient out;
    if (m_hashTable.get(key, &out)) {
        return out;
    }
    throw std::runtime_error("PatientHashTable::getPatient - Looks like, the tableview is not updated");
}

bool PatientHashTable::addPatient(const Patient& patinet)
{
    beginResetModel();

    auto res = m_hashTable.add(patinet);
    if (res) {
        m_registredKeys.push_back(patinet.key());
    }

    endResetModel();
    return res;
}

bool PatientHashTable::getPatient(const PatientHashKey& key, Patient* structToAssign) const
{
    return m_hashTable.get(key, structToAssign);
}

void PatientHashTable::delPatient(const PatientHashKey& key)
{
    beginResetModel();

    m_hashTable.del(key);
    m_registredKeys.removeAll(key);

    endResetModel();
}

void PatientHashTable::delAll()
{
    while (m_registredKeys.size() != 0) {
        delPatient(m_registredKeys.at(0));
    }
}
