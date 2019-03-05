#include "file/datafile.hpp"
#include <fstream>
#include <gtest/gtest.h>

TEST(DataFile, ReadingNormal)
{
    const char* testFile = "testReading.file";
    std::fstream file;
    DataFile df;

    file.open(testFile, std::ios_base::out | std::ios_base::trunc);
    ASSERT_TRUE(file.is_open());

    const int count = 1000;

    for (int i = 0; i < count; i++) {
        file << DATA_CHAR_OPEN_OBJ << "object" << DATA_CHAR_SPACE;
        file << "id" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << i << DATA_CHAR_DIVIDER_ARG << DATA_CHAR_SPACE;
        file << "nid" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << count - i << DATA_CHAR_DIVIDER_ARG;
        file << DATA_CHAR_CLOSE_OBJ;
    }
    file.close();

    ASSERT_TRUE(df.open(testFile, true));

    for (int i = 0; i < count; i++) {
        DataObject obj;
        ASSERT_TRUE(df.ReadNextObject(obj));
        ASSERT_EQ(obj.getType(), "object");
        QString id;
        ASSERT_TRUE(obj.getValue("id", id));
        ASSERT_EQ(id, QString("%1").arg(i));
        ASSERT_TRUE(obj.getValue("nid", id));
        ASSERT_EQ(id, QString("%1").arg(count - i));
    }
}

TEST(DataFile, ReadingEmpty)
{
    std::fstream file;
    DataFile df;
    const char* testFile = "testReadingEmpty.file";

    //Testing empty file
    file.open(testFile, std::ios_base::out | std::ios_base::trunc);
    ASSERT_TRUE(file.is_open());
    file.close();

    ASSERT_FALSE(df.open(testFile, true));
}

TEST(DataFile, ReadingBrokenStructure)
{
    std::fstream file;
    DataFile df;
    const char* testFile = "testReadingBrokenStructure.file";

    //Testing file with broken '<' '>' structure
    //1 obj, opening
    file.open(testFile, std::ios_base::out | std::ios_base::trunc);
    ASSERT_TRUE(file.is_open());
    file << "object" << DATA_CHAR_SPACE << "att" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << "1" << DATA_CHAR_DIVIDER_ARG << DATA_CHAR_CLOSE_OBJ;
    file.close();

    ASSERT_FALSE(df.open(testFile, true));
    df.close();

    //1 obj, closing
    file.open(testFile, std::ios_base::out | std::ios_base::trunc);
    ASSERT_TRUE(file.is_open());
    file << DATA_CHAR_OPEN_OBJ << "object" << DATA_CHAR_SPACE << "att" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << "1" << DATA_CHAR_DIVIDER_ARG;
    file.close();

    ASSERT_FALSE(df.open(testFile, true));
    df.close();

    //3 obj
    file.open(testFile, std::ios_base::out | std::ios_base::trunc);
    ASSERT_TRUE(file.is_open());
    file << DATA_CHAR_OPEN_OBJ << "object" << DATA_CHAR_SPACE << "att" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << "1" << DATA_CHAR_DIVIDER_ARG << DATA_CHAR_CLOSE_OBJ;
    file << DATA_CHAR_OPEN_OBJ << "object" << DATA_CHAR_SPACE << "att" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << "1" << DATA_CHAR_DIVIDER_ARG;
    file << DATA_CHAR_OPEN_OBJ << "object" << DATA_CHAR_SPACE << "att" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << "1" << DATA_CHAR_DIVIDER_ARG << DATA_CHAR_CLOSE_OBJ;
    file.close();

    ASSERT_FALSE(df.open(testFile, true));
    df.close();
}

TEST(DataFile, ReadingPlainText)
{
    std::fstream file;
    DataFile df;
    const char* testFile = "testReadingPlainText.file";

    //Testing file with plain text
    file.open(testFile, std::ios_base::out | std::ios_base::trunc);
    ASSERT_TRUE(file.is_open());
    file << "The quick brown fox jumps over the lazy dog\n"
            "Широкая электрификация южных губерний даст мощный толчок подъёму сельского хозяйства.\n"
            "В чащах юга жил бы цитрус? Да, но фальшивый экземпляр!\n"
            "The five boxing wizards jump quickly.";

    ASSERT_FALSE(df.open(testFile, true));
    df.close();
}

TEST(DataFile, ReadingBrokenObject)
{
    std::fstream file;
    DataFile df;
    const char* testFile = "testReadingBrokenObject.file";

    //Testing file with plain text
    file.open(testFile, std::ios_base::out | std::ios_base::trunc);
    ASSERT_TRUE(file.is_open());
    file << DATA_CHAR_OPEN_OBJ << "object" << DATA_CHAR_SPACE << "att" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << "1" << DATA_CHAR_DIVIDER_ARG << DATA_CHAR_CLOSE_OBJ;
    file << DATA_CHAR_OPEN_OBJ << "Trust me! I'm object" << DATA_CHAR_CLOSE_OBJ;
    file << DATA_CHAR_OPEN_OBJ << "object" << DATA_CHAR_SPACE << "att" << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG << "1" << DATA_CHAR_DIVIDER_ARG << DATA_CHAR_CLOSE_OBJ;

    file.close();

    ASSERT_TRUE(df.open(testFile, true));

    DataObject obj;

    ASSERT_TRUE(df.ReadNextObject(obj));
    ASSERT_FALSE(df.ReadNextObject(obj));
    ASSERT_TRUE(df.ReadNextObject(obj));

    df.close();
}

TEST(DataFile, Writing)
{
    const char* testFile = "testWriting.file";
    DataFile df;

    ASSERT_TRUE(df.open(testFile, false));

    const int count = 1000;

    for (int i = 0; i < count; i++) {
        DataObject obj;
        obj.setType("object");
        obj.setValue("id", QString("%1").arg(i));
        obj.setValue("nid", QString("%1").arg(count - i));

        ASSERT_TRUE(df.insertObject(obj));
    }

    df.close();

    ASSERT_TRUE(df.open(testFile, true));

    for (int i = 0; i < count; i++) {
        DataObject obj;
        ASSERT_TRUE(df.ReadNextObject(obj));
        ASSERT_EQ(obj.getType(), "object");
        QString id;
        ASSERT_TRUE(obj.getValue("id", id));
        ASSERT_EQ(id, QString("%1").arg(i));
        ASSERT_TRUE(obj.getValue("nid", id));
        ASSERT_EQ(id, QString("%1").arg(count - i));
    }
}

TEST(DataFile, RussianLoc)
{
    const char* testFile = "testRussian.file";
    DataFile df;

    ASSERT_TRUE(df.open(testFile, false));

    DataObject obj;
    obj.setType("объект");
    obj.setValue("имя", "Ад букв я");
    obj.setValue("псевдоним", "яЯя");

    ASSERT_TRUE(df.insertObject(obj));

    df.close();

    ASSERT_TRUE(df.open(testFile, true));

    ASSERT_TRUE(df.ReadNextObject(obj));
    ASSERT_EQ(obj.getType(), "объект");
    QString id;
    ASSERT_TRUE(obj.getValue("имя", id));
    ASSERT_EQ(id, "Ад букв я");
    ASSERT_TRUE(obj.getValue("псевдоним", id));
    ASSERT_EQ(id, "яЯя");
}
