/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW03_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* CPUProgram.h                                                             */
/* ---------                                                                */
/* Created on 25/10/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

using namespace std;

class CPUProgram
{
public:
    CPUProgram(char const * c_str,char const* num);//prints error message and exits the programm if either problem in opening file occures or cmd parameter is wrong,calls readFile
    string getLine(int line_num)const;
    string getMode()const;
    int size()const;
private:
    ifstream file;
    char const* file_name;
    string mode;
    vector<string>line;
    int file_size;    
    
    void readFile(char const* name);//opens file and reads it into the string vector,prints error message and exits the programm if problem in opening file occures
};

#endif 

