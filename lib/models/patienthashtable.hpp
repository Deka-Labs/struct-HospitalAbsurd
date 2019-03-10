#ifndef PATIENTHASHTABLE_HPP
#define PATIENTHASHTABLE_HPP

#include "data/patient.hpp"
#include "data/twowaylist.hpp"
#include <QAbstractTableModel>
#include <QFile>
#include <QString>

#define MAX_PATIENTS 100
#define MAX_PATIENT_HASH_STEP 5

class Database;

class PatientHashTable : public QAbstractTableModel {
    Q_OBJECT
    Patient* m_hashTable[MAX_PATIENTS];
    TwoWayList<QString> m_registredKeys;

public:
    explicit PatientHashTable(QObject* parent = nullptr);
    PatientHashTable(const PatientHashTable& other) = delete;
    ~PatientHashTable();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    bool addPatient(const Patient& newPatient);
    bool getPatient(const QString& regid, Patient* structToFill = nullptr) const;

    void delPatient(const QString& regid);

    static void testHashFunctions(QFile& first, QFile& second);

    friend class Database;

private:
    static int hash(const QString& regid);
    static int dopHash(const QString& regid);

    static bool validateKey(const QString& regid);

    int getEmptyCellFor(const QString& regid) const;
    int getPatientCell(const QString& regid) const;
};

#endif // PATIENTHASHTABLE_HPP
