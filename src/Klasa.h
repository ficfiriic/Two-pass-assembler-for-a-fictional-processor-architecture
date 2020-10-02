/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Klasa.h
 * Author: etf
 *
 * Created on July 24, 2019, 2:46 AM
 */

#ifndef KLASA_H
#define KLASA_H

#include <regex>
#include <iostream>
#include <list>
#include <array>
#include<fstream>
#include "TableOfSymbols.h"
#include "Predmetni_Program.h"
using namespace std;

class Klasa {
public:
    Klasa(string ulazniFajl, string izlazniFajl);
    void printMatches(string str, regex reg);
    Klasa(const Klasa& orig);
    virtual ~Klasa();
    void prepareThings();
    void stampaj();
    void work();
    void firstRun();
    int secoundRun();
    int searchThrowDirectives(string directive, string word1, string word2);
    int equSolution(string word1, string word2);
    int insertLabel(string label);
    int instructionWithTwoOperands(string operation, list<string> operands);
    int instructionWithOneOperand(string operation, list<string> operand);
    int instructionWithoutOperand(string operation);
    int insertNewSection(string word, string name, string flags);
    void checkEnd(int filePosition, int fileSize, int linePosition, int lineSize );
    void makeContentToUse();
    int calculateLengthOfInstruction(string operand, bool b, bool w);
    
    
    int directivesSecoundRun(list<string> line);
    int operationSecound(list<string> line);
  static string decToHex(int val);
    string decodeInstruction(string instruction, bool b, bool w);
    string decodeOperand(string operand, bool b, bool w);
    list<int> decToBin(int val);
    int instructionHelper(list<int> op);
    string operandHelper(int adr, int reg);
    string reverseString (string toRev);
    string symbolHelper(string symbol);
    void pomocnoStampaj(list<list<string>> list);
    bool relocationNeeded(Symbol* sym);
    void makeRelocation(Symbol* sym);
    bool checkAdressingWithTwoOp(int type, list<string> restLine);
    bool checkAdressingWithOneOp(int type, list<string> restLine);
    
    void stampajTOS();
    void stampajRelokacije();
protected:
    list<list<string>> sadrzaj; 
    list<list<string>> sadrzaj2;
    Predmetni_Program* predmetniProgram;
    int ending;
    bool text, data, bss, okEnd, endExists, pcRel;
    string currentSection = "und";
    int curSectInt=UND;
    int locationCounter = 0;
    int pc = 0;
    string ulazniFajl, izlazniFajl;
    ofstream izlazniTxt;
    TableOfSymbols* myTOS;
    int size;
private:
    

};

#endif /* KLASA_H */

