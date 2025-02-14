#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int val_error(int returned, int error_value, char *msg){
    if(returned <= error_value){
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main ()
{
  int descr, longmens, i, r;
  short mensaje[1024];

  //sprintf (mensaje, "Un saludo desde el proceso %d", getpid ());
  for(i=0; i<1024; i++){
    mensaje[i] = i;
  }

  //longmens = strlen (mensaje) + 1;
  do{		/* intentar la conexion */
    descr = open ("tuberia", O_WRONLY);
    if (descr == -1) sleep (1);
  }while (descr == -1);

  for (i=0; i<1; i++){
    r = write (descr, mensaje, 1024*2);
    val_error(r, 0, "write error");
    sleep(1);
  }
  close(descr);
  printf("Fin del escritor %d\n", getpid ());
}


