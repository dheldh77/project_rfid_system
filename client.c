/*
-file: client.c
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
        int sock;
        struct sockaddr_in serv_addr;
        char message[BUFSIZE];
        int str_len;

        if(argc != 3) {
                printf("Usage : %s <IP> <port> \n", argv[0]);
                exit(1);
        }


        sock = socket(PF_INET, SOCK_STREAM, 0);   /* create server for socket connection */

        if(sock == -1)
                error_handling("socket() error");
 
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));

        if( connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
                error_handling("connect() error");

           while(1) {
                     /* send message input */
                     fputs("Enter Your ID(q to quit) : ", stdout);
					

					 message[0] = '\0';
                     fgets(message, BUFSIZE, stdin);

                     if(!strcmp(message, "q\n"))
                                break;
                     write(sock, message, strlen(message));

                      /* message reception output */
                     str_len = read(sock, message, BUFSIZE-1);
                     message[str_len] = 0;

                     printf("Message sent from the server : %s \n", message);
           }
          
           close(sock);
           return 0;

}

void error_handling(char *message)
{
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}
