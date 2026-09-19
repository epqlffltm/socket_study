// part01/chapter02/tcp_client.c

/*
 * 단방향 hello 서버
 * 접속한 클라이언트에게 문자열 하나를 보내고 종료한다.
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
    struct sockaddr_in serv_addr;

    char message[30] = {0};

    int str_len = 0;
    int idx = 0;
    ssize_t read_len = 0;

    if (argc != 3)
    {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock,
                (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) == -1)
    {
        error_handling("connect() error!");
    }

    while (idx < (int)sizeof(message) - 1 &&
           (read_len = read(sock, &message[idx], 1)) > 0)
    {
        idx++;
        str_len += read_len;
    }

    if (read_len == -1)
        error_handling("read() error");

    printf("message: %s\n", message);
    printf("length: %d\n", str_len);

    close(sock);

    return 0;
}

void error_handling(const char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}