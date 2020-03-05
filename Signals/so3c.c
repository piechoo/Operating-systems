//Autor: Piotr Piechowicz        
//20.03.2019r              


//program tworzacy proces potomny, który uruchamia procesy potomne, w ktorych uruchamiany jest program do obslugi sygnalow

#include <stdio.h>//funkcja perror
#include <stdlib.h>//funkcje exit
#include <sys/types.h>//funkcja fork
#include <unistd.h>//funkcja fork i exec
#include <signal.h>//obsluga funkcji signal
#include <sys/wait.h>//obsluga wait

#define PATH "./"//sciezka do pliku uruchamianego przez exec
#define PROGRAM "so3a" //nazwa pliku uruchamianego przez exec

void handler (int syg);//funkcja przechwytujaca sygnal

void funkcja(int parent,int er_2,char* PathName,char* syg,char* opcja);//funkcja otwierajaca poprzez exec program do obslugi sygnalu

int main(int argc, char *argv[])
{
    char *opcja = argv[1]; //wybrany sposob obchodzenia sie z sygnalem
    int syg =  atoi(argv[2]); //nr sygnalu
    int potomne=3;//liczba wywolania procesow potomnych
    
    char PathName[100];//zmienna do zapisu sciezki programu
    sprintf(PathName,"%s%s.x",PATH,PROGRAM);//nazwa + sciezka programu 
    
    int i;//zmienna iteracyjna
    int zwrot1,zwrot2,zwrot3;//zmienne, do ktorch zwracana jest wartosc wait
    int er=0;//zmienna do obslugi bledow

    int parent;//zmienna do fork

    if (argc != 3)//obsluga bledu zlej ilosci argumentow
        {        
        printf("Podano zla ilosc argumentow! \nArgumenty powinny byc w postaci : [nazwa_programu]  [d/i/p]  [nr_sygnalu]. \nKoncze program.\n");     
        exit (1);
        }
    
    parent=fork();
    
        switch(parent)
        {
        case -1:
            perror("Blad Fork"); //obsluga bledow
            exit(2);
            break;
        
        case 0://1 proces potomny            
            
            signal(syg,handler);//handler dzieki ktoremu 1 proces potomny ignoruje sygnal
                        
            er=setpgid(0,0);//ustawienie procesu jako lidera swojej grupy 
            if(er==-1)
                {
                perror("Blad setpgid");//obsluga bledow funkcji setpgid
                _exit(2);
                }   
            
            printf("PID: %d    PGID: %d //Pierwszy proces potomny\n",getpid(),getpgid(0));//wypisanie PID i PGID pierwszego procesu potomnego            
                     
            for(i=0;i<potomne;i++)//tworzenie procesow potomnych i uruchamianie w nich programu do obslugi sygnalow(procesy potomne 2 rzedu)
                {
                funkcja(fork(),er, PathName,argv[2], opcja);
                }
            
            er=wait(&zwrot1);//obsluga bledow wait
            if(er==-1)
                {
                perror("Blad wait");
                exit(2);
                }
            printf("Status wait nr 1: %o\n",zwrot1);
            
            
            er=wait(&zwrot2);//obsluga bledow wait
            if(er==-1)
                {
                perror("Blad wait");
                exit(2);
                }
            printf("Status wait nr 2: %o\n",zwrot2);
            
            
            er=wait(&zwrot3);//obsluga bledow wait
            if(er==-1)
                {
                perror("Blad wait");
                exit(2);
                }
            printf("Status wait nr 3: %o\n",zwrot3);
             
            break;  
        
        default:
           
            sleep(1);
            er=kill((-1)*parent,0);//obsluga bledow kill
            if (er==-1)
                {
                perror("Blad procesu potomnego");//obsluga bledow 
                exit(3);
                }              
            
            er=kill((-1)*parent,syg);//oblsuga bledow kill
            if (er==-1)
                {
                perror("Blad Kill");//obsluga bledow 
                exit(4);
                }        
           
            er=wait(0);//obsluga bledow wait
            if(er==-1)
                {
                perror("Blad wait");
                exit(2);
                }

            break;
        }
        
return 0; 
}

void handler (int syg)
    {
     printf("Pierwszy proces potomny ignoruje sygnal: %i\n",syg);// handler ignorujacy sygnaly wysylane do procesu macierzystego
    }

void funkcja(int parent,int er_2,char* PathName,char* syg,char* opcja)//funkcja uruchamiajaca exec w procesach potomnych
{
    switch(parent)    
    {  
        case -1:
            perror("Blad Fork"); //obsluga bledow
            exit(5);
            break;
        
        case 0://proces potomny
            er_2=execl(PathName,PathName,opcja,syg, NULL);//uruchomienie programu obslugujacego sygnaly przy pomocy exec z podanym argumentem(z obsluga bledow)
            if (er_2==-1) 
                {
                perror("Blad Exec");//obsluga bledow exec
                _exit(3);
                }
            break;
                
        default://proces macierzysty nic nie robi
        
            break;
    }

}
    
  
    
