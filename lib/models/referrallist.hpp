#ifndef REFERRALLIST_HPP
#define REFERRALLIST_HPP

#include "data/dataprocessingclasses/twowaylist.hpp"
#include "data/hospital/referral.hpp"
#include "doctorbintree.hpp"
#include "patienthashtable.hpp"

#include <QAbstractTableModel>

class Database;

class ReferralList
    : public QAbstractTableModel
    , private TwoWayList<Referral> {
    Q_OBJECT
  private:
    typedef TwoWayList<Referral> TypeList;

  public:
    explicit ReferralList(QObject* parent = nullptr);
    ReferralList(const ReferralList&) = delete;
    ~ReferralList() override          = default;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    friend class Database;

    Referral getReferral(const QModelIndex& index) const;

    TwoWayList<Referral> getConnectedToPatient(const PatientHashKey& patRegID);
    TwoWayList<Referral> getConnectedToDoctor(const QString& docFullname);

  private:
    bool addReferral(const Referral& newRef);
    void removeReferral(const Referral& ref);
    void removeAll();
};

#endif // REFERRALLIST_HPP
