//
// Created by NghiaPT on 2/13/2018.
//

#include <stdio.h>
#include <winsock2.h>
#include <string.h>

//#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, client_port;
    char* message, *client_ip;
    char ipport[100];

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }

    puts("Bind done");

    //listening to incoming connection
    listen(s, SOMAXCONN);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
    {
        puts("Connection accepted");

        //Reply to the client
        message = "Welcome to Chess Server\n";
        send(new_socket , message , strlen(message) , 0);
        client_ip = inet_ntoa(client.sin_addr);
        client_port = ntohs(client.sin_port);
        sprintf(ipport, "Your ip is %s:%d", client_ip, client_port);
        send(new_socket, ipport, strlen(ipport), 0);
    }

    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d" , WSAGetLastError());
        return 1;
    }

    //getchar();
    closesocket(s);

    WSACleanup();
    return 0;
}


