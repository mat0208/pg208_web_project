#include "Htmlwrapper.h"

HtmlWrapper::HtmlWrapper()
{
}

void HtmlWrapper::buildMainPage(){
    switch( code ){
    case 200:
        mainPage += "HTTP/1.1";
        mainPage += " 200 ";
        mainPage += "OK\r\n\r\n";
        break;
    case 403:
        errorMsg = " ERROR 403 : FORBIDDEN ACCESS ";
        mainPage += "HTTP/1.1";
        mainPage += " 403 ";
        mainPage += "FORBIDDEN\r\n\r\n";
        break;
    case 404:
        errorMsg = " ERROR 404 : UNKNOWN FILE OR DIRECTORY ";
        mainPage += "HTTP/1.1";
        mainPage += " 404 ";
        mainPage += "NOT FOUND\r\n\r\n";
        break;
    case 503:
        errorMsg = " ERROR 503 : SERVICE UNAVAILABLE ";
        mainPage += "HTTP/1.1";
        mainPage += " 503 ";
        mainPage += "SERVICE UNAVAILABLE\r\n\r\n";
        break;
    default:
        errorMsg = " ERROR 500 : INTERNAL ERROR ";
        mainPage += "HTTP/1.1";
        mainPage += " 500 ";
        mainPage += "INTERNAL ERROR\r\n\r\n";
        break;
    }
    mainPage += "<!DOCTYPE HTML>";
    mainPage += "<html>\n";
    if( errorMsg.isEmpty() ){
        mainPage += " <body>\n";
        if( fileContent.isEmpty() ){
            mainPage += "<table>\n";
            mainPage += "<tr><th colspan=\"5\"><hr></th></tr>\n";
            for( int i = 0; i < directories.size(); i++ ){
                mainPage += "<tr><td valign=\"top\"><td><a href=\"";
                mainPage += directories.at( i );
                mainPage += "/\">";
                mainPage += directories.at( i );
                mainPage += "/</a></td>\n";
            }
            for( int i = 0; i < files.size(); i++ ){
                mainPage += "<tr><td valign=\"top\"><td><a href=\"";
                mainPage += files.at( i );
                mainPage += "\">";
                mainPage += files.at( i );
                mainPage += "</a></td>\n";
            }
            mainPage += "<tr><th colspan=\"5\"><hr></th></tr>\n";
            mainPage += "</table>\n";
        } else{
            mainPage += "<tr><th colspan=\"5\"><hr></th></tr>\n";
            mainPage += fileContent;
            mainPage += "<tr><th colspan=\"5\"><hr></th></tr>\n";
        }
    } else{
        mainPage += "<head>\n";
        mainPage += "<title>";
        mainPage += errorMsg;
        mainPage += "</title>";
        mainPage += "</head>\n";
        mainPage += "<body>\n";
        mainPage += "<h1>";
        mainPage += errorMsg;
        mainPage += "</h1>\n";
    }
    mainPage += "<address>(Ubuntu) Server at 192.168.1.64 Port 8080</address>\n";
    mainPage += "</body>\n";
    mainPage += "</html>\n";

    clearLists();
}

void HtmlWrapper::clearLists(){
    files.clear();
    fileContent.clear();
    directories.clear();
    pictures.clear();
    errorMsg.clear();
}

void HtmlWrapper::buildStatsPage(){
    statsPage += "HTTP/1.1";
    statsPage += " 200 ";
    statsPage += "OK\r\n\r\n";

    statsPage += "<!DOCTYPE html>\
                  <html>\
                  <head>\
                  <style>table {\
                    width:100%;\
                  }\
                  table, th, td {\
                      border: 1px solid black;\
                      border: 1px solid black;\
                  }\
                  th, td {\
                      padding: 15px;\
                      text-align: left;\
                  }\
                  table#t01 tr:nth-child(even) {\
                      background-color: #eee;\
                  }\
                  table#t01 tr:nth-child(odd) {\
                     background-color: #fff;\
                  }\
                  table#t01 th {\
                      background-color: black;\
                      color: white;\
                  }\
                  </style>\
                  </head>\
                  <body>";
    statsPage += "<h1>Server Statistics</h1>";
    statsPage += "<h2>Miscellaneous</h2>";

    statsPage += "<table id=\"t01\">\
                  <tr>\
                    <th>Type</th>\
                    <th>Number</th> \
                  </tr>";
    statsPage += "<tr>\
                    <td>Received Requests</td>\
                    <td>";
    statsPage +=    QString::number( stats.nbReceivedRequests );
    statsPage += "  </td>\
                  </tr>";
    statsPage += "<tr>\
                    <td>Treated Requests</td>\
                    <td>";
    statsPage +=    QString::number( stats.nbTreatedRequests );
    statsPage += "  </td>\
                  </tr>";
    statsPage += "<tr>\
                    <td>Connected Clients</td>\
                    <td>";
    statsPage +=    QString::number( stats.nbConnectedClients );
    statsPage += "  </td>\
                  </tr>";
    statsPage += "<tr>\
                    <td>Received Bytes</td>\
                    <td>";
    statsPage +=    QString::number( stats.nbReceivedBytes );
    statsPage += "  </td>\
                  </tr>";
    statsPage += "<tr>\
                    <td>Transmitted Bytes</td>\
                    <td>";
    statsPage +=    QString::number( stats.nbTransmittedBytes );
    statsPage += "  </td>\
                  </tr>";
    statsPage += "</table>\
                    <h2>Errors</h2>\
                      <table id=\"t01\">\
                        <tr>\
                          <th>Type</th>\
                          <th>Number</th>\
                        </tr>\
                        <tr>\
                          <td>404 unknown file or directory</td>\
                          <td>";
    statsPage +=          QString::number( stats.nb404Errors );
    statsPage += "        </td>\
                        </tr>\
                        <tr>\
                          <td>503 service unavailable</td>\
                          <td>";
    statsPage +=          QString::number( stats.nb503Errors );
    statsPage += "        </td>\
                        </tr>\
                      </table>";
    statsPage += "          <h2>Requests</h2>\n";
    statsPage += "          <ol type=\"1\">\n";
    for( int i = 0; i < stats.receivedRequests.size(); i++ ){
        statsPage += "<li>";
        statsPage += stats.receivedRequests.at( i );
        statsPage += "</li>\n";
    }
    statsPage += "</ol>";


    statsPage += "<form action=\"\" method=\"post\">\
                  First name:<br>\
                  <input type=\"password\" name=\"psw\">\
                  <br>\
                  <input type=\"submit\">\
                  </form>";



    statsPage += "  </body>\n";
    statsPage += "</html>\n";
}
