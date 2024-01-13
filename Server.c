#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Winsock2.h>
#include <stddef.h>
#pragma comment (lib, "ws2_32.lib")


int main() {
    SOCKET client;
    char buffer[1024] = "welcome to the server";


    WSADATA wsaData;
    WORD wordVersion = MAKEWORD(2, 2);

    // Start winsock
    int startCheck = WSAStartup(wordVersion, &wsaData);
    if (startCheck != 0) {
        perror("Unable to start winsock!\n");
        return EXIT_FAILURE;
    }

    // Create a socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        perror("Invalid socket error!\n");
        return EXIT_FAILURE;
    }

    // Setup net structure
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(3000);
    sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    // bind the socket
    int bindCheck = bind(serverSocket, (struct sockaddr*)&sa, sizeof(sa));
    if (bindCheck != 0) {
        perror("Bind error!\n");
        return EXIT_FAILURE;
    }

    listen(serverSocket, SOMAXCONN);

    puts("Listening for a client connection...\n");

    client = accept(serverSocket, NULL, NULL);
    if (!client) {
        perror("Unable to accept the client!\n");
        return EXIT_FAILURE;
    }

    puts("Connection established with client\n");

    send(client, buffer, sizeof(buffer), 0);

    // close the socket
    closesocket(client);
    closesocket(serverSocket);

    // shut down winsock
    WSACleanup();

    // exit the program
    return EXIT_SUCCESS;
}