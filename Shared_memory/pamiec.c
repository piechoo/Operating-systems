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


int StworzPam(char* nazwa)
{
	int des;
	printf("Tworze pamiec o nazwie %s\n",nazwa);
	des=shm_open(nazwa, O_CREAT|O_RDWR|O_TRUNC, 0644);
	if(des==-1)
    {
        perror("Blad shm_open");
        exit(1);
    }
	return des;
}

int OtworzPam(char* nazwa)
{
	int des;
	printf("Otwieram pamiec o nazwie %s\n",nazwa);
	des= shm_open(nazwa,O_RDWR, 0644);
	if(des==-1)
    {
        perror("Blad shm_open");
        exit(2);
    }
	return des;
}

void UstawPam(int des, int dlugosc)
{
	int er;
	printf("Pamiec ustawiona na wartosc :%i\n",dlugosc);
	er= ftruncate(des,dlugosc);
	if(er==-1)
    {
        perror("Blad ustawiania dlugosci");
        exit(3);
    }
}

void ZamknijPam(int des)
{
	int er;
	printf("Zamykam pamiec w procesie %i\n",getpid());
	er= close(des);
	if(er==-1)
    {
        perror("Blad zamykania pamieci");
        exit(4);
    }	
}

void UsunPam(char* nazwa)
{
	int er;
	printf("Usuwam pamiec o nazwie %s\n",nazwa);
	er= shm_unlink(nazwa);
	if(er==-1)
    {
        perror("Blad usuwania pamieci");
        exit(5);
    }	
}
void* MapujPam(int des,size_t dlugosc)
{
	void* adres;
	adres= mmap(NULL,dlugosc,PROT_READ|PROT_WRITE,MAP_SHARED,des,0);
	if(adres==MAP_FAILED)
    {
        perror("Blad mapowania pamieci");
        exit(6);
    }	
	return adres;
}

void OdmapujPam(void* adres, int dlugosc)
{
	int er;
	er=munmap(adres,dlugosc);
	if(er==-1)
    {
        perror("Blad odmapowania pamieci");
        exit(7);
    }		
}










