//Autor: Piotr Piechowicz        
//23.05.2019r    

//program serwer obslugujacy problem klienta i serwera
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <mqueue.h>
#include <unistd.h>
#include "kolejki.h"



void zamknij(int sig_num);//sig_handler
mqd_t des;//zmienna globalna na deskryptor aby zamykac kolejke przy SIG_INIT

int main()
{

    struct mq_attr ma;//tworze nowa kolejke - strukture     
    ma.mq_flags = 0;    
    ma.mq_maxmsg = 10;//max liczba wiadomosci w kolejce          
    ma.mq_msgsize = BUF;//max rozmiar wiadomosci
    ma.mq_curmsgs = 0;
	
	des =tworzKolejke(NAZWAS,&ma,(O_CREAT|O_RDONLY));//tworze kolejke serwera 
	//char odbior[BUF];
	char wynik[BUF];//bufor zawierajacy dane do wyslania do klienta
	char klient[10];//zmienna na nazwe kolejki klienta
	char znak;//zmienna na znak dzialania
	char odb[BUF];//bufor 
	int pid;//zmienna na pid klienta
	float i1, i2;//zmienna na liczby dzialania
	float res;//zmienna na wynik dzialania
	unsigned int k=1;
	unsigned int *prio=&k;//zmienna na priorytet
	if(signal(SIGINT,zamknij)==SIG_ERR)//obsluga bledow sig_handlera
	{
		perror ("Blad przechwytu");
		exit (4);
	}
	while(1)//nieskonczona petla
	{
		odbierz(des,odb,BUF,prio);//odbieranie danych od klienta
		printf("odbior: %s\n",odb);
		sscanf(odb,"%d %f%c%f",&pid,&i1,&znak,&i2);//odczyt pidu, liczb i znaku dzialania z wiadomosci klienta
		printf("pid %d, i1 %g, i2 %g, znak %c\n",pid,i1,i2,znak);//wypisanie danych
		sprintf(klient,"/%d",pid);//utworzenie nazwy kolejki klienta
		mqd_t des_k =otworzKolejke(klient,O_WRONLY);//otworzenie kolejki klienta	
			
		if (znak=='+')//dodwawanie
		{
			res=i1+i2;
			sprintf(wynik,"%.2f%c%.2f=%.2f",i1,znak,i2,res);
		}
		
		else if(znak=='-')//odejmowanie
		{
			res=i1-i2;
			sprintf(wynik,"%.2f%c%.2f=%.2f",i1,znak,i2,res);
		}
		else if(znak=='*')//mnozenie
		{
			res=i1*i2;
			sprintf(wynik,"%.2f%c%.2f=%.2f",i1,znak,i2,res);
		}
		
		else if(znak=='/')//dzielenie
		{
			if(i2!=0)
			{
				res=i1/i2;
				sprintf(wynik,"%.2f%c%.2f=%.2f",i1,znak,i2,res);
			}
			
			else//dzielenie przez 0
				sprintf(wynik,"Nie dziel przez 0!");
			
		}
		else
		{
			sprintf(wynik,"Nie rozpoznano dzialania!");
		}
		
		wyslij(des_k,wynik,1);//wysylanie wyniku do klienta
		zamknijKolejke(des_k);//zamkniecie kolejki klienta
	 }

 return 0;
}



void zamknij(int sig_num)
{
	zamknijKolejke(des);//zamkniecie kolejki serwera
	usunKolejke(NAZWAS);//usuniecie kolejki serwera
	exit(2);//wyjscie z programu
}
