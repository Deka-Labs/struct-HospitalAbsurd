#include "doctorbintree.hpp"

DoctorBinTree::DoctorBinTree(QObject* parent)
    : QAbstractTableModel(parent)
    , TypeTree() {
}

QVariant DoctorBinTree::headerData(int section, Qt::Orientation orientation, int role) const {
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

QVariant DoctorBinTree::data(const QModelIndex& index, int role) const {
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

int DoctorBinTree::rowCount(const QModelIndex& parent) const {
    (void)parent;
    return static_cast<int>(m_listToDisplay.size());
}

int DoctorBinTree::columnCount(const QModelIndex& parent) const {
    (void)parent;
    //ФИО, Должность, кабинет, расписание 4 - столбца
    return 4;
}

Doctor DoctorBinTree::getDoctor(const QModelIndex& index) const {
    if (!index.isValid())
        throw std::runtime_error("Wrong index in DoctorBinTree::getDoctor");

    auto   key = m_listToDisplay.at(static_cast<unsigned>(index.row())).key();
    Doctor out = TypeTree::find(key);
    return out;
}

TwoWayList<Doctor> DoctorBinTree::getAllDoctors() const {
    return m_listToDisplay;
}

bool DoctorBinTree::getDoctor(const QString& key, Doctor* structToFill) const {
    try {
        Doctor doc = TypeTree::find(key);
        if (structToFill)
            *structToFill = doc;
        return true;
    } catch (...) {
        return false;
    }
}

void DoctorBinTree::updateList() {
    beginResetModel();

    m_listToDisplay = TypeTree::getListInOrder();

    endResetModel();
}

StatusCodes DoctorBinTree::add(const Doctor& other) {
    auto result = TypeTree::add(other);
    if (result == StatusCode_OK) {
        updateList();
    }

    return result;
}

void DoctorBinTree::remove(const QString& key) {
    TypeTree::remove(key);
    updateList();
}

void DoctorBinTree::removeAll() {
    while (!TypeTree::isEmpty()) {
        remove(m_listToDisplay[0].key());
    }
}
