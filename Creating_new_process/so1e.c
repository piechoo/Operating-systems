//Program sprawia że procesy potomne stają się swoimi liderami grupy, korzysta z funkcji setpgid
#include <stdio.h>//wejscie wyjscie , perror
#include <stdlib.h>//funkcje exit
#include <sys/types.h>//funkcja fork, funkcje identyfikatorow procesow
#include <unistd.h>//funkcja fork,funkcje identyfikatorow procesow,setpgid
#include <sys/wait.h>
void printid(int space,int tata);//funkcja wypisujaca id
void tab(int num);//funkcja wypisujaca tabulacje - pomaga odroznic procesy
int main()
{
    int i;
    int er_1=0;//zmienna do obslugi bledow funkcji wait
    int er_2=0;//zmienna do obslugi bledow setpgid
    int parent;
    printid(0,getpid());//wypisanie id przed podzialem
    for(i=0;i<3;i++)
    {
        parent=fork();
        switch (parent)
        {
        case -1:
            perror("Fork error");exit(1);//obsluga bledow funkcji fork
        case  0:
            er_2=setpgid(0,0);//ustawienie procesu jako lidera swojej grupy 
            if(er_2==-1)
            {
                perror("Setpgid error");//obsluga bledow funkcji wait
                _exit(2);
            }
            printid(i,parent);//wypisanie id
            break;
        default:
            er_1=wait(NULL);//oczekiwanie na procesy potomne
            if(er_1==-1)
            {
                perror("Wait error");//obsluga bledow funkcji wait
                exit(1);
            }
            break;
        }
    }
 return 0;
}

void printid(int space,int tata)
{
   tab(space); printf("UID : %i ",getuid());//id poprzedzone tabulacja
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
