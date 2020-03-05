//Autor: Piotr Piechowicz        
//14.05.2019r    

//program producent obslugujacy problem producenta i konsumenta za pomoca pamieci dzielonej
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "semafory.h"//naglowek biblioteki funkcji semaforowych
#include "pamiec.h"//naglowek biblioteki funkcji pamieci wspoldzielonej

#define SIZE 30 // rozmiar komorki bufora
#define ELE 5 // ilosc komorek w buforze
#define NAZWAP "SmfP"//semafor producenta
#define NAZWAK "SmfK"//semafor konsumenta
#define PAM "Pamiecwsp"//nazwa pamieci wspoldzielonej
#define PATHR "./Source"// sciezka i nazwa pliku zrodlowego
#define NAZWAPL "Source"//nazwa pliku zrodlowego
 
 
int dlpliku(FILE *f);//funkcja zwracajaca dlugosc pliku(ilosc bajtow)

typedef struct { 
	char bufor[SIZE];
 }Towar;//struktura bufora

int main (int argc, char *argv[])
{
	char PATHK[20];//sciezka do programu konsumenta
	sprintf(PATHK,"%s",argv[1]);
	int er;
	int er1;//zmienne bledow
	int op;//zmienna na deskryptor pliku zrodlowego
	int wstaw =0;
	int des;//zmienna na deskryptor pamieci dzielonej
	int dlugosc;//zmienna na dlugosc pliku
	int i=0;//zmienna iteracyjna
	
	
	des=StworzPam(PAM);//utworzenie pamieci
	UstawPam(des,ELE*SIZE);//ustawienie wartosci pamieci
	sem_t *semp;//semafor producenta
	sem_t *semk;//semafor konsumenta
	semp = StworzSemafor(NAZWAP,ELE);//semafor producenta o wartosci = ilosc komorek bufora
	semk = StworzSemafor(NAZWAK,0);//semafor konsumetna o wartosci 0
	Towar *wpd = (Towar *)MapujPam(des,(ELE*(sizeof(Towar))));//mapowanie pamieci dzielonej w przestrzen adresowa
	
	
	FILE *fil;
	if ((fil=fopen(NAZWAPL, "r"))==NULL)//otwieranie pliku zrodlowego
	{
    	perror("Blad fopen");//obsluga bledow fopen
    	exit(5);
    }
    dlugosc=dlpliku(fil);//dlugosc pliku
    fclose(fil);//zamkniecie pliku zrodlowego
    
    char dlplik[40];
    sprintf(dlplik,"%i",dlugosc);//zmiana na string aby przekazac w argumencie programowi konsuentowi
    
    switch(fork())//otworzenie procesu potomnego w ktorym uruchamiany program konsument
    {
        case -1:
            perror("Blad fork");//obsluga bledow fork
            exit(2);
            break;
        
        case 0:
            
            er=execl(PATHK,PATHK,NAZWAK,PAM,NAZWAP,dlplik,NULL);//uruchomienie programu "konsumenta" z przekazana nazwa semafora dla konsumenta,nazwa pamieci,nazwa semafora producenta i dlugoscia pliku zrodlowego
            
            if (er==-1)
            {
                perror("Blad exec");//obsluga bledow exec
                _exit(2);
            } 
            break;
        
        default:
        
			op=open(PATHR,O_RDONLY,0444);//otworzenie pliku zrodlowego
  		  	
  		  	if(op==-1)
    		{
        		perror("Blad open");//obsluga bledow
        		exit(1);
    		}
    		
    		Towar towarProd;//bufor przejsciowy
    		
    		while(i<dlugosc)
    		{
         		
         		opusc(semp);//opuszczenie semafora producenta
        		
        		if((dlugosc-i)>SIZE)//dopoki pozostalo wiecej danych niz rozmiar bufora
        		{
                	er=read(op,towarProd.bufor,SIZE);//zapis z pliku zrodlowego do bufora przejsciowego
                	er1=write(1,"Przesylam do pamieci: ",22);//wypisywanie na ekran
        			er1=write(1,towarProd.bufor,SIZE);
        			er1=write(1,"\n",1);
        			if (er==-1)
        	    	{
        	    	    perror("Blad read");//obsluga bledow write
            		    exit(3);
            		}
            		if (er1==-1)
        	    	{
        	    	    perror("Blad write");//obsluga bledow write
            		    exit(4);
            		}
            	}
            	
            	else//jesli zostalo mniej danych niz rozmiar bufora
           		{
                	er=read(op,towarProd.bufor,(dlugosc-i));//zapis z pliku zrodlowego do bufora przejsciowego
                	er1=write(1,"Przesylam do pamieci: ",22);//wypisanie na ekran
        			er1=write(1,towarProd.bufor,(dlugosc-i));//zapis tyle danych ile zostalo do zapisania(mniej niz rozmiar bufora)
        			er1=write(1,"\n",1);
        			if (er==-1)
        	    	{
        	    	    perror("Blad read");//obsluga bledow read
            		    exit(5);
            		}
            		if (er1==-1)
        	    	{
        	    	    perror("Blad write");//obsluga bledow write
            		    exit(6);
            		}
            	}
        		*(wpd+wstaw)=towarProd;//zapisanie danych do pamieci dzielonej 
        		wstaw = (wstaw+1)%ELE;//przejscie do nastepnej komorki
        		podnies(semk);//podniesienie semafora konsumenta
        		i+=SIZE;//iteracja po rozmiarze bufora
        		sleep(3);  
    		}
            break; 
    }
    
	er=wait(NULL);//czekanie na proces potomny
	if(er==-1)
    	{
        	perror("Blad wait");//obsluga bledow wait
        	exit(0);
    	}
    	
    OdmapujPam(wpd,(ELE*(sizeof(Towar))));//odmapowanie pamieci 
	ZamknijPam(des);//zamkniecie pamieci
	UsunPam(PAM);//usuniecie pamieci
    
	zamknij(semp);//zamkniecie semafora w danym procesie
	zamknij(semk);//zamkniecie semafora w danym procesie
	usun(NAZWAP);//usuniecie semafora w danym procesie
	usun(NAZWAK);//usuniecie semafora w danym procesie
		
 return 0;
}


int dlpliku(FILE *f)//funkcja zwracajaca dlugosc pliku
{
	fseek(f,0,SEEK_END);
	int size = ftell(f);
	return size;

}
