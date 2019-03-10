#include "referrallist.hpp"

ReferralList::ReferralList(QObject* parent)
    : QAbstractTableModel(parent)
{
}

ReferralList::~ReferralList()
{
}

QVariant ReferralList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical) {
        if (role == Qt::DisplayRole) {
            switch (section) {
            case 0:
                return "Регестрационный номер";
            case 1:
                return "ФИО врача";
            case 2:
                return "Дата";
            case 3:
                return "Время";
            default:
                return "ERROR";
            }
        }
    }
    return QVariant();
}

QVariant ReferralList::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        Referral ref = m_list.at(static_cast<unsigned>(index.row()));
        switch (index.column()) {
        case 0:
            return ref.regID();
        case 1:
            return ref.doctorFullname();
        case 2:
            return ref.date();
        case 3:
            return ref.time();
        default:
            return "ERROR";
        }
    }

    return QVariant();
}

int ReferralList::rowCount(const QModelIndex& parent) const
{
    (void)parent;
    return static_cast<int>(m_list.size());
}

int ReferralList::columnCount(const QModelIndex& parent) const
{
    (void)parent;
    //Рег. номер, ФИО, дата, время - 4 столбца
    return 4;
}

bool ReferralList::addReferral(const Referral& newRef)
{
    beginResetModel();
    m_list.push_back(newRef);
    m_list.sort();
    endResetModel();
    return true;
}

void ReferralList::removeReferral(const Referral& ref)
{
    beginResetModel();
    m_list.removeAll(ref);
    endResetModel();
}
