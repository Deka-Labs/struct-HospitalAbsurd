#ifndef DOCTORBINTREE_HPP
#define DOCTORBINTREE_HPP

#include "data/dataprocessingclasses/bintree.hpp"
#include "data/dataprocessingclasses/twowaylist.hpp"
#include "data/hospital/doctor.hpp"

#include <QAbstractTableModel>

class Database;

class DoctorBinTree
    : public QAbstractTableModel
    , private BinTree<Doctor, QString> {
    Q_OBJECT
  private:
    TwoWayList<Doctor> m_listToDisplay;

    typedef BinTree<Doctor, QString> TypeTree;

  public:
    explicit DoctorBinTree(QObject* parent = nullptr);
    DoctorBinTree(const DoctorBinTree&) = delete;
    ~DoctorBinTree() override           = default;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    Doctor             getDoctor(const QModelIndex& index) const;
    TwoWayList<Doctor> getAllDoctors() const;
    TwoWayList<Doctor> getAllDoctorsWithPost(const QString& post) const;
    bool               getDoctor(const QString& key, Doctor* structToFill = nullptr) const;

    friend class Database;

  private:
    void updateList();

    StatusCodes add(const Doctor& other) override;
    void        remove(const QString& key) override;
    void        removeAll();
};

#endif // DOCTORBINTREE_HPP
