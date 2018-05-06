#ifndef HTMLWRAPPER_H
#define HTMLWRAPPER_H

#include <QObject>
#include <QStringList>
#include "Statistics.h"
#include "mylib.h"


class HtmlWrapper
{
public:
    HtmlWrapper();
    unsigned int code;
    QByteArray page;
    QByteArray infosPage;
    QByteArray fileContent;
    QStringList directories;
    QStringList files;
    QStringList pictures;
    QString errorMsg;

    Statistics stats;
    pageType type;

    bool pswRight;

    void buildPage();

private:
    void buildMainPage();
    void buildStatsPage();
    void buildAuthPage();
    void clearLists();
};


#endif // HTMLWRAPPER_H
