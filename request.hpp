// Natalia Piasta, 299487

#include <iostream>
#include "validation.hpp"

using namespace std;

// HTTP Request
#define NOTHING     0
#define GET         1
#define HOST        2
#define CONNECTION  3

class Request {
    public:
        string address;
        string host;
        string connection;
};

void prepareRequest(Request &request, string data);

