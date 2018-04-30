#include "Response.h"


Response::Response()
{
}


DirectoryResponse::DirectoryResponse()
{
}

void DirectoryResponse::listDir( QDir dir, MySocketClient *client )
{
    dir.setFilter( dir.Dirs );
    dirList = dir.entryList();
    cout << dirList.size() << endl;
    for (int i = 0; i < dirList.size(); ++i){
        client->htmlResponse->directories += dirList.at(i);
    }

    dir.setFilter( dir.Files );
    dirList = dir.entryList();
    cout << dirList.size() << endl;
    for (int i = 0; i < dirList.size(); ++i){
        client->htmlResponse->files += dirList.at(i);
    }
}


FileResponse::FileResponse()
{
}


void FileResponse::readFile(QFile *file, MySocketClient *client)
{
    client->htmlResponse->fileContent += file->readAll();
}

ErrorResponse::ErrorResponse()
{
}

void ErrorResponse::printError( unsigned int errorType, MySocketClient *client  )
{
    if( errorType == 404 ){
        client->htmlResponse->errorMsg = "ERROR 404 : UNKNOWN FILE OR DIRECTORY\n";
    }
}
