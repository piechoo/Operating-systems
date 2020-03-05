//Autor: Piotr Piechowicz        
//23.05.2019r    

//program klient obslugujacy problem klienta i serwera
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



int main()
{

	sleep(1);//oczekiwanie aby serwer zdazyl otworzyc kolejke
    struct mq_attr kl;//tworze kolejke - strukture     
    
    //nadaje wartosci utworzonej kolejce
    kl.mq_flags = 0;            
    kl.mq_maxmsg = 10;//max lcizba wiadomosci           
    kl.mq_msgsize = BUF;//max rozmiar wiadomosci    
    kl.mq_curmsgs = 0;
    
	char pid[10];//nazwa kolejki klienta
	char buf[BUF-10];//bufor na znaki z klawiatury
	char wynik[BUF];//zmienna na wynik od serwera
	char mes[BUF];//zmienna na wiadomosc do serwera
	
	sprintf(pid,"/%d",getpid());//zapis nazwy kolejki
	mqd_t des_k;//deskryptor kolejki klienta
	des_k=tworzKolejke(pid,&kl,O_CREAT|O_RDONLY);//stworzenie kolejki klienta
	mqd_t des_s =otworzKolejke(NAZWAS,O_WRONLY);//otworzenie kolejki klienta
	
	unsigned int k=1;
	unsigned int *prio=&k;//zmienna na priorytet

	while((fgets (buf,sizeof(buf), stdin)))//odczyt z klawiatury az do ctrl+D
	{
		sprintf(mes,"%d %s",getpid(),buf);//zapis wiadomosci do serwera(na poczatku pid potem dzialanie)
		wyslij(des_s,mes,1);//wysylanie wiadomosci do serwera
		odbierz(des_k,wynik,BUF,prio);//odbieranie rozwiazania od serwera
		printf("Wynik to: %s\n",wynik);//wypisanie wyniku
	}

	zamknijKolejke(des_s);//zamkniecie kolejki serwera
	zamknijKolejke(des_k);//zamkniecie kolejki klienta
	usunKolejke(pid);//usuniecie kolejki klienta

 return 0;

}
