#include "referrallist.hpp"

ReferralList::ReferralList(QObject* parent)
    : QAbstractTableModel(parent) {
}

QVariant ReferralList::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal) {
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

QVariant ReferralList::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        Referral ref = TypeList::at(static_cast<unsigned>(index.row()));
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

int ReferralList::rowCount(const QModelIndex& parent) const {
    (void)parent;
    return static_cast<int>(TypeList::size());
}

int ReferralList::columnCount(const QModelIndex& parent) const {
    (void)parent;
    //Рег. номер, ФИО, дата, время - 4 столбца
    return 4;
}

Referral ReferralList::getReferral(const QModelIndex& index) const {
    if (!index.isValid())
        throw std::runtime_error("Wrong index in ReferralList::getReferral");

    return TypeList::at(static_cast<unsigned>(index.row()));
}

TwoWayList<Referral> ReferralList::getConnectedToPatient(const PatientHashKey& patRegID) {
    TwoWayList<Referral> listOut;
    for (unsigned pos = 0; pos < TypeList::size(); pos++) {
        auto ref = TypeList::at(pos);
        if (ref.regID() == patRegID.key()) {
            listOut.push_back(ref);
        }
    }

    return listOut;
}

TwoWayList<Referral> ReferralList::getConnectedToDoctor(const QString& docFullname) {
    TwoWayList<Referral> listOut;
    for (unsigned pos = 0; pos < TypeList::size(); pos++) {
        auto ref = TypeList::at(pos);
        if (ref.doctorFullname() == docFullname) {
            listOut.push_back(ref);
        }
    }

    return listOut;
}

bool ReferralList::addReferral(const Referral& newRef) {
    beginResetModel();
    TypeList::push_back(newRef);
    TypeList::sort();
    endResetModel();
    return true;
}

void ReferralList::removeReferral(const Referral& ref) {
    beginResetModel();
    //Так как == перегружен для сравнения по ключу обходим список вручную
    for (unsigned pos = 0; pos < TypeList::size(); pos++) {
        if (TypeList::at(pos).isEqual(ref)) {
            TypeList::remove(pos);
            pos--;
        }
    }
    endResetModel();
}

void ReferralList::removeAll() {
    while (TypeList::size() != 0) {
        removeReferral(TypeList::at(0));
    }
}
