#include "data/hospital/referral.hpp"

#include <gtest/gtest.h>

TEST(Referral, Setters) {
    Referral ref;
    ASSERT_TRUE(ref.setRegID("12-456789"));
    ASSERT_TRUE(ref.setDoctorFullname("Иванов И. И."));
    ASSERT_TRUE(ref.setDate("10.02.2018"));
    ASSERT_TRUE(ref.setTime("10:15"));

    ASSERT_EQ(ref.regID(), "12-456789");
    ASSERT_EQ(ref.doctorFullname(), "Иванов И. И.");
    ASSERT_EQ(ref.date(), "10.02.2018");
    ASSERT_EQ(ref.time(), "10:15");

    QString str;

    // RegID

    str.resize(MAX_PATIENT_REGID_STRING_SIZE + 1);
    str.fill('0');

    ASSERT_FALSE(ref.setRegID(str));
    ASSERT_EQ(ref.regID(), "12-456789");

    ASSERT_FALSE(ref.setRegID("Wrong"));
    ASSERT_EQ(ref.regID(), "12-456789");

    // Doctor's fullname

    str.resize(MAX_DOCTOR_FULLNAME_STRING_SIZE + 1);
    str.fill('0');

    ASSERT_FALSE(ref.setDoctorFullname(str));
    ASSERT_EQ(ref.doctorFullname(), "Иванов И. И.");

    // Date

    str.resize(MAX_DATE_STRING_SIZE + 1);
    str.fill('0');

    ASSERT_FALSE(ref.setDate(str));
    ASSERT_EQ(ref.date(), "10.02.2018");

    // Time

    str.resize(MAX_TIME_STRING_SIZE + 1);
    str.fill('0');

    ASSERT_FALSE(ref.setTime(str));
    ASSERT_EQ(ref.time(), "10:15");
}

TEST(Referral, toDataObject) {
    Referral ref;
    ASSERT_TRUE(ref.setRegID("12-456789"));
    ASSERT_TRUE(ref.setDoctorFullname("Иванов И. И."));
    ASSERT_TRUE(ref.setDate("10.02.2018"));
    ASSERT_TRUE(ref.setTime("10:15"));

    DataObject data = ref.toDataObject();

    ASSERT_EQ(data.getType(), "referral");

    QString out;
    ASSERT_TRUE(data.getValue("regid", out));
    ASSERT_EQ(out, ref.regID());

    ASSERT_TRUE(data.getValue("docfullname", out));
    ASSERT_EQ(out, ref.doctorFullname());

    ASSERT_TRUE(data.getValue("date", out));
    ASSERT_EQ(out, ref.date());

    ASSERT_TRUE(data.getValue("time", out));
    ASSERT_EQ(out, ref.time());
}

TEST(Referral, fromDataObject) {
    Referral ref;
    ASSERT_TRUE(ref.setRegID("12-456789"));
    ASSERT_TRUE(ref.setDoctorFullname("Иванов И. И."));
    ASSERT_TRUE(ref.setDate("10.02.2018"));
    ASSERT_TRUE(ref.setTime("10:15"));

    auto resetData = [](DataObject& data) {
        data.setType("referral");
        data.setValue("regid", "12-456789");
        data.setValue("docfullname", "Иванов И. И.");
        data.setValue("date", "10.02.2018");
        data.setValue("time", "10:15");
    };

    DataObject data;
    resetData(data);

    Referral fromData;
    ASSERT_TRUE(fromData.fromDataObject(data));
    ASSERT_TRUE(ref == fromData);

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

    str.resize(MAX_DOCTOR_FULLNAME_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("docfullname", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    data.setValue("date", "wr.12.2ong");
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    str.resize(MAX_DATE_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("date", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    data.setValue("time", "--:--");
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    str.resize(MAX_TIME_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("time", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);
}

TEST(Referral, OperationCompare) {
    Referral ref;
    ASSERT_TRUE(ref.setRegID("12-456789"));
    ASSERT_TRUE(ref.setDoctorFullname("0"));
    ASSERT_TRUE(ref.setDate("10.02.2018"));
    ASSERT_TRUE(ref.setTime("10:15"));

    Referral other;
    ASSERT_TRUE(other.setRegID("12-456789"));
    ASSERT_TRUE(other.setDoctorFullname("0"));
    ASSERT_TRUE(other.setDate("10.02.2018"));
    ASSERT_TRUE(other.setTime("10:15"));

    ASSERT_TRUE(ref == other);
    ASSERT_FALSE(ref != other);
    ASSERT_FALSE(ref > other);
    ASSERT_FALSE(ref < other);
    ASSERT_TRUE(ref >= other);
    ASSERT_TRUE(ref <= other);

    other.setDoctorFullname("1");
    ASSERT_TRUE(ref != other);
    ASSERT_FALSE(ref == other);
    ASSERT_FALSE(ref > other);
    ASSERT_TRUE(ref < other);
    ASSERT_FALSE(ref >= other);
    ASSERT_TRUE(ref <= other);

    ref.setDoctorFullname("2");
    ASSERT_TRUE(ref != other);
    ASSERT_FALSE(ref == other);
    ASSERT_TRUE(ref > other);
    ASSERT_FALSE(ref < other);
    ASSERT_TRUE(ref >= other);
    ASSERT_FALSE(ref <= other);
}
