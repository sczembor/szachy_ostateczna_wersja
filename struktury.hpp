/** @file */
//  struktury.hpp
//  Szachy
//
//  Created by Stanislaw Czembor on 13/01/2019.
//  Copyright © 2019 Stanislaw Czembor. All rights reserved.
//

#ifndef struktury_hpp
#define struktury_hpp
/** element listy dwukierunkowej, przechowujacy informacje z jakiego pola na jakie pole przesunal sie pionek */
struct ruch
{
    std::string ruch;
    struct ruch* nastepny;
    struct ruch* poprzedni;
};
#endif /* struktury_hpp */
