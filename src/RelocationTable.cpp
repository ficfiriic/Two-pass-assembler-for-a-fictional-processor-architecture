/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RelocationTable.cpp
 * Author: etf
 * 
 * Created on August 3, 2019, 8:15 AM
 */

#include "RelocationTable.h"
#include "Klasa.h"
RelocationTable* RelocationTable::first = nullptr;
RelocationTable* RelocationTable::last=nullptr;

RelocationTable::RelocationTable(Symbol* sym, bool pcRel, string offset, Symbol* section, string curSection) {
    
    this->section = sym->section;
    this->curSection = curSection;
   
    if (pcRel) this->tip = "R_386_PC32";
    else this->tip = "R_386_32";
    
    this->offset = offset;
    
    if (sym->global==1) this->redniBroj=sym->pid;
    else this->redniBroj = section->pid;
    
    this->next = nullptr;
    
    if (first==nullptr) {first = this; last = this;}
    else {last->next = this; last = this;}
}
 void RelocationTable::stampaj(){

    RelocationTable* rt = RelocationTable::first;
    
    while (rt){
    
        cout<<rt->offset<<" "<<rt->tip<<" "<<rt->redniBroj<<" "<<rt->curSection<<"\n";
        rt = rt->next;
    }

}

RelocationTable::RelocationTable(const RelocationTable& orig) {
}

RelocationTable::~RelocationTable() {
}

