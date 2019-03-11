#include "database.hpp"
#include <gtest/gtest.h>

TEST(Database, Loading)
{
    srand(static_cast<unsigned>(time(nullptr)));

    auto generateRegID = []() -> QString {
        return QString("%1-%2")
            .arg(rand() % 100, 2, 10, QLatin1Char('0'))
            .arg(rand() % 1000000, 6, 10, QLatin1Char('0'));
    };

    auto generateDate = []() -> QString {
        return QString("%1.%2.%3")
            .arg(rand() % 28 + 1, 2, 10, QLatin1Char('0'))
            .arg(rand() % 12 + 1, 2, 10, QLatin1Char('0'))
            .arg(rand() % MAX_PATIENT_YEAR, 4, 10, QLatin1Char('0'));
    };
    auto generateTime = []() -> QString {
        return QString("%1:%2")
            .arg(rand() % 24, 2, 10, QLatin1Char('0'))
            .arg(rand() % 60, 2, 10, QLatin1Char('0'));
    };

    auto generatePatinet = [=]() -> Patient {
        Patient pat;
        EXPECT_TRUE(pat.setRegID(generateRegID()));
        EXPECT_TRUE(pat.setAddress(QString("%1").arg(rand())));
        EXPECT_TRUE(pat.setFullName(QString("%1").arg(rand())));
        EXPECT_TRUE(pat.setWorkPlace(QString("%1").arg(rand())));
        EXPECT_TRUE(pat.setYearOfBirth(rand() % MAX_PATIENT_YEAR));
        return pat;
    };

    auto generateDoctor = [=]() -> Doctor {
        Doctor doc;
        EXPECT_TRUE(doc.setFullname(QString("%1").arg(rand())));
        EXPECT_TRUE(doc.setPost(QString("%1").arg(rand())));
        EXPECT_TRUE(doc.setCabinet(rand() % MAX_DOCTOR_CABINET));
        EXPECT_TRUE(doc.setSchedule(QString("%1").arg(rand())));
        return doc;
    };

    auto generateRef = [=]() -> Referral {
        Referral ref;
        EXPECT_TRUE(ref.setRegID(generateRegID()));
        EXPECT_TRUE(ref.setDoctorFullname(QString("%1").arg(rand())));
        EXPECT_TRUE(ref.setDate(generateDate()));
        EXPECT_TRUE(ref.setTime(generateTime()));
        return ref;
    };

    const unsigned count = 250;
    const char* filename = "testDB.txt";

    DataFile df;
    df.open(filename, false);

    TwoWayList<QString> m_doctorsKeyList;
    TwoWayList<PatientHashKey> m_patsKeysList;

    for (unsigned i = 0; i < MAX_PATIENTS / 2; i++) {
        auto pat = generatePatinet();
        while (m_patsKeysList.search(pat.key())) {
            pat = generatePatinet();
        }

        df.insertObject(pat.toDataObject());
        m_patsKeysList.push_back(pat.key());
    }

    for (unsigned i = 0; i < count; i++) {
        auto pat = generateDoctor();
        while (m_doctorsKeyList.search(pat.key())) {
            pat = generateDoctor();
        }

        df.insertObject(pat.toDataObject());
        m_doctorsKeyList.push_back(pat.key());
    }

    for (unsigned i = 0; i < count; i++) {
        auto pat = generateRef();
        df.insertObject(pat.toDataObject());
    }

    df.close();

    Database newDB;
    ASSERT_TRUE(newDB.loadData("testDB.txt"));
}
