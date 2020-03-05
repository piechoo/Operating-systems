//Program wypisuje identyfikatory procesow od najstarszego do najmlodszego,korzysta z funkcji sleep
#include <stdio.h>//wejscie wyjscie , perror
#include <stdlib.h>//funkcje exit
#include <sys/types.h>//funkcja fork, funkcje identyfikatorow procesow
#include <unistd.h>//funkcja fork, funkcje identyfikatorow procesow, funkcja sleep
void printid(int space,int tata);
void tab(int num);
int main()
{
    int i;
    int parent;
    printid(0,getpid());
    for(i=0;i<3;i++)
    {
        parent=fork();
        switch (parent)
        {
        case -1:
            perror("Fork error");exit(1);//obsluga bledow funkcji fork
        case  0:
            if((i==1)) sleep(3);//sleep w celu wypisania w kolejnosci pokolen
            printid(i,parent);sleep(1);//wypisanie id i pauza aby wypisac pokolenia w kolejnosci
            break;
        default:
            break;
        }
        sleep(2);//oczekiwanie aby procesy byly w kolejnosci wg pokolen
    }
 sleep(4);//oczekiwanie procesu macierzystego na koniec procesow potomnych
 return 0;
}

void printid(int space,int tata)//funkcja wypisujaca id
{
   tab(space); printf("UID : %i ",getuid());
   printf("GID : %i ",getgid());
   printf("PID : %i ",getpid());
   printf("PPID: %i ",getppid());
   printf("PGID: %i\n",getpgid(tata));
}
void tab(int num)//funkcja do tabulacji
{
    int k;
    for (k=0;k<num;k++)
    printf("\t");
}
