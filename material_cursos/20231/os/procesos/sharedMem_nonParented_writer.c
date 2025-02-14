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
int cargar(void *ap)
{
    struct dogType *datos; 
    datos = ap;
    
    printf("\nnombre:");
    scanf(" %s", datos->nombre);
    printf("\nedad:");
    scanf(" %i", &datos->edad);
    printf("\nraza:");
    scanf(" %s", datos->raza);
    printf("\nestatura:");
    scanf(" %i", &datos->estatura);
    printf("\npeso:");
    scanf(" %f", &datos->peso);
    printf("\nsexo:");
    scanf(" %c", &datos->sexo);
}
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
    int shmId;
    void *ap;
    struct dogType *dog;
    int *flag;              //bandera para sincronizar los procesos.
    int status, cpid;
    
    shmId = shmget(key, sizeof(struct dogType)+sizeof(int), 0666|IPC_CREAT);
    if(shmId < 0){
        perror("Error en shmget");
        exit(-1);
    }
    ap = shmat(shmId, 0, 0);
    dog = (struct dogType*)ap;
    flag = (int *)(ap + sizeof(struct dogType));
 	  cargar(dog);
 	  *flag = 0xFF;
 	  do{
 	  }while(*flag != 0);

 	shmdt(ap);

}
