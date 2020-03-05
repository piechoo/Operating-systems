#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>

//tworze pamiec wspoldzielona(1 argument - nazwa semafora)
int StworzPam(char* nazwa);
//otwieram pamiec wspoldzielona(1 argument - nazwa semafora)
int OtworzPam(char* nazwa);
//ustawiam rozmiar pamieci (1 argument - deskryptor pamieci,2 argument - wartosc jaka ma zostac ustawiona)
void UstawPam(int des, int dlugosc);
//zamykam pamiec(1 argument - deskryptor pamieci)
void ZamknijPam(int des);
//usuwam pamiec(1 argument - nazwa pamieci)
void UsunPam(char* nazwa);
//mapuje pamiec(1 argument - deskryptor pamieci, 2 argument - dlugosc pamieci)
void* MapujPam(int des,size_t dlugosc);
//odmapowuje pamiec(1 argument - adres odwzorowanej pamieci, 2 argument - dlugosc pamieci)
void OdmapujPam(void* adres, int dlugosc);

