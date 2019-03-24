#ifndef PATIENTHASHTABLE_HPP
#define PATIENTHASHTABLE_HPP

#include "data/dataprocessingclasses/hashtable.hpp"
#include "data/dataprocessingclasses/twowaylist.hpp"
#include "data/hospital/patient.hpp"

#include <QAbstractTableModel>
#include <QFile>
#include <QString>

class Database;

class PatientHashTable
    : public QAbstractTableModel
    , private HashTable<Patient> {
    Q_OBJECT

  private:
    TwoWayList<PatientHashKey> m_registredKeys;

    typedef HashTable<Patient> TypeTable;

  public:
    explicit PatientHashTable(QObject* parent = nullptr);
    PatientHashTable(const PatientHashTable& other) = delete;
    ~PatientHashTable() override                    = default;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    Patient             getPatient(const QModelIndex& index) const;
    TwoWayList<Patient> getAllPatients() const;
    bool                getPatient(const PatientHashKey& key, Patient* structToAssign = nullptr) const;

    friend class Database;

  private:
    StatusCodes addPatient(const Patient& patinet);

    void delPatient(const PatientHashKey& key);
    void delAll();
};

#endif // PATIENTHASHTABLE_HPP
