#include "FileAppClient.h"
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
#include "prints.h"

using namespace std;


int initialize_client() {
    // FileApp -u <local_path> <remote_name> <port_no> <server_IP>
    // FileApp -d <local_path> <remote_name> <port_no> <server_IP>
    cout << "initing client" << endl;

//    struct sockaddr_in my_addr;
//    my_addr.sin_family = AF_INET;
//    my_addr.sin_port = htons(3490);
//    inet_aton("10.12.110.57", &(my_addr.sin_addr));
//    memset(&(my_addr.sin_zero), '\0', 8);

    return 0;
}