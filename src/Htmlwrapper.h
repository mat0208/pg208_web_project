#ifndef HTMLWRAPPER_H
#define HTMLWRAPPER_H

#include <QObject>
#include <QStringList>



class HtmlWrapper
{
public:
    HtmlWrapper();
    unsigned int code;
    QByteArray page;
    QByteArray fileContent;
    QStringList directories;
    QStringList files;
    QStringList pictures;
    QString errorMsg;

    void buildPage();
    void clearLists();
};


#endif // HTMLWRAPPER_H
