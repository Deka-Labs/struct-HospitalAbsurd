#include "patienthashtable.hpp"
#include "../utils.hpp"
#include <string>

PatientHashTable::PatientHashTable(QObject* parent)
    : QAbstractTableModel(parent)
    , m_hashTable()
{
    for (int i = 0; i < MAX_PATIENTS; i++) {
        m_hashTable[i] = nullptr;
    }
}

PatientHashTable::~PatientHashTable()
{
    while (m_registredKeys.size() != 0) {
        delPatient(m_registredKeys[0]);
    }
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
        QString regid = m_registredKeys.at(static_cast<unsigned>(index.row()));
        Patient patient;
        if (!getPatient(regid, patient))
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

bool PatientHashTable::addPatient(const Patient& newPatient)
{
    if (m_registredKeys.search(newPatient.regID()))
        return false;

    int cell = getEmptyCellFor(newPatient.regID());

    if (cell != -1) {
        Patient* copy = new Patient(newPatient);
        m_hashTable[cell] = copy;
        m_registredKeys.push_back(copy->regID());
        return true;
    }
    return false;
}

bool PatientHashTable::getPatient(const QString& regid, Patient& structToFill) const
{
    int cell = getPatientCell(regid);
    if (cell != -1) {

        auto patinet = m_hashTable[cell];

        structToFill.setRegID(patinet->regID());
        structToFill.setFullName(patinet->fullName());
        structToFill.setYearOfBirth(patinet->yearOfBirth());
        structToFill.setAddress(patinet->address());
        structToFill.setWorkPlace(patinet->workPlace());

        return true;
    }
    return false;
}

void PatientHashTable::delPatient(const QString& regid)
{
    int cell = getPatientCell(regid);
    if (cell != -1) {
        delete m_hashTable[cell];
        m_hashTable[cell] = nullptr;
        m_registredKeys.removeAll(regid);
    }
}

void PatientHashTable::testHashFunctions(QFile& first, QFile& second)
{
    const unsigned count = 1000;
    TwoWayList<QString> m_keys;
    unsigned m_firstHashes[MAX_PATIENTS] = { 0 };
    unsigned m_secondHashes[MAX_PATIENT_HASH_STEP + 1] = { 0 };

    for (unsigned i = 0; i < count; i++) {
        QString str;
        do {
            QString first = QString("%1").arg(rand() % 100);
            QString second = QString("%1").arg(rand() % 1000000);
            str = QString("%1-%2").arg(first, 2, '0').arg(second, 6, '0');
        } while (m_keys.search(str));

        m_keys.push_back(str);
        auto h1 = hash(str);
        auto h2 = dopHash(str);

        m_firstHashes[h1]++;
        m_secondHashes[h2]++;
    }

    if (first.isWritable()) {
        for (unsigned i = 0; i < MAX_PATIENTS; i++) {
            first.write(QString("%1, ").arg(m_firstHashes[i]).toUtf8());
        }
    }

    if (second.isWritable()) {
        for (unsigned i = 0; i < MAX_PATIENT_HASH_STEP; i++) {
            second.write(QString("%1, ").arg(m_secondHashes[i]).toUtf8());
        }
    }
}

int PatientHashTable::hash(const QString& regid)
{
    if (!validateKey(regid))
        return -1;

    std::string str = regid.toStdString();

    str = str.substr(3, 6);

    int hash = std::stoi(str);
    hash %= MAX_PATIENTS;

    return hash;
}

int PatientHashTable::dopHash(const QString& regid)
{
    if (!validateKey(regid))
        return -1;
    std::string str = regid.toStdString();

    int hash = 0;
    hash += (str[0] - '0');
    hash += (str[1] - '0') * 10;
    hash %= MAX_PATIENT_HASH_STEP;
    hash += 1;

    return hash;
}

bool PatientHashTable::validateKey(const QString& regid)
{
    if (regid.size() > MAX_PATIENT_REGID_STRING_SIZE)
        return false;

    if (!TemplateValidate(PATIENT_REGID_TEMPLATE, regid))
        return false;
    return true;
}

int PatientHashTable::getEmptyCellFor(const QString& regid) const
{
    if (!validateKey(regid))
        return -1;

    int first = hash(regid);
    int delta = dopHash(regid);

    if (first == -1 || delta == -1)
        return -1;

    int i = 0;
    for (i = first; i < MAX_PATIENTS; i += delta) {
        if (!m_hashTable[i]) {
            return i;
        }
    }

    i %= MAX_PATIENTS;
    for (; i < first; i += delta) {
        if (!m_hashTable[i]) {
            return i;
        }
    }
    return -1;
}

int PatientHashTable::getPatientCell(const QString& regid) const
{
    if (!validateKey(regid))
        return -1;

    int first = hash(regid);
    int delta = dopHash(regid);

    if (first == -1 || delta == -1)
        return -1;

    int i = 0;
    for (i = first; i < MAX_PATIENTS; i += delta) {
        if (m_hashTable[i] && QStringSearch(regid, m_hashTable[i]->regID())) {
            return i;
        }
    }

    i %= MAX_PATIENTS;
    for (; i < first; i += delta) {
        if (m_hashTable[i] && QStringSearch(regid, m_hashTable[i]->regID())) {
            return i;
        }
    }

    return -1;
}
