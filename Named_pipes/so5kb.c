//Autor: Piotr Piechowicz        
//03.04.2019r    

//program "konsument" pobierajacy dane z potoku i zapisujacy je do pliku Output
#include <stdio.h>//obsluga wejscie wyjscie
#include <unistd.h>//funkcje pipe, unlink, close, read, write
#include <sys/types.h>//funckja open
#include <sys/stat.h>//funkcja open
#include <fcntl.h>//funkcja open
#include <stdlib.h>//obsluga exit
#include <fcntl.h>//funkcja open

#define PATHW "./Output"//nazwa i sciezka pliku do ktorego zapisane zostaja dane z potoku
#define FPATH "./" //sciezka do potoku
#define BUF 30 //rozmiar bufora do ktorego zapisywane dane z potoku

int main(int argc,char* argv[])
{
    char DROGA[30];//zmienna na sciezke i nazwe potoku
    sprintf(DROGA,"%s%s",FPATH,argv[1]);
    int op,potok;//zmienne na deskryptory
    int er,er1;//zmienne do obslugi bledow
    char zapis[BUF];//bufor
    
    op=open(PATHW,O_WRONLY|O_TRUNC|O_CREAT,0644);//otworzenie pliku wyjsciowego, jesli nie istnieje to stworzenie , jesli istnieje to nadpisanie
    if(op==-1)
    {
        perror("Blad open");//obsluga bledow open
        exit(1);
    }
    
    potok=open(DROGA,O_RDONLY,0644);//otworzenie potoku z ktorego nastepuje odczyt danych
    if(potok==-1)
    {
        perror("Blad open");//obsluga bledow open
        exit(1);
    }
    
    while ((er1=read(potok, zapis, BUF)) > 0)//petla odczytujaca dane z potoku az nie napotka konca
    {
        er=write(op,zapis,er1);//zapis do pliku wyjsciowego
        if (er==-1)
            {
                perror("Blad write1");//obsluga bledow write
                exit(3);
            }
             
        printf("Przesylam do outputu: \n");   
        er=write(1,zapis,er1);//wypisanie danych na ekran
        printf("\n\n");
        if (er==-1)
            {
                perror("Blad write2");//obsluga bledow write
                exit(3);
            }         
        sleep(1);
       
        
    }
    
    if(er1==-1)
    {
        perror("Blad read");//obsluga bledow read
        exit(0);
    }
    
    er=close(op);//zamkniecie pliku wyjsciowego
    if (er==-1)
        {
             perror("Blad close");//obsluga bledow close
             exit(3);
        }    
    er=close(potok);//zamkniecie potoku
    if (er==-1)
        {
             perror("Blad close");//obsluga bledow close
             exit(3);
        } 
    exit(0);
    
 return 0;
}
