/** @file */
//  main.cpp
//  Szachy
//
//  Created by Stanislaw Czembor on 13/01/2019.
//  Copyright © 2019 Stanislaw Czembor. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "funkcje.hpp"
#include "struktury.hpp"


int kolor = 0;//kolor 0 to biale pionki

int koniec =1;
const int N = 8;
char szachownica[N][N];
std::string wybor;

int main()
{
    struct ruch *pHead = nullptr;
    struct ruch *pTail = nullptr;
    reset_szachownicy(szachownica, N);
    do
    {
        menu2(); //wysweitla początkowe menu po otwarciu programu
        std::cout<<"wybor (np. 1) :";
        std::cin>>wybor;
    }while (wybor.length() != 1 and(wybor[0] != '1' or wybor[0] != '2'));
    
    do
    {
            if(wybor.length()==1)
            {
                switch (wybor[0])
                {
                    case '5'://kontynuuj
                    {
                        gra(pHead,pTail,kolor,szachownica);
                        koniec =zakonczenie_gry(kolor, szachownica);
                        if(kolor==0)
                            kolor =1;
                        else
                            kolor =0;
                        czyszczenie_ekranu();//funkcja czyszcząca ekran
                        if(!koniec)
                        {
                            if(kolor)
                                std::cout<<"wygraly biale!"<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
                    
                            else
                                std::cout<<"wygraly czarne!"<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
                            std::ofstream plikWy("zapis_partii");
                            if(plikWy)
                            {
                                wypisz_od_poczatku(pHead,plikWy);
                                plikWy.close();
                            }
                            else
                                std::cout<<"nie udalo sie otworzyc pliku zapis_partii!"<<std::endl;
                            usun_liste(pHead);
                            pHead=nullptr;
                            pTail=nullptr;
                        }
                        break;
                    }
                    case '1'://nowa gra
                    {
                        reset_szachownicy(szachownica, N);
                        usun_liste(pHead);
                        pHead=nullptr;
                        pTail=nullptr;
                        czyszczenie_ekranu();
                        std::ofstream plikWy("zapis_partii",std::ios::trunc);
                        plikWy.close();
                        break;
                    }
                    case '2'://gra z pliku
                    {
                        reset_szachownicy(szachownica, N);
                        std::ifstream plikW("zapis_partii");
                        if(plikW)
                        {
                            odczytywanie_z_pliku(kolor,plikW, szachownica);
                            plikW.close();
                        }
                        else
                            std::cout<<"nie udalo sie otworzyc pliku zapis_partii!"<<std::endl;
                        czyszczenie_ekranu();
                        break;
                    }
                    case '3'://zapisz i zakoncz
                    {
                        std::ofstream plikWy("zapis_partii",std::ios::app);
                        if(plikWy)
                        {
                            wypisz_od_poczatku(pHead,plikWy);
                            plikWy.close();
                        }
                        else
                            std::cout<<"nie udalo sie otworzyc pliku zapis_partii!"<<std::endl;
                        usun_liste(pHead);
                        pHead=nullptr;
                        pTail=nullptr;
                        czyszczenie_ekranu();
                        koniec =0;
                        break;
                    }
                    case '4'://zakoncz bez zapisywania
                    {
                        koniec =0;
                        usun_liste(pHead);
                        pHead=nullptr;
                        pTail=nullptr;
                        czyszczenie_ekranu();
                        break;
                    }
                        default:
                        std::cout<<"wprowadzono niepoprawne dane, sprobuj ponownie: ";
                        std::cin>>wybor;
                        break;
                }
            }
        if(koniec)
        {
            wyswietl_szachownice(szachownica, N);
            menu1();
            std::cout<<"wybor (np. 1) :";
            std::cin>>wybor;
        }
    }while (koniec);
    

    return 0;
}
