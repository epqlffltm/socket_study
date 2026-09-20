// part01/chapter03/inet_aton.c

/*
 * inet_aton() — 문자열 IP를 struct in_addr에 직접 채워 넣는다.
 *
 * inet_addr()과 달리 성공/실패를 반환값으로 구분하므로
 * 255.255.255.255를 에러로 오인하는 문제가 없다.
 * 성공 시 0이 아닌 값, 실패 시 0을 반환한다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handling(const char *message);

int main(void)
{
    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    if (!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion error");
    else
        printf("Network ordered integer addr: %#x\n", addr_inet.sin_addr.s_addr);

    return 0;
}

void error_handling(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}