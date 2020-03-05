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
 
//tworze semafor
sem_t* StworzSemafor(char * nazwa,int wartosc);

//otworzenie semafora
sem_t* OtworzSemafor(char* nazwa);
 
//uzyskanie wartosci
void wartosc(sem_t *sem);
 
//opuszczenie semafora
void opusc(sem_t* sem);
 
//podniesienie semafora
void podnies(sem_t *sem);
 
//usuniecie semafora
void usun(char* nazwa);
 
//zamkniecie semafor
void zamknij(sem_t *sem);

