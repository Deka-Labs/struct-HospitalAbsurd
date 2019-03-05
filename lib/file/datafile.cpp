#include "datafile.hpp"

DataFile::DataFile()
    : m_file()
    , m_forRead(false)
{
}

DataFile::~DataFile()
{
    close();
}

bool DataFile::open(const char* filename, bool forRead)
{
    close();

    m_file.setFileName(filename);
    if (forRead) {
        m_file.open(QIODevice::ReadOnly);
        m_forRead = true;
    } else {
        m_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        m_forRead = false;
    }

    m_file.seek(0);

    if (m_file.isOpen()) {
        if (!m_forRead || validateFileStructure())
            return true;
    }
    close();
    return false;
}

void DataFile::close()
{
    if (m_file.isOpen())
        m_file.close();
}

bool DataFile::ReadNextObject(DataObject& obj)
{
    if (!m_forRead)
        return false;
    //Ищем первый символ открытия объекта
    char currentSymbol = '\0';
    m_file.read(&currentSymbol, sizeof(char));
    while (currentSymbol != DATA_CHAR_OPEN_OBJ) {
        auto code = m_file.read(&currentSymbol, sizeof(char));
        if (code <= 0)
            return false;
    }

    //Читаем тип. Находим первый пробел между ним и < - название типа
    QString type;
    while (currentSymbol != DATA_CHAR_SPACE) {
        auto code = m_file.read(&currentSymbol, sizeof(char));
        if (code <= 0)
            return false;
        if (!QChar(currentSymbol).isSpace())
            type += currentSymbol;
    }

    if (type.size() == 0)
        return false;
    obj.setType(type);

    while (true) {
        //Читаем до первого непробельного символа
        do {
            auto code = m_file.read(&currentSymbol, sizeof(char));
            if (code <= 0)
                return false;
        } while (QChar(currentSymbol).isSpace());

        if (currentSymbol == DATA_CHAR_CLOSE_OBJ) //Конец
            break;

        //Читаем атрибуты
        {
            QString name;
            QString value;

            //Сначало имя
            while (currentSymbol != DATA_CHAR_EQUAL) {
                name += currentSymbol; //Обязательно вначале. 1 символ уже считан.
                auto code = m_file.read(&currentSymbol, sizeof(char));
                if (code <= 0 || currentSymbol == DATA_CHAR_SPACE)
                    return false;
            }
            //Читаем разделитель
            auto code = m_file.read(&currentSymbol, sizeof(char));
            if (code <= 0 || currentSymbol != DATA_CHAR_DIVIDER_ARG)
                return false;

            //Читаем первый символ после разделителя
            code = m_file.read(&currentSymbol, sizeof(char));
            if (code <= 0)
                return false;

            //Читаем значения до разделителя
            while (currentSymbol != DATA_CHAR_DIVIDER_ARG) {
                value += currentSymbol; //Обязательно вначале. 1 символ уже считан.
                auto code = m_file.read(&currentSymbol, sizeof(char));
                if (code <= 0)
                    return false;
            }
            //Устанавливаем значение
            obj.setValue(name, value);
        }
    }

    return true;
}

void DataFile::startOver()
{
    if (m_file.isOpen())
        m_file.seek(0);
}

bool DataFile::insertObject(const DataObject& obj)
{
    if (m_forRead)
        return false;

    QByteArray toWrite;

    toWrite.append(DATA_CHAR_OPEN_OBJ);
    toWrite.append(obj.getType());
    toWrite.append(DATA_CHAR_SPACE);

    for (unsigned i = 0; i < obj.m_attributes.size(); i++) {
        auto att = obj.m_attributes.at(i);
        toWrite.append(att.name);
        toWrite.append(DATA_CHAR_EQUAL);
        toWrite.append(DATA_CHAR_DIVIDER_ARG);
        toWrite.append(att.value);
        toWrite.append(DATA_CHAR_DIVIDER_ARG);
        toWrite.append(DATA_CHAR_SPACE);
    }

    toWrite.append(DATA_CHAR_CLOSE_OBJ);
    toWrite.append(DATA_CHAR_NEWLINE);

    m_file.write(toWrite);

    return true;
}

bool DataFile::atEOF() const
{
    if (!m_file.isOpen())
        return true;
    return m_file.atEnd();
}

bool DataFile::validateFileStructure()
{
    if (!m_file.isOpen())
        return false;
    startOver();
    //Просто считаем некоторые характеристики без подробного анализа.

    char prevChar = '\0';
    char currentChar = '\0';
    qint64 code = m_file.read(&currentChar, sizeof(char));

    unsigned countOfOpen = 0, countOfClose = 0;

    while (code > 0) {
        if (currentChar == DATA_CHAR_OPEN_OBJ)
            countOfOpen++;
        if (currentChar == DATA_CHAR_CLOSE_OBJ)
            countOfClose++;
        if (prevChar == DATA_CHAR_EQUAL && currentChar != DATA_CHAR_DIVIDER_ARG)
            return false;
        if (prevChar == DATA_CHAR_OPEN_OBJ && !QChar(currentChar).isLetterOrNumber())
            return false;

        prevChar = currentChar;
        code = m_file.read(&currentChar, sizeof(char));
    }

    startOver();

    if (countOfOpen == 0 || countOfClose == 0)
        return false;
    if (countOfOpen != countOfClose)
        return false;
    return true;
}
