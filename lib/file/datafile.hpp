#ifndef DATAFILE_HPP
#define DATAFILE_HPP

#include "dataobject.hpp"
#include <QFile>
#include <QString>
#include <QTextStream>

#define DATA_CHAR_EQUAL '='
#define DATA_CHAR_DIVIDER_ARG '\''
#define DATA_CHAR_OPEN_OBJ '<'
#define DATA_CHAR_CLOSE_OBJ '>'
#define DATA_CHAR_SPACE ' '
#define DATA_CHAR_NEWLINE '\n'
#define DATA_ENCODING "UTF-16"

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

    bool open(const char* filename, bool forRead = true);
    void close();

    bool ReadNextObject(DataObject& obj);
    void startOver();

    bool insertObject(const DataObject& obj);

    bool atEOF() const;

private:
    bool validateFileStructure();

    bool readNext(QChar* ch);
};

#endif // DATAFILE_HPP
