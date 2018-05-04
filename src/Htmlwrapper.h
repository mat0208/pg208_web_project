#ifndef HTMLWRAPPER_H
#define HTMLWRAPPER_H

#include <QObject>
#include <QStringList>
#include "Statistics.h"


class HtmlWrapper
{
public:
    HtmlWrapper();
    unsigned int code;
    QByteArray mainPage;
    QByteArray statsPage;
    QByteArray infosPage;
    QByteArray fileContent;
    QStringList directories;
    QStringList files;
    QStringList pictures;
    QString errorMsg;

    Statistics stats;

    void buildMainPage();
    void buildStatsPage();
    void clearLists();
};


#endif // HTMLWRAPPER_H
