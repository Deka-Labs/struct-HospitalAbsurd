#include "searchpatientbyregid.hpp"

SearchPatientByRegID::SearchPatientByRegID(const Patient& pat, QObject* parent)
    : QAbstractTableModel(parent)
    , m_dataToDisplay()
{
    m_dataToDisplay.patient = pat;
    auto list = g_DATABASE->getReferralsModel().getConnectedToPatient(pat.key());
    m_dataToDisplay.referralsDoctorsFullname = "";
    for (unsigned pos = 0; pos < list.size(); pos++) {
        m_dataToDisplay.referralsDoctorsFullname += list.at(pos).doctorFullname() + "\n";
    }
}

SearchPatientByRegID::~SearchPatientByRegID()
= default;

QVariant SearchPatientByRegID::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Vertical) {
            switch (section) {
            case 0:
                return "Рег. номер";
            case 1:
                return "ФИО";
            case 2:
                return "Год рожд.";
            case 3:
                return "Адрес";
            case 4:
                return "Место работы";
            case 5:
                return "Направления к";
            default:
                return "ERROR";
            }
        }
    }

    return QVariant();
}

QVariant SearchPatientByRegID::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.row()) {
        case 0:
            return m_dataToDisplay.patient.regID();
        case 1:
            return m_dataToDisplay.patient.fullName();
        case 2:
            return m_dataToDisplay.patient.yearOfBirth();
        case 3:
            return m_dataToDisplay.patient.address();
        case 4:
            return m_dataToDisplay.patient.workPlace();
        case 5:
            return m_dataToDisplay.referralsDoctorsFullname;
        default:
            return "ERROR";
        }
    }
    return QVariant();
}

int SearchPatientByRegID::rowCount(const QModelIndex& parent) const
{
    (void)parent;
    return 6;
}

int SearchPatientByRegID::columnCount(const QModelIndex& parent) const
{
    (void)parent;
    return 1;
}
