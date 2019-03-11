#ifndef DOCTORBINTREE_HPP
#define DOCTORBINTREE_HPP

#include "data/bintree.hpp"
#include "data/doctor.hpp"
#include "data/twowaylist.hpp"
#include <QAbstractTableModel>

class Database;

class DoctorBinTree : public QAbstractTableModel {
    Q_OBJECT
private:
    BinTree<Doctor, QString> m_binTree;
    TwoWayList<Doctor> m_listToDisplay;

public:
    explicit DoctorBinTree(QObject* parent = nullptr);
    DoctorBinTree(const DoctorBinTree&) = delete;
    ~DoctorBinTree();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    Doctor getDoctor(const QModelIndex& index) const;

    friend class Database;

private:
    void updateList();

    bool addDoctor(const Doctor& other);
    void removeDoctor(const QString& key);
    bool getDoctor(const QString& key, Doctor* structToFill = nullptr);
};

#endif // DOCTORBINTREE_HPP
