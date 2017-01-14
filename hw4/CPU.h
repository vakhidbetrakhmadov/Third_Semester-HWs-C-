/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW03_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* CPU.h                                                                    */
/* ---------                                                                */
/* Created on 25/10/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#ifndef CPU_H
#define CPU_H

#include "Memory.h"

using namespace std;

typedef enum { UNKNOWN=10,MOV,ADD,SUB,JPN,JPN2,JMP,JMP1,JMP2,PRN,HLT }InstType_t;
typedef enum {NON,ONE,TWO} Parameter_t;

class CPU {
public:
    CPU(int option_value=-1); 
    void setReg(int reg_num,int value);
    void setPc(int value);
    int getReg(int reg_num)const;
    int getPc() const;
    void print()const; // prints all reg
    bool halted()const; // returns currents state of halt flag
    void execute(const string &arg_instr,Memory & my_memory); // executes instruction and increments pc by 1 
    void validate(string & instr,int num_of_instr); //modifies instr passed in getting it to the standart form,checks for syntax errors and sets err flag to true if one is found 
    bool error(); //return the current state of err flag,sets halt flag true if err flag is true 
private:
    int reg[5];
    int REG_SIZE;
    int pc;
    bool halt;
    bool err;
    int option;
    
    int nextNonSpace(const string &str,int last_non_space)const;//returns the index of the next non space char in the string after last_non_space
    void allToUpper(string &str)const;//converts alphabetic charachters to upper case if lower 
    bool isLegalInt(const string & str)const; // returns false if string has any other char then from the range '1'>=ch<='9', which is not terminating ';' char,else retunrs true
    int strToInt(const string & str)const;
    int readSubStr(const string & mainStr,string & subStr,int lastPos)const;// starting from lastPos stores the first ' ' or ';' terminated substr of mainStr to subStr and returns next char index
    bool isLegalAdress(const string & str,char pos)const; 

};

#endif 

