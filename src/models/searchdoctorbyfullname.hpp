#ifndef SEARCHDOCTORBYFULLNAME_HPP
#define SEARCHDOCTORBYFULLNAME_HPP

#include "../globaldatabase.hpp"

#include <QAbstractTableModel>

class SearchDoctorByFullname : public QAbstractTableModel {
    Q_OBJECT
  private:
    struct {
        Doctor  doctor;
        QString referralsDoctorsFullname;
    } m_dataToDisplay;

  public:
    SearchDoctorByFullname(const Doctor& doc, QObject* parent = nullptr);
    SearchDoctorByFullname(const SearchDoctorByFullname&) = delete;
    ~SearchDoctorByFullname();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
};

#endif // SEARCHDOCTORBYFULLNAME_HPP
