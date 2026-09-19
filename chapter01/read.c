// chapter01/open.c

/*
파일 닫기
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
    char buf[100] = {0};
    size_t buf_size = sizeof buf;

    fd = open("data.txt", O_RDONLY);

    if (fd == -1)
        error_handling("open() error!");

    printf("file descriptor: %d\n", fd);

    ssize_t read_size = read(fd, buf, buf_size - 1);

    if (read_size == -1)
        error_handling("read() error!");

    printf("file data: %s", buf);

    close(fd);

    return 0;
}

void error_handling(const char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}