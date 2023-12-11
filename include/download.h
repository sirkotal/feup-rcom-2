#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

#define PORT 21

struct URL {
    char host[500];     
    char resource[500];  
    char file[500];     
    char ip[500];   
    char username[500];      
    char password[500];      
};


