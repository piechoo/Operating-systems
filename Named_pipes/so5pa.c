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
#define PATHK "./so5ka.x"//sciezka i nazwa programu "konsumenta"
#define FNAME "fifo"//nazwa potoku ktory tworzymy
#define FPATH "./"//sciezka potoku ktory tworzymy
#define BUF 40 //rozmiar bufora zczytujacego dane z pliku zrodlowego

int main()
{

int op;//zmienna na deskryptor pliku zrodlowego
int potok=0;//zmienna na deskryptor potoku
int er,er1;//zmienne bledow
char zapis[BUF];//bufor
char DROGA[40];//zmienna na sciezke i nazwe tworzonego potoku
sprintf(DROGA,"%s%s",FPATH,FNAME);

    if(!access(FNAME,F_OK))//sprawdzenie czy potok juz istnieje, jesli tak to zostaje usunięty
    {
        remove(FNAME);
    }
    er=mkfifo(DROGA,0644);//utworzenie potoku o podanej sciezce i nazwie
    if(er==-1)
        {
         perror("Blad mkfifo");//obsluga bledow tworzenia potoku
         exit(0);
        } 

    switch(fork())//otworzenie procesu potomnego w ktorym uruchamiany program konsument
    {
        case -1:
            perror("Blad fork");//obsluga bledow fork
            exit(2);
            break;
        
        case 0:
            
            er=execl(PATHK,PATHK,DROGA,NULL);//uruchomienie programu "konsumenta" z przekazana sciezka i nazwa potoku z ktorego bedzie korzystac
            
            if (er==-1)
            {
                perror("Blad exec");//obsluga bledow exec
                _exit(2);
            } 
            break;
        
        default:
        
            potok=open(DROGA,O_WRONLY);//otworzenie potoku 
            if(potok==-1)
            {
                perror("Blad open");//obsluga bledow open
                exit(1);
            }
 
            break; 
    }

    
    op=open(PATHR,O_RDONLY,0444);//otworzenie pliku zrodlowego
    if(op==-1)
    {
        perror("Blad open");//obsluga bledow
        exit(1);
    }
    
    while((er1=(read(op,zapis,BUF)))>0)//petla zczytujaca dane z pliku zrodlowego dopoki nie napotka konca 
    {
         
        printf("Czytam: ");
        er=write(potok,zapis,er1);//zapis danych do potoku
        printf("\n");
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
    
    er=wait(NULL);//oczekiwanie na proces potomny
    if (er==-1)
        {
             perror("Blad wait");//obsluga bledow wait
             exit(3);
        }       
 
 return 0;
}
