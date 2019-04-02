#include "searchdoctorbypost.hpp"

SearchDoctorByPost::SearchDoctorByPost(TwoWayList<Doctor>&& results, QObject* parent)
    : QAbstractTableModel(parent)
    , m_results(results) {
}

QVariant SearchDoctorByPost::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            switch (section) {
                case 0:
                    return "Фамилия, инициалы";
                case 1:
                    return "Должность";
                case 2:
                    return "Кабинет";
                case 3:
                    return "Расписание";
                default:
                    return "ERROR";
            }
        }
    }
    return QVariant();
}

QVariant SearchDoctorByPost::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return false;

    if (role == Qt::DisplayRole) {
        Doctor doc = m_results.at(static_cast<unsigned>(index.row()));
        switch (index.column()) {
            case 0:
                return doc.fullname();
            case 1:
                return doc.post();
            case 2:
                return doc.cabinet();
            case 3:
                return doc.schedule();
            default:
                return "ERROR";
        }
    }

    return QVariant();
}

int SearchDoctorByPost::rowCount(const QModelIndex& parent) const {
    (void)parent;
    return static_cast<int>(m_results.size());
}

int SearchDoctorByPost::columnCount(const QModelIndex& parent) const {
    (void)parent;
    //ФИО, Должность, кабинет, расписание 4 - столбца
    return 4;
}
