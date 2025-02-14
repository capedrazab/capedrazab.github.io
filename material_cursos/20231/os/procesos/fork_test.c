// fork test

#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    pid_t cpid;

    cpid = fork();
    if (cpid == -1) { 
      perror("fork"); exit(EXIT_FAILURE); 
    }

    if (cpid == 0) {   
      printf("\nPID proceso hijo: %i", cpid);
		  fflush(stdout); 
    } 
    else 
    {   
      printf("\nPID proceso padre: %i", cpid);
		  fflush(stdout); 
    }
}
