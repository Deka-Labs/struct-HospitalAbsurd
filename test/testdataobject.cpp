#include "file/dataobject.hpp"
#include "gtest/gtest.h"

TEST(DataObject, SettersAndGetter)
{
    DataObject obj;

    ASSERT_NO_THROW(obj.setType("Test"));
    ASSERT_NO_THROW(obj.setValue("number", "0"));
    ASSERT_NO_THROW(obj.setValue("color", "The white"));

    ASSERT_EQ(obj.getType(), "Test");
    QString out;
    ASSERT_TRUE(obj.getValue("number", out));
    ASSERT_EQ(out, "0");
    ASSERT_TRUE(obj.getValue("color", out));
    ASSERT_EQ(out, "The white");

    ASSERT_NO_THROW(obj.setValue("color", "black"));
    ASSERT_TRUE(obj.getValue("color", out));
    ASSERT_EQ(out, "black");
}

TEST(DataObject, Delete)
{
    DataObject obj;

    ASSERT_NO_THROW(obj.setType("Test"));
    ASSERT_NO_THROW(obj.setValue("number", "0"));
    ASSERT_NO_THROW(obj.setValue("color", "The white"));

    QString out;

    ASSERT_NO_THROW(obj.delAttribute("color"));
    ASSERT_FALSE(obj.getValue("color", out));

    ASSERT_TRUE(obj.getValue("number", out));
}
