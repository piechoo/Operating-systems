//Autor: Piotr Piechowicz        
//23.05.2019r    

//plik naglowkowy biblioteki funkcji obslugujacych kolejki
#ifndef _KOLEJKA_H
#define _KOLEJKA_H
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>


#define NAZWAS "/Server"// nazwa kolejki serwera zdefiniowana w pliku naglowkowym aby byla w kazdym programie
#define BUF 100//maksymalny rozmiar bufora dla kazdego programu

 
//tworzy kolejke (argumenty: nazwa kolejki, struktura na podstawie ktorej otwarta kolejka, flagi)
int tworzKolejke(const char* nazwa,struct mq_attr *attr,int oflag);
//otwiera kolejke(argumenty: nazwa kolejki, flagi)
int otworzKolejke(char* nazwa,int oflag);
//zamkniecie kolejki komunikatow o podanym deskryptorze
void zamknijKolejke(mqd_t kolej);
//usuwanie kolejki o danej nazwie
void usunKolejke(char* nazwa);
//zwracanie atrybutow kolejki o danym deskryptorze
struct mq_attr* zwroc(mqd_t des,struct mq_attr *attr);
//wysylanie wiadomosci (argumenty: deskryptor kolejki do ktorej wysylamy, wskaznik do wiadomosci, priorytet wiadomosci)
void wyslij(mqd_t des,char* message,int prio);
//odbieranie wiadomosci(argumety: deskryptor kolejki z ktorej odbieramy wiadomosc, wskaznik gdzie chcemy zapisac wiadomosc, maksymalny rozmiar wiadomosci, wskaznik gdzie chcemy zapisac priorytet)
char* odbierz(mqd_t des,char* bufer,int size,unsigned int* prio);
#endif
