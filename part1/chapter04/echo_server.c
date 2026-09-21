// part01/chapter04/echo_server.c

/*
 * echo_server 작성
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
    int serv_sock = -1, clnt_sock = -1;
    ssize_t str_len = 0;
    char message[1024] = {0};
    size_t buf_size = sizeof message;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2)
    {
        printf("usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));

    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    for(int i = 0; i < 5; i++)
    {
        clnt_adr_sz = sizeof(clnt_adr);

        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        if(clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("connected client %d\n", i + 1);

        while((str_len = read(clnt_sock, message, buf_size)) > 0)
        {
            if(write(clnt_sock, message, str_len) == -1)
                error_handling("write() error");
        }

        if(str_len == -1)
            error_handling("read() error");

        close(clnt_sock);
    }

    close(serv_sock);

    return 0;
}

void error_handling(const char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}