#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib")

int main(int argc, char *argv[]){

    WSADATA wsa;
    WORD sockVersion = MAKEWORD(2,2);
    if(WSAStartup(sockVersion,&wsa)!=0){
        return 0;
    }

    if(argc!=3){
        printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
    }

    
    struct sockaddr_in server;
    int clientSocket,sendStatus,receiveStatus, slen=sizeof(server);

    char buffer[256],message[256];

    
    clientSocket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (clientSocket == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}

    memset((char *) &server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    /* -- starts  communication -- */
    while (1){
        printf("\n Send a message : ");
        fgets(message, sizeof(message), stdin);


        /* --- send the message --- */
        sendStatus=sendto(clientSocket, message, strlen(message) , 0 , (struct sockaddr *) &server, slen);

		if (sendStatus == SOCKET_ERROR){
			printf("sendto() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}
        // -- clear the buffer by filling null, it might have previously received data
		memset(buffer,'\0', 256);

		/* receive data */
		receiveStatus=recvfrom(clientSocket, buffer, 256, 0, (struct sockaddr *) &server, &slen);

		if (receiveStatus == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		printf("\n Echo from server : %s",buffer);

		// if(strcmp(buffer,"Bye")==0 || strcmp(buffer,"bye")==0)
        // {
        //         printf("\n Server Closed !! ");
        //         break;
        // }
    }
    closesocket(clientSocket);
    WSACleanup();
    system("pause");
    return 0;
}