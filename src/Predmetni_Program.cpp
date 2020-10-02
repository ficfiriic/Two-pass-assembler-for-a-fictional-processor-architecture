/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Predmetni_Program.cpp
 * Author: etf
 * 
 * Created on August 14, 2019, 8:52 AM
 */

#include "Predmetni_Program.h"
Predmetni_Program* Predmetni_Program::first=nullptr;
Predmetni_Program* Predmetni_Program::last=nullptr;

Predmetni_Program::Predmetni_Program(string section) {
    
    this->sectionName=section;
    
    if (first==nullptr) {first=this; last = this;}
    else {last->next=this; last=this;}
    this->next = nullptr;
    
}

Predmetni_Program::Predmetni_Program(const Predmetni_Program& orig) {
}

Predmetni_Program::~Predmetni_Program() {
}

