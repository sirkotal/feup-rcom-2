#include "../include/app.h"

int parse(const char *url, struct URL *res) {
    int ftp = sstrncmp(url, "ftp://\[", 7);

    if (ftp) {
        int len = sscanf(url, "ftp://%[^/]/%s", res->host, res->resource);
        if (len != 2) {
            perror("The FTP URL is invalid");
            printf("\n");
            return 1;
        }

        strcpy(res->user, DEFAULT_USER);
        strcpy(res->password, DEFAULT_PASSWORD);
    }
    else {
        int len = sscanf(url, "ftp://\[%[^:]:%[^@]@]%[^/]/%s", res->username, res->password, res->host, res->path);
        if (len != 4) {
            perror("The FTP URL is invalid");
            printf("\n");
            return 1;
        }
    }

    return 0;
}