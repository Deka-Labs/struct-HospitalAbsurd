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
        if (validateFileStructure())
            return true;
    }
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
    //Ищем первый символ '<'
    char currentSymbol = '\0';
    m_file.read(&currentSymbol, sizeof(char));
    while (currentSymbol != '<') {
        auto code = m_file.read(&currentSymbol, sizeof(char));
        if (code <= 0)
            return false;
    }

    //Читаем тип. Находим первый пробел между ним и < - название типа
    QString type;
    while (currentSymbol != ' ') {
        auto code = m_file.read(&currentSymbol, sizeof(char));
        if (code <= 0)
            return false;
        if (!isspace(currentSymbol))
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
        } while (isspace(currentSymbol));

        if (currentSymbol == '>') //Конец
            break;

        //Читаем атрибуты
        {
            QString name;
            QString value;

            //Сначало имя
            while (currentSymbol != '=') {
                name += currentSymbol; //Обязательно вначале. 1 символ уже считан.
                auto code = m_file.read(&currentSymbol, sizeof(char));
                if (code <= 0 || currentSymbol == ' ')
                    return false;
            }
            //Читаем "
            auto code = m_file.read(&currentSymbol, sizeof(char));
            if (code <= 0 || currentSymbol != '"')
                return false;

            //Читаем первый символ после "
            code = m_file.read(&currentSymbol, sizeof(char));
            if (code <= 0)
                return false;

            //Читаем значения до "
            while (currentSymbol != '"') {
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

    m_file.write("<");
    m_file.write(obj.getType().toUtf8());
    m_file.write(" ");

    for (unsigned i = 0; i < obj.m_attributes.size(); i++) {
        auto att = obj.m_attributes.at(i);
        m_file.write(att.name.toUtf8());
        m_file.write("=\"");
        m_file.write(att.value.toUtf8());
        m_file.write("\" ");
    }

    m_file.write(">\n");
    return true;
}

bool DataFile::isNull()
{
    return !m_file.isOpen() || !validateFileStructure();
}

bool DataFile::validateFileStructure()
{
    if (!m_file.isOpen())
        return false;
    startOver();
    //Просто считаем некоторые характеристики без подробного анализа.
    qint64 code = 0;
    char currentChar = '\0';

    unsigned countOfOpen = 0, countOfClose = 0;

    while (code == 0) {
        code = m_file.read(&currentChar, sizeof(char));
        if (currentChar == '<')
            countOfOpen++;
        if (currentChar == '>')
            countOfClose++;
    }

    startOver();

    if (countOfOpen != countOfClose)
        return false;
    return true;
}
