#ifndef RESPONSE_H
#define RESPONSE_H


#include <iostream>
using namespace std;

#include <QFile>
#include <QDir>
#include <QtNetwork>
#include "MySocketClient.h"


class MySocketClient;


class Response
{
public:
    Response();
};

class DirectoryResponse : public Response
{
public:
    DirectoryResponse();

    QStringList dirList;

    void listDir( QDir dir, MySocketClient *client );

};

class FileResponse : public Response
{
public:
    FileResponse();

    void readFile( QFile *file, MySocketClient *client );

};

class ErrorResponse : public Response
{
public:
    ErrorResponse();

    void printError( unsigned int errorType, MySocketClient *client );

};


#endif // RESPONSE_H
