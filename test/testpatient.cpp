#include "data/patient.hpp"
#include <gtest/gtest.h>

TEST(Patient, Setters)
{
    Patient pat;
    ASSERT_NO_THROW(pat.setRegID("12-345678"));
    ASSERT_NO_THROW(pat.setFullName("Иванов И.И."));
    ASSERT_NO_THROW(pat.setYearOfBirth(2005));
    ASSERT_NO_THROW(pat.setAddress("г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7"));
    ASSERT_NO_THROW(pat.setWorkPlace("ПАО Черный банк"));

    ASSERT_EQ(pat.regID(), "12-345678");
    ASSERT_EQ(pat.fullName(), "Иванов И.И.");
    ASSERT_EQ(pat.yearOfBirth(), 2005);
    ASSERT_EQ(pat.address(), "г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7");
    ASSERT_EQ(pat.workPlace(), "ПАО Черный банк");

    QString str;

    //REGID

    str.resize(MAX_PATIENT_REGID_STRING_SIZE + 1);
    str.fill('0');

    ASSERT_FALSE(pat.setRegID(str));
    ASSERT_EQ(pat.regID(), "12-345678");

    ASSERT_FALSE(pat.setRegID("Wrong"));
    ASSERT_EQ(pat.regID(), "12-345678");

    //FullName

    str.resize(MAX_PATIENT_FULLNAME_STRING_SIZE + 1);
    str.fill('0');
    ASSERT_FALSE(pat.setFullName(str));
    ASSERT_EQ(pat.fullName(), "Иванов И.И.");

    //Year

    ASSERT_FALSE(pat.setYearOfBirth(MAX_PATIENT_YEAR + 1));
    ASSERT_EQ(pat.yearOfBirth(), 2005);

    //Address

    str.resize(MAX_PATIENT_ADDRESS_STRING_SIZE + 1);
    str.fill('0');
    ASSERT_FALSE(pat.setAddress(str));
    ASSERT_EQ(pat.address(), "г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7");

    //WorkPlace

    str.resize(MAX_PATIENT_WORKPLACE_STRING_SIZE + 1);
    str.fill('0');
    ASSERT_FALSE(pat.setWorkPlace(str));
    ASSERT_EQ(pat.workPlace(), "ПАО Черный банк");
}

TEST(Patient, toDataObject)
{
    Patient pat;
    ASSERT_NO_THROW(pat.setRegID("12-345678"));
    ASSERT_NO_THROW(pat.setFullName("Иванов И.И."));
    ASSERT_NO_THROW(pat.setYearOfBirth(2005));
    ASSERT_NO_THROW(pat.setAddress("г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7"));
    ASSERT_NO_THROW(pat.setWorkPlace("ПАО Черный банк"));

    DataObject data = pat.toDataObject();

    ASSERT_EQ(data.getType(), "patient");

    QString out;
    ASSERT_TRUE(data.getValue("regid", out));
    ASSERT_EQ(out, pat.regID());

    ASSERT_TRUE(data.getValue("fullname", out));
    ASSERT_EQ(out, pat.fullName());

    ASSERT_TRUE(data.getValue("year", out));
    ASSERT_EQ(out, QString("{1}").arg(pat.yearOfBirth()));

    ASSERT_TRUE(data.getValue("address", out));
    ASSERT_EQ(out, pat.address());

    ASSERT_TRUE(data.getValue("workplace", out));
    ASSERT_EQ(out, pat.workPlace());
}

TEST(Patient, fromDataObject)
{
    Patient pat;
    ASSERT_NO_THROW(pat.setRegID("12-345678"));
    ASSERT_NO_THROW(pat.setFullName("Иванов И.И."));
    ASSERT_NO_THROW(pat.setYearOfBirth(2005));
    ASSERT_NO_THROW(pat.setAddress("г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7"));
    ASSERT_NO_THROW(pat.setWorkPlace("ПАО Черный банк"));

    auto resetData = [](DataObject& data) {
        data.setType("patient");

        data.setValue("regid", "12-345678");
        data.setValue("fullname", "Иванов И.И.");
        data.setValue("year", "2005");
        data.setValue("address", "г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7");
        data.setValue("workplace", "ПАО Черный банк");
    };

    DataObject data;
    resetData(data);

    Patient fromData;
    ASSERT_TRUE(fromData.fromDataObject(data));
    ASSERT_TRUE(pat == fromData);

    //Filling with wrong data
    data.setType("aoa");
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    data.setValue("regid", "wrong");
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    QString str;
    str.resize(MAX_PATIENT_REGID_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("regid", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    str.resize(MAX_PATIENT_FULLNAME_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("fullname", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    data.setValue("year", QString("{1}").arg(MAX_PATIENT_YEAR + 1));
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    str.resize(MAX_PATIENT_ADDRESS_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("address", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    str.resize(MAX_PATIENT_WORKPLACE_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("workplace", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);
}

TEST(Patient, OperatorEqual)
{
    Patient pat;
    ASSERT_NO_THROW(pat.setRegID("12-345678"));
    ASSERT_NO_THROW(pat.setFullName("Иванов И.И."));
    ASSERT_NO_THROW(pat.setYearOfBirth(2005));
    ASSERT_NO_THROW(pat.setAddress("г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7"));
    ASSERT_NO_THROW(pat.setWorkPlace("ПАО Черный банк"));

    Patient other;
    ASSERT_NO_THROW(other.setRegID("12-345678"));
    ASSERT_NO_THROW(other.setFullName("Иванов И.И."));
    ASSERT_NO_THROW(other.setYearOfBirth(2005));
    ASSERT_NO_THROW(other.setAddress("г. Новосталинск. Ул. Сталина д. 45 к. 2 кв. 7"));
    ASSERT_NO_THROW(other.setWorkPlace("ПАО Черный банк"));

    ASSERT_TRUE(pat == other);
    ASSERT_FALSE(pat != other);

    other.setRegID("00-000000");
    ASSERT_TRUE(pat != other);
    ASSERT_FALSE(pat == other);
}
