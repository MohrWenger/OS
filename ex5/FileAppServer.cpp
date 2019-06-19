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
    return 0;
}