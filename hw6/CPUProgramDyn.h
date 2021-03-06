/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW06_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* CPUProgramDyn.h                                                          */
/* ---------                                                                */
/* Created on 26/11/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H

using namespace std;

namespace CPUPD
{
    class CPUProgramDyn
    {
    public:
        CPUProgramDyn(int option_value=-1);
        explicit CPUProgramDyn(char const * c_str);//prints error message and exits the programm if either problem in opening file occures or cmd parameter is wrong,
        //calls readFile

        CPUProgramDyn(const CPUProgramDyn& sample); //copy constructor 
        CPUProgramDyn& operator=(const CPUProgramDyn& r_s); // assignment operator overdloading

        string getLine(int line_num)const;
        int size()const;
        void ReadFile(char const* name);//opens file and reads it into the string vector,prints error message and exits the programm if problem in opening file occures
        
        string & operator [] (int indx); //returns program line as a string, exits the execution if indx is out of range
        const string & operator [] (int indx)const; //overloaded version of [] operator works as for r_value objects (constant objects),
        //exits the execution if indx is out of range
        const CPUProgramDyn operator +(string const & str)const;// returns a new program consisting of calling program + new string 
        CPUProgramDyn & operator += (const string str);// appends a string to the end of the calling program
        const CPUProgramDyn operator + (const CPUProgramDyn & r_s)const; //returns a new program consisting of added to each other programs 
        bool operator == (const CPUProgramDyn & r_s)const; //compares the number of lines of two programs 
        bool operator != (const CPUProgramDyn & r_s)const;//compares the number of lines of two programs 
        bool operator > (const CPUProgramDyn & r_s)const;//compares the number of lines of two programs 
        bool operator < (const CPUProgramDyn & r_s)const;//compares the number of lines of two programs 
        bool operator >= (const CPUProgramDyn & r_s)const;//compares the number of lines of two programs 
        bool operator <= (const CPUProgramDyn & r_s)const;//compares the number of lines of two programs 
        friend ostream & operator << (ostream & output, const CPUProgramDyn & r_s); // prints on the screen the program
        const CPUProgramDyn operator -- ();//pre decrement , deletes the last line from the program,prints err message if program is empty and returns the program
        const CPUProgramDyn operator -- (int stub); //post decrement , deletes the last line from the file, and returns the state before decrementing,
        //prints err message if program is empty and returns the program
        const CPUProgramDyn operator () (int limit1,int limit2)const; //returns a new program consisting of the lines in between limit1 and limit2 (including),prints err
        //message if out of range and returns empty program

        ~CPUProgramDyn();
    private:
        string* line;
        int file_size;    
        int option;
        int capacity;

        void addLine(const string& str);//adds a string ellement to the end of the dynamic arr of strings "line" and increments size,
        //if arr is full, doubles capacity and adds a string ellement incrementing size 

    };
 
}


#endif 

