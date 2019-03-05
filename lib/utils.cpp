#include "utils.hpp"

bool QStringSearch(const QString& request, const QString& string)
{
    auto sizeR = request.size();
    auto sizeS = string.size();

    if (sizeR > sizeS || sizeR == 0 || sizeS == 0)
        return false;

    int currentPos = 0;

    for (currentPos = 0; currentPos <= (sizeS - sizeR); currentPos++) {
        int pos = 0;
        for (pos = 0; pos < sizeR; pos++) {
            if (request[pos] != string[currentPos + pos])
                break;
        }

        if (pos == sizeR) //Найдено!
            return true;
    }

    return false;
}

bool TemplateValidate(const QString& templ, const QString& str)
{
    if (templ.size() != str.size())
        return false;

    for (int pos = 0; pos < templ.size(); pos++) {
        QChar curChar = str[pos];
        if (templ[pos] == 'd') {
            if (!curChar.isDigit())
                return false;
        } else {
            if (templ[pos] != curChar)
                return false;
        }
    }

    return true;
}
