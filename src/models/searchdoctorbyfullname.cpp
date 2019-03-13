#include "searchdoctorbyfullname.hpp"

SearchDoctorByFullname::SearchDoctorByFullname(const Doctor& doc, QObject* parent)
    : QAbstractTableModel(parent)
    , m_dataToDisplay()
{
    m_dataToDisplay.doctor = doc;
    auto list = g_DATABASE->getReferralsModel().getConnectedToDoctor(doc.key());
    m_dataToDisplay.referralsDoctorsFullname = "";
    for (unsigned pos = 0; pos < list.size(); pos++) {
        m_dataToDisplay.referralsDoctorsFullname += list.at(pos).regID() + "\n";
    }
}

SearchDoctorByFullname::~SearchDoctorByFullname()
{
}

QVariant SearchDoctorByFullname::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Vertical) {
            switch (section) {
            case 0:
                return "ФИО";
            case 1:
                return "Должность";
            case 2:
                return "Кабинет";
            case 3:
                return "Расписание";
            case 4:
                return "Направления к";
            default:
                return "ERROR";
            }
        }
    }

    return QVariant();
}

QVariant SearchDoctorByFullname::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.row()) {
        case 0:
            return m_dataToDisplay.doctor.fullname();
        case 1:
            return m_dataToDisplay.doctor.post();
        case 2:
            return m_dataToDisplay.doctor.cabinet();
        case 3:
            return m_dataToDisplay.doctor.schedule();
        case 4:
            return m_dataToDisplay.referralsDoctorsFullname;
        default:
            return "ERROR";
        }
    }
    return QVariant();
}

int SearchDoctorByFullname::rowCount(const QModelIndex& parent) const
{
    (void)parent;
    return 5;
}

int SearchDoctorByFullname::columnCount(const QModelIndex& parent) const
{
    (void)parent;
    return 1;
}
