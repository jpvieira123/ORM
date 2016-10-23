/**
 * orm.cpp
 *
 *  Copyright 2016 by Joao Pedro Vieira Pereira Silva <jpvieirapereira@hotmail.com>
 *  Copyright 2015 by Victor Vieira Pereira Silva <victordoctorx@hotmail.com>
 *  Copyright 2014 by Marco Bueno <bueno.marco@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later.
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 */

#ifndef ORM_H
#define ORM_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlResult>
#include <QTime>
#include <QDate>
#include <QString>
#include <QDebug>

typedef enum ORMAttrType_en
{
    ATTR_QString    = 0x01,
    ATTR_int        = 0x02,
    ATTR_double     = 0x03,
    ATTR_bool       = 0x04,
    ATTR_QDate      = 0x05,
    ATTR_QTime      = 0x06,
    ATTR_QChar      = 0x07,
    ATTR_char       = 0x08,
    ATTR_Serial     = 0x09,
}ORMAttrType;

#define _convert_QString(obj)  obj.toString()
#define _convert_int(obj)      obj.toInt()
#define _convert_double(obj)   obj.toDouble()
#define _convert_bool(obj)     obj.toBool()
#define _convert_QDate(obj)    obj.toDate()
#define _convert_QTime(obj)    obj.toTime()
#define _convert_QChar(obj)    obj.toString().at(0)

#define _toString_QString(obj)  obj
#define _toString_int(obj)      QString::number(obj)
#define _toString_double(obj)   QString::number(obj)
#define _toString_bool(obj)     (true == obj) ? "true" : "false"
#define _toString_QDate(obj)    obj.toString("yyyy-MM-dd")
#define _toString_QTime(obj)    obj.toString("hh:mm:ss")
#define _toString_QChar(obj)    QString("%1").arg(obj)

#define IS_STRING_VALUE(attr) ((ATTR_QString == attr->type()) || (ATTR_QDate == attr->type()) || \
                               (ATTR_QTime == attr->type()) || ( ATTR_QChar == attr->type()) || \
                               (ATTR_char  == attr->type()))

#define ATTRIBUTE_CLASS(attrType)\
    class ORMAttribute_##attrType : public ORMAttribute \
    {\
        public: \
            ORMAttrType type() { return ATTR_##attrType; }\
            attrType value() { return _convert_##attrType(m_value); }\
            virtual QString description() { return #attrType; } \
            virtual QString toString() { return _toString_##attrType(value()); }\
    }

class ORMAttribute
{
    public:
        QString fieldName() { return m_fieldName; }
        void setFieldName(QString fieldName) { m_fieldName = fieldName; }
        void setValue(QVariant value) { m_value = value; }
        QVariant value() { return m_value; }

        virtual ORMAttrType type() = 0;
        virtual QString description() = 0;
        virtual QString toString() = 0;
    protected:
        QVariant m_value;
        QString m_fieldName;
        QString m_description;
};

ATTRIBUTE_CLASS(QString);
ATTRIBUTE_CLASS(QDate);
ATTRIBUTE_CLASS(QTime);
ATTRIBUTE_CLASS(QChar);
ATTRIBUTE_CLASS(int);
ATTRIBUTE_CLASS(double);
ATTRIBUTE_CLASS(bool);

#define ORM_DECLARE_ATTRIBUTE(className, attrType, attr)\
    protected:\
        ORMAttribute_##attrType m_##attr;\
    public: \
        attrType get##attr(void) { return m_##attr.value(); }\
        void set##attr(attrType value) { m_##attr.setValue(value); }\
        bool update##attr(attrType value) \
        { \
          m_##attr.setValue(value);\
          QString str = QString("update %1 set %2 = \'%3\' where %4 = \'%5\';") \
                        .arg(tableName()) \
                        .arg(fieldName(#attr)) \
                        .arg(m_##attr.toString().replace("\'", "\'\'"))\
                        .arg(m_primaryKey->fieldName()) \
                        .arg(m_primaryKey->value().toString());\
        QSqlQuery *query;\
        query = new QSqlQuery(getDatabase());\
        int bError = true;\
        if (!query->exec(str)) \
            bError= false;\
         delete query;\
         return bError;\
        }\
        static className##List * findBy##attr(attrType value, QSqlDatabase db = QSqlDatabase::database())\
        {\
           return findByAttribute(#attr, value, db );\
        }



#define ORM_DECLARE_FOREINGKEY(attrType, attrId, obj, objType) \
        protected:\
            ORMAttribute_##attrType m_##attrId;\
            objType * m_##obj;\
        public:\
            attrType get##attrId(void) { return m_##attrId.value(); }\
            void set##attrId(attrType value)\
            {\
               m_##attrId.setValue(value);\
               m_##obj = new objType(database());\
               if(!m_##obj->fillORMByPrimaryKey(value))\
               {\
                 delete m_##obj;\
                 m_##obj = NULL;\
               }\
            }\
            objType* get##obj() { set##attrId(m_##attrId.value()); return m_##obj; } \
            void set##obj(objType* _obj)\
            {\
                   m_##obj = _obj;\
            }\
            bool update##attrId(attrType value) \
            { \
              m_##attrId.setValue(value);\
              QString str = QString("update %1 set %2 = \'%3\' where %4 = \'%5\';") \
                            .arg(tableName()) \
                            .arg(fieldName(#attrId)) \
                            .arg(m_##attrId.toString())\
                            .arg(m_primaryKey->fieldName()) \
                            .arg(m_primaryKey->value().toString());\
                QSqlQuery *query;\
                query = new QSqlQuery(getDatabase());\
                int bError = true;\
                if (!query->exec(str)) \
                    bError= false;\
                 delete query;\
                 return bError; \
            }

#define ORM_DEFAULT_CONSTRUCTOR(className, _tableName) \
        public: \
            className(QSqlDatabase db = QSqlDatabase::database()) : ORM()\
            {\
                mapFields(); \
                m_tableName = _tableName; \
                m_database = db;\
            } \
            static QSqlDatabase database() { return m_database; } \
            QSqlDatabase getDatabase() { return className::database(); } \


#define ORM_SETQUERY(sqlqueryORM, query) \
            sqlqueryORM->setQuery(QSqlQuery(query, database()));

#define ORM_SETQUERY_DATABASE(sqlqueryORM, query, database) \
                sqlqueryORM->setQuery(QSqlQuery(query, database));

#define ORM_STATIC_METHODS(_className, _tableName) \
        protected: QString className() { return QString::fromUtf8(#_className); } \
        public: static QSqlDatabase m_database; \
        public: static QString tableName() { return _tableName; }\
        public: static QString fieldName(QString attrName) { return m_fieldMap[attrName]; }\
        public: static bool fillORMList(_className##List* _lst, QString query, QSqlDatabase db = QSqlDatabase::database()) {\
            QSqlQueryModel *ORM = new QSqlQueryModel();\
            ORM_SETQUERY_DATABASE(ORM, query, db) \
            if (ORM->rowCount() <= 0) { delete ORM; return false; }\
            for (int i=0; i < ORM->rowCount(); i++) {\
                _className* obj = new _className();\
                obj->fillORM(ORM->record(i));\
                _lst->append(obj);\
            } delete ORM;\
            return true;\
        }\
        public: static bool deleteAll(QSqlDatabase db = QSqlDatabase::database()) { \
                QSqlQuery *query; \
                query = new QSqlQuery(db);\
                bool ret = query->exec(QString("delete from %1").arg(_tableName));\
                delete query; \
                return ret; \
        }\
        public: static void ReleaseList(_className##List *plist)\
        {\
            if( NULL == plist )\
                return;\
        \
            ORM_CLEAN_LIST(_className, plist);\
            delete plist;\
        }\
        public: static _className##List* findAll(QSqlDatabase db = QSqlDatabase::database())\
        {\
            _className##List *obj = new _className##List();\
            QString query = QString("select * from %1 ")\
                      .arg(_className::tableName());\
            if (!_className::fillORMList(obj,query, db)) { delete obj; obj = NULL; } \
            return obj;\
        }\
        public: static _className##List* findBy(QString Join, QString Where, QSqlDatabase db = QSqlDatabase::database())\
        {\
            _className##List *obj = new _className##List();\
            QString query = QString("select * from %1 %2 %3 ")\
                      .arg(_className::tableName())\
                      .arg(Join)\
                      .arg(Where);\
            if (!_className::fillORMList(obj,query, db)) { delete obj; obj = NULL; } \
            return obj;\
        }\
        public: static _className##List* findByAttribute(QString attrName, QVariant value, QSqlDatabase db = QSqlDatabase::database())\
        {\
             ORMAttribute *ORMattribute = NULL;\
            _className *obj = new _className(db);\
            foreach(ORMAttribute *mattr, obj->m_attrList)\
            {\
            if( mattr->fieldName().toLower() == attrName.toLower())\
            {\
                ORMattribute = mattr;\
                break;\
            }\
            }\
            if( NULL == ORMattribute)\
            {\
                delete obj;\
                return NULL;\
            }\
            _className##List *lst = new _className##List();\
            QString query = QString("select * from %1 where %2 = %3")\
                      .arg(_className::tableName())\
                      .arg(_className::fieldName(attrName))\
                      .arg(IS_STRING_VALUE(ORMattribute)? "'"+value.toString()+"'":value.toString());\
            delete obj;\
            if (!_className::fillORMList(lst,query, db )) { delete lst; lst = NULL; } \
            return lst;\
        }\
        public: static _className* findByPrimaryKey(QVariant primaryKey,QSqlDatabase db = QSqlDatabase::database())\
        {\
            _className *obj = new _className(db);\
            if (!obj->fillORMByPrimaryKey(primaryKey))\
            {\
                delete obj;\
                obj = NULL;\
            }\
            return obj;\
        } \
        public: void mapFields();

#define ORM_DYNAMIC_METHODS(_className, _tableName) \
    public: bool fillORMFromQuery(QString query) {\
        QSqlQueryModel *ORM = new QSqlQueryModel();\
        ORM_SETQUERY(ORM, query) \
        if (ORM->rowCount() <= 0) { delete ORM; return false; }\
        fillORM(ORM->record(0));\
        delete ORM;\
        return true;\
    }\
    public: bool fillORMByPrimaryKey(QVariant primaryKey)\
    {\
        QString query = QString("select * from %1 where %2 = %3")\
                        .arg(m_tableName)\
                        .arg(m_primaryKey->fieldName())\
                        .arg(primaryKey.toString());\
        QSqlQueryModel *ORM = new QSqlQueryModel();\
        ORM_SETQUERY(ORM, query) \
        if (ORM->rowCount() <= 0) { delete ORM; return false; }\
        fillORM(ORM->record(0));\
        delete ORM;\
        return true;\
    }\


#define ORM_BEGIN_MAP(className) \
            QSqlDatabase className::m_database; \
            void className::mapFields() {

#define ORM_MATCH_TABLE(className, _tableName)\
        ORM_DEFAULT_CONSTRUCTOR(className, _tableName) \
        ORM_STATIC_METHODS(className, _tableName)\
        ORM_DYNAMIC_METHODS(className, _tableName)


#define ORM_MAP_FIELD(attr, _fieldName)\
            m_##attr.setFieldName(_fieldName);\
            ORM::InitAttribute(&m_##attr);\
            m_attrList.append(&m_##attr);\
            m_fieldMap[#attr] = _fieldName;

#define ORM_MAP_PRIMARYKEY(attr, _fieldName)\
            m_##attr.setFieldName(_fieldName);\
            m_attrList.append(&m_##attr);\
            m_fieldMap[#attr] = _fieldName;\
            m_primaryKey = &m_##attr;\
            m_primaryKey->setValue(0);

#define ORM_END_MAP() };

#define DECLARE_ORM(className)\
            class className;\
            typedef QList<className*> className##List;

#define DECLARE_CLASS(className)\
            class className : public ORM\
            {


#define ORM_INIT_LIST(className, _list)\
            if (NULL == _list) _list = new className##List(); \
            foreach(className* obj, *_list) delete obj;\
            _list->clear();

#define ORM_CLEAN_LIST(className, _list) \
            foreach(className* obj, *_list) delete obj;\
            _list->clear();


class ORM
{
public:
    ORM();
    virtual ~ORM() {}

    QString fieldName(QString attribute);
    QSqlError lastError();
    virtual void mapFields() = 0;
    virtual QSqlDatabase getDatabase() = 0;

    virtual bool Save();
    virtual bool Create();
    virtual bool Update();
    virtual bool Delete();
    void setLastError(QSqlError error);

    bool refresh();
    int  lastInsertId();

    void copyFrom(ORM* ORM);

    QList<ORMAttribute*> attributes();

    static void InitAttribute(ORMAttribute *attr);
protected:
    virtual QString className() = 0;
protected:
    QString                 m_tableName;
    QList<ORMAttribute*>  m_attrList;
    ORMAttribute*         m_primaryKey;
    static QMap<QString, QString> m_fieldMap;
    QSqlError m_lastError;
    QString CreateFieldTxt( ORMAttribute *attr );
    void CreateTable();
    void EnsureFieldsExist();
    void fillORM(QSqlRecord record);

    bool do_insert();
    bool do_update();
    bool do_delete();

};

#endif // ORM_H
