#include "patienthashtable.hpp"
#include "../utils.hpp"

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
        }
    }

    return "ERROR";
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

    Patient* copy = new Patient(newPatient);

    int cell = getEmptyCellFor(copy->regID());

    if (cell != -1) {
        m_hashTable[cell] = copy;
        m_registredKeys.push_back(copy->regID());
    } else {
        return false;
    }
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
        m_hashTable[cell] = nullptr;
        m_registredKeys.removeAll(regid);
    }
}

int PatientHashTable::hash(const QString& regid) const
{
    if (!validateKey(regid))
        return -1;
    std::string str = regid.toStdString();
    int hash = 0;
    //From XX-[there]XXXXXX
    for (int i = 3; i < MAX_PATIENT_REGID_STRING_SIZE; i++) {
        hash += (str[i] - '0') * i;
    }

    static const int max = 297;

    hash *= hash;
    hash *= MAX_PATIENTS / max;
    return hash;
}

int PatientHashTable::dopHash(const QString& regid) const
{
    if (!validateKey(regid))
        return -1;
    std::string str = regid.toStdString();

    int hash = 0;
    hash += (str[0] - '0');
    hash += (str[1] - '0') * 10;
    hash %= 5;

    return hash;
}

bool PatientHashTable::validateKey(const QString& regid) const
{
    if (regid.size() > MAX_PATIENT_REGID_STRING_SIZE)
        return false;

    QString templ = PATIENT_REGID_TEMPLATE;
    if (templ.size() != regid.size())
        return false;
    for (int i = 0; i < templ.size(); i++) {
        QChar current = regid[i];
        if (templ[i] == 'd') {
            if (!isdigit(current.toLatin1()))
                return false;
        } else {
            if (current != templ[i])
                return false;
        }
    }
    return true;
}

int PatientHashTable::getEmptyCellFor(const QString& regid) const
{
    if (!validateKey(regid))
        return -1;

    int first = hash(regid);
    int delta = dopHash(regid);

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
