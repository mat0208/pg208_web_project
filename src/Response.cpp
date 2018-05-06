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
        client->htmlWrap->directories += dirList.at(i);
    }

    dir.setFilter( dir.Files );
    dirList = dir.entryList();
    cout << dirList.size() << endl;
    for (int i = 0; i < dirList.size(); ++i){
        client->htmlWrap->files += dirList.at(i);
    }
    client->htmlWrap->code = 200;
}


FileResponse::FileResponse()
{
}


void FileResponse::readFile(QFile *file, MySocketClient *client)
{
    client->htmlWrap->fileContent += file->readAll();
    client->htmlWrap->code = 200;
}

ErrorResponse::ErrorResponse()
{
}

void ErrorResponse::printError( unsigned int errorType, MySocketClient *client  )
{
    if( errorType == 404 ){
        client->htmlWrap->code = 404;
    }
}
