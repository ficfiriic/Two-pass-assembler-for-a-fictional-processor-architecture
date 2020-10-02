/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Predmetni_Program.h
 * Author: etf
 *
 * Created on August 14, 2019, 8:52 AM
 */

#ifndef PREDMETNI_PROGRAM_H
#define PREDMETNI_PROGRAM_H
#include<list>
#include<string>

using namespace std;

class Predmetni_Program {
public:
    
    list<list<string>> predmetniProgram;
    string sectionName;
    Predmetni_Program* next;
    static Predmetni_Program* first;
    static Predmetni_Program* last;
    
    Predmetni_Program(string section);
    Predmetni_Program(const Predmetni_Program& orig);
    virtual ~Predmetni_Program();
private:

};

#endif /* PREDMETNI_PROGRAM_H */

