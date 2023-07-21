// Natalia Piasta, 299487

#include <bits/stdc++.h>
#include <sys/stat.h>
#include "request.hpp"

using namespace std;

// https://www.geeksforgeeks.org/http-status-codes-informational-responses/
// https://www.geeksforgeeks.org/http-status-codes-successful-responses/
// https://www.geeksforgeeks.org/http-status-codes-redirection-responses/
// https://www.geeksforgeeks.org/http-status-codes-client-error-responses/
// https://www.geeksforgeeks.org/http-status-codes-server-error-responses/

// Response status codes
#define OK                  200
#define MOVED_PERMANENTLY   301
#define FORBIDDEN           403
#define NOT_FOUND           404
#define NOT_IMPLEMENTED     501

string check_type(string file);
string prepareResponse(Request &request, string dir);