#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
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
           sleep(1);//czekanie az skonczy sie proces macierzysty
           printid(i,getpid());//wypisanie id 
            break;
        default:
            break;
        }
    }
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
