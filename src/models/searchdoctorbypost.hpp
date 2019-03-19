#ifndef SEARCHDOCTORBYPOST_HPP
#define SEARCHDOCTORBYPOST_HPP

#include "../globaldatabase.hpp"
#include "data/dataprocessingclasses/twowaylist.hpp"

#include <QAbstractTableModel>

class SearchDoctorByPost : public QAbstractTableModel {
    Q_OBJECT
  private:
    TwoWayList<Doctor> m_results;

  public:
    SearchDoctorByPost(TwoWayList<Doctor>&& results, QObject* parent = nullptr);
    SearchDoctorByPost(const SearchDoctorByPost&) = delete;
    ~SearchDoctorByPost();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
};

#endif // SEARCHDOCTORBYPOST_HPP
