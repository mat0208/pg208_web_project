#include "Htmlwrapper.h"

HtmlWrapper::HtmlWrapper()
{
}

void HtmlWrapper::buildPage(){
    switch( code ){
    case 200:
        page += "HTTP/1.1";
        page += " 200 ";
        page += "OK\r\n\r\n";
        break;
    case 404:
        errorMsg = " ERROR 404 : UNKNOWN FILE OR DIRECTORY ";
        page += "HTTP/1.1";
        page += " 404 ";
        page += "NOT FOUND\r\n\r\n";
        break;
    case 403:
        errorMsg = " ERROR 403 : FORBIDDEN ACCESS ";
        page += "HTTP/1.1";
        page += " 403 ";
        page += "FORBIDDEN\r\n\r\n";
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
    page += "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">";
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
        page += "</h1>";
    }
    page += "<address>(Ubuntu) Server at 192.168.1.64 Port 8080</address>\n";
    page += "</body>\n";
    page += "</html>\n";

    clearLists();
}

void HtmlWrapper::clearLists(){
    files.clear();
    fileContent.clear();
    directories.clear();
    pictures.clear();
    errorMsg.clear();
}
