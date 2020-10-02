/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TableOfSymbols.h
 * Author: etf
 *
 * Created on July 24, 2019, 9:11 AM
 */

#ifndef TABLEOFSYMBOLS_H
#define TABLEOFSYMBOLS_H

#include <iostream>
#include "Symbol.h"
#include <list>
#include <fstream>
const int UND = -1;
using namespace std;
  struct Elem{
        Symbol* sym;
        Elem* next;
        Elem(string symbol, string section, int offset, int global, int defined, string rwx){
            sym = new Symbol(symbol, section, offset,global, defined,rwx);
            next = nullptr;
        }
    
    };
    
class TableOfSymbols {
 
public:
    Elem* first;
    Elem* last;
    Elem* lastSection;
    int size;

    TableOfSymbols();
    void pushNewSection(string symbol, string section, int offset, int global, int defined,string rwx);//dodaje na pocetak liste sekciju
    void push(string symbol, string section, int offset, int global, int defined); //dodavanje na kraj liste
    Symbol* search(string symbol); //pretraga simbola u tabeli
  
    void stampaj();
    void sredi();
    virtual ~TableOfSymbols();
private:

};

#endif /* TABLEOFSYMBOLS_H */

