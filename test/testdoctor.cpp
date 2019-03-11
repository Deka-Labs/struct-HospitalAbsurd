#include "data/hospital/doctor.hpp"
#include "file/dataobject.hpp"
#include <gtest/gtest.h>

TEST(Doctor, Setters)
{
    Doctor doc;
    ASSERT_TRUE(doc.setFullname("Иванов И. И"));
    ASSERT_TRUE(doc.setPost("Психолог"));
    ASSERT_TRUE(doc.setCabinet(13));
    ASSERT_TRUE(doc.setSchedule("ПН: 11-16; ПТ: 16-19"));

    ASSERT_EQ(doc.fullname(), "Иванов И. И");
    ASSERT_EQ(doc.post(), "Психолог");
    ASSERT_EQ(doc.cabinet(), 13);
    ASSERT_EQ(doc.schedule(), "ПН: 11-16; ПТ: 16-19");

    QString str;

    //FULLNAME
    str.resize(MAX_DOCTOR_FULLNAME_STRING_SIZE + 1);
    str.fill('0');

    ASSERT_FALSE(doc.setFullname(str));
    ASSERT_EQ(doc.fullname(), "Иванов И. И");

    //POST
    str.resize(MAX_DOCTOR_POST_STRING_SIZE + 1);
    str.fill('0');

    ASSERT_FALSE(doc.setPost(str));
    ASSERT_EQ(doc.post(), "Психолог");

    //CABINET
    ASSERT_FALSE(doc.setCabinet(MAX_DOCTOR_CABINET + 1));
    ASSERT_EQ(doc.cabinet(), 13);

    //SCHEDULE
    str.resize(MAX_DOCTOR_SCHEDULE_STRING_SIZE + 1);
    str.fill('0');

    ASSERT_FALSE(doc.setSchedule(str));
    ASSERT_EQ(doc.schedule(), "ПН: 11-16; ПТ: 16-19");
}

TEST(Doctor, toDataObject)
{
    Doctor doc;
    ASSERT_TRUE(doc.setFullname("Иванов И. И"));
    ASSERT_TRUE(doc.setPost("Психолог"));
    ASSERT_TRUE(doc.setCabinet(13));
    ASSERT_TRUE(doc.setSchedule("ПН: 11-16; ПТ: 16-19"));

    DataObject data = doc.toDataObject();

    ASSERT_EQ(data.getType(), "doctor");

    QString out;
    ASSERT_TRUE(data.getValue("fullname", out));
    ASSERT_EQ(out, doc.fullname());

    ASSERT_TRUE(data.getValue("post", out));
    ASSERT_EQ(out, doc.post());

    ASSERT_TRUE(data.getValue("cabinet", out));
    ASSERT_EQ(out, QString("%1").arg(doc.cabinet()));

    ASSERT_TRUE(data.getValue("schedule", out));
    ASSERT_EQ(out, doc.schedule());
}

TEST(Doctor, fromDataObject)
{
    Doctor doc;
    ASSERT_TRUE(doc.setFullname("Иванов И. И"));
    ASSERT_TRUE(doc.setPost("Психолог"));
    ASSERT_TRUE(doc.setCabinet(13));
    ASSERT_TRUE(doc.setSchedule("ПН: 11-16; ПТ: 16-19"));

    auto resetData = [](DataObject& data) {
        data.setType("doctor");
        data.setValue("fullname", "Иванов И. И");
        data.setValue("post", "Психолог");
        data.setValue("cabinet", "13");
        data.setValue("schedule", "ПН: 11-16; ПТ: 16-19");
    };

    DataObject data;
    resetData(data);

    Doctor fromData;
    ASSERT_TRUE(fromData.fromDataObject(data));
    ASSERT_TRUE(doc.key() == fromData.key());
    resetData(data);

    data.setType("aoaoao");
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    QString str;
    str.resize(MAX_DOCTOR_FULLNAME_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("fullname", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    str.resize(MAX_DOCTOR_POST_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("post", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    data.setValue("cabinet", QString("%1").arg(MAX_DOCTOR_CABINET + 1));
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);

    str.resize(MAX_DOCTOR_SCHEDULE_STRING_SIZE + 1);
    str.fill('0');
    data.setValue("schedule", str);
    ASSERT_FALSE(fromData.fromDataObject(data));
    resetData(data);
}

TEST(Doctor, OperatorCompare)
{
    Doctor doc;
    ASSERT_TRUE(doc.setFullname("Иванов И. И"));
    ASSERT_TRUE(doc.setPost("Психолог"));
    ASSERT_TRUE(doc.setCabinet(13));
    ASSERT_TRUE(doc.setSchedule("ПН: 11-16; ПТ: 16-19"));

    Doctor other;
    ASSERT_TRUE(other.setFullname("Иванов П. И"));
    ASSERT_TRUE(other.setPost("Психолог"));
    ASSERT_TRUE(other.setCabinet(13));
    ASSERT_TRUE(other.setSchedule("ПН: 11-16; ПТ: 16-19"));

    ASSERT_TRUE(other > doc);
    ASSERT_FALSE(doc > other);
    ASSERT_TRUE(other >= doc);
    ASSERT_FALSE(doc >= other);

    ASSERT_TRUE(doc < other);
    ASSERT_FALSE(other < doc);
    ASSERT_TRUE(doc <= other);
    ASSERT_FALSE(other <= doc);

    ASSERT_TRUE(other != doc);
    ASSERT_FALSE(other == doc);

    ASSERT_TRUE(other.setFullname("Иванов И. И"));
    ASSERT_TRUE(other >= doc);
    ASSERT_TRUE(doc >= other);
    ASSERT_TRUE(doc <= other);
    ASSERT_TRUE(other <= doc);

    ASSERT_FALSE(other > doc);
    ASSERT_FALSE(doc > other);
    ASSERT_FALSE(doc < other);
    ASSERT_FALSE(other < doc);

    ASSERT_TRUE(other == doc);
    ASSERT_FALSE(other != doc);
}
