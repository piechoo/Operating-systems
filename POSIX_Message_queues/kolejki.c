//Autor: Piotr Piechowicz        
//23.05.2019r    

//biblioteka funkcji obslugujacych kolejki
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>



//tworzy kolejke 
int tworzKolejke(char* nazwa,struct mq_attr *attr,int oflag)
{
	
	mqd_t kolej;
	kolej=mq_open(nazwa,oflag,0666,attr);
	if(kolej==((mqd_t)-1))
	{
        perror("blad tworzenia kolejki\n");
        exit(1);
    }
	else 
		printf("utworzono kolejke: %s\n", nazwa);

return kolej;
} 

//otwieranie kolejki
int otworzKolejke(char* nazwa,int oflag)
{
	
	mqd_t kolej;
	//key_t klucz=ftok(".", x ); /*tworze klucz dostepu*/
	kolej=mq_open(nazwa,oflag); /*tworze kolejke*/
	if(kolej==-1)
	{
        perror("blad otworzenia kolejki\n");
        exit(1);
    }
	else 
		printf("otworzono kolejke: %s\n", nazwa);

return kolej;
}

//zamkniecie kolejki komunikatow o podanym deskryptorze
void zamknijKolejke(mqd_t kolej)
{
	int er;
	er=mq_close(kolej);
	if(er==-1)
	{
        perror("blad mq_close");
        exit(1);
    }
	printf("zamknieto kolejke\n");
}

//usuwanie kolejki o danej nazwie
void usunKolejke(char* nazwa)
{
	int er;
	er=mq_unlink(nazwa);
	if(er==-1)
	{
        perror("blad mq_unlink");
        exit(1);
    }
	printf("usunieto kolejke %s\n",nazwa);
}

//zwracanie atrybutow kolejki
struct mq_attr* zwroc(mqd_t des,struct mq_attr *attr)
{
	int er;
	er=mq_getattr(des,attr);
	
	if(er==-1)
	{
        perror("blad getattr");
        exit(1);
    }
    
	return attr;
}

//wysylanie wiadomosci
void wyslij(mqd_t des,char* message,int prio)
{
	int er;
	er = mq_send(des,message,strlen(message)+1,prio);
	if(er==-1)
	{
        perror("blad mq_send");
        exit(1);
    }	

};

//odbieranie wiadomosci
void odbierz(mqd_t des,char* bufer,int size,unsigned int* prio)
{
	int er;
	//unsigned int *prio;
	er=mq_receive(des,bufer,size,prio);
	if(er==-1)
	{
        perror("blad mq_receive");
        exit(1);
    }	
}

 
 
 
