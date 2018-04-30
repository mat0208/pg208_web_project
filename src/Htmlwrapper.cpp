#include "Htmlwrapper.h"

HtmlWrapper::HtmlWrapper()
{
}

void HtmlWrapper::buildPage(){
    page += "HTTP/1.1\n\n";
    page += "<html>\n";
    if( errorMsg.isEmpty() ){
        page += " <body>\n";
        if( fileContent.isEmpty() ){
            page += "<table><tr><th><img src=\"/home/mat0208lt/Desktop/http_server/pg208_web_project/public_html/icons/blank.gif\" alt=\"[ICO]\"></th><th><a href=\"?C=N;O=D\">Name</a></th><th><a href=\"?C=M;O=A\">\n";
            page += "<tr><th colspan=\"5\"><hr></th></tr>\n";
            for( int i = 0; i < directories.size(); i++ ){
                page += "<tr><td valign=\"top\"><img src=\"/home/mat0208lt/Desktop/http_server/pg208_web_project/public_html/icons/folder.gif\" alt=\"[DIR]\"></td><td><a href=\"";
                page += directories.at( i );
                page += "/\">";
                page += directories.at( i );
                page += "/</a></td>\n";
            }
            for( int i = 0; i < files.size(); i++ ){
                page += "<tr><td valign=\"top\"><img src=\"/home/mat0208lt/Desktop/http_server/pg208_web_project/public_html/icons/folder.gif\" alt=\"[DIR]\"></td><td><a href=\"";
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
