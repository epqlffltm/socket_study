// part01/chapter04/echo_client.c

/*
 * echo_client 작성
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(const char *message);

int main(int argc, char *argv[])
{
    int sock = -1;
    size_t str_len = 0;
    char message[1024] = {0};
    size_t buf_size = sizeof message;
    struct sockaddr_in serv_adr;

    if(argc != 3)
    {
        printf("usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));

    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        printf("connected .....\n");

    while(1)
    {
        printf("input message(q to quit): ");

        if(scanf(" %1023[^\n]", message) != 1)
            break;

        if(!strcmp(message, "q") || !strcmp(message, "Q"))
            break;

        if(write(sock, message, strlen(message)) == -1)
            error_handling("write() error");

        str_len = read(sock, message, buf_size - 1);

        if(str_len == -1)
            error_handling("read() error");

        if(str_len == 0)
            break;

        message[str_len] = '\0';

        printf("message from server: %s\n", message);
    }

    close(sock);

    return 0;
}

void error_handling(const char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}