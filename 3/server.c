#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib")


int main(int argc, char *argv[]){

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAStartup(MAKEWORD(2,2), &wsa));
        return 1;
    }

    if(argc!=2){
        printf("Failed finding port");
		exit(EXIT_FAILURE);
    }

    SOCKET sock;

    //int sock,length,fromlen,n;
    struct sockaddr_in server,client;
    int bindStatus,sendingStatus,clientLength ,recv_len;
    clientLength = sizeof(client) ;
    char buf[1024];


    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock==INVALID_SOCKET){
        printf("Could not create socket : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf(" Socket created.\n");

    /* Adding Values to struct sockaddr_in for bind  */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    /*  Bind server  */
    bindStatus=bind(sock ,(struct sockaddr *)&server , sizeof(server));
    if(bindStatus<0)
        {
                printf("\n Can't bind port ");
                exit(EXIT_FAILURE);
        }

        else
        {
                printf("\n Bind Successful ");
        }

     /* Start server to Listen */
    while (1){
        printf("\n Listening ... \n");
        fflush(stdout);

        // clear the buffer by filling null, it might have previously received data -- //
        memset(buf,'\0', 1024);

        recv_len = recvfrom(sock,buf,1024,0,(struct sockaddr *)&client,&clientLength);
        if(recv_len == SOCKET_ERROR){
            printf("Failed recvfrom() with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
        }
        printf("recv_length %d : \n",recv_len);

        //print details of the client and the data received
        printf("Received from %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		printf("Data : %s \n\n" , buf);
        
        //Echo
        sendingStatus = sendto(sock, buf, recv_len, 0, (struct sockaddr*) &client, clientLength);

        if (sendingStatus == SOCKET_ERROR){
			printf("Failed sendto() with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		// if(strcmp(buf,"Bye")==0 || strcmp(buf,"bye")==0){
        //         printf("\n Server Closed !! ");
        //         break;
        // }

    }
    closesocket(sock);
    WSACleanup();
    system("pause");
    return 0;
    
}