// part01/chapter03/inet_addr.c

/*
 * 점 찍힌 십진수 문자열을 네트워크 바이트 순서의 정수로 변환
 *
 * inet_addr()은 변환 실패 시 INADDR_NONE(0xFFFFFFFF)을 반환한다.
 * 다만 255.255.255.255도 같은 값이라 에러와 구분되지 않는 결함이 있다.
 */

#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";   /* 256은 범위를 벗어난 값 */

    in_addr_t conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE)
        printf("Error occurred!\n");
    else
        printf("Network ordered integer addr: %#x\n", conv_addr);

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE)
        printf("Error occurred!\n");
    else
        printf("Network ordered integer addr: %#x\n", conv_addr);

    return 0;
}