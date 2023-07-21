// Natalia Piasta, 299487

#include <string>
#include "request.hpp"

void prepareRequest(Request &request, string data) {
    string get = "GET ";
    string http = " HTTP/1.1";
    string host = "Host: ";
    string connection = "Connection: ";
    string lf = "\r\n";
    string tmp;

    size_t start = data.find(get);
    if(start == string::npos)
        error("GET error!");
    size_t end = data.find(http);
    if(end == string::npos)
        error("HTTP error!");
    request.address = data.substr(start + get.length(), end - (start + get.length()));

    start = data.find(host);
    if(start == string::npos)
        error("Host error!");
    tmp = data.substr(start + host.length());
    end = tmp.find(lf);
    if(end == string::npos)
        error("LF error!");
    request.host = tmp.substr(0, end);

    start = data.find(connection);
    if(start == string::npos)
        error("Connection error!");
    tmp = data.substr(start + connection.length());
    end = tmp.find(lf);
    if(end == string::npos)
        error("LF error!");
    request.connection = tmp.substr(0, end);
}