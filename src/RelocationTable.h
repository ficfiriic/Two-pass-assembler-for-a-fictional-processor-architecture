/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RelocationTable.h
 * Author: etf
 *
 * Created on August 3, 2019, 8:15 AM
 */

#ifndef RELOCATIONTABLE_H
#define RELOCATIONTABLE_H
#include<string>
#include "Symbol.h"
#include "Klasa.h"

using namespace std;
class RelocationTable {
    
    
public:
    string section;
    int redniBroj;
    string tip;
    string offset;
    string curSection;
    RelocationTable* next;
    
    static RelocationTable* first;
    static RelocationTable* last;
    RelocationTable(Symbol* sym, bool pcRel, string offset, Symbol* section, string curSection);
    RelocationTable(const RelocationTable& orig);
    static void stampaj();
    virtual ~RelocationTable();
private:

};

#endif /* RELOCATIONTABLE_H */

