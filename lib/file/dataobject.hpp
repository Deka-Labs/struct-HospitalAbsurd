#ifndef DATAOBJECT_HPP
#define DATAOBJECT_HPP

#include "../data/twowaylist.hpp"
#include <QString>

class DataFile;

class DataObject {
private:
    struct info {
        QString name;
        QString value;
    };

    QString m_type;
    TwoWayList<info> m_attributes;

public:
    DataObject(const QString& getType = "Unknown");
    DataObject(const DataObject&);

    void setType(const QString& getType);
    QString getType() const;

    void setValue(const QString& name, const QString& value);
    bool getValue(const QString& name, QString& out_value) const;

    bool containsAttribute(const QString& name, unsigned& out_pos) const;

    void delAttribute(const QString& name);

    friend class DataFile;
};

#endif // DATAOBJECT_HPP
