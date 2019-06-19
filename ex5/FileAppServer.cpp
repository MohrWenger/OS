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

int main(int argc, char *argv[])
{
    // FileApp -s <local_dir_path> <port_no>
    struct hostent *h;
    if ((h = gethostbyname(argv[1])) == nullptr)
    {
        fprintf(stderr, "gethostbyname ");
        exit(1);
    }
    cout << "Host name : " << h->h_name;
    printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *) h->h_addr)));
    return 0;
}