//Autor:Piotr Piechowicz
//13.03.2019r


//Program uruchamiajacy program wypisujacy identyfikatory procesu w kombinacji fork-exec
#include <stdio.h>//funkcja perror
#include <stdlib.h>//funkcje exit
#include <sys/types.h>//funkcja fork
#include <unistd.h>//funkcja fork i exec
#include <sys/wait.h>//funkcja wait

#define PATH "./"


int main (int argc, char *argv[])//w argv[1] nazwa programu wykonywanego przez exec
{
    
    if (argc !=2)//Sprawdzenie ilosci argumenotw
    {
        printf("Zla ilosc argumentow. Argumenty powinny byc w postaci: nazwa_programu  nazwa_programu_wywolanego.\n Koncze program.");
        exit(4);
    }
    
    char PathName[100];//sciezka programu
    int i=0;
    int er_1=0;// zmienna do błedów exec
    int er_2=0;// zmienna do błedów wait
    int parent;
    
    sprintf(PathName,"%s%s",PATH,argv[1]);
    
    for(i=0;i<3;i++)
    {
        parent=fork();
        switch (parent)
        {
        case -1:
            perror("Fork error");exit(1);//obsluga bledow forka
        case  0:
            er_1=execlp(PathName,PathName,NULL);//uruchomienie programu wypisujacego identyfikatory przy pomocy exec
            if (er_1==-1)
            {
                perror("Exec error");//obsluga bledow exec
                _exit(2);
            }
            break;
        default:
            er_2=wait(0);//oczekiwanie na potomne procesy, w zmiennej w celu obslugi bledow
            if(er_2==-1)
            {
                perror("Wait error");//obsługa błędów wait
                exit(3);
            }
            break;
        }
    }
 return 0;
}
