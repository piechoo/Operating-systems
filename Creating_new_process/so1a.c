//Program wypisuje identyfikatory danego procesu
#include <stdio.h>//wejscie wyjscie
#include <sys/types.h>//funkcje do wypisania identyfikatorow
#include <unistd.h>//funkcje do wypisania identyfikatorow
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

