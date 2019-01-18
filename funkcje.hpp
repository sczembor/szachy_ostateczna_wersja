/** @file */
//  funkcje.hpp
//  Szachy
//
//  Created by Stanislaw Czembor on 13/01/2019.
//  Copyright © 2019 Stanislaw Czembor. All rights reserved.
//
#ifndef funkcje_hpp
#define funkcje_hpp

#include <string>

/** Funckja wyswietlajaca szachownice na ekranie
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @param ROZMIAR parametr okreslajacy rozmiar tablicy
  */
void wyswietl_szachownice(char tab[][8],const int ROZMIAR, int kolor);
/** Funckja resetujaca rozmieszczenie figur na szachownicy
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @param ROZMIAR parametr okreslajacy rozmiar tablicy
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 */
void reset_szachownicy(char tab[][8],const int ROZMIAR);//funkcja ustawia pionki na szachownicy w pozycji poczatkowej
/** Funkcja proszaca gracza o wprowadzenie ruchu lub pozycji z menu, wywolujaca inne funkcje sprawdzajace czy ruch jest poprawny, czy ktorys z kroli nie jest szachowany. Po poprawanie wykonanym ruchu, kolejka zostaje przekazna przeciwnikowi.
 @param koniec zmienna przechowujaca informacje o tym czy gra zostala zakonczona
 @param pHead wskaznik na poczatek listy
 @param pTail wskaznik na koniec listy
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 */
void gra(int &koniec, struct ruch * & pHead, struct ruch * & pTail,int &kolor,char tab[][8]);
/** Funckja sprawdzajaca czy na wybranym polu znajduje sie twoj pionek
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli poprawne pole, zwraca 0 gdy niepoprwane
 */
int czy_poprawny_pionek(std::string ruch,int kolor,char tab[][8]);
/** Funkcja sprawdzajca czy ruch jest poprawny, jezeli tak to przesuwa pionek bialy
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli poprawne pole, zwraca 0 gdy niepoprwane
 */
int ruch_pionek_bialy(int kolor,std::string ruch, char tab[][8]);
/** Funkcja sprawdzajca czy ruch jest poprawny, jezeli tak to przesuwa pionek czarny
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli poprawne pole, zwraca 0 gdy niepoprwane
 */
int ruch_pionek_czarny(int kolor,std::string ruch, char tab[][8]);
/** Funkcja sprawdzajca czy ruch jest poprawny, jezeli tak to przesuwa wieze
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli poprawne pole, zwraca 0 gdy niepoprwane
 */
int ruch_wieza(std::string ruch,int kolor, char tab[][8]);
/** Funkcja sprawdzajca czy ruch jest poprawny, jezeli tak to przesuwa skoczka
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli poprawne pole, zwraca 0 gdy niepoprwane
 */
int ruch_skoczek(std::string ruch,int kolor, char tab[][8]);
/** Funkcja sprawdzajca czy ruch jest poprawny, jezeli tak to przesuwa gonca
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli poprawne pole, zwraca 0 gdy niepoprwane
 */
int ruch_goniec(std::string ruch,int kolor, char tab[][8]);
/** Funkcja sprawdzajca czy ruch jest poprawny, jezeli tak to przesuwa wieze. Funkcja w zaleznosci od ruchu odwoluje sie do funkcji odpowiedzialnej za ruch gonca lub wiezy
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli poprawne pole, zwraca 0 gdy niepoprwane
 */
int ruch_hetman(std::string ruch,int kolor, char tab[][8]);
/** Funkcja sprawdzajca czy ruch jest poprawny, jezeli tak to przesuwa krola
 @param pHead wskaznik na poczatek listy
 @param pTail wskaznik na koniec listy
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli poprawne pole, zwraca 0 gdy niepoprwane
 */
int ruch_krol(struct ruch * &pHead, struct ruch *&pTail,std::string ruch,int kolor, char tab[][8]);
/** Funkcja sprawdzajaca jaka figure chcemy przesnac, i wywolujaca odpowienia funkcje odpowiedzalna za sprawdzenie ze ruch jest poprawny i przesuwajaca dana figure po szachownicy
 @param pHead wskaznik na poczatek listy
 @param pTail wskaznik na koniec listy
 @param ruch ruch wprowadzony przez gracza
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli ruch poprwany, zwraca 0 gdy niepoprwane
 */
int ruchy(struct ruch * &pHead, struct ruch *&pTail,std::string ruch,int kolor, char tab[][8]);
/** Funkcja czyszczaca ekran, robi to poprzez wyswietlenie 100 nowych linii
 */
void czyszczenie_ekranu();
/** Funkcja sprawdzajca czy w ostatnim wykonanym ruchu nie zostal zbity ktorys z kroli
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli krol nie zostal zbity, w przeciwnym przypadku zwraca 0
 */
int zakonczenie_gry(int kolor,char tab[][8]);
/** Funkcja dodajaca na koniec dwukierunkowej listy nowy element
 @param pHead wskaznik na poczatek listy
 @param pTail wskaznik na koniec listy
 @param ruch ruch wprowadzony przez gracza
 */
void dodaj_na_koniec(struct ruch *  &pHead, struct ruch * & pTail, std::string ruch);
/** Funkcja dodajaca na koniec dwukierunkowej listy nowy element
 @param pHead wskaznik na poczatek listy
 @param ss strumień do zapisu
 */
void wypisz_od_poczatku(struct ruch *pHead, std::ostream & ss);
/** Funkcja usuwajaca cala liste dwukierunkowa
 @param pHead wskaznik na poczatek listy
 */
void usun_liste(struct ruch *&pHead);
/** Funkcja ktora wczytuje zapis parti ze strumienia i rozmieszcza pionki na szachownicy na podstawie danych z pliku
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param ss strumien, z ktorego zostanie wczytana partia
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 */
void odczytywanie_z_pliku(int &kolor,std::istream & ss,char tab [][8]);
/** Funkcja wyswietlacja menu gry
 */
void menu2();
/** Funkcja wyswietlacja poczatkowe menu gry
 */
void menu1();
/** Funkcja wykonujaca roszade krtoka (o-o)
 @param pHead wskaznik na poczatek listy
 @param pTail wskaznik na koniec listy
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli wykonano roszade, zwraca 0 gdy niewykonano
 */
int rooszada_krotka(struct ruch * &pHead, struct ruch *&pTail,int kolor, char tab[][8]);
/** Funkcja wykonujaca roszade dluga (o-o-o)
 @param pHead wskaznik na poczatek listy
 @param pTail wskaznik na koniec listy
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca 1 jezeli wykonano roszade, zwraca 0 gdy niewykonano
 */
int rooszada_dluga(struct ruch * &pHead, struct ruch *&pTail,int kolor, char tab[][8]);
/** Funkcja sprawdzająca czy krol przeciwnika jest szachowany, jezeli czarny krol jest szachowany zwraca wartosc 1, jezeli bialy wartosc 2, jezeli zaden wartosc 0.
 @param pHead wskaznik na poczatek listy
 @param pTail wskaznik na koniec listy
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca wartosc typu int w zaleznosci od wyniku
 */
int szachowanie_krola(struct ruch * & pHead, struct ruch * & pTail,int kolor, char tab[][8]);
/** Funckja wyszukujaca aktualne polozenie krola przeciwnika
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @return zwraca string przechowujacy aktualne polozenie krola przeciwnika na szachownicy
 */
std::string znajdz_polozenie_krola(int kolor, char tab[][8]);
/** Funckja wyszukujaca aktualne polozenie krola przeciwnika
 @param kolor kolor gracza, ktoremu jest przyznany ruch
 @param tab dwuwymiarowa tablica przechowujaca aktualne pozycje figur na szachownicy
 @param poprawny przymuje wartosc true jezeli ruch jest poprawny
 @param docelowy_wiersz numer docelowego wiersza
 @param docelowy_kolumna numer docelowej kolumny
 @param poczatkowy_wiersz numer poczatkowego wiersza
 @param poczatkowy_kolumna numer poczatkowej kolumny
 @return zwraca wartosc typu int rowna 1 jezeli wykonano ruch, w przeciwnym wypadku zwraca 0 
 */
int ruch_figury(bool poprawny, int kolor, int docelowy_wiersz, int docelowy_kolumna, int poczatkowy_wiersz, int poczatkowy_kolumna, char tab[][8]);//funkcja wykonujaca ruch
#endif /* funkcje_hpp */
