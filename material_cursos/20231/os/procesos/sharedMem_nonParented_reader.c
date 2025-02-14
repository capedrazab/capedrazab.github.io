#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

/*****************************************************************************/
struct dogType
{
    char nombre[32];
    int edad;
    char raza[16];
    int estatura;
    float peso;
    char sexo;
};

/*****************************************************************************/
int guardar(void *ap)
{
    FILE *fd;
    fd = fopen("dataDogs.dat", "a+");    
    fwrite(ap, sizeof(struct dogType), 1, fd);
    fclose(fd);
}

int main()
{
    pid_t pid;
    key_t key=1234;
    int shmId, *flag;               //bandera para sincronizar los procesos.
    void *ap;
    struct dogType *dog;
    int status, cpid;
    
    shmId = shmget(key, sizeof(struct dogType)+sizeof(int), 0666);
    if(shmId < 0){
        perror("Error en shmget: ");
        exit(-1);
    }
    ap = shmat(shmId, 0, 0);
    dog = (struct dogType *)ap;
    flag = (int *)(ap + sizeof(struct dogType));
 	  guardar(dog);
    *flag = 0;
 	  shmdt(ap);
}
