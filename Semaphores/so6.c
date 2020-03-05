//Autor: Piotr Piechowicz        
//24.04.2019r    

//program powielacz uruchamiajacy program obslugujacy semafory w kombinacji fork exec - w argumentach exec przekazana nazwa semafora i ilosc wywolan sekcji krytycznej

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "so6f.h"//naglowek biblioteki z funkcjami semaforow
 
#define NAZWA "Smf"//nazwa semafora

int main (int argc, char *argv[])//w argumentach nazwa uruchamianego w exec programu, ilosc procesow otwieranych w fork/exec i liczba sekcji krytycznych kazdego procesu
{

int i;//zmienna iteracyjna
sem_t *semid;//zmienna na adres semafora nazwanego
int ileProc = atoi( argv[2]);//ilosc procesow potomnych, podana podczas uruchamiania
int er;//zmienna bledow

    if(argc !=4 )//obsluga zlego uruchomienia programu
    {       
        printf("Zla liczba parametrow\nParametryw postaci:\n[Nazwa programu obslugujacego semafor] [ilosc kopi procesu] [ilosc sekcji krytycznych w procesie potomnym]");
        exit(1);
    }
    
    if (ileProc<1||atoi(argv[3])<1)//obsluga podania zlych wartosci w ilosci porcesow potomnych lub ilosci sekcji krytycznych
    {
        printf("Parametry musza miec wartosc >= 1!\n");
        exit(1); 
    }
printf("\n\n");//koniec linii dla estetyki
semid = StworzSemafor(NAZWA,1);//tworze semafor
printf("\n\n");
	
	for(i=0;i<ileProc;i++)//petla w ktorej otwierany jest nowy proces i w nim program do obslugi semaforow
        {
            switch(fork())//tworzenie procesow potomnych                                             
            {
                    case -1:
                      perror("Blad fork");//oblsuga bledow fork                  
                      exit(1);                         
                    case 0://proces potomny             
                        
						er=execl(argv[1],argv[1],NAZWA,argv[3],NULL);//uruchomienie programu obslugujacego semafory z przekazana nazwa semafora oraz iloscia sekcji krytycznych
            			if (er==-1)
            			{
                			perror("Blad exec");//obsluga bledow exec
                			_exit(2);
         				}
         				 break;                                                    
                    
                    default://proces macierzysty nic nie robi, czeka na potomne
                    	break;
            }
        }
        
	for(i=0;i<ileProc;i++)//oczekiwanie na procesy potomne, tyle razy ile utworzono procesow potomnych
	{
    	er=wait(NULL);
    	if(er==-1)
    	{
        	perror("Blad wait");//obsluga bledow wait
        	exit(0);
    	}
	}
	        
zamknij(semid);//zamykam semafor
usun(NAZWA); //usuwam semafor

return 0;
}
