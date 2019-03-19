#include "utils.hpp"

#include <gtest/gtest.h>

TEST(Utils, QStringSearch) {
    QString request = "", string = "";
    ASSERT_FALSE(QStringSearch(request, string));

    request = "abc";
    string  = "abcsdqfabd";
    ASSERT_TRUE(QStringSearch(request, string));
    ASSERT_FALSE(QStringSearch(string, request));

    request = "abc";
    string  = "vbcsdabcqfabd";
    ASSERT_TRUE(QStringSearch(request, string));

    request = "abc";
    string  = "vbcsdbcqfabc";
    ASSERT_TRUE(QStringSearch(request, string));

    request = "abc";
    string  = "vbcsdabqfabd";
    ASSERT_FALSE(QStringSearch(request, string));

    request = "abc";
    string  = "abc";
    ASSERT_TRUE(QStringSearch(request, string));
}

TEST(Utils, TemplateValidate) {
    QString str = "", templ = "";
    ASSERT_TRUE(TemplateValidate(templ, str));

    str   = "-01-20-:93";
    templ = "-dd-dd-:dd";
    ASSERT_TRUE(TemplateValidate(templ, str));

    str   = "0123456789";
    templ = "dddd";
    ASSERT_FALSE(TemplateValidate(templ, str));

    str   = "0123";
    templ = "dddddddd";
    ASSERT_FALSE(TemplateValidate(templ, str));

    str   = "1234";
    templ = "dddd";
    ASSERT_TRUE(TemplateValidate(templ, str));

    str   = "QFASA";
    templ = "QFASA";
    ASSERT_TRUE(TemplateValidate(templ, str));

    str   = "QFddASA";
    templ = "QFddASA";
    ASSERT_FALSE(TemplateValidate(templ, str));

    str   = "QF00ASA";
    templ = "QFddASA";
    ASSERT_TRUE(TemplateValidate(templ, str));
}
