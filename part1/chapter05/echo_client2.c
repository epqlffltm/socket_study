// part01/chapter05/echo_client2.c

/*
 * echo_client2 작성
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
    ssize_t str_len = 0;
    ssize_t recv_len = 0;
    ssize_t recv_cnt = 0;
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
        printf("connected.......\n");

    while(1)
    {
        printf("input message(q to quit): ");

        if(scanf(" %1023[^\n]", message) != 1)
            break;

        if(!strcmp(message, "q") || !strcmp(message, "Q"))
            break;

        str_len = write(sock, message, strlen(message));

        if(str_len == -1)
            error_handling("write() error");

        recv_len = 0;

        while(recv_len < str_len)
        {
            recv_cnt = read(sock, &message[recv_len], str_len - recv_len);

            if(recv_cnt == -1)
                error_handling("read() error");

            if(recv_cnt == 0)
                break;

            recv_len += recv_cnt;
        }

        message[recv_len] = '\0';

        printf("message : %s\n", message);
    }

    close(sock);

    return 0;
}

void error_handling(const char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}