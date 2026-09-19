// chapter01/fd_seri.c

/*
파일 디스크립터 비교
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void)
{
    int fd1 = socket(PF_INET, SOCK_STREAM,0);
    int fd2 = open("test.dat", O_CREAT|O_RDWR|O_TRUNC,0644);
    int fd3 = socket(PF_INET, SOCK_DGRAM,0);

    printf("file descriptor 1 : %d\n",fd1);
    printf("file descriptor 2 : %d\n",fd2);
    printf("file descriptor 3 : %d\n",fd3);

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}