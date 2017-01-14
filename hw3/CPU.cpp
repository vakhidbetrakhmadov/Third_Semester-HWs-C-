/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW03_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* CPU.cpp                                                                  */
/* ---------                                                                */
/* Created on 25/10/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>


#include "CPU.h"

using namespace std;

CPU::CPU()
    : pc(1),halt(false),err(false)
{
    for(int i=1;i<=5;++i)
    {
        setReg(i,0);
    }
}

void CPU::setReg(int reg_num,int value)
{
    reg[reg_num-1]=value;
}

int CPU::getReg(int reg_num)const
{
    return(reg[reg_num-1]);
}

void CPU::setPc(int value)
{
    pc=value;
}
 
int CPU::getPc()const
{
    return pc;
}

// prints current instruction,all reg and pc if the mode == 1 
void CPU::print(const string &mode,const string &instr)const
{
    if(mode == "1")
    {
        cout << instr.substr(0,instr.size()-1)<<"-"
             << "R1="<<getReg(1)<<" "
             << "R2="<<getReg(2)<<" "
             << "R3="<<getReg(3)<<" "
             << "R4="<<getReg(4)<<" "
             << "R5="<<getReg(5)<<" "
             << "PC="<< getPc() << endl;
    }
}

//prints all reg and pc
void CPU::print()const
{
    cout << "R1="<<getReg(1)<<" "
         << "R2="<<getReg(2)<<" "
         << "R3="<<getReg(3)<<" "
         << "R4="<<getReg(4)<<" "
         << "R5="<<getReg(5)<<" "
         << "PC="<< getPc() << endl;
}

 // returns currents state of halt flag
bool CPU::halted()const
{
    return(halt);
}

 //return the current state of err flag,sets halt flag true if err flag is true 
bool CPU::error()
{
    if(err)
    {
        halt=true;
    }
    
    return err;
}

//returns the index of the next non space char in the string after last_non_space
int CPU::nextNonSpace(const string &str,int last_non_space)const
{
    int i;
    for(i=last_non_space;str[i]==' ' && i<str.size();++i);
    
    return i;
}

//converts alphabetic charachters to upper case if lower 
void CPU::allToUpper(string &str)const
{
    for(int i=0;i<str.size();++i)
    {
        if(str[i] >='a' && str[i] <='z')
        {
            str[i]-=('a'-'A');
        }
    }
}

// returns false if string has any other char then from the range '1'>=ch<='9', which is not terminating ';' char,else retunrs true
bool CPU::isLegalInt(const string & str)const
{
   for (int i = 0; i < str.length(); ++i)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            if(str[i]==';' && i==str.length()-1)
            {
                //do nothing
            }
            else
            {
                return false;
            }
        }
    }

    return true; 
}

int CPU::strToInt(const string &str)const
{
    int intLen;
    int i;
    int ans(0);

    for (i = 0; str[i] >= '0' && str[i] <='9'; ++i);
    intLen=i;

    for (i = 0; i < intLen; ++i)
    {
        ans*=10;
        ans+=(str[i]-'0');
    }

    return ans;
}

//modifies instr passed in getting it to the standart form,checks for syntax errors and sets err flag to true if one is found 
void CPU::validate(string & instr,int num_of_instr)
{   
    bool done(false);
    int pos(0);
    string temp_instr;
    string temp_str;
    string space(" ");
    InstType_t curInst(UNKNOWN);
    InstType_t jumpType(UNKNOWN);
    Parameter_t curParam(NON);
    
    allToUpper(instr);

    while(!done && !err)
    {
        switch (curInst)
        {
            case UNKNOWN :
            {
                pos=nextNonSpace(instr,pos);
                temp_str+=instr.substr(pos,3);
                pos+=3;

                if(temp_str == "MOV" || temp_str=="ADD" || temp_str=="SUB")
                {
                    curInst=MOV;
                    curParam=ONE;
                    temp_instr+=temp_str;
                    temp_str.clear();
                    if(instr[pos++]!=' ')
                    {
                        err=true;
                    }
                    temp_instr+=space;
                }
                else if(temp_str == "JMP")
                {
                    curInst=JMP;
                    curParam=ONE;
                    temp_instr+=temp_str;
                    temp_str.clear();
                    if(instr[pos++]!=' ')
                    {
                        err=true;
                    }
                    temp_instr+=space;
                    pos=nextNonSpace(instr,pos);
                    if(instr[pos]=='R' || instr[pos] == 'r')
                    {
                        jumpType=JMP2;
                    }
                    else
                    {
                        jumpType=JMP1;
                    }
                }
                else if(temp_str == "PRN")
                {
                    curInst=PRN;
                    curParam=ONE;
                    temp_instr+=temp_str;
                    temp_str.clear();
                    if(instr[pos++]!=' ')
                    {
                        err=true;
                    }
                    temp_instr+=space;
                }
                else if(temp_str=="HLT")
                {
                    curInst=HLT;
                    temp_instr+=temp_str;
                    temp_str.clear(); 
                }
                else
                {
                    err=true;
                }
            }break; 

            case MOV :
            case ADD :
            case SUB :
            {
                switch(curParam)
                {
                    case (ONE):
                    {	
                        pos=nextNonSpace(instr,pos);
                        temp_str+=instr.substr(pos,2);
                        pos+=2;
                        pos=nextNonSpace(instr,pos);
                        temp_str+=instr.substr(pos,1);
                        ++pos;

                        if(temp_str=="R1," || temp_str=="R2," || temp_str=="R3,"
                            || temp_str=="R4," || temp_str=="R5,")
                        {
                            curParam=TWO;
                            temp_instr+=temp_str+space;
                            temp_str.clear();
                        }
                        else
                        {
                            err=true;
                        }
                    }break;

                    case (TWO):
                    {
                        pos=nextNonSpace(instr,pos);
                        int next_space_pos=instr.find_first_of(' ',pos);
                        int next_colon_pos=instr.find_first_of(';',pos);
                        
                        if(next_space_pos== string::npos 
                                && next_colon_pos==string::npos)
                        {
                            temp_str+=instr.substr(pos);
                            pos=instr.size();
                        }
                        else if((next_space_pos!=string::npos &&
                                next_colon_pos==string::npos) || 
                                (next_space_pos<next_colon_pos && 
                                next_space_pos!=string::npos &&
                                next_colon_pos!=string::npos))
                        {
                            temp_str+=instr.substr(pos,next_space_pos-pos);
                            pos=next_space_pos;
                        }    
                        else
                        {
                            temp_str+=instr.substr(pos,next_colon_pos-pos);
                            pos=next_colon_pos;
                        }
                        
                        if(temp_str=="R1" || temp_str=="R2" || temp_str=="R3"
                            || temp_str=="R4" || temp_str=="R5")
                        {
                            temp_instr+=temp_str;
                            temp_str.clear();
                            done=true;
                            if(pos!=instr.size())
                            {
                                pos=nextNonSpace(instr,pos);
                                if(instr[pos]!=';' && pos!=instr.size())
                                {
                                    err=true;
                                }
                            }
                            temp_instr+=";";                            
                        }
                        else if(isLegalInt(temp_str))
                        {
                            temp_instr+=temp_str;
                            temp_str.clear();
                            done=true;
                            if(pos!=instr.size())
                            {
                                pos=nextNonSpace(instr,pos);
                                if(instr[pos]!=';' && pos!=instr.size())
                                {
                                    err=true;
                                }
                            }
                            temp_instr+=";"; 
                        }
                        else
                        {
                            err=true;
                        }
                        
                    }break;

                    default:break;
                }
            }break;

            case JMP :
            {
                switch (jumpType)
                {
                    case JMP1 :
                    { 
                        pos=nextNonSpace(instr,pos);
                        int next_space_pos=instr.find_first_of(' ',pos);
                        int next_colon_pos=instr.find_first_of(';',pos);
                        
                        if(next_space_pos== string::npos 
                                && next_colon_pos==string::npos)
                        {
                            temp_str+=instr.substr(pos);
                            pos=instr.size();
                        }
                        else if((next_space_pos!=string::npos &&
                                next_colon_pos==string::npos) || 
                                (next_space_pos<next_colon_pos && 
                                next_space_pos!=string::npos &&
                                next_colon_pos!=string::npos))
                        {
                            temp_str+=instr.substr(pos,next_space_pos-pos);
                            pos=next_space_pos;
                        }    
                        else
                        {
                            temp_str+=instr.substr(pos,next_colon_pos-pos);
                            pos=next_colon_pos;
                        }
                        
                        if(isLegalInt(temp_str))
                        {
                            temp_instr+=temp_str;
                            done=true;
                            if(pos!=instr.size())
                            {
                                pos=nextNonSpace(instr,pos);
                                if(instr[pos]!=';' && pos!=instr.size())
                                {
                                    err=true;
                                }
                            }
                            temp_instr+=";"; 
                            
                            if(strToInt(temp_str)>num_of_instr)
                            {
                                err=true;
                            }
                        }
                        else
                        {
                            err=true;
                        }
                    }break;

                    case JMP2 :
                    {
                        switch(curParam)
                        {
                            case (ONE):
                            {
                                pos=nextNonSpace(instr,pos);
                                temp_str+=instr.substr(pos,2);
                                pos+=2;
                                pos=nextNonSpace(instr,pos);
                                temp_str+=instr.substr(pos,1);
                                ++pos;

                                if(temp_str=="R1," || temp_str=="R2," || temp_str=="R3,"
                                    || temp_str=="R4," || temp_str=="R5,")
                                {
                                    curParam=TWO;
                                    temp_instr+=temp_str+space;
                                    temp_str.clear();
                                }
                                else
                                {
                                    err=true;
                                }
                            }break;

                            case (TWO):
                            {
                                pos=nextNonSpace(instr,pos);
                                int next_space_pos=instr.find_first_of(' ',pos);
                                int next_colon_pos=instr.find_first_of(';',pos);

                                if(next_space_pos== string::npos 
                                        && next_colon_pos==string::npos)
                                {
                                    temp_str+=instr.substr(pos);
                                    pos=instr.size();
                                }
                                else if((next_space_pos!=string::npos &&
                                        next_colon_pos==string::npos) || 
                                        (next_space_pos<next_colon_pos && 
                                        next_space_pos!=string::npos &&
                                        next_colon_pos!=string::npos))
                                {
                                    temp_str+=instr.substr(pos,next_space_pos-pos);
                                    pos=next_space_pos;
                                }    
                                else
                                {
                                    temp_str+=instr.substr(pos,next_colon_pos-pos);
                                    pos=next_colon_pos;
                                }

                                if(isLegalInt(temp_str))
                                {
                                    temp_instr+=temp_str;
                                    done=true;
                                    if(pos!=instr.size())
                                    {
                                        pos=nextNonSpace(instr,pos);
                                        if(instr[pos]!=';' && pos!=instr.size())
                                        {
                                            err=true;
                                        }
                                    }
                                    temp_instr+=";"; 

                                    if(strToInt(temp_str)>num_of_instr)
                                    {
                                        err=true;
                                    }
                                }
                                else
                                {
                                    err=true;
                                }
                            }break;

                            default:break;
                        }
                    }break;

                    default:break;
                }
            }break;

            case PRN :
            {
                pos=nextNonSpace(instr,pos);
                int next_space_pos=instr.find_first_of(' ',pos);
                int next_colon_pos=instr.find_first_of(';',pos);

                if(next_space_pos== string::npos 
                        && next_colon_pos==string::npos)
                {
                    temp_str+=instr.substr(pos);
                    pos=instr.size();
                }
                else if((next_space_pos!=string::npos &&
                        next_colon_pos==string::npos) || 
                        (next_space_pos<next_colon_pos && 
                        next_space_pos!=string::npos &&
                        next_colon_pos!=string::npos))
                {
                    temp_str+=instr.substr(pos,next_space_pos-pos);
                    pos=next_space_pos;
                }    
                else
                {
                    temp_str+=instr.substr(pos,next_colon_pos-pos);
                    pos=next_colon_pos;
                }

                if(temp_str=="R1" || temp_str=="R2" || temp_str=="R3"
                    || temp_str=="R4" || temp_str=="R5")
                {
                    temp_instr+=temp_str;
                    temp_str.clear();
                    done=true;
                    if(pos!=instr.size())
                    {
                        pos=nextNonSpace(instr,pos);
                        if(instr[pos]!=';' && pos!=instr.size())
                        {
                            err=true;
                        }
                    }
                    temp_instr+=";";                            
                }
                else if(isLegalInt(temp_str))
                {
                    temp_instr+=temp_str;
                    temp_str.clear();
                    done=true;
                    if(pos!=instr.size())
                    {
                        pos=nextNonSpace(instr,pos);
                        if(instr[pos]!=';' && pos!=instr.size())
                        {
                            err=true;
                        }
                    }
                    temp_instr+=";"; 
                }
                else
                {
                    err=true;
                }

            }break;

            case HLT :
            {
                done=true;
                temp_instr+=';';
                pos=nextNonSpace(instr,pos);
                if(pos!=instr.size())
                {
                    if(instr[pos]!=';' && pos!=instr.size())
                    {
                        err=true;
                    }
                }
            }break;

            default:break;
        }
    }
    
    instr=temp_instr;
}

// starting from lastPos stores the first ' ' or ';' terminated substr of mainStr to subStr and returns next char index
int CPU::readSubStr(const string & mainStr,string & subStr,int lastPos)const
{
	char ch;
	int i;

	for(i=0,ch=mainStr[i];ch!=' ' && ch!= ';' ;i++,ch=mainStr[i])
	{
		subStr+=ch;
	}

	return i+lastPos;
}

// executes instruction and increments pc by 1 
void CPU::execute(const string & instr)
{
    string tempStr;
    string argStr;
    int lastPos(0);
    int regNum1,regNum2,constant,line;

    lastPos=readSubStr(instr,tempStr,lastPos);

    if(tempStr == "MOV")
    {
        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        regNum1=tempStr[1]-'0';

        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);

        if(tempStr == "R1" || tempStr == "R2" || tempStr == "R3" 
            || tempStr == "R4" || tempStr == "R5")
        {
            regNum2=tempStr[1]-'0';
            setReg(regNum2,getReg(regNum1));
        }
        else
        {
            constant=strToInt(tempStr);
            setReg(regNum1,constant);
        }

    }
    else if(tempStr == "ADD")
    {
        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        regNum1=tempStr[1]-'0';

        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        if(tempStr == "R1" || tempStr == "R2" || tempStr == "R3" 
            || tempStr == "R4" || tempStr == "R5")
        {
            regNum2=tempStr[1]-'0';
            
            setReg(regNum1,(getReg(regNum1)+getReg(regNum2)));
        }
        else
        {
            constant=strToInt(tempStr);
            setReg(regNum1,(getReg(regNum1)+constant));
        }

    }
    else if(tempStr =="SUB")
    {
        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        regNum1=tempStr[1]-'0';

        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        if(tempStr == "R1" || tempStr == "R2" || tempStr == "R3" 
            || tempStr == "R4" || tempStr == "R5")
        {
            regNum2=tempStr[1]-'0';

            setReg(regNum1,(getReg(regNum1)-getReg(regNum2)));
        }
        else
        {
            constant=strToInt(tempStr);
            setReg(regNum1,(getReg(regNum1)-constant));
        }
    }
    else if(tempStr== "JMP")
    {
        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        if(tempStr == "R1," || tempStr == "R2," || tempStr == "R3," 
            || tempStr == "R4," || tempStr == "R5,")
        {
            regNum1=tempStr[1]-'0';

            tempStr.clear();
            argStr=instr.substr(++lastPos);
            lastPos=readSubStr(argStr,tempStr,lastPos);
            line=strToInt(tempStr);

            if(getReg(regNum1)==0)
            {
                setPc(line-1);
            }
        }
        else
        {
            line=strToInt(tempStr);
            setPc(line-1);
        }   
    }
    else if(tempStr == "PRN")
    {
        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        if(tempStr == "R1" || tempStr == "R2" || tempStr == "R3" 
            || tempStr == "R4" || tempStr == "R5")
        {
            regNum1=tempStr[1]-'0';

            cout << getReg(regNum1) << endl;
        }
        else
        {
            constant=strToInt(tempStr);

            cout << constant << endl;
        }   
    }
    else if(tempStr == "HLT")
    {
        halt = true;
    }
    else
    {
        //do nothing
    }

    setPc(getPc()+1);
}