#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
   char str[80] = "$ ls -a; echo hello && mkdir test || echo world; git status";
   const char s[3] = "&&";
   char *token;
   
   /* get the first token */
   token = strtok(str, s);
   
   /* walk through other tokens */
   while( token != NULL ) 
   {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0);
}
