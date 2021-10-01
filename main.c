#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int obliczDlugosc(char *napis);
int sprawdzam(char *napis, char litera, char *cracked);
void tip(char *napis, char *kategoria, int attempt);
void wydrukHasla(char *napis);
int validate(char *napis);


void main() {
srand(time(NULL)); // zerowanie ziarna
int i, j, losowa;
int counter = 0; // LICZNIK WYSWIETLONYCH PODPOWIEDZI
int attempt = 1; // LICZNIK PRÓB ODGANIECIA HASLA

   char *Baza[4][8]={
       {"Kraje", "Polska","Niemcy","Hiszpania", "Portugalia", "Czechy", "Litwa","Estonia"},
       {"Kolory", "zielony","czerwony","turkusowy","fioletowy", "truskawkowy", "jagodowy", "budyniowy"},
       {"Zierzeta","kotek", "piesek", "wrona", "slimak","szczupak","osa", "komar"},
       {"Napoje","kawa", "herbata","piwo","lemoniada","kakao","mleko","cola"},
   };

//printf("Hasla w kategorii %s: %s, %s\n",Baza[3][0], Baza[3][1], Baza[3][2]);

// Zakres losowych liczb dla Kategorii 0:Kraje, 1: Kolory, 2: Zwierzeta, 3; Napoje
int min = 0;
int max = 3;

// zakres liczb losowych dla hasel w danej kategorii
int max2 = 7;
int min2 = 1; // od 1 bo 0 to nazwa kategorii hasła

int losKategorii = min + rand() % (max-min+1);
int loshasla = min2 + rand() % (max2-min2+1);

char *pointer = Baza[losKategorii][loshasla]; // ustawienie wskaźnika na wylosowanym hasle

char *kategoria_wsk = Baza[losKategorii][0]; // ustawienia wskzanika na wylosowanej kategirii hasla

int dlugoscHasla = obliczDlugosc(pointer);
//printf("Dlugosc wylosowanego hasla: %d\n", dlugoscHasla);

char password[15]={};          //tablica w której przechowywane jest hasło do odganięcia
 
//password[sizeof password - 1] = '\0';

strncpy(password, Baza[losKategorii][loshasla], sizeof(password) - strlen(password) - 1);

char cracked[strlen(password)];     // tablica do przechowywania odganietych literek, o rozmiarze takim samym jak poszukiwane hasło
char buffor[strlen(password)];

for (int i=0; i<strlen(password); i++)  cracked[i]='_';
printf("\n");
/*
printf("Kategoria hasla to: %s\n", kategoria_wsk);
printf("Wylosowane haslo to: %s\n", pointer);*/

tip(pointer, kategoria_wsk, counter);

//wydrukHasla(pointer);
int ileZgadnietych = 0;

do {

printf("\nOdganij Haslo: ");
printf("Do tej pory odganieto %d z %d liter\n", ileZgadnietych, dlugoscHasla);
for(int i=0; i < strlen(password); i++){
     printf(" %c ", cracked[i]);
     }
printf("\nProba nr: %d z %d\nPodaj literke do wyszukania w hasle: ", attempt, obliczDlugosc(pointer) + 5);
char a;
scanf(" %c", &a); // spacja przed %c kasuje znak końca linie ze strumienia stdin 
fflush(stdin);
 
 // printf("Sprawdzam czy w hasle jest podana literka\n");
 if(sprawdzam(pointer, a, cracked) ){
    printf("Literka \"%c\" trafiona! W sumie znalezionych %d literek w hasla\n", a, ileZgadnietych+=sprawdzam(pointer, a, cracked));
 }
 else{ 
      
    if(counter < 5 ){ // jesli ilos podpowiedzi nie przekroczy 5
    printf("Pudlo\n"); counter++; tip(pointer, kategoria_wsk, counter);
    }
    else{ 
        printf("Pudlo, wykorzystano wszystkie mozliwe %d podpowiedzi\n Haslo to:", counter);
        tip(pointer, kategoria_wsk, counter);
    }
 }
    attempt++;
    
    
}
    while( attempt < (dlugoscHasla+5) && ileZgadnietych != dlugoscHasla);
    

    printf("\n*** Koniec gry ***\n HASlO TO: ");
    wydrukHasla(pointer);

} // end of mainclear


//Definicje funkcji
int obliczDlugosc(char *napis){
        int ile = 0;
       /* for (int i=0; i<strlen(napis); i++){
            ile++;
        }*/
        //lub
        while(*napis != '\0'){ // na końcu napisu zawsze znajduje się NULL, jako koniec napisu.
            ile++;             // jeśli to jesteś to znaczy, że w napisie jest choć jedna literka, wiec je dodajemy
            napis++;           // inkrementujemy wskaznik, zeby pokazywal na kolejne literki, czyli elemnty w przesłanej jako argument tablicy, aż do znaku końca napisu '\0'
        }
        return ile;           // zwrcamy ilośc literek w napisie
    }

int sprawdzam(char *napis, char litera, char *cracked){
    int ileLiter = 0;
    for (int j = 0; j < strlen(napis); j++){
           //printf("%d: %c\n",j, *(napis+j));
           if(litera == *(napis+j)) { ileLiter++; cracked[j] = litera;}
        }
       //printf("Znalazlem %d liter %c w hasle\n", ileLiter, litera);
       return ileLiter;
    }

 void tip(char *napis, char *kategoria, int attempt){  
    printf("\n*TIP %d/5:\nHaslo ropoczyna sie na literke: %c i sklada sie z %d literek\nKategoria hasla to: %s\n", attempt, *napis, obliczDlugosc(napis),kategoria);
    if(attempt == 5) printf("\nPrzegarles :( Haslo bylo proste: \"%s\"\n", napis);
    }
    // wydrukHasła
    void wydrukHasla(char *napis){
        //printf("***************\n");
        printf("%s",napis);
        // printf("\n***************\n");
    }

