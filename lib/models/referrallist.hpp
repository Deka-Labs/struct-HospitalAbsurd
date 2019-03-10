#ifndef REFERRALLIST_HPP
#define REFERRALLIST_HPP

#include "data/referral.hpp"
#include "data/twowaylist.hpp"
#include "doctorbintree.hpp"
#include "patienthashtable.hpp"
#include <QAbstractTableModel>

class Database;

class ReferralList : QAbstractTableModel {
    Q_OBJECT
private:
    TwoWayList<Referral> m_list;

public:
    ReferralList(QObject* parent = nullptr);
    ReferralList(const ReferralList&) = delete;
    ~ReferralList();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    bool addReferral(const Referral& newRef);
    void removeReferral(const Referral& ref);

    friend class Database;
};

#endif // REFERRALLIST_HPP
