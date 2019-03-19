#include "datafile.hpp"

DataFile::DataFile()
    : m_file()
    , m_stream()
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
    m_stream.setCodec(DATA_ENCODING);
    if (forRead) {
        m_file.open(QIODevice::ReadOnly);
        m_stream.setDevice(&m_file);
        m_forRead = true;
    } else {
        m_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        m_stream.setDevice(&m_file);
        m_forRead = false;
    }

    if (m_file.isOpen()) {
        if (!m_forRead || validateFileStructure())
            return true;
    }
    close();
    return false;
}

void DataFile::close()
{
    m_stream.setDevice(nullptr);
    if (m_file.isOpen())
        m_file.close();
}

StatusCodes DataFile::ReadNextObject(DataObject& obj)
{
    if (!m_forRead)
        return StatusCode_WrongMode;
    //Ищем первый символ открытия объекта
    QChar currentSymbol = '\0';
    auto code = readNext(&currentSymbol);
    if (!code)
        return StatusCode_File_NoObject;
    while (currentSymbol != DATA_CHAR_OPEN_OBJ) {
        code = readNext(&currentSymbol);
        if (!code)
            return StatusCode_File_NoObject;
    }

    //Читаем тип. Находим первый пробел между ним и < - название типа
    QString type;
    while (currentSymbol != DATA_CHAR_SPACE) {
        code = readNext(&currentSymbol);
        if (!code)
            return StatusCode_File_UnexpectedEnd;
        if (!currentSymbol.isSpace())
            type += currentSymbol;
    }

    if (type.size() == 0)
        return StatusCode_InvalidObject;
    obj.setType(type);

    while (true) {
        //Читаем до первого непробельного символа
        do {
            code = readNext(&currentSymbol);
            if (!code)
                return StatusCode_File_UnexpectedEnd;
        } while (currentSymbol.isSpace());

        if (currentSymbol == DATA_CHAR_CLOSE_OBJ) //Конец
            break;

        //Читаем атрибуты
        {
            QString name;
            QString value;

            //Сначало имя
            while (currentSymbol != DATA_CHAR_EQUAL) {
                name += currentSymbol; //Обязательно вначале. 1 символ уже считан.
                code = readNext(&currentSymbol);
                if (!code)
                    return StatusCode_File_UnexpectedEnd;
                if (currentSymbol == DATA_CHAR_SPACE)
                    return StatusCode_InvalidObject;
            }
            //Читаем разделитель
            code = readNext(&currentSymbol);
            if (!code)
                return StatusCode_File_UnexpectedEnd;
            if (currentSymbol != DATA_CHAR_DIVIDER_ARG)
                return StatusCode_InvalidObject;

            //Читаем первый символ после разделителя
            code = readNext(&currentSymbol);
            if (!code)
                return StatusCode_File_UnexpectedEnd;

            //Читаем значения до разделителя
            while (currentSymbol != DATA_CHAR_DIVIDER_ARG) {
                value += currentSymbol; //Обязательно вначале. 1 символ уже считан.
                code = readNext(&currentSymbol);
                if (!code)
                    return StatusCode_File_UnexpectedEnd;
            }
            //Устанавливаем значение
            obj.setValue(name, value);
        }
    }

    return StatusCode_OK;
}

void DataFile::startOver()
{
    m_stream.seek(0);
    if (m_file.isOpen())
        m_file.seek(0);
}

bool DataFile::insertObject(const DataObject& obj)
{
    if (m_forRead)
        return false;

    m_stream << DATA_CHAR_OPEN_OBJ << obj.getType() << DATA_CHAR_SPACE;

    for (unsigned i = 0; i < obj.m_attributes.size(); i++) {
        auto att = obj.m_attributes.at(i);
        m_stream << att.name << DATA_CHAR_EQUAL << DATA_CHAR_DIVIDER_ARG;
        m_stream << att.value << DATA_CHAR_DIVIDER_ARG << DATA_CHAR_SPACE;
    }

    m_stream << DATA_CHAR_CLOSE_OBJ << DATA_CHAR_NEWLINE;

    return true;
}

bool DataFile::atEOF() const
{
    if (!m_file.isOpen())
        return true;
    return m_stream.atEnd();
}

bool DataFile::validateFileStructure()
{
    if (!m_file.isOpen())
        return false;
    startOver();
    //Просто считаем некоторые характеристики без подробного анализа.

    QChar prevChar = '\0';
    QChar currentChar = '\0';
    bool code = readNext(&currentChar);

    unsigned countOfOpen = 0, countOfClose = 0;

    while (code) {
        if (currentChar == DATA_CHAR_OPEN_OBJ)
            countOfOpen++;
        if (currentChar == DATA_CHAR_CLOSE_OBJ)
            countOfClose++;
        if (prevChar == DATA_CHAR_EQUAL && currentChar != DATA_CHAR_DIVIDER_ARG)
            return false;
        if (prevChar == DATA_CHAR_OPEN_OBJ && !currentChar.isLetterOrNumber())
            return false;

        prevChar = currentChar;
        code = readNext(&currentChar);
    }

    startOver();

    if (countOfOpen == 0 || countOfClose == 0)
        return false;
    if (countOfOpen != countOfClose)
        return false;
    return true;
}

bool DataFile::readNext(QChar* ch)
{
    if (!m_file.isOpen() || atEOF())
        return false;

    if (ch) {
        m_stream >> *ch;
    }

    return true;
}
