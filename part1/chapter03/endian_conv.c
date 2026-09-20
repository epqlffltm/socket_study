// part01/chapter03/endian_conv.c

/*
 * 빅 엔디안과 리틀 엔디안 변환 확인
 *
 * htons/htonl은 호스트 바이트 순서를 네트워크 바이트 순서(빅 엔디안)로 바꾼다.
 * x86-64와 ARM64는 리틀 엔디안이므로 바이트가 뒤집힌 값이 출력된다.
 */

#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main(void)
{
    uint16_t host_port = 0x1234;
    uint16_t net_port  = htons(host_port);
    uint32_t host_addr = 0x12345678;
    uint32_t net_addr  = htonl(host_addr);

    printf("Host ordered port  : %#x\n", host_port);
    printf("Network ordered port: %#x\n", net_port);
    printf("Host ordered address: %#x\n", host_addr);
    printf("Network ordered address: %#x\n", net_addr);

    return 0;
}