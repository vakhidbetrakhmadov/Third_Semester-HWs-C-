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

#include <vector>

using namespace std;

class CPUProgram
{
public:
	CPUProgram(int option_value=-1);
    CPUProgram(char const * c_str);//prints error message and exits the programm if either problem in opening file occures or cmd parameter is wrong,calls readFile
    string getLine(int line_num)const;
    int size()const;
    void ReadFile(char const* name);//opens file and reads it into the string vector,prints error message and exits the programm if problem in opening file occures
private:
    vector<string>line;
    int file_size;    
    int option;
};

#endif 

