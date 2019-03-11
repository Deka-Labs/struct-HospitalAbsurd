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
    if (orientation == Qt::Vertical) {
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
