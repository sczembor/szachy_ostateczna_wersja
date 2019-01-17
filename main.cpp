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




int main()
{
    int kolor = 0;//kolor 0 to biale pionki
    int koniec =1;//jezeli zmienna przyjmuje wartosc jeden oznacza koniec gry
    const int N = 8;//dlgusoc tablicy
    char szachownica[N][N];//tablica przechowujaca figury na szachownicy
    std::string wybor;//wybor w poczatkowym menu
    struct ruch *pHead = nullptr; //wskaznik na glowe listy
    struct ruch *pTail = nullptr; //wskaznik na ogon listy
    reset_szachownicy(szachownica, N);
    do
    {
        czyszczenie_ekranu();
        std::cout << "   _____ _    _ ______  _____ _____ \n  / ____| |  | |  ____|/ ____/ ____| \n | |    | |__| | |__  | (___| (___  \n | |    |  __  |  __|  \\___  \\___ \\ \n | |____| |  | | |____ ____) |___) | \n  \\_____|_|  |_|______|_____/_____/ \n" <<std::endl;
        std::cout<<"WITAJ W GRZE SZACHY C++"<<std::endl;
        std::cout<<"GRA STWORZONA PRZEZ STANISŁAWA CZEMBOR"<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
        menu1(); //wysweitla początkowe menu po otwarciu programu
        std::cout<<"wybor (np. 1) :";
        std::cin>>wybor;
    }while (wybor.length() != 1 and(wybor[0] != '1' or wybor[0] != '2'));
    switch (wybor[0])
    {
        case '1'://nowa gra
        {
            reset_szachownicy(szachownica, N);
            usun_liste(pHead);
            pHead=nullptr;
            pTail=nullptr;
            czyszczenie_ekranu();
            std::ofstream plikWy("zapis_parti",std::ios::trunc);
            plikWy.close();
            break;
        }
        case '2'://gra z pliku
        {
        reset_szachownicy(szachownica, N);
        std::ifstream plikW("zapis_parti");
        if(plikW)
        {
            odczytywanie_z_pliku(kolor,plikW, szachownica);
            plikW.close();
        }
        else
            std::cout<<"nie udalo sie otworzyc pliku zapis_parti!"<<std::endl;
        czyszczenie_ekranu();
        break;
                                }
    }
    while(koniec)
    {
        gra(koniec, pHead, pTail, kolor, szachownica);
        if(koniec)
        {
            koniec =zakonczenie_gry(kolor, szachownica);
            if(!koniec)
            {
                if(kolor)
                {
                    std::cout<<std::endl<<std::endl;
                    std::cout<<"-----------------------WYGRALY BIALE GRATULACJE----------------------"<<std::endl<<std::endl<<std::endl;
                }
                else
                {
                    std::cout<<std::endl<<std::endl;
                    std::cout<<"---------------------WYGRALY CZARNE GRATULACJE---------------------"<<std::endl<<std::endl<<std::endl;
                }
                usun_liste(pHead);
                pHead=nullptr;
                pTail=nullptr;
                }
            else
                czyszczenie_ekranu();//funkcja czyszcząca ekran
        }
    }
    

    return 0;
}
