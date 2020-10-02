/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: etf
 *
 * Created on July 24, 2019, 2:45 AM
 */

#include <cstdlib>
#include "Klasa.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    //cout<<"ono sto ste uneli je\n";
    
   // for (int i=0; i<argc; i++) cout<<argv[i]<<"*"<<i<<"\n";
    
    if (((string)argv[1])!="asembler" || ((string)argv[2])!="-o") cout<<"Proverite argument komandne linije\n";
    
    Klasa* klasa = new Klasa(argv[4], argv[3]);

    cout<<"Finished\n";
    return 0;
}

