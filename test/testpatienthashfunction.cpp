#include "data/dataprocessingclasses/twowaylist.hpp"
#include "data/hospital/patienthashkey.hpp"

#include <QFile>
#include <gtest/gtest.h>

TEST(PatientHashKey, TestWithOut) {
    const unsigned             count = 1000;
    TwoWayList<PatientHashKey> m_keys;
    unsigned                   m_firstHashes[MAX_PATIENTS]               = {0};
    unsigned                   m_secondHashes[MAX_PATIENT_HASH_STEP + 1] = {0};

    for (unsigned i = 0; i < count; i++) {
        QString str;
        do {
            QString first  = QString("%1").arg(rand() % 100);
            QString second = QString("%1").arg(rand() % 1000000);
            str            = QString("%1-%2").arg(first, 2, '0').arg(second, 6, '0');
        } while (m_keys.search(PatientHashKey(str)));

        m_keys.push_back(PatientHashKey(str));
        auto h1 = PatientHashKey(str).hash();
        auto h2 = PatientHashKey(str).dopHash();

        m_firstHashes[h1]++;
        m_secondHashes[h2]++;
    }

    QFile first, second;

    first.setFileName("testHashFun1.txt");
    second.setFileName("testHashFun2.txt");

    EXPECT_TRUE(first.open(QIODevice::WriteOnly | QIODevice::Truncate));
    EXPECT_TRUE(second.open(QIODevice::WriteOnly | QIODevice::Truncate));

    if (first.isWritable()) {
        for (unsigned int m_firstHashe : m_firstHashes) {
            first.write(QString("%1, ").arg(m_firstHashe).toUtf8());
        }
    }

    if (second.isWritable()) {
        for (unsigned i = 0; i < MAX_PATIENT_HASH_STEP; i++) {
            second.write(QString("%1, ").arg(m_secondHashes[i]).toUtf8());
        }
    }
}

TEST(PatientHashKey, OutOfRange) {
    srand(unsigned(time(nullptr)));
    const unsigned count = 100000;

    auto generateRegID = []() -> QString {
        return QString("%1-%2")
            .arg(rand() % 100, 2, 10, QLatin1Char('0'))
            .arg(rand() % 1000000, 6, 10, QLatin1Char('0'));
    };

    for (unsigned i = 0; i < count; i++) {
        PatientHashKey key(generateRegID());
        ASSERT_LT(key.hash(), unsigned(MAX_PATIENTS));
        ASSERT_LE(key.dopHash(), unsigned(MAX_PATIENT_HASH_STEP));
    }
}
