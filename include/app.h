#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include<arpa/inet.h>

struct URL {
    char host[400];     
    char resource[400];  
    char file[400];     
    char ip[400];   
    char username[400];      
    char password[400];      
};

int parse(const char *url, struct URL *res);