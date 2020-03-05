//Autor:Piotr Piechowicz
//13.03.2019r


//Program wypisuje identyfikatory danego procesu
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void printid(); //funkcja wypisujaca wszystkie id procesu
int main()
{
    printid();
    return 0;
}

void printid()
{
    printf("UID : %i ",getuid());
    printf("GID : %i ",getgid());
    printf("PID : %i ",getpid());
    printf("PPID: %i ",getppid());
    printf("PGID: %i\n",getpgid(getpid()));

}

