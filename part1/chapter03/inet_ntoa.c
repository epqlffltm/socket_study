// part01/chapter03/inet_ntoa.c

/*
 * inet_ntoa() — 네트워크 바이트 순서 정수를 점 찍힌 십진수 문자열로 변환
 *
 * 내부 정적 버퍼의 주소를 반환하므로 다음 호출 시 이전 결과가 덮어써진다.
 * 결과를 계속 쓰려면 즉시 별도 배열에 복사해야 한다.
 * 정적 버퍼를 공유하는 탓에 스레드 안전하지 않다 → inet_ntop() 권장.
 */

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(void)
{
    struct sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[INET_ADDRSTRLEN];

    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);

    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation1: %s\n", str_ptr);

    inet_ntoa(addr2.sin_addr);   /* 대입하지 않아도 내부 버퍼가 바뀐다 */
    printf("Dotted-Decimal notation2: %s\n", str_ptr);
    printf("Dotted-Decimal notation3: %s\n", str_arr);

    return 0;
}