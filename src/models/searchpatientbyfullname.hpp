#ifndef SEARCHPATIENTBYFULLNAME_HPP
#define SEARCHPATIENTBYFULLNAME_HPP

#include "../globaldatabase.hpp"
#include "data/dataprocessingclasses/twowaylist.hpp"

#include <QAbstractTableModel>

class SearchPatientByFullname : public QAbstractTableModel {
    Q_OBJECT
  private:
    TwoWayList<Patient> m_results;

  public:
    SearchPatientByFullname(TwoWayList<Patient>&& results, QObject* parent = nullptr);
    SearchPatientByFullname(const SearchPatientByFullname&) = delete;
    ~SearchPatientByFullname() override                     = default;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
};

#endif // SEARCHPATIENTBYFULLNAME_HPP
