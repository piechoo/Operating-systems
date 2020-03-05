//Autor: Piotr Piechowicz        
//24.04.2019r    

//program obslugujacy semafory i wykonujacy sekcje krytyczna po opuszczeniu semafora - w argumentach otrzymuje nazwe semafora i ilosc wywolan sekcji krytycznej
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "so6f.h"//naglowek biblioteki funkcji semaforowych
 
int main (int argc, char *argv[])
{
	int i;//zmienna iteracyjna
	int ile=atoi(argv[2]);//ilosc sekcji krytycznych
	sem_t *semid;//zmienna na adres semafora
		
	semid=OtworzSemafor(argv[1]);//otworzenie semafora
	printf("\nOtwieram semafor o nazwie %s w procesie %i\n",argv[1],getpid());
	//sleep(1);//sleep dla estetyki
	for(i=0;i<ile;i++)
	{
		opusc(semid);//opuszczenie semafora
		printf("Opuszczam semafor \n");
		wartosc(semid);//podanie wartosci semafora
		//sekcja krytyczna
		printf("Sekcja krytyczna procesu %d nr %d\n",getpid(),i+1);
        printf("proces: %d rozpoczal sekcje krytyczna %d\n",getpid(),i+1);
		sleep(2);
		printf("Koniec sekcji krytycznej %d\n",i+1);
		//koniec sekcji krytycznej
    	podnies(semid);//podnoszenie semafora
    	wartosc(semid);//podanie wartosci semafora
		sleep(2);
    	printf("\n\n");
    }
    
	zamknij(semid);//zamkniecie semafora w danym procesie
 return 0;
}
