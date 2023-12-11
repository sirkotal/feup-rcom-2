#include "../include/download.h"

int parse(const char *url, struct URL *res) {
    int ftp = strncmp(url, "ftp://\[", 7);
    if (ftp) {
        int len = sscanf(url, "ftp://%[^/]/%s", res->host, res->resource);
        if (len != 2) {
            perror("The FTP URL is invalid");
            printf("\n");
            return 1;
        }

        strcpy(res->username, "anonymous");
        strcpy(res->password, "anonymous");
    }
    else {
        int len = sscanf(url, "ftp://\[%[^:]:%[^@]@]%[^/]/%s", res->username, res->password, res->host, res->resource);
        if (len != 4) {
            perror("The FTP URL is invalid");
            printf("\n");
            return 1;
        }
    }
    strcpy(res->file, strrchr(url, '/') + 1);
    struct hostent *h;
    if ((h = gethostbyname(res->host)) == NULL) {
        herror("gethostbyname()");
        exit(-1);
    }

    strcpy(res->ip, inet_ntoa(*((struct in_addr *) h->h_addr)));

    return 0;
}

    
int socketInit(int *sockfd, const char *ip, int port){
    struct sockaddr_in server_addr;

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);   
    server_addr.sin_port = htons(port);        

    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(-1);
    }

    if (connect(*sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect()");
        exit(-1);
    }
}



void getResponse(int sockfd, char *response) {
    char byte;
    int i = 0;
    char type;
    memset(response, 0, 500);
    enum message_state state = START;
    while (state != END) {
        read(sockfd, &byte, 1);
        switch (state) {
            case START:
                if (byte == ' ' || byte == '-'){
                    state = LINE;
                    type = byte;
                }
                else
                    response[i++] = byte;
                break;
            case CODE:
                if (byte == ' ' || byte == '-'){
                    state = LINE;
                    type = byte;

                }
                else if (byte == '\n'){
                    state = END;
                }
                break;
            case LINE:
                if (byte == '\n'){
                    if (type == '-'){
                        state = CODE;
                    }
                    else{
                        state = END;
                    }
                }
                break;
            case END:
                break;
            default:
                break;
        }
    }
    response[i]='\0';
    printf("fim\n");
}

void login(int sockfd, const char* username, const char* password) {
    int user_len = 6+strlen(username);
    char user[user_len];
    strcpy(user, "USER ");
    strcat(user, username);
    strcat(user, "\n");  
    write(sockfd, user, user_len);

    char response[1024];

    if (read(sockfd, response, 1024) < 0) {
        perror("read()");
        exit(-1);
    }

    int code;
    sscanf(response, "%d", &code);
    printf("%d", code);

    char response2[1024];

    int pass_len = 6+strlen(password);
    char pass[pass_len];
    strcpy(pass, "PASS ");
    strcat(pass, password);
    strcat(pass, "\n");  
    write(sockfd, pass, pass_len);

    if (read(sockfd, response2, 1024) < 0) {
        perror("read()");
        exit(-1);
    }
    int code2;
    sscanf(response2, "%d", &code2);
    printf("%d", code2);

}

void activatePassive(int sockfd, char *ip, int *port){
    write(sockfd, "pasv\n", 5);
    char response[1024];
    if (read(sockfd, response, 1024) < 0) {
        perror("read()");
        exit(-1);
    }
    int byte1, byte2, byte3, byte4, byte5, byte6;
    sscanf(response, "%*[^(](%d,%d,%d,%d,%d,%d)%*[^\n$)]", &byte1, &byte2, &byte3, &byte4, &byte5, &byte6);
    sprintf(ip, "%d.%d.%d.%d", byte1, byte2, byte3, byte4);
    *port = (byte5*256)+byte6;   
}

void requestResource(const int socket, const char *resource) {
    int user_len = 6+strlen(resource);
    char file[user_len];
    strcpy(file, "retr ");
    strcat(file, resource);  
    strcat(file, "\n");  
    write(socket, file, user_len);
}

int resourceDownload(const int controlSocket, const int dataSocket, char *filename) {
    char buf[1000];
    FILE *fptr; 
    fptr = fopen(filename, "wb");

    if (fptr == NULL) {
        perror("This file wasn't found\n");
        exit(EXIT_FAILURE);
    }

    int bytes_to_read = read(dataSocket, buf, 1000);

    while (bytes_to_read > 0) {

        if (fwrite(buf, bytes_to_read, 1, fptr) < 0) {
            return -1;
        }

        bytes_to_read = read(dataSocket, buf, 1000);
    }

    fclose(fptr);

    return 1;
}

int main(int argc, char *argv[]) {
    struct URL url; 
    parse(argv[1], &url);
    
    printf("Host: %s\n", url.host);
    printf("Resource: %s\n", url.resource);
    printf("Username: %s\n", url.username);
    printf("Password: %s\n", url.password);
    printf("File: %s\n", url.file);
    printf("Ip: %s\n", url.ip);
    
    int sockfd;
    socketInit(&sockfd, url.ip, PORT);
    
    char response[1024];

    if (read(sockfd, response, 1024) < 0) {
        perror("read()");
        exit(-1);
    }

    int code;
    sscanf(response, "%d", &code);

    printf("%d", code);
    login(sockfd, url.username, url.password);
    char ip[500];
    int port = 0;
    activatePassive(sockfd, ip, &port);
    int sockfdB;
    socketInit(&sockfdB, ip, port);
    requestResource(sockfd, url.resource);
    resourceDownload(sockfd, sockfdB, url.file);
}