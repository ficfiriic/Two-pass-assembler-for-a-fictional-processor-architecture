/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tabela_Neizracunljivih_Simbola.h
 * Author: etf
 *
 * Created on August 12, 2019, 7:57 AM
 */

#ifndef TABELA_NEIZRACUNLJIVIH_SIMBOLA_H
#define TABELA_NEIZRACUNLJIVIH_SIMBOLA_H

#include <string>
#include "TableOfSymbols.h"
using namespace std;


class Tabela_Neizracunljivih_Simbola {
    string simbol;
    string izraz;
    string sekcija;
    Tabela_Neizracunljivih_Simbola* next;
    Tabela_Neizracunljivih_Simbola* prev;
    
    
public:
    static int brojUbacenih;
    static Tabela_Neizracunljivih_Simbola* first;
    static Tabela_Neizracunljivih_Simbola* last;
    
    Tabela_Neizracunljivih_Simbola(string simbola, string izraz, string sekcija);
    Tabela_Neizracunljivih_Simbola(const Tabela_Neizracunljivih_Simbola& orig);
    static void stampaj();
    void izbaciIzTabele();
    static int solve(TableOfSymbols* tos);
    virtual ~Tabela_Neizracunljivih_Simbola();
private:

};

#endif /* TABELA_NEIZRACUNLJIVIH_SIMBOLA_H */

