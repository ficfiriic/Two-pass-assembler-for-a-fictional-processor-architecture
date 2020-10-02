/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Klasa.cpp
 * Author: etf
 * 
 * Created on July 24, 2019, 2:46 AM
 */

#include "Klasa.h"
#include "Tabela_Neizracunljivih_Simbola.h"
#include "TableOfSymbols.h"
#include "RelocationTable.h"
#include "Predmetni_Program.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <iterator>
#include <math.h>
#include <ctype.h>
using namespace std;
struct Elem;
enum dir {
    GLOBAL, EXTERN, EQU, TEXT, DATA, SECTION, BSS, BYTE, WORD, ALIGN, SKIP
};
map<int, string> directives;

enum twoOP {
    XCHG, MOV, ADD, SUB, MUL, DIV, CMP, AND, OR, XOR, TEST, SHL, SHR
};
map<int, string> operationsWithTwoOp;

enum oneOP {
    INT, NOT, PUSH, POP, JMP, JEQ, JNE, JGT, CALL
};
map<int, string> operationsWithOneOp;

enum withoutOP {
    RET, IRET, HALT
};
map<int, string> operationsWithoutOp;

enum allOperationsEnum {
    HALTe = 1, XCHGe, INTe, MOVe, ADDe, SUBe, MULe, DIVe, CMPe, NOTe, ANDe, ORe, XORe, TESTe, SHLe, SHRe, PUSHe, POPe, JMPe, JEQe, JNEe, JGTe, CALLe, RETe, IRETe
};
map<int, string> allOperations;

enum Adr{IMMED=0, REGDIR, REGIND0, REGIND8, REGIND16, MEM};

enum Relocation{R_386_32=0, R_386_PC32};

enum ArithmeticEnum{ADDa, SUBa, MULa, DIVa, ANDa, ORa, XORa, SHLa, SHRa};
map<int, string> arithmeticOperations;

enum Jumps{JMPj, JEQj, JNEj, JGTj, CALLj};
map<int, string> jumpMap;

Klasa::Klasa(string ulazniFajl, string izlazniFajl) {

    //cout<<"Ulazni fajl je "<<ulazniFajl<<" a izlazni je "<<izlazniFajl<<"\n";
    this->ulazniFajl = ulazniFajl;
    this->izlazniFajl = izlazniFajl;
    //printf("Konstruktor klase \n");
    prepareThings();
    work();

}

void Klasa::prepareThings() {

    data = false;
    text = false;
    bss = false;
    endExists = false;
    okEnd = false;
    myTOS = new TableOfSymbols();

    directives.insert(pair<int, string>(GLOBAL, ".global"));
    directives.insert(pair<int, string>(EXTERN, ".extern"));
    directives.insert(pair<int, string>(EQU, ".equ"));
    directives.insert(pair<int, string>(TEXT, ".text"));
    directives.insert(pair<int, string>(DATA, ".data"));
    directives.insert(pair<int, string>(SECTION, ".section"));
    directives.insert(pair<int, string>(BSS, ".bss"));
    directives.insert(pair<int, string>(BYTE, ".byte"));
    directives.insert(pair<int, string>(WORD, ".word"));
    directives.insert(pair<int, string>(ALIGN, ".align"));
    directives.insert(pair<int, string>(SKIP, ".skip"));

    operationsWithTwoOp.insert(pair<int, string>(XCHG, "xchg"));
    operationsWithTwoOp.insert(pair<int, string>(MOV, "mov"));
    operationsWithTwoOp.insert(pair<int, string>(ADD, "add"));
    operationsWithTwoOp.insert(pair<int, string>(SUB, "sub"));
    operationsWithTwoOp.insert(pair<int, string>(MUL, "mul"));
    operationsWithTwoOp.insert(pair<int, string>(DIV, "div"));
    operationsWithTwoOp.insert(pair<int, string>(CMP, "cmp"));
    operationsWithTwoOp.insert(pair<int, string>(AND, "and"));
    operationsWithTwoOp.insert(pair<int, string>(OR, "or"));
    operationsWithTwoOp.insert(pair<int, string>(XOR, "xor"));
    operationsWithTwoOp.insert(pair<int, string>(TEST, "test"));
    operationsWithTwoOp.insert(pair<int, string>(SHL, "shl"));
    operationsWithTwoOp.insert(pair<int, string>(SHR, "shr"));

    operationsWithOneOp.insert(pair<int, string>(INT, "int"));
    operationsWithOneOp.insert(pair<int, string>(NOT, "not"));
    operationsWithOneOp.insert(pair<int, string>(PUSH, "push"));
    operationsWithOneOp.insert(pair<int, string>(POP, "pop"));
    operationsWithOneOp.insert(pair<int, string>(JMP, "jmp"));
    operationsWithOneOp.insert(pair<int, string>(JEQ, "jeq"));
    operationsWithOneOp.insert(pair<int, string>(JNE, "jne"));
    operationsWithOneOp.insert(pair<int, string>(JGT, "jgt"));
    operationsWithOneOp.insert(pair<int, string>(CALL, "call"));

    operationsWithoutOp.insert(pair<int, string>(RET, "ret"));
    operationsWithoutOp.insert(pair<int, string>(IRET, "iret"));
    operationsWithoutOp.insert(pair<int, string>(HALT, "halt"));

    allOperations.insert(pair<int, string>(HALTe, "halt"));
    allOperations.insert(pair<int, string>(XCHGe, "xchg"));
    allOperations.insert(pair<int, string>(INTe, "int"));
    allOperations.insert(pair<int, string>(MOVe, "mov"));
    allOperations.insert(pair<int, string>(ADDe, "add"));
    allOperations.insert(pair<int, string>(SUBe, "sub"));
    allOperations.insert(pair<int, string>(MULe, "mul"));
    allOperations.insert(pair<int, string>(DIVe, "div"));
    allOperations.insert(pair<int, string>(CMPe, "cmp"));
    allOperations.insert(pair<int, string>(NOTe, "not"));
    allOperations.insert(pair<int, string>(ANDe, "and"));
    allOperations.insert(pair<int, string>(ORe, "or"));
    allOperations.insert(pair<int, string>(XORe, "xor"));
    allOperations.insert(pair<int, string>(TESTe, "test"));
    allOperations.insert(pair<int, string>(SHLe, "shl"));
    allOperations.insert(pair<int, string>(SHRe, "shr"));
    allOperations.insert(pair<int, string>(PUSHe, "push"));
    allOperations.insert(pair<int, string>(POPe, "pop"));
    allOperations.insert(pair<int, string>(JMPe, "jmp"));
    allOperations.insert(pair<int, string>(JEQe, "jeq"));
    allOperations.insert(pair<int, string>(JNEe, "jne"));
    allOperations.insert(pair<int, string>(JGTe, "jgt"));
    allOperations.insert(pair<int, string>(CALLe, "call"));
    allOperations.insert(pair<int, string>(RETe, "ret"));
    allOperations.insert(pair<int, string>(IRETe, "iret"));

    arithmeticOperations.insert(pair<int, string>(ADDa, "add"));
    arithmeticOperations.insert(pair<int, string>(SUBa, "sub"));
    arithmeticOperations.insert(pair<int, string>(MULa, "mul"));
    arithmeticOperations.insert(pair<int, string>(DIVa, "div"));
    arithmeticOperations.insert(pair<int, string>(ANDa, "and"));
    arithmeticOperations.insert(pair<int, string>(XORa, "xor"));
    arithmeticOperations.insert(pair<int, string>(ORa, "or"));
    arithmeticOperations.insert(pair<int, string>(SHRa, "shr"));
    arithmeticOperations.insert(pair<int, string>(SHLa, "shl"));

    jumpMap.insert(pair<int,string>(JMPj, "jmp"));
    jumpMap.insert(pair<int,string>(JEQj, "jeq"));
    jumpMap.insert(pair<int,string>(JNEj, "jne"));
    jumpMap.insert(pair<int,string>(JGTj, "jgt"));
    jumpMap.insert(pair<int,string>(CALLj, "call"));
    

}

void Klasa::work() {

    makeContentToUse();

    firstRun();
    if (endExists == false) {
        cout << "Fali end\n";
        return;
    }
    //cout << "Tabela simbola izgleda" << "\n";
    izlazniTxt.open(izlazniFajl);
    if (izlazniTxt.is_open()==false){cout<<"Ne mogu da napravim fajl\n"; return ; }
    //myTOS->stampaj();

    //Tabela_Neizracunljivih_Simbola::stampaj();
    int ret = Tabela_Neizracunljivih_Simbola::solve(myTOS);
    if (ret==0) {cout<<"Nerazresen simbol!\n"; return;}
   // myTOS->stampajTOS();
   // cout << "LocationCounter ima vrednost " << locationCounter << "\n";
    //pomocnoStampaj(sadrzaj2);
    locationCounter=0;
    ret=secoundRun();
    if (ret==-1) {return;}
    izlazniTxt<<"Tabela simbola\n";
    stampajTOS();
    izlazniTxt<<"\n";
    izlazniTxt<<"Predmetni program po sekcijama\n";
    stampaj();
    izlazniTxt<<"\n";
    izlazniTxt<<"Relokacioni zapisi\n";
    stampajRelokacije();
   // cout << "LocationCounter ima vrednost " << locationCounter << "\n";
    
    //cout << "PC ima vrednost " << pc << "\n";

    //RelocationTable::stampaj();
    izlazniTxt.close();
}

void Klasa::makeContentToUse() {

    string filename = "tekst.txt";

    ifstream input;

    ending = 0;
    input.open(ulazniFajl);

    if (!input.is_open()) {
        printf("Fajl nije otvoren\n");
    }

    while (input) {
        string line;

        getline(input, line, '\n');

        regex reg("[^ ,]+"); //sve sto nije blanko znak i zarez uzmi
        printMatches(line, reg);
        if (ending == 1) break;
    }
    input.close();



}

void Klasa::printMatches(string str, regex reg) {

    sregex_iterator currentMatch(str.begin(), str.end(), reg);

    sregex_iterator lastMatch;
    int cnt = 0;
    list<string> linija;
    while (currentMatch != lastMatch) {
        smatch match = *currentMatch;
        // cout<<match.str();
        currentMatch++;
        cnt++;
        //cout<<"USAO";
        linija.push_back(match.str());
        /*         if (match.str()==".end") {
                     ending = 1;
                     if (linija.size()!=1) cout<<".end nije u novom redu"<<"\n";
                     size = sadrzaj.size();
                     break;}
            }
            if (cnt) */
    }
    sadrzaj.push_back(linija);


}

Klasa::Klasa(const Klasa& orig) {
}

void Klasa::stampaj() {
    Predmetni_Program* tek=Predmetni_Program::first;
    
    while (tek!=nullptr){
     list<list<string>>   pp = tek->predmetniProgram;
     
    izlazniTxt<<tek->sectionName<<"\n";
    while (!pp.empty()) {

        list<string> linija = (list<string>) pp.front();
        pp.pop_front();

        while (!linija.empty()) {
            string str = (string) linija.front();
            izlazniTxt << str;
           izlazniTxt << " ";
            linija.pop_front();
        };

        izlazniTxt << "\n";
    }

     tek = tek->next;
}
}

void Klasa::stampajTOS(){


    myTOS->sredi();
    Elem* temp;
    temp = myTOS->first;
   izlazniTxt<<"Ime | Sekcija| ofset|Global| Definisan| Redni broj | Velicina sekcije1 | Flagovi sekcija\n";
    while (temp){
       izlazniTxt<<temp->sym->symbol<<" "<<temp->sym->section<<" "<<temp->sym->offHex<<" "<< temp->sym->global<<" "<<temp->sym->defined<<" "<<temp->sym->pid<<" "<<temp->sym->sectionSize<<" "<<temp->sym->rwx;
        izlazniTxt<<"\n";
        temp = temp->next;
    }

}

void Klasa::stampajRelokacije() {
    
    RelocationTable* rt = RelocationTable::first;
    
    while (rt){
    
        izlazniTxt<<rt->offset<<" "<<rt->tip<<" "<<rt->redniBroj<<" "<<rt->curSection<<"\n";
        rt = rt->next;
    }


}

void Klasa::pomocnoStampaj(list<list<string>> pom ){

    while (!pom.empty()) {

        list<string> linija = (list<string>) pom.front();
        pom.pop_front();

        while (!linija.empty()) {
            string str = (string) linija.front();
            cout << str;
            cout << " ";
            linija.pop_front();
        };

        cout << "\n";
    }

}

void Klasa::firstRun() {

    int size;
    int i = 0;
    int ret = 0;
    size = sadrzaj.size();
    while (i < size) {
        //pretraga po linijama
        i++; //povecavam broj procitanih linija
        list<string> linija = sadrzaj.front(); //citam prvu liniju
        sadrzaj2.push_back(linija); // cuvam tu prvu liniju
        sadrzaj.pop_front(); // skidam prvu liniju, da bih dobila novu prvu

        int lineSize = linija.size();
        int j = 0;
        string key = "und";
        string tempWord = "und";
        while (j < lineSize) {
            j++;
            string word = linija.front(); //uzima prvu rec iz niza reci
            linija.pop_front();
            //if (i==(sadrzaj.size()+i) && word!=".end") {cout<<"Fali end!"<<"\n"; return;}
            if (j == 1 && word[word.length() - 1] == ':') {
                ret = insertLabel(word); lineSize--; j=0;
                continue;
            }
            if (word[0] == '.') {
                if (word == ".end") {
                    //cout<<j<< " line size "<<lineSize<<"\n";
                    checkEnd(i, size, j, lineSize);
                    return;
                }
                if ((word == ".text" || word == ".data" || word == ".bss") && lineSize == 1) {
                    ret = insertNewSection(word, "und", "und");
                    continue;
                }
                if ((word == ".text" || word == ".data" || word == ".bss") && lineSize > 2) {
                    cout << "Syntax error, too much operands for section!\n";
                    return;
                }
                if (word == ".byte" || word == ".word") {
                    ret = searchThrowDirectives(word, "undStr", "undStr");
                    j = lineSize;
                }
                if (word == ".equ" && lineSize != 3) {
                    cout << "Syntax error!" << "\n";
                    return;
                }
                if ((word == ".skip" || word == ".align") && lineSize != 2) {
                    cout << "Syntax error!" << "\n";
                    return;
                }
                key = word;
                //cout<<"Key word je "<< key<<" i njen lineSize je "<<lineSize<<"\n";
            } else if (key != "und") {
                //cout<<j<<"\n";
                //cout<<word<<"\n";
                if (key == ".global" || key == ".skip" || key == ".extern" || key == ".align") ret = searchThrowDirectives(key, word, "undStr");
                else if (key == ".text" || key == ".data" || key == ".bss") {
                    ret = insertNewSection(key, "und", word);
                } else if (key == ".section" && lineSize == 2) ret = insertNewSection(key, word, "und");
                else if (tempWord == "und") tempWord = word; //ovde ulazi samo .equ ili /section da postavi ptvi operand
                else if (key == ".section" && lineSize == 3) ret = insertNewSection(key, tempWord, word);
                else ret = searchThrowDirectives(key, tempWord, word); //nakon citanja drugog operanda .equ poziva
            } else if (linija.size() == 2) {
                ret = instructionWithTwoOperands(word, linija);
                j += 2;
            } else if (linija.size() == 1) {
                ret = instructionWithOneOperand(word, linija);
                j++;
            } else if (linija.size() == 0) {
                ret = instructionWithoutOperand(word);
            }
            else {
                cout << "Syntax error broj operanada! " << word << "\n";
                j += linija.size();
            }
        }

        if (ret == -1) return;

    }
}

int Klasa::searchThrowDirectives(string directive, string word1, string word2) {

    map<int, string>::iterator itr;
    int found = 0;
    int keyDirective = -1;
    for (itr = directives.begin(); itr != directives.end(); ++itr) {
        if (itr->second == directive) {
            found = 1;
            keyDirective = itr->first;
            break;
        }
    };

    if (found == 0) {
        cout << "Syntax error!" << "\n";
        return -1;
    } else {
        Symbol* sym = nullptr; Symbol* sec = nullptr;
        int x;
        if (word1 != "undStr") sym = myTOS->search(word1); //da li vec postoji
        if (directive == ".skip" || directive == ".align") {
            bool digi = true;
            for (int i = 0; i < word1.size(); i++) if (!isdigit(word1[i])) {
                    digi = false;
                    cout << "Proverite vreednost\n";
                    return -1;
                }
            x = stoi(word1);
        }
        switch (keyDirective) {
            case GLOBAL:
                if (sym) sym->global = 1;
                else myTOS->push(word1, currentSection, -1, 1, -1);
                return 0;
                break;
            case EXTERN:
                // cout<<word1<<"\n";
                if (sym) {
                    if (sym->defined == 1) cout << "Syntax error!" << "\n";
                    return -1;
                } else myTOS->push(word1, currentSection, -1, 1, -1);
                return 0;
                break;
            case EQU:

                return equSolution(word1, word2);
                ;
                break;
            case BYTE:
                sec = myTOS->search(currentSection);
                if (sec->rwx[1]=='0') {cout<<"Error, defining data in "<<sec->section<<" section!\n"; return -1;}
                locationCounter++;
                return 0;
                break;
            case WORD:
                sec = myTOS->search(currentSection);
                if (sec->rwx[1]=='0') {cout<<"Error, defining data in "<<sec->section<<" section!\n"; return -1;}
                locationCounter += 2;
                return 0;
            case ALIGN:
                while (locationCounter % x) locationCounter++;
                break;
            case SKIP:
                //cout<<word1;
                locationCounter += x;
                return 0;
                break;
            default:
            {
                cout << "EROR finding directive" << "\n";
                return -1;
            }
        }

    }



}

int Klasa::equSolution(string word1, string word2) {
    //WORD1 je sta definises, a word 2 je kako definises, pomocu cega
    Symbol* sym = myTOS->search(word1);
    bool digit = true;
    for (int i = 0; i < word2.length(); i++) if (!isdigit(word2[i])) {
            digit = false;
            break;
        }

    int res;
    char op = 'U';
    Symbol* ss;
    if (digit) {
        res = stoi(word2);
        if (sym==nullptr) myTOS->push(word1,currentSection, res, -1, 1);
        else {
            if (sym->defined==1) return -1;
            sym->defined = 1; sym->offset=res;
            sym->section=currentSection;
            return 0;
        }
    
    }else {new Tabela_Neizracunljivih_Simbola(word1, word2, currentSection);}
    
    return 0;
    
}

int Klasa::insertLabel(string label) {

    label.erase(label.length() - 1);

    Symbol* sym = myTOS->search(label);
   // cout << "Labela je: " << label << " i njena sekcija je " << currentSection << "\n";
    if (sym) {
        if (sym->defined == 1) {
            cout << "Syntax error! 5" << "\n";
            return -1;
        }
        sym->offset = locationCounter;
        sym->section = currentSection;
        sym->defined = 1;
    } else {
        myTOS->push(label, currentSection, locationCounter, -1, 1);
    }
    return 0;
}

int Klasa::insertNewSection(string word, string name, string flags) {


    if ((word == ".text" && text) || (word == ".data" && data) || (word == ".bss" && bss)) {
        cout << word << "\n";
        cout << "Error with sections, multiple declarations!" << "\n";
        return -1;
    }
    //cout<<flags<<"\n";
    if (flags != "und") {
        //cout<<word<<"**"<<name<<"**"<<flags<<"\n";
        //cout<<"duzina flegova je "<<flags.size()<<"\n";
        if (flags.size() == 3) {
            if ((flags[0] != '0' && flags[0] != '1') || (flags[1] != '0' && flags[1] != '1') || (flags[2] != '0' && flags[2] != '1')) {
                cout << "Section flag error!\n";
                return -1;
            }
        } else {
            cout << "Section flag error!\n";
            return -1;
        }
    }
    if (name == "und") {
        //ako je nesto od ove tri ulazi ovde
        if (word == ".text") text = true;
        if (word == ".data") data = true;
        if (word == ".bss") bss = true;

        if (currentSection == "und") {
            currentSection = word;
            //cout<<"Nije bilo ranije nove sekcije, prva sekcija je "<<currentSection<<"\n";
            locationCounter = 0;
            //cout<<"Ubacujem sekciju sa flegovima"<<word<<" flegovi:"<<flags <<"\n";
            myTOS->pushNewSection(word, currentSection, -1, -1, -1, flags);
        } else {
            Symbol* sym = myTOS->search(currentSection);
            sym->sectionSize = locationCounter;

            //cout<<"Dohvatam sekciju "<<sym->symbol<<" i njena velicina je "<<sym->sectionSize<<"\n";
            currentSection = word;
            locationCounter = 0;
            myTOS->pushNewSection(word, currentSection, -1, -1, -1, flags);

            //cout<<"Ubacujem sekciju "<<word<<"\n";
        }
    } else {
        //ako je .section
        //cout<<"Ovde sam\n";
        Symbol* sym = myTOS->search(currentSection);
        if (sym) sym->sectionSize = locationCounter;
        sym = myTOS->search(name);
        if (sym) {
            //cout<<name<<"\n";
            cout << "Error with sections, multiple declarations!" << "\n";
            return -1;
        }
        currentSection = name;
        locationCounter = 0;
        myTOS->pushNewSection(name, currentSection, -1, -1, -1, flags);
    }
}

int Klasa::instructionWithOneOperand(string operation, list<string> operand) {

    map<int, string>::iterator itr;
    int found = 0;
    int keyOp = -1;
    bool w = false;
    bool b = false;
    if (operation[operation.size() - 1] == 'w') {
        operation.erase(operation.length() - 1);
        w = true;
    }
    if (operation[operation.size() - 1] == 'b') {
        operation.erase(operation.length() - 1);
        b = true;
    }
    for (itr = operationsWithOneOp.begin(); itr != operationsWithOneOp.end(); ++itr) {
        if (itr->second == operation) {
            found = 1;
            keyOp = itr->first;
            break;
        }
    };

    if (found == 0) {
        cout << "Illigal instruction, syntax error! " << operation << "\n";
        return -1;
    }
    Symbol* sec = myTOS->search(currentSection);
    if (sec->rwx[2]=='0') {cout<<"Error, instruction in "<<sec->section<<" section!\n"; return -1;}
    
    int type=0;
    for (itr = jumpMap.begin(); itr != jumpMap.end(); ++itr) {
        if (itr->second == operation) {
            type = 1;
            keyOp = itr->first;
            break;
        }
    };

    if (type==0 && operation=="push") type=2;
    if (type==0) type=3;
    
    bool flag = checkAdressingWithOneOp(type, operand);
    
    if (flag==false) {cout<<"Greska pri adresiranju instrukcija\n"; return -1;}
    string op = operand.front();
    operand.pop_front();

    locationCounter++; //POVECALA SI VEC VELICU OPERATION CODAAAAAA
    int ret = calculateLengthOfInstruction(op, b, w);
    if (ret == -1) return -1;
    locationCounter += ret;

    return 0;
}


bool Klasa::checkAdressingWithOneOp(int type, list<string> restLine){

    if (type==2) return true; //ako je push onda moze sve
    
    
    string op = restLine.front();
    restLine.pop_front();
    
    if (op[0] == '0' && op[1] == 'x') return false;
    
    regex reg("r[0-7]"); regex pc("pc"); regex psw("psw");regex sp("sp");  
    bool matches;
    switch(type){
    
        case 1:
             matches = regex_search(op, reg);
             if ((matches == true && op.size() == 2) || op == "sp" || op == "pc" || op == "psw") return false;
             else if (op[0] == '[' && op[op.size() - 1] == ']' && ((matches && op.size() == 4) || regex_search(op, pc) || regex_search(op, psw) || regex_search(op, sp))) return false;
             else if ((matches || regex_search(op, pc) || regex_search(op, sp) || regex_search(op, psw)) && (op[2] == '[' || (regex_search(op,psw) && op[3]=='[')) && op[op.size() - 1] == ']') return false;
             else if (op[0] == '*' || op [0] == '&') return false;
             return true;
        case 3: return true; // pop int not instrukcije, moze sve
    
    }

}
int Klasa::instructionWithTwoOperands(string operation, list<string> operands) {

    map<int, string>::iterator itr;
    int found = 0;
    int keyOp = -1;
    bool w = false;
    bool b = false;
    if (operation[operation.size() - 1] == 'w') {
        operation.erase(operation.length() - 1);
        w = true;
    }
    if (operation[operation.size() - 1] == 'b' && operation!="sub") {
        operation.erase(operation.length() - 1);
        b = true;
    }
    for (itr = operationsWithTwoOp.begin(); itr != operationsWithTwoOp.end(); ++itr) {
        if (itr->second == operation) {
            found = 1;
            keyOp = itr->first;
            break;
        }
    };

    if (found == 0) {
        cout << "Illigal instruction, syntax error! " << operation << "\n";
        return -1;
    }
    Symbol* sec = myTOS->search(currentSection);
    if (sec->rwx[2]=='0') {cout<<"Error, instruction in "<<sec->section<<" section!\n"; return -1;}
    
    int type=0;
    
    for (itr = arithmeticOperations.begin(); itr != arithmeticOperations.end(); ++itr) {
        if (itr->second == operation) {
            type=1;
            keyOp = itr->first;
            break;
        }
    };
    if (type==0 && operation=="xchg") type=2;
    if (type==0 && operation=="mov") type=3;
    
    bool flag = checkAdressingWithTwoOp(type, operands);
    
    if (flag==false) {cout<<"Greska pri adresiranju u instrukcijama!\n"; return -1;}
    
    string op1 = operands.front();
    operands.pop_front();
    string op2 = operands.front();
    operands.pop_front();

    locationCounter++;

    int ret = calculateLengthOfInstruction(op1, b, w);
    locationCounter += ret;
    if (ret == -1) return -1;
    ret = calculateLengthOfInstruction(op2, b, w);
    locationCounter += ret;
    if (ret == -1) return -1;
    return 0;
}

bool Klasa::checkAdressingWithTwoOp(int type, list<string> restLine){
   
    string op1 = restLine.front();
    restLine.pop_front();
    string op2 = restLine.front();
    restLine.pop_front();
    
    if (op1[0] == '0' && op1[1] == 'x') return false;
    
    regex reg("r[0-7]"); bool matches1, matches2, matches;
    switch(type){
        case 1: return true; //aritmeticke operacije, samo da kao odrediste nemaju immed adresiranje
        case 2:
            //xchg instrukcija, mora da oba ima registarska
          //  cout<<"XCHG INSTRUKCIJA\n";
            
            matches1 = regex_search(op1, reg);
            matches2= regex_search(op2,reg);
            if (((matches == true && op1.size() == 2) || op1 == "sp" || op1 == "pc" || op1 == "psw") && ((matches == true && op2.size() == 2) || op2 == "sp" || op2 == "pc" || op2 == "psw")) return true;
            return false;
            break;
        case 3:
            //mov mora da bude makar jedno registarsko
     /*       matches = regex_search(op1, reg);
            if ((matches == true && op1.size() == 2) || op1 == "sp" || op1 == "pc" || op1 == "psw") return true;
            matches= regex_search(op2,reg);
            if ((matches == true && op2.size() == 2) || op2 == "sp" || op2 == "pc" || op2 == "psw") return true;
            return false;*/
            return true;
        default: return true;
    }

}


int Klasa::instructionWithoutOperand(string operation) {

    map<int, string>::iterator itr;
    int found = 0;
    int keyOp = -1;
    for (itr = operationsWithoutOp.begin(); itr != operationsWithoutOp.end(); ++itr) {
        if (itr->second == operation) {
            found = 1;
            keyOp = itr->first;
            break;
        }
    };

    if (found == 0) {
        cout << "Illigal instruction, syntax error! " << operation << "\n";
        return -1;
    }
    Symbol* sec = myTOS->search(currentSection);
    if (sec->rwx[2]=='0') {cout<<"Error, instruction in "<<sec->section<<" section!\n"; return -1;}
    
    locationCounter++;

}

int Klasa::calculateLengthOfInstruction(string op, bool b, bool w) {

    bool matches;
    regex reg("r[0-7]");
    regex pc("pc");
    regex sp("sp");
    regex psw("psw");

    matches = regex_search(op, reg);
    bool immed = false;
    if (op[0] == '0' && op[1] == 'x') immed = true; 
    if (immed) {
        string value;
        bool digi = true;
        int val;
        for (int i = 2; i < op.size(); i++) {
            value += op[i];
            if (!isdigit(op[i])) {
               digi = false;
                break;
            }
        }
        if (digi) {
           // cout << "Neposredna vrednost je " << value << "\n";
            val = stoi(value);
        } else {cout << "Problem sa neposrednim adresiranjem\n"; return -1;}
        if (b== false && w==false) {cout<<"Oznacite velicinu\n";return -1;}
        if (b)
            if (value.length()==2) return 2;
            else {cout << "Unesite ispravnu duzinu operanada!\n"; return -1;}
        else if (value.length()==4) return 3;
        else {cout<<"Unesite ispravnu duzinu operanada!\n"; return -1;}   
    } else if ((matches == true && op.size() == 2) || op == "sp" || op == "pc" || op == "psw") {
       // cout << "Registarsko direktno" << "\n";
        return 1;
    } else if (op[0] == '[' && op[op.size() - 1] == ']' && ((matches && op.size() == 4) || regex_search(op, pc) || regex_search(op, psw) || regex_search(op, sp))) {
        //cout << "REGISTARSKO INDIREKTNO" << "\n";
        return 1;
    } else if ((matches || regex_search(op, pc) || regex_search(op, sp) || regex_search(op, psw)) && (op[2] == '[' || (regex_search(op,psw) && op[3]=='[')) && op[op.size() - 1] == ']') {
        int size = op.size() - 1;
        string pom; int k;
        if (regex_search(op, psw)) k=4;
        else k=3;
        for (int i = k; i < size; i++) pom += op[i];
        bool digi = true;
        for (int i = 0; i < pom.size(); i++) if (!isdigit(pom[i])) {
                digi = false;
                break;
            }

        if (!digi) {
            if (b==true) {cout<<"Problem sa duzinom operanada!\n"; return -1;}
           // cout << "Registarsko indirektno gde je simbol " << pom << " pomeraj\n";
            return 3;
        } else {
           // cout << "Registarsko indirektno gde je vrednost " << pom << " pomeraj\n";
            int value = stoi(pom);
            if (value == 0) {
                //cout << "Pomeraj je nula\n";
                return 1;
            } else if (value<-128 || value > 127) {
                if (b == false) {
                    return 3;
                } else {cout << "Imate problem sa pomerajem " << value << "\n"; return -1;}
            } else {//moze da stane na jedan bajt, ali se upisuje u samo ako se tako naznaci
                if (b==true) {/*cout << "locationCounter povecavam za dva\n";*/ return 2;}
                else return 3;
            }
        }
    } else if (op[0] == '*') {
        bool only = true;
        if (op.size() != 5 || b==true) {
            cout << "Memorijska adresa nije ispravna ili duzina operanada " << op << "\n";
            return -1;
        }
        for (int i = 1; i < op.size(); i++) if (!isdigit(op[i])) {
                only = false;
                break;
            }

        if (only) {
            //cout << "Memorija " << op << "\n";
            return 3;
        }else return -1;
    } else if (op[0] == '$' || op [0] == '&') {
        int size = op.size();
        string pom;
        if (b==true) {cout<<"Problem sa duzinom operanada!\n"; return -1;}
        for (int i = 1; i < size; i++) pom += op[i];
       // cout << "PCrel sa simbolom " << pom << "\n";
        return 3;
    } else {
        if (b==true) {cout<<"Problem sa duzinom operanada!\n"; return -1;}
       // cout << "Memorijsko sa simbolom " << op << "\n";
        return 3;
    }//else cout<<"PROBLEMS PROBLEMS PROBLEMS"<<"\n";


}

void Klasa::checkEnd(int filePosition, int fileSize, int linePosition, int lineSize) {
    endExists = true;
    //cout<<filePosition << " fileSize je "<<fileSize<<"\n";
    if ((filePosition == (fileSize - 1)) && (linePosition == 1 && lineSize == 1)) okEnd = true;
    else okEnd = false;
    //cout<<okEnd<<"\n";
    if (okEnd) {
        Symbol* sym = myTOS->search(currentSection);
        if (sym) sym->sectionSize = locationCounter;
        locationCounter = 0;
    } else {cout << "End ili nije sam u redu ili nije poslednja linija koda\n"; endExists = false;}
}

int Klasa::secoundRun() {

    while (!sadrzaj2.empty()) {
        list<string> linija = sadrzaj2.front();
        sadrzaj2.pop_front();

        while (!linija.empty()) {
            string word = linija.front();
            if (word == ".end") return 0;
            if (word[word.size() - 1] == ':') { linija.pop_front();}
            else {
                int found = 0;
                found = directivesSecoundRun(linija);
                if (found == 0) {found = operationSecound(linija);if (found==0){ cout<<"Logical error\n"; return -1;}}
                else if (found == -1) {
                    cout << "Logical error\n";
                    return -1;
                }
            linija.clear();
            }
        }

    }
    return 0;
}

int Klasa::directivesSecoundRun(list<string> line) {

    string operation = line.front();
    line.pop_front();

    map<int, string>::iterator itr;
    int found = 0;
    int keyDirective = -1;
    for (itr = directives.begin(); itr != directives.end(); ++itr) {
        if (itr->second == operation) {
            found = 1;
            keyDirective = itr->first;
            break;
        }
    };
    if (found == 0) return 0;
    if (operation == ".text" || operation == ".section" || operation == ".data" || operation == ".bss") {
        locationCounter = 0;pc=0;
        if (operation==".section") currentSection = line.front();
        else currentSection = operation;
        predmetniProgram = new Predmetni_Program(currentSection);
        return 1;
    }
    int x;
    string bajt;
    list<string> linija; Symbol* sec;
    int pom; bool rel = true;
    switch (keyDirective) {
        case GLOBAL:
            while (!line.empty()) {
                string op = line.front();
                line.pop_front();
                Symbol* s = myTOS->search(op);
                if (!s || s->global == -1) return -1;
            }
            return 1;
            break;
        case EXTERN:
            while (!line.empty()) {
                string op = line.front();
                line.pop_front();
                Symbol* s = myTOS->search(op);
                if (!s || s->global == -1 || s->defined == 1) return -1;
            }
            return 1;
            break;
        case EQU:
            break;
        case BYTE:
            locationCounter++; pc++;
            if (line.size() != 0) {
                x = stoi(line.back());
                line.pop_back();
            } else x = 0;
            if (x > 127 || -128 > x) return -1;
            if (currentSection==".bss") rel=false;
          if (rel){  bajt = decToHex(x);
            linija.push_back(bajt);
            predmetniProgram->predmetniProgram.push_back(linija);}
            return 1;

        case WORD:
            locationCounter += 2; pc+=2;
            if (line.size() != 0) {
                x = stoi(line.back());
                line.pop_back();
            } else x = 0;
            bajt = decToHex(x);
            if (currentSection==".bss") rel=false; 
             if (rel) {if (bajt.length()==3) bajt+="00";
                       else bajt = reverseString(bajt);
            linija.push_back(bajt);
            predmetniProgram->predmetniProgram.push_back(linija);}
            return 1;
        case ALIGN:
            x = stoi(line.front());
            line.pop_front();
            pom = 0;
            while (locationCounter % x) {
                locationCounter++;pc++;
                pom++;
            }
            if (currentSection==".bss") rel=false;
            if (rel){
               while (pom) {
                pom--;
                bajt = decToHex(0);
                linija.push_front(bajt);
            }
            predmetniProgram->predmetniProgram.push_back(linija);}
            return 1;
            break;

        case SKIP:
            x = stoi(line.front());
            line.pop_front();
            locationCounter += x;
            pc=locationCounter;
            pom = x;
            if (currentSection==".bss") rel=false;
            if (rel){
            while (pom) {
                pom--;
                bajt = decToHex(0);
                linija.push_front(bajt);
            }
            predmetniProgram->predmetniProgram.push_back(linija);
            }
            return 1;
            break;
        default:
        {
            cout << "EROR finding directive" << "\n";
            return -1;
        }
    }


}

string Klasa::decToHex(int n) {

    char hexaDeciNum[100];
    string hexa;
    // counter for hexadecimal number array 
    int i = 0;
    if (n == 0) {
        hexa = "00";
        return hexa;
    }
    while (n != 0) {
        // temporary variable to store remainder 
        int temp = 0;

        // storing remainder in temp variable. 
        temp = n % 16;

        // check if temp < 10 
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }

        n = n / 16;
    }


    int turn = 0;
    if (i % 2) {
        hexa += "0";
        turn = 1;
    }
    // printing hexadecimal number array in reverse order 

    for (int j = i - 1; j >= 0; j--) {
        hexa += hexaDeciNum[j];
        if (turn == 0) turn = 1;
        else {
            hexa += ' ';
            turn = 0;
        }
    }


    return hexa;
}

int Klasa::operationSecound(list<string> line) {

    list<string> toPut;
    string op = line.front();
    string operand;
    line.pop_front();

    bool w = false;
    bool b = false;
    if (op[op.size() - 1] == 'w') {
        op.erase(op.length() - 1);
        w = true;
    }
    if (op[op.size() - 1] == 'b' && op!="sub") {
        op.erase(op.length() - 1);
        b = true;
    }

    
    string operationBajt = decodeInstruction(op, b, w);
    toPut.push_back(operationBajt);
    locationCounter++; //POVECALA SI ZA OP CODE
    pc++;
    
    list<string> linija; linija = line; 
    while (linija.size()>0){
        operand = linija.front();
        linija.pop_front();
        int rez = calculateLengthOfInstruction(operand, b, w);
        //cout<<rez<<"\n";
        pc+=rez;
       }

   // cout<<"Operacija je "<< op <<" lc je "<<locationCounter <<" pc je " << pc<<"\n";
    string operandBajtDesk;
    while (line.size()>0){
        operand = line.front();
        line.pop_front();
        operandBajtDesk = decodeOperand(operand,b,w);
        if (operandBajtDesk=="und") return 0;
       toPut.push_back(operandBajtDesk);
       }

   
    if (currentSection!=".bss") predmetniProgram->predmetniProgram.push_back(toPut);

    return 1;
}

string Klasa::decodeInstruction(string instruction, bool b, bool w) {

    map<int, string>::iterator itr;
    int found = 0;
    int keyOp = -1;
    int pom = 0;
    for (itr = allOperations.begin(); itr != allOperations.end(); ++itr) {
        if (itr->second == instruction) {
            found = 1;
            keyOp = itr->first;
            break;
        }
    };
    int x = 4;
    int i = 0;
    int y;
    if (b) x = 0;
    string ret;
    list<int> op;
    int sum = 0;
    switch (keyOp) {
        case HALTe:
            op = decToBin(HALTe);
            break;
        case XCHGe://0010
            op = decToBin(XCHGe);
            break;
        case INTe:
            op = decToBin(INTe);
            break; //0011
        case MOVe:
            op = decToBin(MOVe);
            break; //0100
        case ADDe:
            op = decToBin(ADDe);
            break; //
        case SUBe:
            op = decToBin(SUBe);
            break; //
        case MULe:
            op = decToBin(MULe);
            break; //
        case DIVe:
            op = decToBin(DIVe);
            break; //
        case CMPe:
            op = decToBin(CMPe);
            break; //
        case NOTe:
            op = decToBin(NOTe);
            break; //
        case ANDe:
            op = decToBin(ANDe);
            break; //
        case ORe:
            op = decToBin(ORe);
            break; //
        case XORe:
            op = decToBin(XORe);
            break; //
        case TESTe:
            op = decToBin(TESTe);
            break; //
        case SHLe:
            op = decToBin(SHLe);
            break; //
        case SHRe:
            op = decToBin(SHRe);
            break; //
        case PUSHe:
            op = decToBin(PUSHe);
            break; //
        case POPe:
            op = decToBin(POPe);
            break; //
        case JMPe:
            op = decToBin(JMPe);
            break; //
        case JEQe:
            op = decToBin(JEQe);
            break; //
        case JNEe:
            op = decToBin(JNEe);
            break; //
        case JGTe:
            op = decToBin(JGTe);
            break;
        case CALLe:
            op = decToBin(CALLe);
            break;
        case RETe:
            op = decToBin(RETe);
           break;
        case IRETe:
            op = decToBin(IRETe);
            break;
   }
   
            sum += instructionHelper(op);
            sum += x;
            ret = decToHex(sum);
            return ret;

}

int Klasa::instructionHelper(list<int> op) {

    int i = 0;
    int y = 0;
    int pom = 0;
    int sum = 0;

    while (!op.empty()) {
       // cout << op.front();
        y = i + 3;
        pom = 0;
        //cout << "y je " << y << "\n";
        if (op.front()) {
            pom = 1;
            while (y != 0) {
                pom = pom * 2;
                --y;
            }
        }
       // cout << "pom je " << pom << "\n";
        sum = sum + pom;
        op.pop_front();
       // cout << "++" << sum << "++\n";
        i++;
        y = 0;
    }

    return sum;
}

string Klasa::decodeOperand(string op, bool b, bool w){

    bool matches;
    regex reg("r[0-7]");
    regex pc("pc");
    regex sp("sp");
    regex psw("psw");

    pcRel=false;
    matches = regex_search(op, reg);
    bool immed = false;
    if (op[0] == '0' && op[1] == 'x') immed = true; 
    if (immed) {
        string value;
        int val;
        for (int i = 2; i < op.size(); i++) {value += op[i]; if (i%2 && i!=2) value+=" ";}
            string ret = operandHelper(IMMED, -1); ret +=" ";
          if (value.length()>3) {value= reverseString(value);}
           // cout<<"VALUE JE "<<value<<" I NJEGOVA DUZINA JE "<<value.length()<<"\n";
          if (w && value.length()==3) {value = reverseString(value);}
          
            ret+=value;
          if (b) locationCounter+=2;
          else locationCounter+=3;
          return ret;
        } else if ((matches == true && op.size() == 2) || op == "sp" || op == "pc" || op == "psw") {
        string val; int value; val=op[1];
        if (op == "sp") value = 6;
        else if (op == "pc") value = 7;
        else if (op == "psw") value = 15;
        else value = stoi(val);
        locationCounter++;
        string ret = operandHelper(REGDIR, value);
        return ret;
    } else if (op[0] == '[' && op[op.size() - 1] == ']' && ((matches && op.size() == 4) || regex_search(op, pc) || regex_search(op, psw) || regex_search(op, sp))) {
       // cout << "REGISTARSKO INDIREKTNO" << "\n";
        string val; int value; val=op[3];
        if (op == "[sp]") value = 6;
        else if (op == "[pc]") value = 7;
        else if (op == "[psw]") value = 15;
        else value = stoi(val);
        locationCounter++;
        string ret = operandHelper(REGIND0, value);
        return ret;
    } else if ((matches || regex_search(op, pc) || regex_search(op, sp) || regex_search(op, psw)) && (op[2] == '[' || (regex_search(op, psw) && op[3]=='['))&& op[op.size() - 1] == ']') {
        int size = op.size() - 1;
        string pom; int k;
        if (regex_search(op,psw)) k=4;
        else k=3;
        for (int i = k; i < size; i++) pom += op[i];
        bool digi = true;
        for (int i = 0; i < pom.size(); i++) if (!isdigit(pom[i])) {
                digi = false;
                break;
            }

        if (!digi) {
           // cout << "Registarsko indirektno gde je simbol " << pom << " pomeraj\n";
            string val;
            val=op[1]; int valuee;
            if (regex_search(op, sp)) valuee = 6;
            else if (regex_search(op, pc)) {valuee = 7; pcRel=true;}
            else if (regex_search(op, psw)) valuee = 15;
            else valuee = stoi(val);
            locationCounter++;
            string ret = operandHelper(REGIND16, valuee); ret+=" ";
            string rev = symbolHelper(pom);
            if (rev=="und") return "und";
            
      //  cout << "Registarsko indirektno sa simbolom " << pom << "koji se kodirao "<<rev <<"\n";
            ret+=rev;
            locationCounter+=2;
            return ret;
        } else {
           // cout << "Registarsko indirektno gde je vrednost " << pom << " pomeraj\n";
            int value = stoi(pom);
            if (value == 0) {
          //  cout << "Pomeraj je nula\n";
            string val;
            int value;
            val = op[1]; 
            locationCounter++;
            if (regex_search(op, sp)) value = 6;
            else if (regex_search(op, pc)) value = 7;
            else if (regex_search(op, psw)) value = 15;
            else value = stoi(val);
            string ret = operandHelper(REGIND0, value);
            return ret;
            } else if (value<-128 || value > 127) {//ne moze da stane u jedan bajt
            string val;
            int valuee;
            val = op[1];
            if (regex_search(op, sp)) valuee = 6;
            else if (regex_search(op, pc)) valuee = 7;
            else if (regex_search(op, psw)) valuee = 15;
            else valuee = stoi(val);
            string ret = operandHelper(REGIND16, valuee);
            string rev = decToHex(value);
            if (rev.length()==3) rev+="00";
            else rev=reverseString(rev); 
            ret+=rev; locationCounter+=3;
            return ret;
            } else {//staje u jedan bajt, ako je word onda predstavljam na dva bajta
            string val;
            int valuee;
            val = op[1];
            if (regex_search(op, sp)) valuee = 6;
            else if (regex_search(op, pc)) valuee = 7;
            else if (regex_search(op, psw)) valuee = 15;
            else valuee = stoi(val);string ret; string rev;
            rev = decToHex(value);
            if (b) {ret = operandHelper(REGIND8,valuee); locationCounter+=2;}
            else {ret = operandHelper(REGIND16, valuee);locationCounter+=3; rev+=" 00"; } 
            ret+=rev;
            return ret;
            }
        }
    } else if (op[0] == '*') {
        string value;
        int val;
        for (int i = 1; i < op.size(); i++) {value += op[i]; if (i%2==0) value+=" ";}
        string ret = operandHelper(MEM, -1); ret+=" ";
        value=reverseString(value);
        locationCounter+=3;
        ret+=value;
        return ret;
        
    } else if (op[0] == '$' || op [0] == '&') {
        int size = op.size();
        string pom;
        for (int i = 1; i < size; i++) pom += op[i];
        string ret;
        locationCounter++;
        if (op[0]=='$'){ret= operandHelper(REGIND16, 7);pcRel=true;}
        else ret = operandHelper(IMMED, -1);
        ret+=" ";
        string rev = symbolHelper(pom);
        if (rev=="und") return "und";
        
       // cout << "PCrel ili immed sa simbolom " << pom << " koji se kodirao "<<rev <<"\n";
        ret += rev;
        locationCounter+=2;
        return ret;
     } else {
        locationCounter++;
        string ret = operandHelper(MEM, -1);
        ret += symbolHelper(op);
        locationCounter+=2;
        regex und("und");
        if (regex_search(ret, und)) ret="und";
       // cout << "Memorijsko sa simbolom " << op << "koji se kodirao "<<ret <<"\n";
        return ret;
    }//else cout<<"PROBLEMS PROBLEMS PROBLEMS"<<"\n";


    return "und";

    }    
string Klasa::symbolHelper(string symbol){

    if (currentSection==".bss") return "";
    Symbol* sym = myTOS->search(symbol);
    if (sym==nullptr) return "und";
    
    if (pcRel){
    //ako je korisceno pcRel adresiranje
        int vr=0;
        string hex;
        bool rel = relocationNeeded(sym);
        if (sym->global==1){
           // cout<<"Usao sam ovde!\n";
            vr = pc-locationCounter;
           // cout<<vr<<"\n";
            vr= 65536-vr;
            hex = decToHex(vr);
            hex=reverseString(hex);
        }else {
            vr = pc-locationCounter;
          //  cout<<"LC je "<<locationCounter<<" PC je "<<pc<<" razlika je "<<vr<<"\n";
            vr = sym->offset-vr;
           // cout<<" razlika je "<<vr<<"\n";
            if (vr<0) vr=65536+vr;
            hex = decToHex(vr);
            //cout<<hex<<"***";
            if (hex.length()<=3) hex+=" 00";
            else hex = reverseString(hex);
            //cout<<hex<<"\n";
        }
        
        Symbol* s = myTOS->search(currentSection);
        if (s->rwx[2]=='0') rel=false;
        if (rel) makeRelocation(sym);
       return hex;
    }else {
    //ako je korisceno bilo koje drugo adresiranje ABS relokacija
        int vr;
        //cout<<"Pogresan ulazak";
        if (sym->global==1) vr=0;
        else vr = sym->offset;
        string hex = decToHex(vr);
        bool rel = true;
        Symbol* s = myTOS->search(currentSection);
        if (s->rwx[2]=='0') rel=false;
        if (rel) makeRelocation(sym);
        if (hex.length()<=3) hex+=" 00";
        else reverseString(hex);
        return hex;
    
    }
}

bool Klasa::relocationNeeded(Symbol* sym){

    if (sym->global==1) return true;

    if (sym->global==-1 && (sym->section==currentSection)) return false;

    return true;
}

void Klasa::makeRelocation(Symbol* sym){
    
    Symbol* section;
    section = myTOS->search(sym->section);
    string locCounter = decToHex(locationCounter);
    
    new RelocationTable(sym, pcRel, locCounter, section, currentSection);
}
list<int> Klasa::decToBin(int n) {

    list <int> binaryNum;
    int x;
    int i = 0;
    while (n > 0) {
        x = n % 2;
        binaryNum.push_back(x);
        n = n / 2;
        i++;
    }
    return binaryNum;
}

string Klasa::reverseString(string toRev) {

    string newStr;
    
    for (int i=3;i<toRev.length();i++)
        newStr+=toRev[i];
    
    //newStr+=' ';
    for (int i=0;i<2;i++) newStr+=toRev[i];
    
    return newStr;
}


string Klasa::operandHelper(int adr, int reg) {

    list<int> am = decToBin(adr);
    list<int> r;
    list<int> vr;
    int i = 0;
    int y = 0;
    int pom = 0;
    int sum = 0;

    while (!am.empty()) {
        y = i + 5;
        pom = 0;
        if (am.front()) {
            pom = 1;
            while (y != 0) {
                pom = pom * 2;
                --y;
            }
        }
        sum = sum + pom;
        am.pop_front();
        i++;
        y = 0;
    }
    if (reg != -1) {
        i=0;
        r = decToBin(reg);
        while (!r.empty()) {
            y = i + 1;
            pom = 0;
            if (r.front()) {
                pom = 1;
               
                while (y != 0) {
                    pom = pom * 2;
                    --y;
                }
               
            }
            sum = sum + pom;
            r.pop_front();
            i++;
            y = 0;
        }
    }

string hex = decToHex(sum);    
    return hex;
}

Klasa::~Klasa() {
}

