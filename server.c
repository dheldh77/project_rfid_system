/*
-file: server.c
-name: 2014097044_Park_HyungSeok
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 1024

void error_handling(char *message);

int main(int argc, char **argv)
{
        int serv_sock;
        int clnt_sock;
           char message[BUFSIZE];
           int str_len;

        struct sockaddr_in serv_addr;
        struct sockaddr_in clnt_addr;
        int clnt_addr_size;
		int i;
		char ID[BUFSIZE];	/* save rfid id */
 
        if(argc != 2) {
                printf("Usage : &s <port>\n", argv[0]);
                exit(1);
        }

        serv_sock = socket(PF_INET, SOCK_STREAM, 0);    /* make sever socket */

        if(serv_sock == -1)
                error_handling("socket() error");
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(atoi(argv[1]));

           /*assign address to a socket */
if( bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr) )==-1)
error_handling("bind() error");


        if(listen(serv_sock, 5) == -1)  /*enter connection request wait state */
                error_handling("listen() error");

        clnt_addr_size = sizeof(clnt_addr);

           /* accept connection requests */

        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

        if(clnt_sock == -1)
                error_handling("accept() error");

           /* data reception and transmission, echo to server and client */

           while( (str_len = read(clnt_sock, message, BUFSIZE)) != 0) {
					/* reset ID*/
					ID[0] = '\0';	

					strncpy(ID, message, str_len-1);
					ID[str_len-1] = 0;
					
					

					printf("Your ID: %s\n", ID);

					
					 write(clnt_sock, message, str_len);
                     write(1, message, str_len);
           }
        close(clnt_sock);       /* connection exit */

        return 0;
}

 

void error_handling(char *message)
{
	    fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}
