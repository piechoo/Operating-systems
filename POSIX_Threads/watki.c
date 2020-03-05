//Autor: Piotr Piechowicz        
//26.05.2019r    

//program obrazujacy dzialanie watkow i mutexow
#define _REENTRAND //do korzystania z biblioteki watkow
#include <pthread.h>//biblioteka watkow
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define WAT 4//ilosc watkow
#define SZER 82//maksymalna szerokosc konsoli
#define WYS 30//maksymalna wysokosc konsoli
#define POWT 2//ilosc sekcji krytycznych w petli
 
int LICZ=0; //zmienna wspoldzielona przez watki

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; //mutex wspolny dla watkow

void* watek(void*x); //funkcja obslugujaca watki

void gotoxy(unsigned int x, unsigned int y);//funkcja przesuwajaca kursor do danych koordyantow


int main()
{
	int i;
	int id[WAT];
	pthread_t id_watku[WAT];//tablica ID dla watkow
	for(i=0;i<WAT;i++)//tworzneie watkow
	{
		id[i]=i+1;
		if(pthread_create(&id_watku[i],NULL,(void*(*)())watek,(void*)&(id[i]))!=0)//stworzenie watkow, przekazanie im jaki maja numer
		{
			printf("Blad pthread_create\n"); //obsluga bledow
	        exit(2);
	    }
	}
	
	for(i=0;i<WAT;i++)//czekanie na watki
	{
		if(pthread_join(id_watku[i],NULL)!=0)
		{
			printf("Blad pthread_join\n"); //obsluga bledow
	        exit(2);
	    }
		
	}
	printf("\nKoncowa wartosc licznika: %d\n", LICZ);//ostateczna wartosc sekcji krytycznej
	return 0; 
}
 
void *watek(void*x)
{
	int i,id;
	int licz; ///prywatny licznik dla kazdego watku
	id=*(int*)x;
	printf("Watek o numerze: %d przed sekcjami krytycznymi\n", id);


	//sekcje krytyczne
	for(i=0;i<POWT;i++)
	{	
		pthread_mutex_lock(&m); ///opuszczenie mutexu
		licz=LICZ; //przypisanie wartosci globalnej do zmiennej prywatnej watku
		licz++;//inkrementacja zmiennej lokalnej
		gotoxy((SZER-strlen("SEKCJA KRYTYCZNA WATKU NR:%d")),WYS);
		printf("SEKCJA KRYTYCZNA WATKU NR:%d\n",id);
		gotoxy((SZER-strlen("sekcje krytyczna zacznie watek: %d")),WYS);
		printf("sekcje krytyczna zacznie watek: %d\n",id);
		gotoxy((SZER-strlen("wejscie w sekcje krytyczna nr: %d")),WYS);
		printf("wejscie w sekcje krytyczna nr: %d\n",i+1);
		sleep(2);
		LICZ=licz; //zapis z wartosci prywatnej licznika do zmiennej globalnej
		pthread_mutex_unlock(&m); //podniesienie mutexu
		printf("Watek: %d skonczyl sekcje krytyczna",id);//po podniesienu mutexu wypisanie z lewej strony
		
	}
}


void gotoxy(unsigned int x, unsigned int y)
{
	printf("\033[%d;%dH", y, x);
}


