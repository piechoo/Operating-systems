//Autor: Piotr Piechowicz        
//20.03.2019r              


//program wywolujacy program a) (obsluge sygnalow) poprzez funkcje exec i wysyla do niego sygnal

#include <stdio.h>//funkcja perror
#include <stdlib.h>//funkcje exit
#include <sys/types.h>//funkcja fork
#include <unistd.h>//funkcja fork i exec
#include <signal.h>//obsluga funkcji signal
#include <sys/wait.h>//obsluga wait


#define PATH "./"//sciezka do pliku uruchamianego przez exec
#define PROGRAM "so3a" //nazwa pliku uruchamianego przez exec
 
int main(int argc, char *argv[])
{
    char PathName[100];    
    sprintf(PathName,"%s%s.x",PATH,PROGRAM);//nazwa + sciezka programu 
    
    if (argc != 3)//obsluga bledu zlej ilosci argumentow
        {
        printf("Podano zla ilosc argumentow! \nArgumenty powinny byc w postaci : [nazwa_programu]  [d/i/p]  [nr_sygnalu]. \nKoncze program.\n");
        exit (1); 
        }
    
    int er_1=0;
    int er_2=0;//zmienne do obslugi bledow
    int er_3=0;
    
    char *opcja = argv[1]; //argument do uruchomienia programu a)
    int nr = atoi(argv[2]); //nr sygnalu
    int pid=fork(); //tworzenie procesu potomnego

    switch(pid)//switch obslugujacy proces potomny w ktorym uruchamiany jest exec 
    {
        case -1://obsluga bledow fork
            perror("Blad fork");
            exit(1);
            break;
        
        case 0://proces potomny
            
            er_1=execl(PathName,PathName,opcja,argv[2],NULL);//uruchomienie programu obslugujacego sygnaly przy pomocy exec z podanym argumentem
            if (er_1==-1)
                {
                perror("Blad exec");//obsluga bledow exec
                _exit(2);
                } 
            break;
            
        default://proces macierzysty
            sleep(1);
            
            er_2=kill(pid,0);//sprawdzenie czy proces istnieje
            if (er_2==-1)
                {
                perror("Blad procesu potomnego");//obsluga bledow 
                exit(2);
                }            
            
            er_3=kill(pid,nr);//wyslanie sygnalu do procesu potomnego
            if (er_3==-1)
                {
                perror("Blad kill");//obsluga bledow 
                exit(3);
                } 
            printf("Sygnal %d wyslany do procesu %d\n",nr,pid);
            wait(0);
                          
        break;
    }
       
 return 0;
}

  
  
    
