// Natalia Piasta, 299487

#include <filesystem>
#include <cstring>
#include "response.hpp"

string check_type(string file) {
    string file_extension;
    size_t pos = file.find_last_of('.'); // return file extension, or rather text after last .
    if(pos != string::npos)
        file_extension = file.substr(pos);

    // https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types
    if(file_extension == ".txt")
        return "text/plain";
    if(file_extension == ".html")
        return "text/html";
    if(file_extension == ".css")
        return "text/css";
    if(file_extension == ".jpg")
        return "image/jpg";
    if(file_extension == ".jpeg")
        return "image/jpeg";
    if(file_extension == ".png")
        return "image/png";
    if(file_extension == ".pdf")
        return "application/pdf";
    return "application/octet-stream"; // for .bin extension
}

int check_path(string path) {
    struct stat info;
    if(path.find("..") != string::npos)
        return FORBIDDEN;
    if(stat(path.c_str(), &info) != 0)
        return NOT_FOUND;
    if(S_ISDIR(info.st_mode))
        return MOVED_PERMANENTLY;
    return OK;
}

string prepareResponse(Request &request, string path) {
    string header;
    string body;

    int code = check_path(path);
    if(code == MOVED_PERMANENTLY) {
        if(path[path.length() - 1] == '/')
            path += "index.html";
        else
            path += "/index.html";
        code = check_path(path);
        if(code == 200)
            code = MOVED_PERMANENTLY;
    }
    
    if(!request.address.length() || !request.host.length() || !request.connection.length()) {
        body = "<center><b>501 Not Implemented</b></center>";
        header = "HTTP/1.1 501 Not Implemented\r\n";
        header += "Content-Length: " + to_string(body.length()) + "\r\n";
        header += "Content-Type: text/html\r\n";
    }
    else if(code == FORBIDDEN) { 
        body = "<center><b>403 Forbidden</b></center>";
        header = "HTTP/1.1 403 Forbidden\r\n";
        header += "Content-Length: " + to_string(body.length()) + "\r\n";
        header += "Content-Type: text/html\r\n";
    }
    else if(code == NOT_FOUND) { 
        body = "<center><b>404 Not Found</b></center>";
        header = "HTTP/1.1 404 Not Found\r\n";
        header += "Content-Length: " + to_string(body.length()) + "\r\n";
        header += "Content-Type: text/html\r\n";
    }
    else if(code == MOVED_PERMANENTLY) { 
        // MOVED_PERMANENTLY
        ifstream file(path);//, ios::binary);
        stringstream buffer;
        buffer << file.rdbuf();
        body = buffer.str();
        header = "HTTP/1.1 301 Moved Permanently\r\n";
        header += "Content-Length: " + to_string(body.length()) + "\r\n";
        header += "Content-Type: " + check_type(path) + "\r\n";
    }
    else { 
        // OK
        ifstream file(path);
        stringstream buffer;
        buffer << file.rdbuf();
        body = buffer.str();
        header = "HTTP/1.1 200 OK\r\n";
        header += "Content-Length: " + to_string(body.length()) + "\r\n";
        header += "Content-Type: " + check_type(path) + "\r\n";
    }

    return header + "\r\n" + body;
}