#include "FileAppServer.h"
#include <netinet/in.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include "prints.h"

using namespace std;

#define MAXHOSTNAME 1000 // TODO - fix value


int start_server_bla(string path, unsigned short portnum) {
    // client call = FileApp -s <local_dir_path> <port_no>
    char myname[MAXHOSTNAME + 1];
    struct sockaddr_in server_addr{};
    int fd_server, fd_connect;
    struct hostent *hp;

    // get host name
    gethostname(myname, MAXHOSTNAME);
    hp = gethostbyname(myname);
    if (hp == nullptr)
        return (-1);

    //sockaddrr_in initlization
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = hp->h_addrtype;

    /* this is our host address */
    memcpy(&server_addr.sin_addr, hp->h_addr, hp->h_length);
    /* this is our port number */
    server_addr.sin_port = htons(portnum);


    cout << "starting server" << endl;
    return 0;
}