#include "models/patienthashtable.hpp"
#include <QFile>
#include <gtest/gtest.h>
#include <iomanip>
#include <sstream>

TEST(PatientHashTable, Adding)
{
    srand(time(nullptr));
    PatientHashTable hashTable;
    Patient pat = Patient();
    pat.setRegID("12-345678");
    pat.setFullName("Иванов И.И.");
    pat.setYearOfBirth(2005);
    pat.setAddress("г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7");
    pat.setWorkPlace("ПАО Черный банк");

    ASSERT_TRUE(hashTable.addPatient(pat));

    pat.setAddress("Другой");
    pat.setWorkPlace("ИТМО ФСПО!");

    ASSERT_FALSE(hashTable.addPatient(pat));

    hashTable.delPatient(pat.regID());

    //Filling to half
    const int count = MAX_PATIENTS / 2;

    ASSERT_LT(count, MAX_PATIENTS);

    for (int i = 0; i < count; i++) {
        while (!hashTable.addPatient(pat)) {
            std::stringstream SS;
            SS << std::setw(2) << std::setfill('0') << rand() % 100;
            SS << "-";
            SS << std::setw(6) << std::setfill('0') << rand() % 1000000;
            std::string str = SS.str();
            pat.setRegID(str.c_str());
        }
    }

    ASSERT_EQ(hashTable.rowCount(), count);
}

TEST(PatientHashTable, Getting)
{
    PatientHashTable hashTable;
    Patient pat = Patient();
    pat.setRegID("12-345678");
    pat.setFullName("Иванов И.И.");
    pat.setYearOfBirth(2005);
    pat.setAddress("г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7");
    pat.setWorkPlace("ПАО Черный банк");

    //Filling to half
    const int count = MAX_PATIENTS / 2;
    int cannotInsertes = 0;

    ASSERT_LT(count, MAX_PATIENTS);

    for (int i = 0; i < count; i++) {
        std::stringstream SS;
        SS << std::setw(2) << std::setfill('0') << i;
        SS << "-";
        SS << std::setw(6) << std::setfill('0') << i + 10 * i + 100 * i;
        std::string str = SS.str();
        pat.setRegID(str.c_str());
        if (!hashTable.addPatient(pat))
            cannotInsertes++;
    }

    ASSERT_EQ(hashTable.rowCount(), count - cannotInsertes);

    int getted = 0;

    for (int i = 0; i < count; i++) {
        std::stringstream SS;
        SS << std::setw(2) << std::setfill('0') << i;
        SS << "-";
        SS << std::setw(6) << std::setfill('0') << i + 10 * i + 100 * i;
        std::string str = SS.str();

        if (hashTable.getPatient(str.c_str(), pat)) {
            getted++;
        }
    }

    ASSERT_EQ(getted, hashTable.rowCount());
    ASSERT_EQ(getted, count - cannotInsertes);
}

TEST(PatientHashTable, Deleting)
{
    PatientHashTable hashTable;
    Patient pat = Patient();
    pat.setRegID("12-345678");
    pat.setFullName("Иванов И.И.");
    pat.setYearOfBirth(2005);
    pat.setAddress("г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7");
    pat.setWorkPlace("ПАО Черный банк");

    //Filling to half
    const int count = MAX_PATIENTS / 2;
    int cannotInsertes = 0;

    ASSERT_LT(count, MAX_PATIENTS);

    for (int i = 0; i < count; i++) {
        std::stringstream SS;
        SS << std::setw(2) << std::setfill('0') << i;
        SS << "-";
        SS << std::setw(6) << std::setfill('0') << i + 10 * i + 100 * i;
        std::string str = SS.str();
        pat.setRegID(str.c_str());
        if (!hashTable.addPatient(pat))
            cannotInsertes++;
    }

    ASSERT_EQ(hashTable.rowCount(), count - cannotInsertes);

    for (int i = 0; i < count; i++) {
        std::stringstream SS;
        SS << std::setw(2) << std::setfill('0') << i;
        SS << "-";
        SS << std::setw(6) << std::setfill('0') << i + 10 * i + 100 * i;
        std::string str = SS.str();

        hashTable.delPatient(str.c_str());
    }

    ASSERT_EQ(hashTable.rowCount(), 0);
}

TEST(PatientHashTable, HashFunction)
{
    QFile first;
    QFile second;

    first.setFileName("testHashFun1.txt");
    second.setFileName("testHashFun2.txt");

    ASSERT_TRUE(first.open(QIODevice::WriteOnly | QIODevice::Truncate));
    ASSERT_TRUE(second.open(QIODevice::WriteOnly | QIODevice::Truncate));

    ASSERT_NO_THROW(PatientHashTable::testHashFunctions(first, second));
}
