#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "prints.h"
#include "FileAppClient.h"
#include "FileAppServer.h"

using namespace std;


int main(int argc, char *argv[]) {
    if (argc != 4 && argc != 6) {
        cout << "bad input" << endl;
    }

    if (strcasecmp(argv[1], "-s") == 0) {
        cout << "server" << endl;
        start_server_bla(argv[2], (unsigned short) *argv[3]);
    }

    if (strcasecmp(argv[1], "-u") == 0) {
        cout << "user" << endl;
        initialize_client();
    }

    return 0;
}