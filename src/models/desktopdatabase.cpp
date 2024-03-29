#include <QDebug>
#include "desktopdatabase.h"

DesktopDatabase *DesktopDatabase::desktopDatabaseInstance = NULL;

DesktopDatabase::DesktopDatabase(QObject *parent) :
    QObject(parent)
{
    settings = new QSettings("MeeGo", "meego-tablet-components", this);
    db = settings->value("desktops", QHash<QString, QVariant>()).toHash();
}

DesktopDatabase *DesktopDatabase::instance()
{
    if (!desktopDatabaseInstance)
        desktopDatabaseInstance = new DesktopDatabase;

    return desktopDatabaseInstance;
}

int DesktopDatabase::getRow(QString filename)
{
    if (!db.contains(filename + ":row"))
        return -1;

    return db[filename + ":row"].toInt();
}

void DesktopDatabase::setRow(QString filename, int row)
{
    db[filename + ":row"].setValue(row);
    settings->setValue("desktops", db);
}

int DesktopDatabase::getColumn(QString filename)
{
    if (!db.contains(filename + ":column"))
        return -1;

    return db[filename + ":column"].toInt();
}

void DesktopDatabase::setColumn(QString filename, int column)
{
    db[filename + ":column"].setValue(column);
    settings->setValue("desktops", db);
}

int DesktopDatabase::getPage(QString filename)
{
    if (!db.contains(filename + ":page"))
        return -1;

    return db[filename + ":page"].toInt();
}

void DesktopDatabase::setPage(QString filename, int page)
{
    db[filename + ":page"].setValue(page);
    settings->setValue("desktops", db);
}
