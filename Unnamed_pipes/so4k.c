//Autor: Piotr Piechowicz        
//27.03.2019r    

//program "konsument" pobierajacy dane z potoku i zapisujacy je do pliku Output
#include <stdio.h>//obsluga wejscie wyjscie
#include <unistd.h>//funkcje pipe, unlink, close, read, write
#include <sys/types.h>//funckja open
#include <sys/stat.h>//funkcja open
#include <fcntl.h>//funkcja open
#include <stdlib.h>//obsluga exit
#include <time.h>//liczby pseudolosowe

#define PATHW "./Output"//nazwa i sciezka pliku do ktorego zapisane zostaja dane z potoku
#define BUF 20 //wielkosc bufora
#define RANDOM 5 //maksymalna wylosowywana liczba

int main()
{
    srand(time(NULL));//rozpoczecie losowania
    int losuj;//zmienna na wynik losowania
    int op;//zmienna do zapisu deskryptora pliku zrodlowego
    int er,er1;// zmienne bledow
    char zapis[BUF];// bufor
    
    op=open(PATHW,O_WRONLY|O_TRUNC,0666);//otworzenie pliku wyjsciowego
    if(op==-1)
    {
        perror("Blad open");//obsluga bledow open
        exit(1);
    }
    
    while ((er1=read(STDIN_FILENO, zapis, BUF)) > 0)//petla czytajaca z pliku zrodlowego dopoki znajduje jakies znaki
    {
        losuj=(rand()%RANDOM+1);
        er=write(op,zapis,er1);//zapis do pliku wyjsciowego z potoku 
        if (er==-1)
            {
                perror("Blad write1");//obsluga bledow write
                exit(3);
            } 
        printf("Przesylam do outputu: \n");   
        er=write(1,zapis,er1);//wypisanie danych ktore sa przesylane do pliku wyjsciowego
        if (er==-1)
            {
                perror("Blad write2");//obsluga bledow write
                exit(3);
            }         
        printf("\n\n");
        sleep(losuj);    
    }
    
   if (er1==-1)
        {
             perror("Blad read");//obsluga bledow read
             exit(3);
        }
    
    er=close(op);//zamkniecie pliku wyjsciowego
    if (er==-1)
        {
             perror("Blad close");//obsluga bledow close
             exit(3);
        }    
    
 return 0;
}
