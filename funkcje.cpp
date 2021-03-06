/** @file */
//  funkcje.cpp
//  Szachy
//
//  Created by Stanislaw Czembor on 13/01/2019.
//  Copyright © 2019 Stanislaw Czembor. All rights reserved.
//

#include "funkcje.hpp"
#include "struktury.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
void wyswietl_szachownice(char tab[][8],const int ROZMIAR,int kolor)
{
    int indeks_literowy = 8;
    std::cout<<"        A      B      C      D      E      F      G      H   "<<std::endl;
    
    for(int i =0;i<8;i++)
    {
        std::cout<<"     #########################################################"<<std::endl;
        std::cout<<"     #      #      #      #      #      #      #      #      #"<<std::endl;
        std::cout<<"  "<<indeks_literowy<<"  ";
        indeks_literowy--;
        for(int j =0;j<8;j++)
        {
            std::cout<<"#  "<<tab[i][j]<<"   ";
            
        }
        
        std::cout<<"#"<<std::endl;
        std::cout<<"     #      #      #      #      #      #      #      #      #"<<std::endl;
        
    }
    std::cout<<"     #########################################################"<<std::endl<<std::endl<<std::endl;
    menu2();
    if(!kolor)
        
        std::cout<<"----------------------------Ruch bialych-------------------------"<<std::endl;
    else
        std::cout<<"----------------------------Ruch czarnych-------------------------"<<std::endl;
}


void reset_szachownicy(char tab[][8],const int ROZMIAR)
{
    //gracz 2
    tab[0][0] = tab[0][7] = 'W'; //wieża
    tab[0][1] = tab[0][6] = 'S'; //skoczek
    tab[0][2] = tab[0][5] = 'G'; //goniec
    tab[0][3] = 'H'; //hetman
    tab[0][4] = 'K'; //krol
    for(int i = 0; i < 8; i++)
        tab[1][i] = 'P'; //pionki
    
    //gracz 1
    tab[7][0] = tab[7][7] = 'w';
    tab[7][1] = tab[7][6] = 's';
    tab[7][2] = tab[7][5] = 'g';
    tab[7][3] = 'h';
    tab[7][4] = 'k';
    for(int i = 0; i < 8; i++)
        tab[6][i] = 'p';
    
    //puste pola
    for(int i = 2; i < 6; i++)
        for(int j = 0; j < 8; j++)
            tab[i][j] = ' ';
}
void gra(int &koniec, struct ruch * &pHead, struct ruch *&pTail,int &kolor,char tab[][8])
{
    std::string ruch;
    int poprawny1=0;
    int poprawny2=0;
    int szachowanie=0;
    szachowanie = szachowanie_krola(pHead, pTail, kolor, tab);
    czyszczenie_ekranu();
    while(!(poprawny1 and poprawny2))
    {
        wyswietl_szachownice(tab, 8, kolor);
        if(szachowanie==1)
            std::cout<<"CZARNY KROL JEST SZACHOWANY!"<<std::endl;
        else if (szachowanie==2)
            std::cout<<"BIALY KROL JEST SZACHOWANY!"<<std::endl;
        std::cout<<"wprowadz ruch(np. a4-a6, 2, o-o): ";
        std::cin>>ruch;
        poprawny1=0;
        poprawny2=0;
        std::cout<<std::endl;
        if(ruch.length()==1)
        {
            switch(ruch[0])
            {
                case '1'://zapisz i zakoncz
                {
                    std::ofstream plikWy("zapis_parti",std::ios::app);
                    if(plikWy)
                    {
                        wypisz_od_poczatku(pHead,plikWy);
                        plikWy.close();
                    }
                    else
                        std::cout<<"nie udalo sie otworzyc pliku zapis_parti!"<<std::endl;
                    usun_liste(pHead);
                    pHead=nullptr;
                    pTail=nullptr;
                    czyszczenie_ekranu();
                    koniec =0;
                    poprawny1 =1;
                    poprawny2 =1;
                    break;
                }
                case '2'://zakoncz bez zapisywania
                {
                    usun_liste(pHead);
                    pHead=nullptr;
                    pTail=nullptr;
                    czyszczenie_ekranu();
                    koniec =0;
                    poprawny1 =1;
                    poprawny2 =1;
                    break;
                }
                default:
                    break;
            }
        }
        else
        {
            if(ruch.length()==5 or ruch.length()==3)//upewnenie sie, ze ruch wprowadzony przez uzytkownika ma dokladnie 5 lub 3 znakow, aby uniknac chodzenia po obcej pamieci
            {
                poprawny1 = czy_poprawny_pionek(ruch, kolor, tab);
                    if(poprawny1)
                    {
                        poprawny2 = ruchy(pHead,pTail,ruch, kolor, tab);
                        if(poprawny2)
                        {
                            dodaj_na_koniec(pHead, pTail, ruch);
                            if(kolor==0)
                                kolor =1;
                            else
                                kolor =0;
                        }
                    }
            }
        }
        czyszczenie_ekranu();
    }
}
int czy_poprawny_pionek(std::string ruch,int kolor,char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string roszada_krotka = "o-o";
    std::string roszada_dluga ="o-o-o";
    if(ruch == roszada_krotka or ruch==roszada_dluga)
        return 1;
    else if(kolor==1)
    {
        if(65<(tab[7-(skad[1]-49)][skad[0]-97]) and (tab[7-(skad[1]-49)][skad[0]-97])<90)
            return 1;
        else
            return 0;
    }
    if(kolor==0)
    {
        if(96<(tab[7-(skad[1]-49)][skad[0]-97]) and (tab[7-(skad[1]-49)][skad[0]-97])<122)
            return 1;
        else
            return 0;
    }
    return 0;
}
int ruch_pionek_bialy(int kolor,std::string ruch, char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string dokad = ruch.substr(3,5);
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny=false;
    char nowy_pionek;
    
    if (poczatkowy_wiersz-docelowy_wiersz>0 and poczatkowy_wiersz-docelowy_wiersz<3)
    {
        
        if(docelowy_wiersz ==poczatkowy_wiersz-1 and((tab[docelowy_wiersz][docelowy_kolumna]==' ' and poczatkowy_kolumna==docelowy_kolumna) or (abs(docelowy_kolumna-poczatkowy_kolumna)==1 and isupper(tab[docelowy_wiersz][docelowy_kolumna]))))
        {
            poprawny =true;
        }
        else if (poczatkowy_wiersz== 6 and docelowy_wiersz ==poczatkowy_wiersz-2 and (tab[docelowy_wiersz+1][docelowy_kolumna] ==' ' and (tab[docelowy_wiersz][docelowy_kolumna]==' ')))
        {
            poprawny = true;
        }
        
        
    }
    if(poprawny)
    {
        if(docelowy_wiersz==0)
        {
            std::cout<<"wprowadz figure, ktora wybierzasz(np. h) : ";
            std::cin>>nowy_pionek;
            tab[poczatkowy_wiersz][poczatkowy_kolumna] = ' ';
            tab[docelowy_wiersz][docelowy_kolumna]=nowy_pionek;
        }
        else
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        return 1;
    }
    else
    {
        return 0;
    }
    
    
}
int ruch_pionek_czarny(int kolor,std::string ruch,char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string dokad = ruch.substr(3,5);
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny=false;
    char nowy_pionek;
    
    if (docelowy_wiersz-poczatkowy_wiersz>0 and docelowy_wiersz-poczatkowy_wiersz<3)
    {
        
        if(docelowy_wiersz ==poczatkowy_wiersz+1 and((tab[docelowy_wiersz][docelowy_kolumna]==' ' and poczatkowy_kolumna==docelowy_kolumna) or (abs(docelowy_kolumna-poczatkowy_kolumna)==1 and islower(tab[docelowy_wiersz][docelowy_kolumna]))))
        {
            poprawny=true;
        }
        else if (poczatkowy_kolumna==docelowy_kolumna and poczatkowy_wiersz== 1 and docelowy_wiersz ==poczatkowy_wiersz+2 and (tab[docelowy_wiersz-1][docelowy_kolumna] ==' ' and (tab[docelowy_wiersz][docelowy_kolumna]==' ')))
        {
            poprawny = true;
        }
        
    }
    if(poprawny)
    {
        if(docelowy_wiersz==7)
        {
            std::cout<<"wprowadz figure, ktora wybierzasz(np. H) : ";
            std::cin>>nowy_pionek;
            tab[poczatkowy_wiersz][poczatkowy_kolumna] = ' ';
            tab[docelowy_wiersz][docelowy_kolumna]=nowy_pionek;
        }
        else
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        return 1;
    }
    else
    {
        return 0;
    }
    
}
int ruch_wieza(std::string ruch,int kolor, char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string dokad = ruch.substr(3,5);
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny =true;
    if(poczatkowy_kolumna==docelowy_kolumna)
    {
        if(poczatkowy_wiersz>docelowy_wiersz)
        {
            for(int i = 1 ;i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
            {
                if(tab[poczatkowy_wiersz-i][poczatkowy_kolumna]!=' ')
                    poprawny=false;
                if(!poprawny)
                    break;
            }
        }
        else if (poczatkowy_wiersz<docelowy_wiersz)
        {
            for(int i = 1 ;i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
            {
                if(tab[poczatkowy_wiersz+i][poczatkowy_kolumna]!=' ')
                    poprawny=false;
                if(!poprawny)
                    break;
            }
        }
    }
    else if (poczatkowy_wiersz==docelowy_wiersz)
    {
        if(poczatkowy_kolumna>docelowy_kolumna)
        {
            for(int i = 1 ;i<abs(docelowy_kolumna-poczatkowy_kolumna);i++)
            {
                if(tab[poczatkowy_wiersz][poczatkowy_kolumna-i]!=' ')
                    poprawny=false;
                if(!poprawny)
                    break;
            }
        }
        else if (poczatkowy_kolumna<docelowy_kolumna)
        {
            for(int i = 1 ;i<abs(docelowy_kolumna-poczatkowy_kolumna);i++)
            {
                if(tab[poczatkowy_wiersz][poczatkowy_kolumna+i]!=' ')
                    poprawny=false;
                if(!poprawny)
                    break;
            }
            
        }
        
        
    }
    if(docelowy_wiersz==poczatkowy_wiersz or docelowy_kolumna==poczatkowy_kolumna)
    {
        return ruch_figury(poprawny, kolor, docelowy_wiersz, docelowy_kolumna,poczatkowy_wiersz, poczatkowy_kolumna, tab);
    }
    else
        return 0;
}
int ruch_skoczek(std::string ruch,int kolor, char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string dokad = ruch.substr(3,5);
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny =false;
    
    if(poczatkowy_wiersz+2==docelowy_wiersz or poczatkowy_wiersz-2==docelowy_wiersz)
    {
        if(poczatkowy_kolumna+1==docelowy_kolumna or poczatkowy_kolumna-1==docelowy_kolumna)
        {
            poprawny=true;
        }
    }
    else if (poczatkowy_kolumna+2==docelowy_kolumna or poczatkowy_kolumna-2==docelowy_kolumna)
    {
        if(poczatkowy_wiersz+1==docelowy_wiersz or poczatkowy_wiersz-1==docelowy_wiersz)
        {
            poprawny=true;
        }
    }
    return ruch_figury(poprawny, kolor, docelowy_wiersz, docelowy_kolumna,poczatkowy_wiersz, poczatkowy_kolumna, tab);
    
}
int ruch_goniec(std::string ruch,int kolor, char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string dokad = ruch.substr(3,5);
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny =true;
    if(docelowy_kolumna>poczatkowy_kolumna and docelowy_wiersz>poczatkowy_wiersz)
    {
        for(int i = 1; i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
        {
            if(tab[poczatkowy_wiersz+i][poczatkowy_kolumna+i]!=' ')
                poprawny=false;
            if(!poprawny)
                break;
        }
    }
    if(docelowy_kolumna<poczatkowy_kolumna and docelowy_wiersz>poczatkowy_wiersz)
    {
        for(int i = 1; i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
        {
            if(tab[poczatkowy_wiersz+i][poczatkowy_kolumna-i]!=' ')
                poprawny=false;
            if(!poprawny)
                break;
        }
    }
    if(docelowy_kolumna<poczatkowy_kolumna and docelowy_wiersz<poczatkowy_wiersz)
    {
        for(int i = 1; i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
        {
            if(tab[poczatkowy_wiersz-i][poczatkowy_kolumna-i]!=' ')
                poprawny=false;
            if(!poprawny)
                break;
        }
    }
    if(docelowy_kolumna>poczatkowy_kolumna and docelowy_wiersz<poczatkowy_wiersz)
    {
        for(int i = 1; i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
        {
            if(tab[poczatkowy_wiersz-i][poczatkowy_kolumna+i]!=' ')
                poprawny=false;
            if(!poprawny)
                break;
        }
    }
    if(abs(docelowy_wiersz-poczatkowy_wiersz)==abs(docelowy_kolumna-poczatkowy_kolumna))
       {
        return ruch_figury(poprawny, kolor, docelowy_wiersz, docelowy_kolumna,poczatkowy_wiersz, poczatkowy_kolumna, tab);
       }
    else
        return 0;
}
int ruch_hetman(std::string ruch,int kolor, char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string dokad = ruch.substr(3,5);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    if(poczatkowy_kolumna==docelowy_kolumna or poczatkowy_wiersz==docelowy_wiersz)
        return ruch_wieza(ruch, kolor, tab);
    else
        return ruch_goniec(ruch, kolor,tab);
}
int ruch_krol(struct ruch * &pHead, struct ruch *&pTail,std::string ruch,int kolor, char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string dokad = ruch.substr(3,5);
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny =false;
    
    if(poczatkowy_wiersz+1==docelowy_wiersz or poczatkowy_wiersz-1==docelowy_wiersz or poczatkowy_wiersz==docelowy_wiersz)
    {
        if(poczatkowy_kolumna==docelowy_kolumna or poczatkowy_kolumna+1==docelowy_kolumna or poczatkowy_kolumna-1 ==docelowy_kolumna)
        {
            poprawny=true;
        }
    }
    return ruch_figury(poprawny, kolor, docelowy_wiersz, docelowy_kolumna,poczatkowy_wiersz, poczatkowy_kolumna, tab);
    
}
int rooszada_krotka(struct ruch * &pHead, struct ruch *&pTail,int kolor, char tab[][8])
{
    if(!kolor and tab[7][4]=='k' and tab[7][5]==' ' and tab[7][6]==' ' and tab[7][7]=='w')
    {
        tab[7][4]=' ';
        tab[7][7]=' ';
        tab[7][5]='w';
        tab[7][6]='k';
        dodaj_na_koniec(pHead, pTail, "e1-g1");
        dodaj_na_koniec(pHead, pTail, "h1-f1");
        return 1;
    }
    else if(kolor and tab[0][4]=='K' and tab[0][5]==' ' and tab[0][6]==' ' and tab[0 ][7]=='W')
    {
        tab[0][4]=' ';
        tab[0][7]=' ';
        tab[0][5]='W';
        tab[0][6]='K';
        dodaj_na_koniec(pHead, pTail, "e8-g8");
        dodaj_na_koniec(pHead, pTail, "h8-f8");
        return 1;
    }
    else
        return 0;
}
int rooszada_dluga(struct ruch * &pHead, struct ruch *&pTail,int kolor, char tab[][8])
{
    if(!kolor and tab[7][4]=='k' and tab[7][3]==' ' and tab[7][2]==' ' and tab[7][1]==' ' and tab[7][0]=='w')
    {
        tab[7][0]=' ';
        tab[7][1]=' ';
        tab[7][4]=' ';
        tab[7][3]='w';
        tab[7][2]='k';
        dodaj_na_koniec(pHead, pTail, "e1-c1");
        dodaj_na_koniec(pHead, pTail, "a1-d1");
        return 1;
    }
    else if(kolor and tab[0][4]=='K' and tab[0][3]==' ' and tab[0][2]==' ' and tab[0][1]==' ' and tab[0][0]=='W')
    {
        tab[0][0]=' ';
        tab[0][1]=' ';
        tab[0][4]=' ';
        tab[0][3]='W';
        tab[0][2]='K';
        dodaj_na_koniec(pHead, pTail, "e8-c8");
        dodaj_na_koniec(pHead, pTail, "a8-d8");
        return 1;
    }
    else
        return 0;
}
int ruchy(struct ruch * &pHead, struct ruch *&pTail,std::string ruch,int kolor, char tab[][8])
{
    std::string skad = ruch.substr(0,2);
    std::string dokad = ruch.substr(3,5);
    std::string roszada_krotka = "o-o";
    std::string roszada_dluga ="o-o-o";
    if(ruch == roszada_krotka)
        return rooszada_krotka(pHead,pTail,kolor,tab);
    else if(ruch ==roszada_dluga)
        return rooszada_dluga(pHead,pTail,kolor,tab);
    else
    switch (tab[7-(skad[1]-49)][skad[0]-97])
    {
        case 'p':
            return ruch_pionek_bialy(kolor,ruch,tab);
            break;
        case 'P':
            return ruch_pionek_czarny(kolor,ruch,tab);
            break;
        case 'W':
            return ruch_wieza(ruch,kolor,tab);
            break;
        case 'w':
            return ruch_wieza(ruch,kolor,tab);
            break;
        case 'S':
            return ruch_skoczek(ruch,kolor, tab);
            break;
        case 's':
            return ruch_skoczek(ruch,kolor, tab);
            break;
        case 'G':
            return ruch_goniec(ruch,kolor, tab);
            break;
        case 'g':
            return ruch_goniec(ruch,kolor, tab);
            break;
        case 'H':
            return ruch_hetman(ruch,kolor, tab);
            break;
        case 'h':
            return ruch_hetman(ruch,kolor, tab);
            break;
        case 'K':
            return ruch_krol(pHead,pTail,ruch,kolor,tab);
            break;
        case 'k':
            return ruch_krol(pHead,pTail,ruch,kolor,tab);
            break;
        default:
            return 0;
            break;
    }
}
void czyszczenie_ekranu()
{
    for(int i = 0 ;i<100;i++)
        std::cout<<std::endl;
}
int zakonczenie_gry(int kolor, char tab[][8])
{
    if(kolor)
    {
        for(int i = 0; i<8;i++)
        {
            for(int j = 0; j<8;j++)
            {
                if(tab[i][j] =='K')
                    return 1;
            }
        }
    }
    else
    {
        for(int i = 0; i<8;i++)
        {
            for(int j = 0; j<8;j++)
            {
                if(tab[i][j] =='k')
                    return 1;
            }
        }
    }
    return 0;
}
void dodaj_na_koniec(struct ruch * & pHead, struct ruch * & pTail, std::string move)
{
    if(pHead==nullptr)
    {
        ruch *pNowy = new ruch {move,nullptr,nullptr};
        pTail = pNowy;
        pHead = pNowy;
    }
    else
    {
        ruch *pNowy = new ruch{move,nullptr,pTail};
        pTail->nastepny=pNowy;
        pTail=pNowy;
    }
}
void wypisz_od_poczatku(struct ruch *pHead, std::ostream & ss)
{
    
    if(pHead)
    {
        ss<<pHead->ruch<<std::endl;
        wypisz_od_poczatku(pHead->nastepny,ss);
    }
}
void usun_liste(struct ruch *& pHead)
{
    while(pHead)
    {
        ruch * pNastepnik = pHead->nastepny;
        delete pHead;
        pHead = pNastepnik;
    }
}
void odczytywanie_z_pliku(int &kolor,std::istream & ss,char tab [][8])
{
    
    std::string ruch;
    while(std::getline( ss, ruch))
    {
        int poczatkowy_wiersz = 7-(ruch[1]-49);
        int docelowy_wiersz = 7-(ruch[4]-49);
        int poczatkowy_kolumna = ruch[0]-97;
        int docelowy_kolumna = ruch[3]-97;
        if(isupper(tab[poczatkowy_wiersz][poczatkowy_kolumna]))
            kolor = 0;
        else
            kolor = 1;
        tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
        tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        
    }
}
void menu2()
{   std::cout<<std::setw(5)<<"---------MENU GRY---------"<<std::endl;
    std::cout<<"1.ZAPISZ I ZAKONCZ"<<std::endl;
    std::cout<<"2.ZAKONCZ BEZ ZAPISYWANIA"<<std::endl;
}
void menu1()
{
    std::cout<<std::setw(5)<<"----MENU----"<<std::endl;
    std::cout<<std::setw(5)<<"1.NOWA GRA"<<std::endl;
    std::cout<<"2.GRA Z PLIKU"<<std::endl;
}
int szachowanie_krola(struct ruch * & pHead, struct ruch * & pTail,int kolor, char tab[][8])
{
    std::string polozenie_krol = znajdz_polozenie_krola(kolor, tab);
    std::string ruch_sprawdzajacy;
    int szachowanie = 0;
    for(int a = 0; a<8; a++)
    {
        for(int b = 0; b<8; b++)
        {
            
            if(kolor and islower(tab[a][b]))
            {
                char tmp = tab[a][b];
                std::string cyfra = std::to_string(8-a);
                char c = b+97;
                std::string ruch_sprawdzajacy = c+cyfra+'-'+polozenie_krol;
                szachowanie = ruchy(pHead,pTail,ruch_sprawdzajacy, !kolor, tab);
                if(szachowanie)
                {
                    std::string skad = ruch_sprawdzajacy.substr(0,2);
                    std::string dokad = ruch_sprawdzajacy.substr(3,5);
                    int poczatkowy_wiersz = 7-(skad[1]-49);
                    int docelowy_wiersz = 7-(dokad[1]-49);
                    int poczatkowy_kolumna = skad[0]-97;
                    int docelowy_kolumna = dokad[0]-97;
                    tab[docelowy_wiersz][docelowy_kolumna]= 'K';//cofniecie ruchu
                    tab[poczatkowy_wiersz][poczatkowy_kolumna] = tmp;
                    return 1;
                }
            }
            else if(!kolor and isupper(tab[a][b]))
            {
                char tmp = tab[a][b];
                std::string cyfra = std::to_string(8-a);
                char c = b+97;
                std::string ruch_sprawdzajacy = c+cyfra+'-'+polozenie_krol;
                szachowanie = ruchy(pHead,pTail,ruch_sprawdzajacy, !kolor, tab);
                if(szachowanie)
                {
                    std::string skad = ruch_sprawdzajacy.substr(0,2);
                    std::string dokad = ruch_sprawdzajacy.substr(3,5);
                    int poczatkowy_wiersz = 7-(skad[1]-49);
                    int docelowy_wiersz = 7-(dokad[1]-49);
                    int poczatkowy_kolumna = skad[0]-97;
                    int docelowy_kolumna = dokad[0]-97;
                    tab[docelowy_wiersz][docelowy_kolumna]= 'k';//cofniecie ruchu
                    tab[poczatkowy_wiersz][poczatkowy_kolumna] = tmp;
                    return 2;
                }
            }
        }
    }
    return 0;
}
std::string znajdz_polozenie_krola(int kolor, char tab[][8])
{
    if(kolor)
    {
        for(int a = 0; a<8; a++)
        {
            for(int b = 0; b<8; b++)
            {
                if(tab[a][b]=='K')//pozycja krola bialego
                {
                    std::string cyfra = std::to_string(8-a);
                    char c = b+97;
                    return std::string (c+cyfra);
                }
            }
        }
    }
    else
    {
        for(int a = 0; a<8; a++)
        {
            for(int b = 0; b<8; b++)
            {
                if(tab[a][b]=='k')//pozycja krola czarnego
                {
                    std::string cyfra = std::to_string(8-a);
                    char c = b+97;
                    return std::string (c+cyfra);
                }
            }
        }
    }
    return "0";
}
int ruch_figury(bool poprawny,int kolor, int docelowy_wiersz, int docelowy_kolumna, int poczatkowy_wiersz, int poczatkowy_kolumna, char tab[][8])
{
    if(!kolor)
    {
        if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or isupper(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or islower(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
