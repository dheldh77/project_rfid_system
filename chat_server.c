/* 
-file: chat_server.c     
-name: 2014097044_Park_HyunSeok
-description: chat server, send message and broadcast
*/ 

#include   <stdio.h> 
#include   <fcntl.h> 
#include   <stdlib.h> 
#include   <signal.h> 
#include   <sys/socket.h> 
#include   <sys/file.h> 
#include   <netinet/in.h> 

#define MAXLINE    1024 
#define MAX_SOCK    512 

char *escapechar = "exit\n"; 
int readline(int, char *, int); 
 
int main(int argc, char *argv[])    { 
   char   rline[MAXLINE], my_msg[MAXLINE]; 
   char   *start = "Welcome to ChattingRoom...\n"; 
   int  i, j, n; 
   int  s, client_fd, clilen; 
   int  nfds;      /*  maximum socket +1 */ 

   fd_set  read_fds;    /*  socket struct */ 
   int  num_chat = 0;    /*  chatter number */ 
   /*  socket number list */ 

   int  client_s[MAX_SOCK]; 
   struct sockaddr_in  client_addr, server_addr;     

   if (argc < 2)  { 
      printf("execute:%s portnum\n",argv[0]);  
      return -1; 
   } 

   printf("reset ChattingRoom server....\n"); 

   /* create socket  */ 

      if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)    { 
      printf("Server: Can't open stream socket.");    
      return -1; 
   } 
    

   /* server_addr  struct setting */ 

   bzero((char *)&server_addr, sizeof(server_addr));   
   server_addr.sin_family = AF_INET;               
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
   server_addr.sin_port = htons(atoi(argv[1]));      

      if (bind(s,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) { 
      printf("Server: Can't bind local address.\n"); 
      return -1; 
   } 

   /* waiting connect to client */ 

   listen(s, 5); 

      nfds = s + 1;   /* maximum socketnum +1 */ 
   FD_ZERO(&read_fds); 
    
   while(1) { 
      /* (maximum socketnum +1)  renuewal */ 
      if ((num_chat-1) >= 0)  nfds = client_s[num_chat-1] + 1; 

      FD_SET(s, &read_fds);
      for (i=0; i<num_chat; i++)  FD_SET(client_s[i], &read_fds); 


      /*----------------- select() ----------------------- */ 

        if (select(nfds, &read_fds, (fd_set *)0, (fd_set *)0,(struct timeval *)0) < 0) { 

       printf("select error\n"); 
       return -1; 
      } 

      /*------------------  process client connection requests-------------- */ 

      if (FD_ISSET(s, &read_fds)) { 
       clilen = sizeof(client_addr); 
            client_fd = accept(s, (struct sockaddr *)&client_addr, &clilen); 

       if (client_fd != -1)  { 
        /*add chatting client list */ 

        client_s[num_chat] = client_fd;  
        num_chat++; 
        send(client_fd, start, strlen(start), 0); 
        printf("%d user added\n",num_chat); 
       } 
      } 

      /*- message broad - */ 


      for (i = 0; i < num_chat; i++)  { 
      if (FD_ISSET(client_s[i], &read_fds)) { 
         if ((n = recv(client_s[i], rline, MAXLINE,0))  > 0)  { 
           rline[n] = '\0'; 

           /*if exit command, quit chatting */ 

           if (exitCheck(rline, escapechar, 5) == 1) { 
         shutdown(client_s[i], 2); 
         if(i != num_chat-1)  client_s[i] = client_s[num_chat-1]; 
         num_chat--; 

         continue; 
        } 

            /*broad message to every chatter  */   
            for (j = 0; j < num_chat; j++)  send(client_s[j], rline, n, 0); 
            printf("%s", rline); 
         } 
      } 
   } 
} 
}

/* ------------------exitcheck()---------*/


int exitCheck(rline, escapechar, len) 
  char  *rline;    /*message from client */ 
  char  *escapechar;  /*exit char */ 
  int    len; 
  { 

     int  i, max; 
     char  *tmp; 

     max = strlen(rline);   
     tmp = rline; 

     for(i = 0; i<max; i++) { 
        if (*tmp == escapechar[0]) { 
          if(strncmp(tmp, escapechar, len) == 0) 
          return 1; 
        } else  
  tmp++; 
     }  

   return -1;
} 
