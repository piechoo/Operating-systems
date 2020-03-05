//Autor: Piotr Piechowicz        
//27.03.2019r    

//program "producent" pobierajacy dane z pliku Source i zapisujacy je do potoku
#include <stdio.h>//obsluga wejscie wyjscie
#include <unistd.h>//funkcje pipe, unlink, close, read, write
#include <sys/types.h>//funckja open
#include <sys/stat.h>//funkcja open
#include <fcntl.h>//funkcja open
#include <sys/wait.h>//obsluga wait
#include <stdlib.h>//obsluga exit
#include <time.h>//do liczb pseudolosowych

#define PATHR "./Source"// sciezka i nazwa pliku zrodlowego
#define PATHK "./so4k.x"//sciezka i nazwa programu "konsumenta"
#define BUF 30 // wielkosc bufora
#define RANDOM 5// maks wielkosc wylosowanej liczby

int main()
{
    srand(time(NULL));// rozpoczecie losowania liczb pseudolosowych
    int op;//zmienna do ktorej zapisany deskryptor pliku wejsciowego
    int er,er1;//zmienne do obslugi bledow
    int potok[2];//tablica na deskryptory potokow nienazwanych
    char zapis[BUF];//bufor
    
    er=pipe(potok);//stworzenie potoku nienazwanego
    if(er==-1)
        {
         perror("Blad pipe");//obsluga bledow funkcji pipe
         exit(0);
        }
        
    switch(fork())//stworzenie procesu potomnego w ktorym otwierany program konsument
    {
        case -1:
            perror("Blad fork");//obsluga bledow fork
            exit(2);
            break;
        
        case 0:
            
            er=dup2(potok[0],0);//podmiana standardowego wejscia w procesie potomnym na potok
            if(er==-1)
            {
                perror("Blad dup");//obsluga bledow dup
                _exit(9);
            }
            
            close(potok[1]);//zamkniecie  niepotrzebnego deskryptora
            close(potok[0]);//zamkniecie deskryptora ktory juz zostal podmieniony z standardowym wejsciem
            er=execl(PATHK,PATHK,NULL);//uruchomienie programu "konsumenta"
            
            if (er==-1)
            {
                perror("Blad exec");//obsluga bledow exec
                _exit(2);
            }
            break;
        
        default:
           close(potok[0]);//zamkniecie niewykorzystywanego konca potoku
 
            break; 
    }

    op=open(PATHR,O_RDONLY,0444);//otworzenie pliku zrodlowego
    if(op==-1)
    {
        perror("Blad open");
        exit(1);
    }
    
    while((er1=(read(op,zapis,BUF)))>0)//petla odczytujaca dane z pliku dopoki napotyka znaki do odczytania
    {
        printf("Czytam: \n"); 
        er=write(potok[1],zapis,er1);//zapis z pliku do potoku
        int losuj=(rand()%RANDOM+1);//losowanie 
        if (er==-1)
            {
                perror("Blad write1");//obsluga bledow write
                exit(3);
            }       
        er=write(1,zapis,er1);//wypisanie na ekran aktualnie przesylanych danych
        if (er==-1)
            {
                perror("Blad write2");//obsluga bledow write
                exit(3);
            }         
        printf("\n\n");
        sleep(losuj);//oczekiwanie przez losowy czas
    }
    
    if (er1==-1)
        {
             perror("Blad read");//obsluga bledow read
             exit(3);
        }    
    
    er=close(op);//zamkniecie deskryptora pliku z ktorego nastepowal zapis
    if (er==-1)
        {
             perror("Blad close");//obsluga bledow close
             exit(3);
        }    
    
    er=close(potok[1]);//zamkniecie potoku do ktorego zapisywane byly dane
    if (er==-1)
        {
             perror("Blad close");//obsluga bledow close
             exit(3);
        }   
    
    er=wait(NULL);//oczekiwanie na proces potomny
    if (er==-1)
        {
             perror("Blad wait");//obsluga bledow wait
             exit(3);
        }       
 
 return 0;
}
