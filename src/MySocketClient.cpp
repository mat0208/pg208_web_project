/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the example classes of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/
#include "MySocketClient.h"

#include <QtNetwork>
#include <sstream>


MySocketClient::MySocketClient(int socketDescriptor, QObject *parent, DirectoryResponse *dirResp,
                               FileResponse *fileResp, ErrorResponse *errorResp,
                               HtmlWrapper *htmlResp, Statistics *stats, bool *serverAvailable)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
    dirResponse    = dirResp;
    fileResponse   = fileResp;
    errorResponse  = errorResp;
    htmlWrap       = htmlResp;
    statistics     = stats;
    pagesAvailable = serverAvailable;
}

inline string removeEndLine(string s){
        while( s.at(s.length()-1) == '\r' ||
                        s.at(s.length()-1) == '\n' ){
                s = s.substr(0, s.length()-1);
        }
        return s;
}

void MySocketClient::run()
{
    cout << "Starting MySocketClient::run()" << endl;

    statistics->nbReceivedRequests ++;

    QTcpSocket tcpSocket;

    // ON RECUPERE LE LIEN DE COMMUNICATION AVEC LE CLIENT ET ON QUITTE EN CAS
    // DE PROBLEME...
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    // SI LE CLIENT N'A PAS EU LE TEMPS DE NOUS TRANSMETTRE SA REQUETE,
    // ON SE MET EN ATTENTE PENDANT 1s
    while (tcpSocket.bytesAvailable() < (int)sizeof(quint16)) {
        if (!tcpSocket.waitForReadyRead( 1000 )) {
                cout << "(EE) Erreur de time out !" << endl;
                return;
        }
    }

    // LA PREMIERE REQUETE CORRESPOND AU GET NORMALEMENT
    char tampon[65536];

    // ON RECUPERE LA REQUETE ET SA TAILLE
    int lineLength = tcpSocket.read( tampon, 65536 );
    statistics->nbReceivedBytes += lineLength;

    // ON TRANSFORME LA REQUETE SOUS FORME DE STRING
    // ET ON RECUPERE LA PREMIERE LIGNE ==> COMMANDE
    string ligne( tampon );
    string command;
    istringstream tmp( ligne );
    getline( tmp, command );
    command = removeEndLine( command );

    // ON AFFICHE LA COMMANDE A L'ECRAN...
    cout << "COMMANDE : =>" << command << "<=" << endl;

    statistics->receivedRequests << QString::fromStdString( command );

    // ON GERE LA RECEPTION D'UN MOT DE PASSE ie ON TESTE SI LA
    // METHODE HTTP UTILISEE POUR L'ENVOI DES DONNEES EST POST
    size_t methodPos = command.find( ' ' );
    if( !( command.substr( 0, methodPos ).compare( "POST" ) ) ){
        size_t pswPos = ligne.find( "psw=" );
        string psw = ligne.substr( pswPos + 4 );
        if( psw == "admin" ){
            htmlWrap->pswRight = true;
        } else{
            htmlWrap->pswRight = false;
            htmlWrap->errorMsg = QString::fromStdString( "Incorrect password" );
            htmlWrap->type = mainPage;
        }
    }

   int pos1 = command.find(" ");
   string cmde = command.substr(0, pos1);
   command = command.substr(pos1+1, command.length()-pos1);

   //cout << "1. : " << cmde  << endl;
   //cout << "2. : " << ligne << endl;

   int pos2 = command.find(" ");
   string filename = command.substr(0, pos2);
   command = command.substr(pos2+1, command.length()-pos2);

   //cout << "3. : " << filename  << endl;
   //cout << "4. : '" << ligne << "'" << endl;

       /* while( tcpSocket.bytesAvailable() > 0 ){
        int lineLength = tcpSocket.readLine(tampon, 65536);
        if (lineLength != -1 &&  lineLength != 0) {
                //cout << "C" << lineLength << " :: " << tampon;
        }else if(lineLength != -1 ){
                cout << "Nothing for the moment !" << endl;
        }
    }*/

   QString str = tr("/home/mat0208lt/Desktop/http_server/pg208_web_project/public_html") + tr(filename.c_str());
   QFile f( str );
   QDir  d( str );

   cout << " - Chemin du fichier : " << str.toStdString() << endl;
   cout << " - isFile :          : " << f.exists() << endl;
   cout << " - isDirectory       : " << d.exists() << endl;

   if( f.exists() == false &&  d.exists() == false ){
       errorResponse->printError( 404, this );
       htmlWrap->type = mainPage;
       statistics->nb404Errors ++;
   }else if( d.exists() == true ){
       if( !filename.compare( "/private/" ) && !( htmlWrap->pswRight ) ){
           htmlWrap->type = authPage;
       } else if( !filename.compare( "/private/" ) && htmlWrap->pswRight ){
           htmlWrap->pswRight = false;
           dirResponse->listDir( d, this );
           htmlWrap->type = mainPage;
       } else if( *pagesAvailable || !filename.compare( "/" ) ){
           dirResponse->listDir( d, this );
           htmlWrap->type = mainPage;
       } else{
           htmlWrap->code = 503;
           htmlWrap->type = mainPage;
           statistics->nb503Errors ++;
       }

   }else if( f.exists() == true ){
        if( !filename.compare( "/private/desactivate.html" ) ){
            *pagesAvailable = false;
            htmlWrap->errorMsg = "Server disabled";
            htmlWrap->type = mainPage;
        } else if( !filename.compare( "/private/activate.html" ) ){
            *pagesAvailable = true;
            htmlWrap->errorMsg = "Server enabled";
            htmlWrap->type = mainPage;
        } else if( !filename.compare( "/private/statistics.html" ) ){
            htmlWrap->stats = *statistics;
            htmlWrap->type = statsPage;
        }
        if( *pagesAvailable ){
            QFile* file = new QFile( str );
             if (!file->open(QIODevice::ReadOnly))
             {
                     delete file;
                     return;
             }
            fileResponse->readFile( file, this );
            file->close();
        } else if( filename.compare( "/private/statistics.html" ) ){
            htmlWrap->type = mainPage;
        } else{
            htmlWrap->code = 503;
            htmlWrap->type = mainPage;
            statistics->nb503Errors ++;
        }
   }


   /*if( !filename.compare( "/private/statistics.html" ) ){
       htmlWrap->stats = *statistics;
       htmlWrap->buildStatsPage();
       statistics->nbTransmittedBytes += tcpSocket.write( htmlWrap->statsPage );
       htmlWrap->statsPage.clear();
   } else{
       htmlWrap->buildMainPage();
       statistics->nbTransmittedBytes += tcpSocket.write( htmlWrap->mainPage );
       htmlWrap->mainPage.clear();
   }*/

   htmlWrap->buildPage();
   statistics->nbTransmittedBytes += tcpSocket.write( htmlWrap->page );
   htmlWrap->page.clear();

   tcpSocket.disconnectFromHost();
   tcpSocket.waitForDisconnected();
   cout << "Finishing MySocketClient::run()" << endl;
}
//! [4]
