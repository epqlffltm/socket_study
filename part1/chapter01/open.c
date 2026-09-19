// chapter01/open.c

/*
파일 열기
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(const char *message);

int main(void)
{
    int fd = -1;
    char buf[] = "let's go!\n";

    fd = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if(fd == -1)
        error_handling("open() error!");

    printf("file descriptor: %d \n", fd);

    if(write(fd, buf, strlen(buf)) == -1)
        error_handling("write() error!");

    close(fd);
    return 0;
}

void error_handling(const char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}