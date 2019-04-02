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
    ~SearchDoctorByFullname() override                    = default;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
};

#endif // SEARCHDOCTORBYFULLNAME_HPP
