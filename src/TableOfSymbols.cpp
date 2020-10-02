/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TableOfSymbols.cpp
 * Author: etf
 * 
 * Created on July 24, 2019, 9:11 AM
 */

#include "TableOfSymbols.h"
#include "Klasa.h"
#include <fstream>
using namespace std;
TableOfSymbols::TableOfSymbols() {
    
    first = nullptr;
    last = nullptr;
    lastSection = nullptr;

    size = 0;
}


void TableOfSymbols::push(string symbol, string section, int offset, int global, int defined){

    	size++;
	Elem* novi = new Elem(symbol, section, offset, global, defined, "und");
	if (first == nullptr) {last = novi; first = novi;}
        else{
	last->next = novi;
	last = novi;
	}

    Elem* temp;
    temp = first;
    while (temp){
        temp->sym->pid = ++Symbol::numSymbols;
        temp = temp->next;}

    Symbol::numSymbols = 0;


}

/* 
void TableOfSymbols::stampaj (){

    Elem* temp;
    temp = first;
    cout<<"Ime | Sekcija| ofset|Global| Definisan| Redni broj | Velicina sekcije1 | Flagovi sekcija\n";
    while (temp){
       cout<<temp->sym->symbol<<" "<<temp->sym->section<<" "<<temp->sym->offset<<" "<< temp->sym->global<<" "<<temp->sym->defined<<" "<<temp->sym->pid<<" ";
        if (temp->sym->symbol == temp->sym->section) cout<<temp->sym->sectionSize<<"***"<<temp->sym->rwx;
        cout<<"\n";
        temp = temp->next;
    }
}*/
void TableOfSymbols::pushNewSection(string symbol, string section, int offset, int global, int defined, string rwx){
    
    Elem* novi = new Elem(symbol, section, offset, global, defined, rwx);
    size++;
    if (lastSection==nullptr){
        novi->next = first;
        first = novi;
        lastSection = novi;
        if (last==nullptr) last= novi;
    }else{
    
        Elem* pom = lastSection->next;        
        if (last==lastSection) last = novi;
        lastSection->next = novi;
        lastSection = novi;
        novi->next = pom;
    
    }
    
    
    Elem* temp;
    temp = first;
    while (temp){
        temp->sym->pid = ++Symbol::numSymbols;
        temp = temp->next;}

    Symbol::numSymbols = 0;

    /*
    novi->next = first;
    first = novi;*/
}
Symbol* TableOfSymbols::search(string symbol){
      

    Elem* temp;
    
    temp = first;
    
    Symbol* found = nullptr;
    
    while (temp){
    
        if (temp->sym->getSymbol() == symbol) {found = temp->sym; break;}
        temp = temp->next;
    }
    
    return found;
}

TableOfSymbols::~TableOfSymbols() {
    
    
	Elem* pom = 0;
	size = 0;
	while(first){
		pom = first;
		first = first->next;
		pom->next = 0;
		delete pom;
	}

}

void TableOfSymbols::sredi(){

    Elem* tek = first;
    
    while (tek){
        if (tek->sym->offset!=-1) tek->sym->offHex = Klasa::decToHex(tek->sym->offset);
        else tek->sym->offHex="und";
        tek = tek->next;
    
    
    }


}

