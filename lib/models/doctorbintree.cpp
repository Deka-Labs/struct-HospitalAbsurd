#include "doctorbintree.hpp"

DoctorBinTree::DoctorBinTree(QObject* parent)
    : QAbstractTableModel(parent)
    , m_binTree()
{
}

DoctorBinTree::~DoctorBinTree()
{
}

QVariant DoctorBinTree::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical) {
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

QVariant DoctorBinTree::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return false;

    if (role == Qt::DisplayRole) {
        Doctor doc = m_listToDisplay.at(static_cast<unsigned>(index.row()));
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

int DoctorBinTree::rowCount(const QModelIndex& parent) const
{
    (void)parent;
    return static_cast<int>(m_listToDisplay.size());
}

int DoctorBinTree::columnCount(const QModelIndex& parent) const
{
    (void)parent;
    //ФИО, Должность, кабинет, расписание 4 - столбца
    return 4;
}

bool DoctorBinTree::addDoctor(const Doctor& other)
{
    if (m_binTree.add(other)) {
        updateList();
        return true;
    }

    return false;
}

void DoctorBinTree::removeDoctor(const QModelIndex& index)
{
    if (index.isValid()) {
        Doctor doc = m_listToDisplay.at(static_cast<unsigned>(index.row()));
        m_binTree.remove(doc.key());
        updateList();
    }
}

bool DoctorBinTree::containsDoctorWithKey(const QString& key)
{
    try {
        Doctor doc = m_binTree.find(key);
        return true;
    } catch (...) {
        return false;
    }
}

void DoctorBinTree::updateList()
{
    beginResetModel();

    m_listToDisplay = m_binTree.getListInOrder();
    m_listToDisplay.sort();

    endResetModel();
}
