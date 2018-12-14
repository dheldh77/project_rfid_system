/*
-file: readline.c
-name: 2014097044_Park_HyungSeok
-description: write message
*/

int readline(int fd, char *ptr, int maxlen) 
{
   int n, rc;
   char c;

      for(n = 1; n < maxlen; n++) {
  if((rc = read(fd, &c, 1)) == 1) {
     *ptr++ = c;
        if (c == '\n') break;
  } else if (rc == 0) {
        if(n == 1) return (0);
     else break;
 }
   }

   *ptr = 0;
   return (n);
} 

