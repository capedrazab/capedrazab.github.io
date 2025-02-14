//programa para probar una tubería
//el hijo pasa un mensaje al padre
//el padre lo imprime en pantalla

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define CHARLEN 4

int main()
{
    pid_t pid;
    int r;
    int pipefd[2];
    char buf[11];
    
    r = pipe(pipefd);
    if(pipefd < 0){ 
        perror("Error pipe() "); 
        exit(-1);
    }
    pid = fork();
    if (pid == -1){  //handle errors
        perror("fork"); 
        exit(EXIT_FAILURE); 
    }
    
    if(pid == 0){
        //hijo escribe pipe - pipefd[1]
        close(pipefd[0]);
        r = write(pipefd[1], "hola", CHARLEN);
        if(r != CHARLEN){   //handle errors
            perror("error writting pipe"); 
        }
        close(pipefd[1]);
        exit(0);    
    }
    else{ 
      //padre lee pipe - pipefd[0]
        close(pipefd[1]);
        r = read(pipefd[0], buf, 10);
        if(r != CHARLEN){   //handle errors
            perror("error reading pipe");
        }
        close(pipefd[0]); 
        buf[r] = 0;
        printf("\nMensaje del hijo: %s \n", buf);
    }
}
