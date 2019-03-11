#ifndef PATIENTHASHTABLE_HPP
#define PATIENTHASHTABLE_HPP

#include "data/dataprocessingclasses/hashtable.hpp"
#include "data/dataprocessingclasses/twowaylist.hpp"
#include "data/hospital/patient.hpp"
#include <QAbstractTableModel>
#include <QFile>
#include <QString>

class Database;

class PatientHashTable : public QAbstractTableModel {
    Q_OBJECT

private:
    HashTable<Patient> m_hashTable;
    TwoWayList<PatientHashKey> m_registredKeys;

public:
    explicit PatientHashTable(QObject* parent = nullptr);
    PatientHashTable(const PatientHashTable& other) = delete;
    ~PatientHashTable();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    friend class Database;
};

#endif // PATIENTHASHTABLE_HPP
