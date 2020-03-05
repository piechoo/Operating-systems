//Autor: Piotr Piechowicz        
//27.05.2019r    

//program przedstawiajacy dzialanie algortymu piekarnianego
#define _REENTRAND //do korzystania z biblioteki watkow
#include <pthread.h>//biblioteka watkow
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define WAT 4//ilosc watkow
#define SZER 82//maksymalna szerokosc konsoli
#define WYS 30//maksymalna wysokosc konsoli

volatile bool WYB[WAT];	//tablica wartosci logicznych ktore sa potrzebne do odpowiedniego dzialania drzwi (volatile bo zmieniana przez watki w czasie rzeczywistym)
volatile int WART[WAT]; //tablica wartosci na numerki (volatile bo zmieniana przez watki w czasie rzeczywistym)


void* watek(void*x); //funkcja obslugujaca watki

void gotoxy(unsigned int x, unsigned int y);//funkcja przesuwajaca kursor do danych koordyantow
 
int max(volatile int tab[]);
int main()
{
	int i;
	int id[WAT];
	pthread_t id_watku[WAT];//tablica ID dla watkow
	for(i=0;i<WAT;i++)
	{
		WYB[i]=0;
		WART[i]=0;
		id[i]=i;
	}
	for(i=0;i<WAT;i++)//tworzneie watkow
	{

		if(pthread_create(&id_watku[i],NULL,&watek,(void*)&(id[i]))!=0)//stworzenie watkow, przekazanie im jaki maja numer
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
	printf("\nKoniec programu - piekarni \n");//ostateczna wartosc sekcji krytycznej
	return 0; 
}
 
void *watek(void*x)
{
	int p,id;
	id=*(int*)x;
	
	
	WYB[id]=1;					//drzwi
	WART[id]=((max(WART))+1);
	WYB[id]=0;
	
	printf("Watek o id: %d i nr: %d przed sekcja krytyczna\n", id,WART[id]);
	
	for(p=0;p<WAT;++p)
	{
		if(id!=p)
		{
			while(WYB[p]){};
			while (WART[p] != 0 && (WART[p] < WART[id] || (WART[p] == WART[id] && p < id))){}
		}	
	}				//koniec drzwi
	
	//sekcja krytyczna
	gotoxy((SZER-strlen("Watek o id: %d i numerku: %d w sekcji krytycznej")),WYS);
	printf("Watek o id: %d i numerku: %d w sekcji krytycznej\n",id,WART[id]);
	gotoxy((SZER-strlen("Watek o numerku: %d wychodzi z sekcji")),WYS);
	printf("Watek o numerku: %d wychodzi z sekcji\n",WART[id]);
	sleep(1);
	WART[id]=0;//opuszczenie numerka do 0
	printf("Watek o id: %d wyszedl z sekcji i ma nr %d\n",id,WART[id]);

return 0;
}


void gotoxy(unsigned int x, unsigned int y)
{
	printf("\033[%d;%dH", y, x);
}



int max(volatile int tab[])
{

  int i, max;
 
  max = tab[0];
 
  for (i = 1; i < WAT; i++) 
  {
  	if (tab[i] > max) 
  	{
    	max = tab[i];
	}
  }
 
  return max;
}	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

