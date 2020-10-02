/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Symbol.h
 * Author: etf
 *
 * Created on July 24, 2019, 9:46 AM
 */

#ifndef SYMBOL_H
#define SYMBOL_H
#include <iostream>

using namespace std;


class Symbol {
public:
    Symbol(string symbol, string section, int offset, int global, int defined, string rwx);       
    Symbol(const Symbol& orig);
    
    string getSymbol();
    string getSection();
    int getOffset();
    int getGlobal();
    int getDefined();
    
    virtual ~Symbol();
public:
    
    static int numSections, numSymbols;
    int pid;
        string symbol; //koji simbol
        string section; //kojoj sekciji pripada
        int offset; //koliki je ofset od pocetka sekcije
        int global; // da li je globalni
        int defined; // da li je definisan unutar koda
        int sectionSize;
        string rwx;
        string offHex;
};

#endif /* SYMBOL_H */

