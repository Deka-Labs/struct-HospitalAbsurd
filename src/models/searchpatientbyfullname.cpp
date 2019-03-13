#include "searchpatientbyfullname.hpp"

SearchPatientByFullname::SearchPatientByFullname(TwoWayList<Patient>&& results, QObject* parent)
    : QAbstractTableModel(parent)
    , m_results(results)
{
}

SearchPatientByFullname::~SearchPatientByFullname()
{
}

QVariant SearchPatientByFullname::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "Рег. номер";
            case 1:
                return "ФИО";
            default:
                return "ERROR";
            }
        }
    }
    return QVariant();
}

QVariant SearchPatientByFullname::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        auto pat = m_results.at(static_cast<unsigned>(index.row()));
        switch (index.column()) {
        case 0:
            return pat.regID();
        case 1:
            return pat.fullName();
        default:
            return "ERROR";
        }
    }
    return QVariant();
}

int SearchPatientByFullname::rowCount(const QModelIndex& parent) const
{
    (void)parent;
    return static_cast<int>(m_results.size());
}

int SearchPatientByFullname::columnCount(const QModelIndex& parent) const
{
    (void)parent;
    return 2;
}
