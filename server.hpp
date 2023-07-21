// Natalia Piasta, 299487

#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "response.hpp"
#include "validation.hpp"

#define max_clients 100

using namespace std;

class Server {
    int port;
    string dir;
    int sockfd;
    
    public:
        Server(int port, string dir);
        void run();

    private:
        // https://www.geeksforgeeks.org/socket-programming-cc/
        // https://www.geeksforgeeks.org/tcp-and-udp-server-using-select/
        // https://cpp0x.pl/kursy/Kurs-WinSock-C++/Troche-zaawansowane-techniki/277
        string create_path(Request &request);
        int Socket(int domain, int type, int protocol);
        void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        void Listen(int sockfd, int backlog);
        int Accept(int sockfd, const struct sockaddr *addr, socklen_t *addrlen);
        int Select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
        void Close(int sockfd);

        void Send(int sockfd, const void *buf, size_t len, int flags);
        ssize_t Recv(int sockfd, void *buf, size_t len, int flags);
};