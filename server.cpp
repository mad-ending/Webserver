// Natalia Piasta, 299487

#include "server.hpp"

Server::Server(int port, string dir) {
    this->port = port;
    this->dir = dir;

    this->sockfd = this->Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family       = AF_INET;
    server_address.sin_port         = htons(this->port);
    server_address.sin_addr.s_addr  = htonl(INADDR_ANY);
    
    this->Bind(this->sockfd, (struct sockaddr*) &server_address, sizeof(server_address));
    this->Listen(this->sockfd, 64);
}

void Server::run() {
    while(true) {
        int connected_sockfd = this->Accept(this->sockfd, NULL, NULL);

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(connected_sockfd, &descriptors);

        int ready = 1;
        while(ready) {
            int ready = this->Select(connected_sockfd+1, &descriptors, NULL, NULL, &tv);
            if(ready == 0)
                break;
            if(ready > 0) {
                char buffer[IP_MAXPACKET];
                bzero(buffer, IP_MAXPACKET);
                Request request;

                ssize_t size = this->Recv(connected_sockfd, buffer, IP_MAXPACKET, 0);
                if(size == 0)
                    ready = 0;
                else {
                    string data = string(buffer);
                    
                    prepareRequest(request, data);
                    string path = this->create_path(request);
                    string response = prepareResponse(request, path);
                    this->Send(connected_sockfd, response.c_str(), response.length(), 0);

                    if(request.connection == "close") {
                        ready = 1;
                        tv.tv_sec = 1;
                        tv.tv_usec = 0;
                    }
                }
            }
        }
        Close(connected_sockfd);
    }
}

string Server::create_path(Request &request) {
    size_t pos = request.host.find(':');
    if(pos != string::npos)
        request.host.erase(pos);

    if(this->dir[this->dir.length() - 1] == '/')
        this->dir.erase(this->dir.length() - 1);

    return this->dir+'/'+request.host+request.address;
}

int Server::Socket(int domain, int type, int protocol) {
    int sockfd = socket(domain, type, protocol); 
    if(sockfd < 0)
        error("Socket error!");
    return sockfd;
}

void Server::Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    if(bind(sockfd, (struct sockaddr*) addr, addrlen) < 0)
        error("Bind error!");
}

void Server::Listen(int sockfd, int backlog=64) { // we just assume that size of queue, backlog = 64
    if(listen(sockfd, backlog) < 0)
        error("Listen error!");
}

int Server::Accept(int sockfd, const struct sockaddr *addr, socklen_t *addrlen) {
    int x = accept(sockfd, (struct sockaddr*) addr, addrlen);
    if(x < 0)
        error("Accept error!");
    return x;
}

int Server::Select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
    int x = select(numfds, readfds, writefds, exceptfds, timeout);
    if(x < 0)
        error("Select error");
    return x;
}

void Server::Close(int sockfd) { // exactly connected_sockfd
    if(close(sockfd) < 0) // we try to close server
        error("Close error!");
}

void Server::Send(int sockfd, const void *buf, size_t len, int flags) {
    int x = send(sockfd, buf, len, flags);
	if(x < 0){	
		error("Send error");	
	}
}

ssize_t Server::Recv(int sockfd, void *buf, size_t len, int flags) {
    int x = recv(sockfd, buf, len, flags);
    if(x < 0)
        error("Recv error!");
    return x;
}
