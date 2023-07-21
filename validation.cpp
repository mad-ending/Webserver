// Natalia Piasta, 299487

#include "validation.hpp"

void error(string error) {
    cerr<<error<<endl;
    exit (EXIT_FAILURE);
}

void validate_port(int port) {
    if(port<1 || port>65535)
        error("Invalid port!\nPort should be integer ϵ[1, 65535]!");
}

void validate_directory(char path[]) {
    // https://www.ibm.com/docs/en/i/7.4?topic=ssw_ibm_i_74/apis/stat.htm
    struct stat info;
    if(stat(path, &info) != 0 || !S_ISDIR(info.st_mode))
        error("Directory error!");
}
