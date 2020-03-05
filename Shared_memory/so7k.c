//Autor: Piotr Piechowicz        
//14.05.2019r    

//program obslugujacy problem producenta i konsumenta za pomoca pamieci dzielonej
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include "semafory.h"//naglowek biblioteki funkcji semaforowych
#include "pamiec.h"//naglowek biblioteki funkcji pamieci dzielonej 

#define SIZE 30//rozmiar komorki bufora
#define ELE 5//ilosc komorek bufora
#define PATHW "./Output"//sciezka pliku wyjsciowego


typedef struct { 
	char bufor[SIZE];
 }Towar;

int main (int argc, char *argv[])
{
	char nazwaPam[20];//zmienna na nazwe pamieci dzielonej
	char nazwaSemk[20];//zmienna na nazwe semafora konsumenta
	char nazwaSemp[20];//zmienna na nazwe semafora producenta
	sprintf(nazwaPam,"%s",argv[2]);
	sprintf(nazwaSemk,"%s",argv[1]);
	sprintf(nazwaSemp,"%s",argv[3]);
	int dlugosc=atoi(argv[4]);//dlugosc pliku zrodlowego
	int er;
	int er1;//zmienne bledow
	int op;//zmienna na deskryptor pliku wyjsciowego
	int wyjmij=0;
	int des;//zmienna na deskryptor pamieci dzielonej
	int i=0;//zmienna iteracyjna
	
	
	des=OtworzPam(nazwaPam);//otworzenie pamieci dzielonej stworzonej w procesie producenta o nazwie przekazanej w argumencie
	sem_t *semk;//semafor konsumenta
	sem_t *semp;//semafor producenta
	semk = OtworzSemafor(nazwaSemk);//otworzenie semaforow stworzonych w procesie producenta
	semp = OtworzSemafor(nazwaSemp);
	Towar *wpd = (Towar *)MapujPam(des,(ELE*(sizeof(Towar))));//mapowanie pamieci dzielonej 
 	
	op=open(PATHW,O_WRONLY|O_TRUNC|O_CREAT,0644);//otworzenie pliku wyjsciowego, jesli go nie ma to go tworzy , jesli juz jest to nadpisuje
    if(op==-1)
	    {
	        perror("Blad open");//obsluga bledow open
	        exit(1);
	    }
    		
    Towar towarKons;//bufor przejsciowy
         		
    while(i<dlugosc)//dopoki zapisano mniej bajtow niz rozmiar pliku zrodlowego
 	{
    	opusc(semk);//opuszczenie semafora konsumenta
        towarKons=*(wpd+wyjmij);//zapis z pamieci dzielonej do bufora posredniego
        er1=write(1,"Zapisuje do outputu: ",21);
        if (er1==-1)
        {
        	perror("Blad write");//obsluga bledow write
            exit(2);
        }
        
        wyjmij = (wyjmij+1)%ELE;//przejscie do nastepnego elementu bufora 
      	podnies(semp);
        
        if((dlugosc-i)>SIZE)//jesli ilosc danych wieksza niz rozmiar bufora
        {
        	er=write(op,towarKons.bufor,sizeof(towarKons.bufor));//zapis danych do pliku wyjsciowego
        	er1=write(1,towarKons.bufor,SIZE);
        	if (er==-1)
        	{
        		perror("Blad write");//obsluga bledow write
        	    exit(3);
        	}
        	if (er1==-1)
        	{
        		perror("Blad write");//obsluga bledow write
        	    exit(4);
        	}
        }
        
        else//jesli rozmiar danych mniejszy od rozmiaru bufora
        {
        	er=write(op,towarKons.bufor,(dlugosc-i));//zapis danych do pliku wyjsciowego, tyle ile zostalo w pliku < rozmiar bufora
            er1=write(1,towarKons.bufor,(dlugosc-i));//wypisanie na ekran
        	if (er==-1)
        	{
        		perror("Blad write");//obsluga bledow write
            	exit(5);
            }
            if (er1==-1)
        	{
        		perror("Blad write");//obsluga bledow write
                exit(6);
            }
        }
        
        i+=SIZE;//iteracja po rozmiarze bufora
        printf("\n");//nastepna linia dla estetyki
        sleep(1);
    }

    
   	ZamknijPam(des);//zamkniecie pamieci w procesie konsumenta    
	zamknij(semp);//zamkniecie semafora w danym procesie
	zamknij(semk);
 return 0;
}













