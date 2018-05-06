#include "Htmlwrapper.h"

HtmlWrapper::HtmlWrapper()
{
    pswRight = false;
}

void HtmlWrapper::buildMainPage(){
    switch( code ){
    case 200:
        page += "HTTP/1.1";
        page += " 200 ";
        page += "OK\r\n\r\n";
        break;
    case 403:
        errorMsg = " ERROR 403 : FORBIDDEN ACCESS ";
        page += "HTTP/1.1";
        page += " 403 ";
        page += "FORBIDDEN\r\n\r\n";
        break;
    case 404:
        errorMsg = " ERROR 404 : UNKNOWN FILE OR DIRECTORY ";
        page += "HTTP/1.1";
        page += " 404 ";
        page += "NOT FOUND\r\n\r\n";
        break;
    case 503:
        errorMsg = " ERROR 503 : SERVICE UNAVAILABLE ";
        page += "HTTP/1.1";
        page += " 503 ";
        page += "SERVICE UNAVAILABLE\r\n\r\n";
        break;
    default:
        errorMsg = " ERROR 500 : INTERNAL ERROR ";
        page += "HTTP/1.1";
        page += " 500 ";
        page += "INTERNAL ERROR\r\n\r\n";
        break;
    }
    page += "<!DOCTYPE HTML>";
    page += "<html>\n";
    if( errorMsg.isEmpty() ){
        page += " <body>\n";
        if( fileContent.isEmpty() ){
            page += "<table>\n";
            page += "<tr><th colspan=\"5\"><hr></th></tr>\n";
            for( int i = 0; i < directories.size(); i++ ){
                page += "<tr><td valign=\"top\"><td><a href=\"";
                page += directories.at( i );
                page += "/\">";
                page += directories.at( i );
                page += "/</a></td>\n";
            }
            for( int i = 0; i < files.size(); i++ ){
                page += "<tr><td valign=\"top\"><td><a href=\"";
                page += files.at( i );
                page += "\">";
                page += files.at( i );
                page += "</a></td>\n";
            }
            page += "<tr><th colspan=\"5\"><hr></th></tr>\n";
            page += "</table>\n";
        } else{
            page += "<tr><th colspan=\"5\"><hr></th></tr>\n";
            page += fileContent;
            page += "<tr><th colspan=\"5\"><hr></th></tr>\n";
        }
    } else{
        page += "<head>\n";
        page += "<title>";
        page += errorMsg;
        page += "</title>";
        page += "</head>\n";
        page += "<body>\n";
        page += "<h1>";
        page += errorMsg;
        page += "</h1>\n";
    }
    page += "<address>(Ubuntu) Server at 192.168.1.64 Port 8080</address>\n";
    page += "</body>\n";
    page += "</html>\n";
}

void HtmlWrapper::clearLists(){
    files.clear();
    fileContent.clear();
    directories.clear();
    pictures.clear();
    errorMsg.clear();
}

void HtmlWrapper::buildStatsPage(){
    page += "HTTP/1.1";
    page += " 200 ";
    page += "OK\r\n\r\n";

    page += "<!DOCTYPE html>\
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
    page += "<h1>Server Statistics</h1>";
    page += "<h2>Miscellaneous</h2>";

    page += "<table id=\"t01\">\
                  <tr>\
                    <th>Type</th>\
                    <th>Number</th> \
                  </tr>";
    page += "<tr>\
                    <td>Received Requests</td>\
                    <td>";
    page +=    QString::number( stats.nbReceivedRequests );
    page += "  </td>\
                  </tr>";
    page += "<tr>\
                    <td>Treated Requests</td>\
                    <td>";
    page +=    QString::number( stats.nbTreatedRequests );
    page += "  </td>\
                  </tr>";
    page += "<tr>\
                    <td>Connected Clients</td>\
                    <td>";
    page +=    QString::number( stats.nbConnectedClients );
    page += "  </td>\
                  </tr>";
    page += "<tr>\
                    <td>Received Bytes</td>\
                    <td>";
    page +=    QString::number( stats.nbReceivedBytes );
    page += "  </td>\
                  </tr>";
    page += "<tr>\
                    <td>Transmitted Bytes</td>\
                    <td>";
    page +=    QString::number( stats.nbTransmittedBytes );
    page += "  </td>\
                  </tr>";
    page += "</table>\
                    <h2>Errors</h2>\
                      <table id=\"t01\">\
                        <tr>\
                          <th>Type</th>\
                          <th>Number</th>\
                        </tr>\
                        <tr>\
                          <td>404 unknown file or directory</td>\
                          <td>";
    page +=          QString::number( stats.nb404Errors );
    page += "        </td>\
                        </tr>\
                        <tr>\
                          <td>503 service unavailable</td>\
                          <td>";
    page +=          QString::number( stats.nb503Errors );
    page += "        </td>\
                        </tr>\
                      </table>";
    page += "          <h2>Requests</h2>\n";
    page += "          <ol type=\"1\">\n";
    for( int i = 0; i < stats.receivedRequests.size(); i++ ){
        page += "<li>";
        page += stats.receivedRequests.at( i );
        page += "</li>\n";
    }
    page += "</ol>";
    page += "  </body>\n";
    page += "</html>\n";
}

void HtmlWrapper::buildAuthPage(){
    page += "HTTP/1.1";
    page += " 200 ";
    page += "OK\r\n\r\n";

    page += "<!DOCTYPE html>\
                  <html>\
                  <body>\
                    <h2>Password Required to access private page</h2>";

    page += "<form action=\"\" method=\"post\">\
                      Password:<br>\
                      <input type=\"password\" name=\"psw\">\
                      <br>\
                      <input type=\"submit\">\
                    </form>";
    if( !( errorMsg.isEmpty() ) ){
        page += errorMsg;
    }

    page += "</body>\
             </html>";
}

void HtmlWrapper::buildPage(){
    if( type == mainPage )
        buildMainPage();
    else if( type == statsPage )
        buildStatsPage();
    else if( type == authPage )
        buildAuthPage();

    clearLists();
}
