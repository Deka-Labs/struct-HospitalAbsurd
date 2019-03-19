#ifndef SEARCHPATIENTBYREGID_HPP
#define SEARCHPATIENTBYREGID_HPP

#include "../globaldatabase.hpp"

#include <QAbstractTableModel>

class SearchPatientByRegID : public QAbstractTableModel {
    Q_OBJECT
  private:
    struct {
        Patient patient;
        QString referralsDoctorsFullname;
    } m_dataToDisplay;

  public:
    SearchPatientByRegID(const Patient& pat, QObject* parent = nullptr);
    SearchPatientByRegID(const SearchPatientByRegID&) = delete;
    ~SearchPatientByRegID();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
};

#endif // SEARCHPATIENTBYREGID_HPP
