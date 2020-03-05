//Autor:Piotr Piechowicz
//19.03.2019r


//Program obslugujacy sygnaly
#include <stdio.h>//funkcja perror
#include <stdlib.h>//funkcje exit
#include <sys/types.h>//funkcja fork
#include <unistd.h>//funkcja fork i exec
#include <signal.h>//obsluga funkcji signal
#include <string.h>//obluga funkcji strcmp

void handler (int syg);//funkcja obslugujaca przechwycenie sygnalu 


int main (int argc, char *argv[])
{    
    
    char* opcja=argv[1];//wybrana opcja obslugi
    int nr;//nr sygnalu
    
    
    if (argc != 3)//obsluga bledu w postaci zlej liczby argumentow
        {
        printf("Podano zla ilosc argumentow! \nArgumenty powinny byc w postaci : [nazwa_programu]  [d/i/p]  [nr_sygnalu]. \nKoncze program.\n");
        exit(1);  
        }
    
    
        
    else if(argc==3)
    { 
        printf("PID: %d    PGID: %d\n",getpid(),getpgid(getppid()));//wypisanie pid procesu(ulatwia wyslanie sygnalu z konsoli)
        
        nr=atoi(argv[2]);
        
        if(nr>64)
            {
            printf("Podano zly nr sygnalu!\n Sygnaly maja numery 1-64.\n Koncze program.");
            exit(1);
            }
        
        if (strcmp (opcja,"d")==0)//wykoanie akcji domyslnej
        {
            if(signal(nr,SIG_DFL)==SIG_ERR)//obsluga bledow
                {
                perror("Blad akcji domyslnej");
                exit(2);
                }
            
            else
                {
                printf("Wykonuje akcje domyslna\n");
                pause();//oczekiwanie na sygnal
                
                }
        }
        
        else if (strcmp (opcja, "i")==0)//ignorowanie sygnalu
        {
            if ( signal (nr, SIG_IGN) == SIG_ERR )//obsluga bledow
		        {
			    perror ("Blad ignorowania");
			    exit (3);
		        }
		    
		    else
		        {
		        printf("Ignoruje sygnal nr: %d\n",nr);
		        sleep(15);//oczekiwanie na sygnal
                }
        }
        
        else if (strcmp (opcja,"p")==0)//przechwycenie sygnalu
        {
            if(signal(nr,handler)==SIG_ERR)//obsluga bledow
		        {
		    	perror ("Blad przechwytu");
		    	exit (4);
		        }
		    
		    else
		        {
		        pause();//oczekiwanie na sygnal    
		    
		        }
        }
           
        else//obsluga bledu w postaci nieobslugiwanego argumentu
            {
            printf("Zly argument wykonywanej czynnosci.\nMozliwe wybory to : d i p\nKoncze program.\n");
            exit(5);
            }
    }
        
 return 0;
}


void handler (int syg)//funkcja uruchamiana przy przechwycie sygnalu
    {
    printf ("Wlasna obsluga sygnalu nr: %d.\n", syg);
    }

  
  
  
   
   
