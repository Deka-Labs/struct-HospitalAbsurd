#ifndef PATIENTHASHTABLE_HPP
#define PATIENTHASHTABLE_HPP

#include "patient.hpp"
#include "twowaylist.hpp"
#include <QAbstractTableModel>
#include <QString>

#define MAX_PATIENTS 100

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
    bool getPatient(const QString& regid, Patient& structToFill) const;

    void delPatient(const QString& regid);

private:
    int hash(const QString& regid) const;
    int dopHash(const QString& regid) const;

    bool validateKey(const QString& regid) const;

    int getEmptyCellFor(const QString& regid) const;
    int getPatientCell(const QString& regid) const;
};

#endif // PATIENTHASHTABLE_HPP
