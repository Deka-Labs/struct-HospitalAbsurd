#include "file/datafile.hpp"
#include <gtest/gtest.h>

TEST(DataFile, OpenClose)
{
    DataFile df;
    df.open("test.data", false);

    DataObject obj;
    obj.setType("Test");
    obj.setValue("number", "0");
    obj.setValue("color", "The white");

    ASSERT_NO_THROW(df.insertObject(obj));

    obj.setType("Another");
    obj.delAttribute("number");
    obj.setValue("float", "1.65");

    ASSERT_NO_THROW(df.insertObject(obj));

    df.close();

    df.open("test.data", true);

    obj = DataObject();

    ASSERT_TRUE(df.ReadNextObject(obj));

    QString out;
    ASSERT_TRUE(obj.getValue("number", out));
    ASSERT_EQ(out, "0");
    ASSERT_TRUE(obj.getValue("color", out));
    ASSERT_EQ(out, "The white");

    obj = DataObject();

    ASSERT_TRUE(df.ReadNextObject(obj));

    ASSERT_TRUE(obj.getValue("float", out));
    ASSERT_EQ(out, "1.65");
    ASSERT_TRUE(obj.getValue("color", out));
    ASSERT_EQ(out, "The white");
}
