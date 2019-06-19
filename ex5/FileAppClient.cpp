#ifdef __WIN32__

# include <winsock2.h>
#include <time.h>

#else
#include<netinet/in.h>
#include<netdb.h>
#include <sys/uio.h>
# include <sys/socket.h>
#endif

#include<iostream>
#include<sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>


using namespace std;

//int main(int argc, char *argv[])
//{
//    // FileApp -u <local_path> <remote_name> <port_no> <server_IP>
//    // FileApp -d <local_path> <remote_name> <port_no> <server_IP>
//    if (argc != 6)
//    {
//        cerr << "Bad input" << endl;
//        return 1;
//    }
//
//    struct hostent *h;
//    if ((h = gethostbyname(argv[1])) == NULL)
//    {
//        fprintf(stderr, "gethostbyname ");
//        exit(1);
//    }
//
//    return 0;
//}