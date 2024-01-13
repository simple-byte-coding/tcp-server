#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Winsock2.h>
#include <tcpip.h>
#pragma comment (lib, "ws2_32.lib");

int main() {
    WSADATA wsaData;
    WORD wordVersion = MAKEWORD(2, 2);
    int startCheck = WSAStartup(wordVersion, &wsaData);
}