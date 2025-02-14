/* Tuberia con nombre usando mkfifo */
//writer pasa 1024 números a reader. reader los recibe y los imprime en pantalla
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
    int descr, i, r;
    short cadena[1024];

    unlink ("tuberia");
    sleep(1);
    r = mkfifo ("tuberia", 0);
    val_error(r, -1, "mkfifo error");
    r = chmod("tuberia", 0777);  //777 en octal
    val_error(r, -1, "chmod error");
    descr = open("tuberia", O_RDONLY);
    val_error(descr, 0, "open error");
    r = read (descr, cadena, 1024*2);
    val_error(r, 0, "read error");
	for(i=0; i<1024; i++)
    {
    	printf("%hi ", cadena[i]); fflush(stdout);
    }
    close (descr);
    printf ("Fin del lector.\n");
}


