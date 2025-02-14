//Ejemplo de comunicación de dos procesos mediante memoria compartida
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    pid_t pid;
    key_t key=1234;
    int shmId;
    float a,b,c, *ap;
    int status, cpid, r;
    //crear espacio de memoria compartida
    shmId = shmget(key, 3*sizeof(float), 0666|IPC_CREAT);
    if(shmId < 0){
        perror("Error en shmget");
        exit(-1);
    }
    //asociar espacio de memoria creada a este proceso
    ap = (float *)shmat(shmId, 0, 0);
    *ap = 3.1416;   //número inicial en la memoria
    pid = fork();
    if (pid == -1){  //handle errors
        perror("error fork"); 
        exit(EXIT_FAILURE); 
    }
    if(pid == 0){ //hijo
        *(ap+1) = 0.707;    //dato del hijo para el padre
    }
    else{ //padre
        if (wait(&status) == pid){ //esperar a hijo
            printf("\ndato *ap: %f   \ndato *(ap+1) recibido del hijo: %f \n", *ap, *(ap+1));
        }
    }
    r = shmdt(ap);  //desasociar espacio de memoria compartida
    if(r < 0){
      perror("error shmdt ");
      exit(-1);
    }
}
