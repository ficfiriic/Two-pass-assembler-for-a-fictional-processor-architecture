/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tabela_Neizracunljivih_Simbola.cpp
 * Author: etf
 * 
 * Created on August 12, 2019, 7:57 AM
 */

#include "Tabela_Neizracunljivih_Simbola.h"
#include "Klasa.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
Tabela_Neizracunljivih_Simbola* Tabela_Neizracunljivih_Simbola::first = nullptr;
Tabela_Neizracunljivih_Simbola* Tabela_Neizracunljivih_Simbola::last = nullptr;
int Tabela_Neizracunljivih_Simbola::brojUbacenih=0;


Tabela_Neizracunljivih_Simbola::Tabela_Neizracunljivih_Simbola(string simbol, string izraz, string sekcija) {

    this->simbol = simbol; this->izraz= izraz;
    this->sekcija = sekcija;
    
    if (first==nullptr) {first = this; last = this; prev=nullptr;}
    else {last->next = this; this->prev=last; last = this;}

    this->next = nullptr;
}

Tabela_Neizracunljivih_Simbola::Tabela_Neizracunljivih_Simbola(const Tabela_Neizracunljivih_Simbola& orig) {
}

void Tabela_Neizracunljivih_Simbola::stampaj(){

    Tabela_Neizracunljivih_Simbola* rt = Tabela_Neizracunljivih_Simbola::first;
    
    while (rt){
    
        cout<<rt->simbol<<"***"<<rt->izraz<<"\n";
        rt = rt->next;
    }


}


int Tabela_Neizracunljivih_Simbola::solve(TableOfSymbols* tos) {

    if (tos==nullptr) return -1;
    brojUbacenih=0;
    Tabela_Neizracunljivih_Simbola* tek;
    tek = first;
    while(tek){
        
        Symbol* ss; int res;
        if (ss = tos->search(tek->izraz)) {res = ss->offset; 
                                          tos->push(tek->simbol, ss->section,res, -1,1 );
                //this->izbaciIzTabele();
                                         Tabela_Neizracunljivih_Simbola* pom;
                                         pom=tek;
                                         //cout<<"Ubacujem u tos "<<tek->simbol<<"\n";
                                         pom->izbaciIzTabele();
                                         brojUbacenih++;}
            else {
        
                int i;string pom; string pom2; 
                i=0; char op;
                while (i<tek->izraz.length()){
        if  (tek->izraz[i]=='+' || tek->izraz[i]=='-') break; 
        pom+=tek->izraz[i];
        i++;
        }
                //cout<<"*****"<<pom<<"***\n";
    
                if (i!=tek->izraz.length()) {op = tek->izraz[i];i++; 
                                       while (i<tek->izraz.length()){pom2+=tek->izraz[i];i++;}}
        
                int j; j=0; bool digi = true;
                while (j<pom.length()){ if (isdigit(pom[j])==false) {digi = false; break;}; j++;}
                //cout<<"*"<<pom<<"*"<<op<<"*"<<pom2<<"\n";
                bool fir=false;res=0;
                if (digi) {res+=stoi(pom); fir = true;}
                else {
            Symbol* s = tos->search(pom);
            if (s) {res+=s->offset; fir = true;}
            else fir = false;
        }
                bool secound = false; int res2=0;
                if (fir){
                int j; j=0; bool digi = true;
                while (j<pom2.length()){ if (isdigit(pom2[j])==false) {digi = false; break;}; j++;}
        
                if (digi) {res2+=stoi(pom2); secound = true;}
                else {
                    //cout<<"||||"<<pom2<"\n";
                    Symbol* s = tos->search(pom2);
                    if (s) {res2+=s->offset; secound = true;}
                    else secound = false;
                    }
       }

        if (fir && secound){
            if (op=='+') res+=res2;
            else res-=res2;
            
            if (res>=0) {
                Symbol* s = tos->search(tek->simbol);
                if (s) {s->section=tek->sekcija; s->offset = res;}
                else tos->push(tek->simbol, tek->sekcija,res, -1,1 );
                //this->izbaciIzTabele();
                Tabela_Neizracunljivih_Simbola* pom;
                pom=tek;
                pom->izbaciIzTabele();
                brojUbacenih++;
            }
        }
        
        
    }
        
 tek = tek->next;   
 if (tek==nullptr) {if (brojUbacenih>0) {tek = first; brojUbacenih=0;}
 }
    
    }
 if (first==nullptr) {/*cout<<"TNZ je prazna\n";*/ return 1;}
    return 0;
}


void Tabela_Neizracunljivih_Simbola::izbaciIzTabele(){


    Tabela_Neizracunljivih_Simbola* pret = this->prev;
    
    if (pret) pret->next= this->next;
    if (first==this) first=this->next;
    



}


Tabela_Neizracunljivih_Simbola::~Tabela_Neizracunljivih_Simbola() {
}

