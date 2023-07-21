// Natalia Piasta, 299487

#include <iostream>
#include "validation.hpp"
#include "server.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 3) 
        error("Invalid number of arguments!\nUsage: ./webserver <port> <directory>\n");

    int port = atoi(argv[1]); // If atoi(port) = 0, then we will return error in line below
    validate_port(port);
    validate_directory(argv[2]);

    Server server(port, argv[2]);
    server.run();
    
    return EXIT_SUCCESS;
}