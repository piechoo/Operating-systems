//Autor: Piotr Piechowicz        
//03.04.2019r    

//program "konsument" pobierajacy dane z potoku i zapisujacy je do pliku Output poprzez potok nazwany utworzony w programie producencie
#include <stdio.h>//obsluga wejscie wyjscie
#include <unistd.h>//funkcje pipe, unlink, close, read, write
#include <sys/types.h>//funckja open
#include <sys/stat.h>//funkcja open
#include <fcntl.h>//funkcja open
#include <stdlib.h>//obsluga exit
#include <fcntl.h>//funkcja open

#define PATHW "./Output"//nazwa i sciezka pliku do ktorego zapisane zostaja dane z potoku
#define BUF 30 //rozmiar bufora do ktorego zapisywane dane z potoku

int main(int argc,char* argv[])
{
    char droga[50];//lancuch znakow do zapisu sciezki i nazwy potoku
    sprintf(droga,"%s",argv[1]);
    int op,potok;//zmienne na deskryptory plikow
    int er,er1;//zmienne do obslugi bledow
    char zapis[BUF];//bufor do ktorego zapisywane dane
    
    op=open(PATHW,O_WRONLY|O_TRUNC|O_CREAT,0644);//otworzenie pliku wyjsciowego, jesli go nie ma to go tworzy , jesli juz jest to nadpisuje
    if(op==-1)
    {
        perror("Blad open");//obsluga bledow open
        exit(1);
    }
    
    potok=open(droga,O_RDONLY,0644);//otworzenie potoku z ktorego nastepuje zapis
    if(potok==-1)
    {
        perror("Blad open");//obsluga bledow open
        exit(1);
    }
    
    while ((er1=read(potok, zapis, BUF)) > 0)//petla odczytujaca dane z potoku dopoki nie napotka konca 
    {
        er=write(op,zapis,er1);//zapis danych do pliku wyjsciowego
        
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
        sleep(2);              
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
    
 return 0;
}
