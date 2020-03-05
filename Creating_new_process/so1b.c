//Program wywołuje funkcje fork i wypisuje identyfikatory procesu macierzystego i potomnych, korzysta z funkcji wait
#include <stdio.h>//wejscie wyjscie , perror
#include <stdlib.h>//funkcje exit
#include <sys/types.h>//funkcja fork, funkcje identyfikatorow procesow
#include <unistd.h>//funkcja fork, funkcje identyfikatorow procesow
#include <sys/wait.h>//funkcja wait

void printid(int space,int tata);// funkcja wypisujaca id procesu

void tab(int num);// funkcja wstawajaca tabulacje(pomaga w okresleniu ktory proces jest wykonywany)

int main()
{
    int i=0;
    int er=0;
    int parent;
    printid(i,getpid());// wypisanie id przed tworzeniem procesow potomnych
    for(i=0;i<3;i++)
    {
        parent=fork();
        switch (parent)
        {
        case -1:
            perror("Fork error");exit(1);//obsluga bledow forka
        case  0:
            printid(i,parent);// wypisanie id procesow potomnych
            break;
        default:
            er=waitpid(0,NULL,0);//oczekiwanie na potomne procesy, w zmiennej w celu obslugi bledow
            if(er==-1)
            {
                perror("Wait error");//obsluga bledow waitpid
                exit(1);
            }
            break;
        }
    }
 return 0;
}

void printid(int space,int tata)
{
   tab(space); printf("UID : %i ",getuid());//id poprzedzone tabulacja (ilosc tabulacji zalezy od zmiennej space)
   printf("GID : %i ",getgid());
   printf("PID : %i ",getpid());
   printf("PPID: %i ",getppid());
   printf("PGID: %i\n",getpgid(tata));
}
void tab(int num)
{
    int k;
    for (k=0;k<num;k++)
    printf("\t");
}
