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

#include "Memory.h"
#include "CPU.h"

using namespace std;


CPU::CPU(int option_value) 
	: pc(1),halt(false),err(false),REG_SIZE(5),option(option_value)
{
    for(int i=1;i<=REG_SIZE;++i)
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

// prints all reg 
void CPU::print()const
{
	for (int i = 1; i <= REG_SIZE; ++i)
	{
		cout <<"["<<i-1<<"]"<<" -> "<<getReg(i)<<endl;  
	}
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

    if(!(str[0] >= '0' && str[0] <='9'))
    {
        return -1;
    }

    for (i = 0; str[i] >= '0' && str[i] <='9'; ++i);
    intLen=i;

    for (i = 0; i < intLen; ++i)
    {
        ans*=10;
        ans+=(str[i]-'0');
    }

    return ans;
}

bool CPU::isLegalAdress(const string & str,char pos)const
{
	bool ans;

	switch (pos)
	{
		case 'm':
		{
			if(str[0]=='#' && strToInt(str.substr(1,str.size()-2))<=49 
				&& strToInt(str.substr(1,str.size()-2))>=0 && str[str.size()-1]==',')
			{
				ans	= true;
			}
			else
			{
				ans = false;
			}
		}break;

		case 'e' :
		{
			if(str[0]=='#' && strToInt(str.substr(1,str.size()-2))<=49 
				&& strToInt(str.substr(1,str.size()-2))>=0 && str[str.size()-1]==';')
			{
				ans= true;
			}
			else if(str[0]=='#' && strToInt(str.substr(1,str.size()-1))<=49 
				&& strToInt(str.substr(1,str.size()-1))>=0 )
			{
				ans= true;
			}
			else
			{
				ans =false;
			}
		}break;

		default:break;
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
                    if(temp_str == "MOV")
                        curInst=MOV;
                    else
                        curInst=ADD;

                    curParam=ONE;
                    temp_instr+=temp_str;
                    temp_str.clear();
                    if(instr[pos++]!=' ')
                    {
                        err=true;
                    }
                    temp_instr+=space;
                }
                else if(temp_str == "JPN")
                {
                    curInst=JPN;
                    curParam=ONE;
                    temp_instr+=temp_str;
                    temp_str.clear();
                    if(instr[pos++]!=' ')
                    {
                        err=true;
                    }
                    temp_instr+=space;
                    jumpType=JPN2;
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
            {
            	switch(curParam)
                {
                    case (ONE):
                    {	

                        pos=nextNonSpace(instr,pos);
                        int first_pos=pos;
                        temp_str+=instr.substr(pos,2);
                        pos+=2;
                        pos=nextNonSpace(instr,pos);
                        temp_str+=instr.substr(pos,1);
                        ++pos;
                        int last_pos=pos;

                        if(temp_str=="R1," || temp_str=="R2," || temp_str=="R3,"
                            || temp_str=="R4," || temp_str=="R5,")
                        {
                            curParam=TWO;
                            temp_instr+=temp_str+space;
                            temp_str.clear();
                        }
                        else
                        {
                        	if(isLegalAdress(temp_str,'m'))
                        	{
                        		curParam=TWO;
	                            temp_instr+=temp_str+space;
	                            temp_str.clear();
                        	}
                        	else
                        	{
                        		if(last_pos-first_pos > 3)
                        		{
                        			err=true;
                        		}

                        		pos=nextNonSpace(instr,pos);
	                        	temp_str+=instr.substr(pos,1);
	                        	++pos;
	                        	if(isLegalAdress(temp_str,'m'))
	                        	{
	                        		curParam=TWO;
		                            temp_instr+=temp_str+space;
		                            temp_str.clear();
	                        	}
	                        	else
	                        	{
	                        		err=true;	
	                        	}
                        	}        	
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
                        else if(isLegalAdress(temp_str,'e'))
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
                        else if(isLegalAdress(temp_str,'e'))
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
            case JPN :
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
                    case JPN2 :
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
                else if(isLegalAdress(temp_str,'e'))
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
void CPU::execute(const string & arg_instr,Memory & my_memory)
{
    string instr;

    if(arg_instr[arg_instr.size()-1]!=';')
    {
        instr=arg_instr+';';
    }
    else
    {
        instr=arg_instr;
    }

    string tempStr;
    string argStr;
    int lastPos(0);
    int adress(-1);
    int regNum1(-1),regNum2(-1),constant(-1),line(-1);

    lastPos=readSubStr(instr,tempStr,lastPos);

    if(tempStr == "MOV")
    {
        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);

        if(tempStr == "R1," || tempStr == "R2," || tempStr == "R3," 
            || tempStr == "R4," || tempStr == "R5,")
        {
            regNum1=tempStr[1]-'0';
        }
        else
        {
            adress=strToInt(tempStr.substr(1,2));
        }

        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);

        if(tempStr == "R1" || tempStr == "R2" || tempStr == "R3" 
            || tempStr == "R4" || tempStr == "R5")
        {
            regNum2=tempStr[1]-'0';
        }
        else if(tempStr[0]=='#')
        {
            adress=strToInt(tempStr.substr(1,2));
        }
        else
        {
            constant=strToInt(tempStr);
        }

        if(regNum1 != -1)
        {
            if(regNum2!=-1)
            {
                setReg(regNum2,getReg(regNum1));
            }
            else if(adress!=-1)
            {
                my_memory.setMem(adress,getReg(regNum1));
            }
            else if(constant!=-1)
            {
                setReg(regNum1,constant);
            }
            else;
        }
        else
        {
            if(regNum2!=-1)
            {
                setReg(regNum2,my_memory.getMem(adress));
            }
            else
            {
                my_memory.setMem(adress,constant);
            }
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
        }
        else if(tempStr[0]=='#')
        {
            adress=strToInt(tempStr.substr(1,2));
        }
        else
        {
            constant=strToInt(tempStr);
        }

        if(regNum2!=-1)
        {
            setReg(regNum1,(getReg(regNum1)+getReg(regNum2)));
        }
        else if(adress!=-1)
        {
            setReg(regNum1,(getReg(regNum1)+my_memory.getMem(adress)));
        }
        else if(constant!=-1)
        {
            setReg(regNum1,(getReg(regNum1)+constant));
        }
        else;

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
        }
        else if(tempStr[0]=='#')
        {
            adress=strToInt(tempStr.substr(1,2));
        }
        else
        {
            constant=strToInt(tempStr);
        }

        if(regNum2!=-1)
        {
            setReg(regNum1,(getReg(regNum1)-getReg(regNum2)));
        }
        else if(adress!=-1)
        {
            setReg(regNum1,(getReg(regNum1)-my_memory.getMem(adress)));
        }
        else if(constant!=-1)
        {
            setReg(regNum1,(getReg(regNum1)-constant));
        }
        else;
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
    else if(tempStr== "JPN")
    {
        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        regNum1=tempStr[1]-'0';

        tempStr.clear();
        argStr=instr.substr(++lastPos);
        lastPos=readSubStr(argStr,tempStr,lastPos);
        line=strToInt(tempStr);

        if(getReg(regNum1)<=0)
        {
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
        else if(tempStr[0]=='#')
        {
            adress=strToInt(tempStr.substr(1,2));

            cout << my_memory.getMem(adress) << endl;
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
        print();
        cout <<endl;
        my_memory.printAll();
    }
    else
    {
        //do nothing
    }

    setPc(getPc()+1);
}