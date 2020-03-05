//Autor: Piotr Piechowicz        
//03.04.2019r    

//program "producent" pobierajacy dane z pliku Source i zapisujacy je do potoku
#include <stdio.h>//obsluga wejscie wyjscie
#include <unistd.h>//funkcje pipe, unlink, close, read, write
#include <sys/types.h>//funckja open
#include <sys/stat.h>//funkcja open
#include <fcntl.h>//funkcja open
#include <sys/wait.h>//obsluga wait
#include <stdlib.h>//obsluga exit
#include <fcntl.h>//funkcja open

#define PATHR "./Source"// sciezka i nazwa pliku zrodlowego
#define PATHK "./so5kb.x"//sciezka i nazwa programu "konsumenta"
#define FPATH "./" //sciezka do potoku
#define BUF 40 //rozmiar bufora do ktorego zapisywane dane z pliku zrodlowego

int main(int args, char * argv[])
{

int op,potok;//zmienne na deskryptory
int er,er1;//zmienne do obslugi bledow
char zapis[BUF];//bufor
char DROGA[30];//zmienna na sciezke i nzawe potoku
sprintf(DROGA,"%s%s",FPATH,argv[1]);//zapis sciezki i nazwy potoku do lancucha DROGA
      
    potok=open(DROGA,O_WRONLY);//otworzenie potoku do ktorego nastepuje zapis
    if(potok==-1)
    {
        perror("Blad open");//obsluga bledow open
        exit(1);
    }
    
    op=open(PATHR,O_RDONLY,0444);//otworzenie pliku zrodlowego
    if(op==-1)
    {
        perror("Blad open");//obsluga bledow open
        exit(1);
    }
    
    while((er1=(read(op,zapis,BUF)))>0)//petla odczytujaca znaki z pliku zrodlowego dopoki nie napotka konca 
    {
         
        printf("Czytam:\n");
        er=write(potok,zapis,er1);//zapis danych do potoku
        
        if (er==-1)
            {
                perror("Blad write do potoku");//obsluga bledow write
                exit(3);
            }   
        
        er=write(1,zapis,er1);//wypisanie danych na ekran
        if (er==-1)
            {
                perror("Blad write na ekran");//obsluga bledow write
                exit(3);
            }         
        printf("\n\n");
        sleep(1);
        
    }
    if (er1==-1)
        {
             perror("Blad read");//obsluga bledow read
             exit(3);
        } 
    
    er=close(op);//zamkniecie pliku zrodlowego
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
