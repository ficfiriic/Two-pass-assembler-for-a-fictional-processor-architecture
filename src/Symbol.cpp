/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Symbol.cpp
 * Author: etf
 * 
 * Created on July 24, 2019, 9:46 AM
 */

#include "Symbol.h"

int Symbol::numSections = 0;
int Symbol::numSymbols = 0;

 Symbol::Symbol(string symbol, string section, int offset, int global, int defined, string rwx)
{
 this->symbol = symbol; 
 this->section = section;
 this->offset = offset; 
 this->global = global; 
 this->defined = defined;
 this->sectionSize = -1;
 if (rwx != "und") {this->rwx = rwx;}
 else {
    // cout<<this->symbol<<"\n";
     if (this->symbol==".text") this->rwx="101";
     else if (this->symbol==".data") this->rwx = "110";
     else if (this->symbol==".bss") this->rwx="110";
     else this->rwx="und";
 }
 }



Symbol::Symbol(const Symbol& orig) {
    this->defined = orig.defined;
    this->global = orig.global;
    this->offset = orig.offset;
    this->section = orig.section;
    this->symbol = orig.symbol;
}

string Symbol::getSymbol() {return symbol;}
string Symbol::getSection() {return section;}

int Symbol::getGlobal() {return global;}

int Symbol::getOffset() {return offset;}

int Symbol::getDefined() {return defined;}

Symbol::~Symbol() {
}

