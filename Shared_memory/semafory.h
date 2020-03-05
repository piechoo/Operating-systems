//Autor: Piotr Piechowicz        
//24.04.2019r    

//naglowek biblioteki z funkcjami obslugujacymi semafory
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/sem.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
 
//tworze semafor(1 argument - nazwa semafora, 2 wartosc poczatkowa)
sem_t* StworzSemafor(char * nazwa,int wartosc);

//otworzenie semafora(1 argument - nazwa semafora)
sem_t* OtworzSemafor(char* nazwa);
 
//uzyskanie wartosci(1 argument - wskaznik do semafora)
void wartosc(sem_t *sem);
 
//opuszczenie semafora(1 argument - wskaznik do semafora)
void opusc(sem_t* sem);
 
//podniesienie semafora(1 argument - wskaznik do semafora)
void podnies(sem_t *sem);
 
//usuniecie semafora(1 argument - nazwa semafora)
void usun(char* nazwa);
 
//zamkniecie semafor(1 argument - wskaznik do semafora)
void zamknij(sem_t *sem);

