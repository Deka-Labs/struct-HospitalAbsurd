#ifndef DATAFILE_HPP
#define DATAFILE_HPP

#include "dataobject.hpp"
#include "statuscodes.hpp"
#include <QFile>
#include <QString>
#include <QTextStream>

#define DATA_CHAR_EQUAL '='
#define DATA_CHAR_DIVIDER_ARG '`'
#define DATA_CHAR_OPEN_OBJ '<'
#define DATA_CHAR_CLOSE_OBJ '>'
#define DATA_CHAR_SPACE ' '
#define DATA_CHAR_NEWLINE '\n'
#define DATA_ENCODING "UTF-8"

const QChar restrictedChars[] = { DATA_CHAR_EQUAL, DATA_CHAR_DIVIDER_ARG, DATA_CHAR_OPEN_OBJ, DATA_CHAR_CLOSE_OBJ };

/*
File template:

<type attr1="111" attr2="">

Условия:
* Тип - одно слово
* Аттрибут - одно слово
* Значения - любое число слов в кавычках
* Между атрибутом и '=' нет пробелов
* Между значением и '=' нет пробелов
* Между объектами могут быть любые пробельные символы
* Все что написано между <...>[здесь]<...> игонорируется
* Все выше объявленые символы запрещены в названий объектах или комментариев
*/

class DataFile {
private:
    QFile m_file;
    QTextStream m_stream;
    bool m_forRead;

public:
    DataFile();
    DataFile(const DataFile& other) = delete;
    ~DataFile();

    StatusCodes open(const char* filename, bool forRead = true);
    void close();

    StatusCodes ReadNextObject(DataObject& obj);
    void startOver();

    bool insertObject(const DataObject& obj);

    bool atEOF() const;

private:
    StatusCodes validateFileStructure();

    bool readNext(QChar* ch);
};

#endif // DATAFILE_HPP
