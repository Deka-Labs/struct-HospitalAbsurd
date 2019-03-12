#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "statuscodes.hpp"
#include <stdexcept>

class IHashKey {
public:
    virtual ~IHashKey() {}

    virtual unsigned hash() const = 0;
    virtual unsigned dopHash() const = 0;
    virtual bool validateKey() const = 0;
    virtual bool operator==(const IHashKey& other) const = 0;
};

/**
 * \brief HashTable класс, реализующий хэш таблицу
 * \pre TypeData должен быть НЕ указателем
 * \pre Класс TypeData должен иметь метод key() const, возвращающий наследуемый от IHashKey объект;
 * \pre Класс TypeData должен иметь конструктор копирования и копирующий оператор =
 */
template <class TypeData>
class HashTable {
    TypeData** m_dataArray;
    unsigned m_maxSize;

public:
    explicit HashTable(const unsigned maxSize);
    HashTable(const HashTable&) = delete;
    ~HashTable();

    StatusCodes add(const TypeData& data);
    bool get(const IHashKey& key, TypeData* dataToAssign = nullptr) const;
    void del(const IHashKey& key);

private:
    bool getEmptyCellFor(const IHashKey& key, unsigned* outPos = nullptr) const;
    bool getCell(const IHashKey& key, unsigned* outPos = nullptr) const;
};

template <class TypeData>
HashTable<TypeData>::HashTable(const unsigned maxSize)
    : m_dataArray(nullptr)
    , m_maxSize(maxSize)
{
    m_dataArray = new TypeData*[maxSize];
    for (unsigned pos = 0; pos < m_maxSize; pos++) {
        m_dataArray[pos] = nullptr;
    }
}

template <class TypeData>
HashTable<TypeData>::~HashTable()
{
    for (unsigned pos = 0; pos < m_maxSize; pos++) {
        if (m_dataArray[pos]) {
            delete m_dataArray[pos];
            m_dataArray[pos] = nullptr;
        }
    }

    delete[] m_dataArray;
}

template <class TypeData>
StatusCodes HashTable<TypeData>::add(const TypeData& data)
{
    unsigned cell = 0;

    if (getCell(data.key()))
        return StatusCode_AlreadyExist;

    if (getEmptyCellFor(data.key(), &cell)) {
        m_dataArray[cell] = new TypeData(data);
        return StatusCode_OK;
    } else {
        return StatusCode_Overloaded;
    }
}

template <class TypeData>
bool HashTable<TypeData>::get(const IHashKey& key, TypeData* dataToAssign) const
{
    unsigned cell = 0;

    if (getCell(key, &cell)) {
        if (dataToAssign)
            *dataToAssign = *m_dataArray[cell];
        return true;
    } else {
        return false;
    }
}

template <class TypeData>
void HashTable<TypeData>::del(const IHashKey& key)
{
    unsigned cell = 0;

    if (getCell(key, &cell)) {
        delete m_dataArray[cell];
        m_dataArray[cell] = nullptr;
    }
}

template <class TypeData>
bool HashTable<TypeData>::getEmptyCellFor(const IHashKey& key, unsigned* outPos) const
{
    if (!key.validateKey())
        return false;

    unsigned first = key.hash();
    unsigned delta = key.dopHash();

    if (first >= m_maxSize)
        throw std::runtime_error("Invalid hash function : Out of range");
    if (delta >= m_maxSize)
        throw std::runtime_error("Invalid dopHash function : Out of range");
    if (delta == 0)
        throw std::runtime_error("Invalid dopHash function : Delta is 0");

    unsigned pos = 0;
    for (pos = first; pos < m_maxSize; pos += delta) {
        if (!m_dataArray[pos]) {
            if (outPos)
                *outPos = pos;
            return true;
        }
    }

    pos %= m_maxSize;

    for (; pos < first; pos += delta) {
        if (!m_dataArray[pos]) {
            if (outPos)
                *outPos = pos;
            return true;
        }
    }

    return false;
}

template <class TypeData>
bool HashTable<TypeData>::getCell(const IHashKey& key, unsigned* outPos) const
{
    if (!key.validateKey())
        return false;

    unsigned first = key.hash();
    unsigned delta = key.dopHash();

    if (first >= m_maxSize)
        throw std::runtime_error("Invalid hash function : Out of range");
    if (delta >= m_maxSize)
        throw std::runtime_error("Invalid dopHash function : Out of range");
    if (delta == 0)
        throw std::runtime_error("Invalid dopHash function : Delta is 0");

    unsigned pos = 0;
    for (pos = first; pos < m_maxSize; pos += delta) {
        if (m_dataArray[pos] && key == m_dataArray[pos]->key()) {
            if (outPos)
                *outPos = pos;
            return true;
        }
    }

    pos %= m_maxSize;

    for (; pos < first; pos += delta) {
        if (m_dataArray[pos] && key == m_dataArray[pos]->key()) {
            if (outPos)
                *outPos = pos;
            return true;
        }
    }

    return false;
}

#endif // HASHTABLE_HPP
