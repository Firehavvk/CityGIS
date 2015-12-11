#pragma once
#ifndef GISDATABASE
#define GISDATABASE

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QDebug>
#include <QCryptographicHash>
#include <QTextCodec>

class gisDatabase
{
private:
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlQueryModel model;
    QSqlRecord rec;
    QString connName;

public:
    gisDatabase(){}
    ~gisDatabase(){qDebug() << "gisDatabase destructor launched";}

    void connect(QString databasePath)
    {
        db = QSqlDatabase::addDatabase("QSQLITE","gisDB");
        db.setDatabaseName(databasePath);
        if (!db.open()) qDebug() << "open database: ERROR"; else qDebug() << "open database: OK";
        query = new QSqlQuery(db);
    }
    void disconnect()
    {
        db.close();
        QSqlDatabase::removeDatabase("gisDB");
    }

    //прецеденты
    int addCity(QString cityName)                                      //добавление города в БД
    {
        int cityID;
        QString strF = "SELECT id FROM city WHERE name='%1';";        //проверка существования записи
                strF = strF.arg(cityName);

        query->exec(strF);
        if (query->next()) rec = query->record();
        QString recIsEx = query->value(rec.indexOf("id")).toString();

        if (recIsEx!="") qDebug() << recIsEx <<  "City \""+ cityName +"\" is already exist";
        else
        {                                                               //если записи не существует, добавить
            strF =
            "INSERT INTO city (name) VALUES('%1');";
            strF = strF.arg(cityName);
            if (!query->exec(strF)) qDebug() << "Unable to make insert operation"; else qDebug() << "City \""+ cityName +"\" added";
        }

        strF = "SELECT id FROM city WHERE name='%1';";        //проверка существования записи
        strF = strF.arg(cityName);
        query->exec(strF);
        if (query->next()) rec = query->record();
        cityID = query->value(rec.indexOf("id")).toInt();
        return cityID;
    }
    void deleteCityByID(int cityID)                                     //удаление города из БД
    {
        QString strF =
        "DELETE FROM city WHERE id ='%1';";
        strF = strF.arg(cityID);
        if (!query->exec(strF)) qDebug() << "Unable to make delete operation"; else qDebug() << "City deleted";
    }

    void addUser(QString login,QString pass,QString username,int cityID)//добавление пользователя в БД
    {
        QString strF = "SELECT id FROM users WHERE login='%1';";        //проверка существования записи
                strF = strF.arg(login);
        model.setQuery(strF);

        if (model.rowCount() != 0) qDebug() <<  "User \""+ login +"\" is already exist";
        else
        {                                                               //если записи не существует, добавить
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QByteArray encodedString = codec->fromUnicode(pass);
            QString md5pass = QString(QCryptographicHash::hash((encodedString),QCryptographicHash::Md5).toHex());

            strF =
            "INSERT INTO users (login, pass, name, cityid) VALUES('%1', '%2', '%3', '%4');";
            strF = strF.arg(login)
                       .arg(md5pass)
                       .arg(username)
                       .arg(cityID);
            if (!query->exec(strF)) qDebug() << "Unable to make insert operation"; else qDebug() << "User \""+ login +"\" added";
        }
    }
    void deleteUserByID(int userID)                                     //удаление пользователя из БД
    {
        QString strF =
        "DELETE FROM users WHERE id ='%1';";
        strF = strF.arg(userID);
        if (!query->exec(strF)) qDebug() << "Unable to make delete operation"; else qDebug() << "User deleted";
    }
    bool userIsNotExist(QString usrname)
    {
        QString strF = "SELECT id FROM users WHERE login='%1';";        //проверка существования записи
                strF = strF.arg(usrname);
                query->exec(strF);
                if (query->next()) rec = query->record();
                QString recIsEx = query->value(rec.indexOf("id")).toString();
        return (recIsEx == "");
    }

    void addOrganizationType(QString orgTypeName)                       //добавление типа организации в БД
    {
        QString strF = "SELECT id FROM organizationtype WHERE name='%1';";        //проверка существования записи
                strF = strF.arg(orgTypeName);
        model.setQuery(strF);

        if (model.rowCount() != 0) qDebug() <<  "Organization type \""+ orgTypeName +"\" is already exist";
        else
        {                                                               //если записи не существует, добавить
        strF =
        "INSERT INTO organizationtype (name) VALUES('%1');";
        strF = strF.arg(orgTypeName);
        if (!query->exec(strF)) qDebug() << "Unable to make insert operation"; else qDebug() << "Organization type \""+ orgTypeName +"\" added";
        }
    }
    void deleteOrganizationTypeByID(int orgTypeID)                      //удаление типа организации из БД
    {
        QString strF =
        "DELETE FROM organizationtype WHERE id ='%1';";
        strF = strF.arg(orgTypeID);
        if (!query->exec(strF)) qDebug() << "Unable to make delete operation"; else qDebug() << "Organization type deleted";
    }

    void addOrganization(QString orgName,int orgTypeID)                 //добавление организации в БД
    {
        QString strF = "SELECT * FROM organizationtype WHERE id='%1';"; //проверка существования типа организации
                strF = strF.arg(orgTypeID);
        model.setQuery(strF);
        bool orgTypeExist = (model.rowCount() != 0);

                strF = "SELECT id FROM organization WHERE name='%1';";  //проверка существования организации
                strF = strF.arg(orgName);
        model.setQuery(strF);
        bool organizationNotExist = (model.rowCount() == 0);


        if (orgTypeExist && organizationNotExist)                       //если организации не существует, добавить
        {
            strF =
            "INSERT INTO organization (name,typeid) VALUES('%1','%2');";
            strF = strF.arg(orgName).arg(orgTypeID);
            if (!query->exec(strF)) qDebug() << "Unable to make insert operation"; else qDebug() << "Organization \""+ orgName +"\" added";
        }
        else
        {
            if(!orgTypeExist)         qDebug() <<  "Organization type with id=\"" + QString::number(orgTypeID) + "\" is not exist";
            if(!organizationNotExist) qDebug() <<  "Organization \""+ orgName +"\" is already exist";
        }

    }
    void deleteOrganizationByID(int orgID)                              //удаление организации из БД
    {
        QString strF =
        "DELETE FROM organization WHERE id ='%1';";
        strF = strF.arg(orgID);
        if (!query->exec(strF)) qDebug() << "Unable to make delete operation"; else qDebug() << "Organization deleted";
    }

                                                                        //добавление отдела в БД
    void addDepartment(QString depName,QString depAddress,QString depPhone,int orgID,int cityID)
    {
        QString strF = "SELECT name FROM organization WHERE id='%1';";  //проверка существования организации по id
                strF = strF.arg(orgID);
        model.setQuery(strF);
        bool organizationExist = (model.rowCount() != 0);

                strF = "SELECT name FROM city WHERE id='%1';";          //проверка существования города по id
                strF = strF.arg(cityID);
        model.setQuery(strF);
        bool cityExist = (model.rowCount() != 0);

        if(organizationExist && cityExist)
        {
            strF =
            "INSERT INTO department (name,address,phonenumber,orgid,cityid) VALUES('%1','%2','%3','%4','%5');";
            strF = strF.arg(depName)
                       .arg(depAddress)
                       .arg(depPhone)
                       .arg(orgID)
                       .arg(cityID);
            if (!query->exec(strF)) qDebug() << "Unable to make insert operation"; else qDebug() << "Department \""+ depName +"\" added";
        }
        {
            if (!organizationExist) qDebug() << "Organization with id=\"" + QString::number(orgID) + "\" is not exist";
            if (!cityExist)          qDebug() <<  "City with id=\"" + QString::number(cityID) + "\" is not exist";
        }
    }
    void deleteDepartmentByID(int depID)                                //удаление отдела из БД
    {
        QString strF =
        "DELETE FROM department WHERE id ='%1';";
        strF = strF.arg(depID);
        if (!query->exec(strF)) qDebug() << "Unable to make delete operation"; else qDebug() << "Department deleted";
    }

    void addCityMap(QString mapPath, int cityID)                        //добавление карты в БД
    {
        QString strF = "SELECT id FROM maps WHERE cityid='%1';";        //проверка существования карты по id города
                strF = strF.arg(cityID);
        model.setQuery(strF);
        bool mapNotExist = (model.rowCount() == 0);

                strF = "SELECT name FROM city WHERE id='%1';";          //проверка существования города по id города
                strF = strF.arg(cityID);
        model.setQuery(strF);
        bool cityExist = (model.rowCount() != 0);

        if (mapNotExist && cityExist)                                   //если карты не существует, добавить
        {
            strF =
            "INSERT INTO maps (cityid,path) VALUES('%1','%2');";
            strF = strF.arg(cityID).arg(mapPath);
            if (!query->exec(strF)) qDebug() << "Unable to make insert operation"; else qDebug() << "Map added";
        }
        else
        {
            if(!cityExist)   qDebug() <<  "City with id=\"" + QString::number(cityID) + "\" is not exist";
            if(!mapNotExist) qDebug() <<  "Map is already exist";
        }
    }
    void deleteMapByID(int mapID)                                       //удаление карты из БД
    {
        QString strF =
        "DELETE FROM maps WHERE id ='%1';";
        strF = strF.arg(mapID);
        if (!query->exec(strF)) qDebug() << "Unable to make delete operation"; else qDebug() << "Map deleted";
    }

    void addGeoTag(QString geoTagName, qreal geoTag_x,qreal geoTag_y)   //добавление геометки в БД
    {
        QString strF =
        "INSERT INTO geotag (name,xcoord,ycoord) VALUES('%1','%2','%3');";
        strF = strF.arg(geoTagName).arg(geoTag_x).arg(geoTag_y);
        if (!query->exec(strF)) qDebug() << "Unable to make insert operation"; else qDebug() << "Geotag added";
    }
    void deleteGeoTagByID(int geoTagID)                                 //удаление геометки из БД
    {
        QString strF =
        "DELETE FROM geotag WHERE id ='%1';";
        strF = strF.arg(geoTagID);
        if (!query->exec(strF)) qDebug() << "Unable to make delete operation"; else qDebug() << "Geotag deleted";
    }

    bool accessIsGranted(QString login, QString encr_pass)
    {
        QString strF = "SELECT pass FROM users WHERE login='%1';";        //проверка существования записи
                strF = strF.arg(login);
        query->exec(strF);
        if (query->next()) rec = query->record();
        QString passFromDB = query->value(rec.indexOf("pass")).toString();

        if (encr_pass == passFromDB)
            return true;
    return false;
    }

};

#endif // GISDATABASE

