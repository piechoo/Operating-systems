//Autor: Piotr Piechowicz        
//24.04.2019r    

//biblioteka funkcji wykorzystywanych do obslugi semaforow
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/sem.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "so6f.h"
 
sem_t* StworzSemafor(char * nazwa,int wartosc)//stworzenie semafora
{
	sem_t *nowy;
	printf("Tworze semafor o nazwie %s w procesie %i, inicjuje go wartoscia %i\n",nazwa,getpid(),wartosc);
	nowy=sem_open(nazwa,O_CREAT|O_EXCL,0644,wartosc);
	if(nowy==SEM_FAILED)
    {
        perror("Blad sem_open");
        exit(0);
    }
	return nowy;
}
 
sem_t* OtworzSemafor(char* nazwa)//otworzenie semafora
{
	sem_t *nowy;
	nowy=sem_open(nazwa,O_EXCL);
	if(nowy==SEM_FAILED)
    {
        perror("Blad sem_open");
        exit(0);
    }
	return nowy;
}

void opusc(sem_t* sem)//opuszczanie semafora
{
	int er=0;
	er=sem_wait(sem);
	if(er==-1)
    {
        perror("Blad opuszczenia semafora");
        exit(0);    
    }
}
 
void podnies(sem_t *sem)//podnoszenie semafora
{
	int er=0;
	printf("Podnosze semafor\n");
	er=sem_post(sem);
	if(er==-1)
    {
        perror("Blad podnoszenia semafora");
        exit(0);
    }
}

void zamknij(sem_t *sem)//zamkniecie semafora
{
	int er=0;
	printf("Zamykam semafor w procesie %d \n",getpid());
	er=sem_close(sem);
	if(er==-1)
    {
        perror("Blad zamkniecia semafora");
        exit(0);
    }
}
 
void usun(char* nazwa)//usuniecie semafora
{
	int er=0;
	printf("Usuwam semafor o nazwie :%s\n",nazwa);
	er=sem_unlink(nazwa);
	if(er==-1)
    {
        perror("Blad usuwania semafora");
        exit(0);
    }
}
 
void wartosc(sem_t *sem)//podanie wartosci semafora
{
	int val;
	int er=0;
	er=sem_getvalue(sem,&val);
	if(er==-1)
    {
     perror("Blad uzyskania wartosci");
     exit(0);   
    }
    printf("Wartosc semafora to %i \n",val);
}
