/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* main.cpp                                                                 */
/* ---------                                                                */
/* Created on 05/15/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef enum { UNKNOWN=10,MOV,ADD,SUB,JPN,JPN2,JMP,JMP1,JMP2,PRN,HLT }InstType_t;
typedef enum {NON,ONE,TWO} Parameter_t;


int numOfLinesInTheFile(ifstream & file);
void setReturnPoints(ifstream & file,streampos returnPoint[],int const size); //creates a return point at the begining of each line in the file and stores them in the returnPoint arr
int readNRunInstructions(ifstream & file,int mode,streampos returnPoint[],int size,int reg[],int line_num,int myRam[],const int ram_size); // calls parseTheLine and exeInstraction, returns 1 if any syntax error is found
int cStrLen(char const * cStr);
int readSubStr(string & mainStr,string & subStr,int lastPos);  // stores the first ' ' or ';' terminated substr of mainStr to subStr and returns next char index
int exeInstraction(string instr,int reg[],int &nextInstr,bool & sentinel,int myRam[]); //executes one instruction,returns 1 if HLT instruction is executed
int strToInt(string str); //returns -1 on failer
int strToInt(char * str);
int parseTheLine(ifstream & file,string & instr,int line_num); //pasrses the line of the file checking for syntax errors,returns valid instruction set through instr parameter,func returns 1 if 
// error is found , 0 if no error 
void toUpper(char &ch); //converts alphabetic charachters to upper case if lower 
void eatSpaces(ifstream & file); // removes all spaces up to the next non-space char 
bool isLegalInt(string str,char pos);// returns false if string has any other char then from the range '1'>=ch<='9' and is not terminating ';' char,else retunrs true
void initReturnPoints(ifstream &file,streampos returnPoint[],int const size); // initializes the arr of returnPoint-s to the EOF 
void initMyRam(int myRam[],const int size);
void printMyRam(int myRam[],const int size);
bool isLegalAdress(string str,char pos); // checks if the adress's syntax is correct deppending on its position 
// 'm' - midle , 'e' - end 

int main(int argc, char const *argv[])
{
	int const RAM_SIZE=50; 
	int myRam[RAM_SIZE];

	int const SIZE(260);
	streampos returnPoint[SIZE];
	int reg[5]={0,0,0,0,0};
	int line_num(0);
	ifstream file;
	int mode;


	mode = strToInt(argv[2]);

	if(argc <=1 || cStrLen(argv[2])>1 || (mode!=0 && mode!=1 && mode!=2))
	{
		cerr << "File name and option flag are not set or incorrect.\n"
		<< "Please try running the program again!\n";

		return 1;
	}

	file.open(argv[1]);
	if(file.fail())
	{
		cerr << "File could not be opened.\nExiting the program ... \n";

		return 1;
	}

	line_num=numOfLinesInTheFile(file);

	initMyRam(myRam,RAM_SIZE);
	initReturnPoints(file,returnPoint,SIZE);
	setReturnPoints(file,returnPoint,SIZE);

	if(readNRunInstructions(file,mode,returnPoint,SIZE,reg,line_num,myRam,RAM_SIZE))
	{
		cerr << "Syntax error!\nTerminating the program ...\n";
		return 1;
	}

	cout <<"R1="<<reg[0]<<",R2="<<reg[1]<<",R3="<<reg[2]<<",R4="<<reg[3]<<",R5="<<reg[4]<<endl;
	printMyRam(myRam,RAM_SIZE);

	file.close();

	return 0;
}

void initMyRam(int myRam[],const int size)
{
	for (int i = 0; i < size; ++i)
	{
		myRam[i]=0;
	}
}

int strToInt(string str)
{
	int intLen;
	int i;
	int ans(0);

	for (i = 0; str[i] >= '0' && str[i] <='9'; ++i);
	intLen=i;

	if(intLen == 0)
	{
		return -1;
	}
	
	for (i = 0; i < intLen; ++i)
	{
		ans*=10;
		ans+=(str[i]-'0');
	}

	return ans;
}

int strToInt(char * str)
{
	int intLen;
	int i;
	int ans(0);

	for (i = 0; str[i] >= '0' && str[i] <='9'; ++i);
	intLen=i;

	if(intLen == 0)
	{
		return -1;
	}
	
	for (i = 0; i < intLen; ++i)
	{
		ans*=10;
		ans+=(str[i]-'0');
	}

	return ans;
}

int cStrLen(char const * cStr)
{
	char ch;
	int i;

	for (i = 0,ch=cStr[i]; ch!='\0'; ++i,ch=cStr[i]);

	return i;
}

void printMyRam(int myRam[],const int size)
{
	cout << "Memory state: ";
	for (int i = 0; i < size; ++i)
	{
		cout << myRam[i]<< " ";
	}
	cout << endl;
}

// calls parseTheLine and exeInstraction, returns 1 if any syntax error is found
int readNRunInstructions(ifstream & file,int mode,streampos returnPoint[],int size,int reg[],int line_num,int myRam[],const int ram_size)
{
	bool sentinel(true);
	bool err(false);
	string instr;
	int nextInstr(0);
	int halt_read(0);

	while (sentinel && nextInstr < size)
	{
		file.seekg(returnPoint[nextInstr]);
		nextInstr++;
		instr.clear();

		err=parseTheLine(file,instr,line_num);
		if(err)
		{
			sentinel=false;
		}
		else
		{	
			halt_read=exeInstraction(instr,reg,nextInstr,sentinel,myRam);

			if(mode ==1 )
			{
				cout << instr.substr(0,instr.size()-1)<<"-"<<"R1="<<reg[0]
				<<",R2="<<reg[1]<<",R3="<<reg[2]<<",R4="<<reg[3]<<",R5="<<reg[4]<<endl;
			}
			else if(mode == 2)
			{
				cout << instr.substr(0,instr.size()-1)<<"-"<<"R1="<<reg[0]
				<<",R2="<<reg[1]<<",R3="<<reg[2]<<",R4="<<reg[3]<<",R5="<<reg[4]<<endl;
				printMyRam(myRam,ram_size);
			}	
		}
	}

	if(err || !halt_read)
	{
		return 1;
	}

	return 0;
}

// stores the first ' ' or ';' terminated substr of mainStr to subStr and returns next char index
int readSubStr(string & mainStr,string & subStr,int lastPos)
{
	char ch;
	int i;

	for(i=0,ch=mainStr[i];ch!=' ' && ch!= ';' ;i++,ch=mainStr[i])
	{
		subStr+=ch;
	}

	return i+lastPos;
}

 //executes one instruction,returns 1 if HLT instruction is executed
int exeInstraction(string instr,int reg[],int &nextInstr,bool & sentinel,int myRam[])
{
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
				reg[regNum2-1]=reg[regNum1-1];
			}
			else if(adress!=-1)
			{
				myRam[adress]=reg[regNum1-1];
			}
			else if(constant!=-1)
			{
				reg[regNum1-1]=constant;
			}
			else;
		}
		else
		{
			if(regNum2!=-1)
			{
				reg[regNum2-1]=myRam[adress];
			}
			else
			{
				myRam[adress]=constant;
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
			reg[regNum1-1]+=reg[regNum2-1];
		}
		else if(adress!=-1)
		{
			reg[regNum1-1]+=myRam[adress];
		}
		else if(constant!=-1)
		{
			reg[regNum1-1]+=constant;
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
			reg[regNum1-1]-=reg[regNum2-1];
		}
		else if(adress!=-1)
		{
			reg[regNum1-1]-=myRam[adress];
		}
		else if(constant!=-1)
		{
			reg[regNum1-1]-=constant;
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

			if(reg[regNum1-1]==0)
			{
				nextInstr=line-1;
			}
		}
		else
		{
			line=strToInt(tempStr);
			nextInstr=line-1;
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

		if(reg[regNum1-1]<=0)
		{
			nextInstr=line-1;
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

			cout << reg[regNum1-1] << endl;
		}
		else if(tempStr[0]=='#')
		{
			adress=strToInt(tempStr.substr(1,2));

			cout << myRam[adress] << endl;
		}
		else
		{
			constant=strToInt(tempStr);
			
			cout << constant << endl;
		}	
	}
	else if(tempStr == "HLT")
	{
		sentinel = false;
		return 1;
	}
	else
	{
		//do nothing
	}

	return 0;
}

// initializes the arr of returnPoint-s to the EOF 
void initReturnPoints(ifstream &file,streampos returnPoint[],int const size)
{
	streampos endOfFile;

	file.seekg(0,file.end);
	endOfFile=file.tellg();

	for (int i = 0; i < size; ++i)
	{
		returnPoint[i]=endOfFile;
	}

	file.clear();
	file.seekg(0,file.beg);
}

//creates a return point at the begining of each line in the file and stores them in the returnPoint arr
void setReturnPoints(ifstream & file,streampos returnPoint[],int const size)
{
	char ch;
	int i(0);

	returnPoint[i]=file.tellg();

	while(file.get(ch) && i<size)
	{
		if(ch == '\n' && file.peek()!=EOF)
		{
			i++;
			returnPoint[i]=file.tellg();
		}
	}

	file.clear();
	file.seekg (0, file.beg);
}

int numOfLinesInTheFile(ifstream & file) 
{
	int ans(1);
	char ch;

	while(file.get(ch))
	{
		if(ch == '\n')
		{
			ans++;
		}
	}

	file.clear();
	file.seekg (0, file.beg);

	return ans;
}

 //converts alphabetic charachters to upper case if lower 
void toUpper(char &ch)
{
	if(ch >='a' && ch <='z')
	{
		ch-=('a'-'A');
	}
}

// removes all spaces up to the next non-space char 
void eatSpaces(ifstream & file)
{
	char ch;

	for (ch = file.peek() ; ch == ' '; ch = file.peek())
	{
		file.get(ch);
	}
}

// returns false if string has any other char then from the range '1'>=ch<='9' and is not terminating ';' char,else retunrs true
bool isLegalInt(string str,char pos)
{
	switch (pos)
	{
		case 'm':
		{
			for (int i = 0; i < str.length(); ++i)
			{
				if(str[i] < '0' || str[i] > '9')
				{
					if(str[i]==',' && i==str.length()-1)
					{
						//do nothing
					}
					else
					{
						return false;
					}
				}
			}

		}break;

		case 'e':
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

		}break;

		default:break;
	}

	return true;
}

bool isLegalAdress(string str,char pos)
{
	bool ans;

	switch (pos)
	{
		case 'm':
		{
			if(str[0]=='#' && strToInt(str.substr(1,str.size()-1))<=49 
				&& strToInt(str.substr(1,str.size()-1))>=0 && isLegalInt(str.substr(1,str.size()-1),'m'))
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
			if(str[0]=='#' && strToInt(str.substr(1,str.size()-1))<=49 
				&& strToInt(str.substr(1,str.size()-1))>=0 && isLegalInt(str.substr(1,str.size()-1),'e'))
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

//pasrses the line of the file checking for syntax errors,returns valid instruction set through instr parameter,func returns 1 if 
// error is found , 0 if no error 
int parseTheLine(ifstream & file,string & instr,int line_num)
{
	string tempStr;
	string space(" ");
	char ch;
	int charRead(0);
	bool done(false),err(false);
	bool eatSpacesIsOn(true);
	InstType_t curInst(UNKNOWN);
	InstType_t jumpType(UNKNOWN);
	Parameter_t curParam(NON);

	while (!err && !done)
	{
		if(eatSpacesIsOn)
		{
			eatSpaces(file);
			eatSpacesIsOn=false;
		}
		
		ch=file.get();
		toUpper(ch);
		++charRead;

		if(ch == EOF && curInst !=HLT)
		{
			err=true;
		}

		if(!err)
		{
			switch (curInst)
			{
				case UNKNOWN :
				{
					tempStr+=ch;
					if(charRead == 3)
					{
						if(tempStr == "MOV")
						{
							curInst=MOV;
							curParam=ONE;
							charRead=0;
							instr+=tempStr;
							tempStr.clear();
							file.get(ch);
							if(ch!=' ')
							{
								err=true;
							}
							instr+=space;
						}
						else if(tempStr=="ADD" || tempStr=="SUB")
						{
							curInst=ADD;
							curParam=ONE;
							charRead=0;
							instr+=tempStr;
							tempStr.clear();
							file.get(ch);
							if(ch!=' ')
							{
								err=true;
							}
							instr+=space;
						}
						else if(tempStr == "JPN")
						{
							curInst=JPN;
							curParam=ONE;
							charRead=0;
							instr+=tempStr;
							tempStr.clear();
							file.get(ch);
							if(ch!=' ')
							{
								err=true;
							}
							instr+=space;
							jumpType=JPN2;
						}
						else if(tempStr == "JMP")
						{
							curInst=JMP;
							curParam=ONE;
							charRead=0;
							instr+=tempStr;
							tempStr.clear();
							file.get(ch);
							if(ch!=' ')
							{
								err=true;
							}
							instr+=space;
							eatSpaces(file);
							if(file.peek()=='R' || file.peek() == 'r')
							{
								jumpType=JMP2;
							}
							else
							{
								jumpType=JMP1;
							}

						}
						else if(tempStr == "PRN")
						{
							curInst=PRN;
							curParam=ONE;
							charRead=0;
							instr+=tempStr;
							tempStr.clear();
							file.get(ch);
							if(ch!=' ')
							{
								err=true;
							}
							instr+=space;
						}
						else if(tempStr=="HLT")
						{
							curInst=HLT;
							charRead=0;
							instr+=tempStr;
							tempStr.clear();
						}
						else
						{
							err=true;
						}

						eatSpacesIsOn=true;
					}
				}break;

				case MOV :
				{
					switch(curParam)
					{
						case (ONE):
						{	
							if(charRead == 1)
							{
								tempStr+=ch;
							}
									
							if(tempStr[0]=='#')
							{
								if(ch!=' ' && charRead!=1)
								{
									tempStr+=ch;
								}

								if(ch == ' ' || ch == ',')
								{
									if(isLegalAdress(tempStr,'m'))
									{
										curParam=TWO;
										charRead=0;
										instr+=tempStr;
										tempStr.clear();
										if(instr[instr.length()-1]!=',')
										{
											eatSpaces(file);
											file.get(ch);
											if(ch!=',')
											{
												err=true;
											}

											instr+=",";
										}

										instr+=space;
									}
									else
									{
										err=true;
									}

									eatSpacesIsOn=true;
								}
							}
							else
							{
								if(charRead !=1)
								{
									tempStr+=ch;
								}
								
								if(charRead == 2)
								{	
									eatSpacesIsOn=true;
								}

								if(charRead==3)
								{
									if(tempStr=="R1," || tempStr=="R2," || tempStr=="R3,"
										|| tempStr=="R4," || tempStr=="R5,")
									{
										curParam=TWO;
										charRead=0;
										instr+=tempStr+space;
										tempStr.clear();

									}
									else
									{
										err=true;
									}

									eatSpacesIsOn=true;
								}
							}
						}break;

						case (TWO):
						{
							if(ch!='\n' && ch!=' ')
							{
								tempStr+=ch;
							}
							
							if(ch==';' || ch=='\n' || ch==' ')
							{
								if(tempStr=="R1" || tempStr=="R2" || tempStr=="R3"
									|| tempStr=="R4" || tempStr=="R5" || tempStr=="R1;" 
									|| tempStr=="R2;" || tempStr=="R3;" || tempStr=="R4;" 
									|| tempStr=="R5;")
								{
									instr+=tempStr;
									done=true;
									if(instr[instr.length()-1]!=';')
									{
										if(ch==' ')
										{
											eatSpaces(file);
											file.get(ch);
											if(ch!=';' && ch!='\n')
											{
												err=true;
											}
										}

										instr+=";";
									}
								}
								else if(isLegalAdress(tempStr,'e'))
								{
									instr+=tempStr;
									done=true;
									if(instr[instr.length()-1]!=';')
									{
										if(ch==' ')
										{
											eatSpaces(file);
											file.get(ch);
											if(ch!=';' && ch!='\n')
											{
												err=true;
											}
										}

										instr+=";";
									}
								}
								else if(isLegalInt(tempStr,'e'))
								{
									instr+=tempStr;
									done=true;
									if(instr[instr.length()-1]!=';')
									{
										if(ch==' ')
										{
											eatSpaces(file);
											file.get(ch);
											if(ch!=';' && ch!='\n')
											{
												err=true;
											}
										}

										instr+=";";
									}
								}
								else
								{
									err=true;
								}
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
							if(charRead == 2)
							{
								eatSpacesIsOn=true;
							}

							tempStr+=ch;
							if(charRead==3)
							{
								if(tempStr=="R1," || tempStr=="R2," || tempStr=="R3,"
									|| tempStr=="R4," || tempStr=="R5,")
								{
									curParam=TWO;
									charRead=0;
									instr+=tempStr+space;
									tempStr.clear();

								}
								else
								{
									err=true;
								}

								eatSpacesIsOn=true;
							}
						}break;

						case (TWO):
						{
							if(ch!='\n' && ch!=' ')
							{
								tempStr+=ch;
							}
							
							if(ch==';' || ch=='\n' || ch==' ')
							{
								if(tempStr=="R1" || tempStr=="R2" || tempStr=="R3"
									|| tempStr=="R4" || tempStr=="R5" || tempStr=="R1;" 
									|| tempStr=="R2;" || tempStr=="R3;" || tempStr=="R4;" 
									|| tempStr=="R5;")
								{
									instr+=tempStr;
									done=true;
									if(instr[instr.length()-1]!=';')
									{
										if(ch==' ')
										{
											eatSpaces(file);
											file.get(ch);
											if(ch!=';' && ch!='\n')
											{
												err=true;
											}
										}

										instr+=";";
									}
								}
								else if(isLegalAdress(tempStr,'e'))
								{
									instr+=tempStr;
									done=true;
									if(instr[instr.length()-1]!=';')
									{
										if(ch==' ')
										{
											eatSpaces(file);
											file.get(ch);
											if(ch!=';' && ch!='\n')
											{
												err=true;
											}
										}

										instr+=";";
									}
								}
								else if(isLegalInt(tempStr,'e'))
								{
									instr+=tempStr;
									done=true;
									if(instr[instr.length()-1]!=';')
									{
										if(ch==' ')
										{
											eatSpaces(file);
											file.get(ch);
											if(ch!=';' && ch!='\n')
											{
												err=true;
											}
										}

										instr+=";";
									}
								}
								else
								{
									err=true;
								}
							}
						}break;

						default:break;
					}
				}break;

				case JPN :
				case JMP :
				{		
					switch (jumpType)
					{
						case JMP1 :
						{ 
							if(ch!='\n' && ch!=' ')
							{
								tempStr+=ch;
							}
							
							if(ch==';' || ch=='\n' || ch==' ')
							{
								if(isLegalInt(tempStr,'e'))
								{
									instr+=tempStr;
									done=true;
									if(instr[instr.length()-1]!=';')
									{
										if(ch==' ')
										{
											eatSpaces(file);
											file.get(ch);
											if(ch!=';' && ch!='\n')
											{
												err=true;
											}
										}

										instr+=";";
									}
									if(strToInt(tempStr)>line_num)
									{
										err=true;
									}
								}
								else
								{
									err=true;
								}
							}
						}break;

						case JPN2 :
						case JMP2 :
						{
							switch(curParam)
							{
								case (ONE):
								{	
									if(charRead == 2)
									{
										eatSpacesIsOn=true;
									}

									tempStr+=ch;
									if(charRead==3)
									{
										if(tempStr=="R1," || tempStr=="R2," || tempStr=="R3,"
											|| tempStr=="R4," || tempStr=="R5,")
										{
											curParam=TWO;
											charRead=0;
											instr+=tempStr+space;
											tempStr.clear();

										}
										else
										{
											err=true;
										}

										eatSpacesIsOn=true;
									}
								}break;

								case (TWO):
								{
									if(ch!='\n' && ch!=' ')
									{
										tempStr+=ch;
									}
									
									if(ch==';' || ch=='\n' || ch==' ')
									{
										if(isLegalInt(tempStr,'e'))
										{
											instr+=tempStr;
											done=true;
											if(instr[instr.length()-1]!=';')
											{
												if(ch==' ')
												{
													eatSpaces(file);
													file.get(ch);
													if(ch!=';' && ch!='\n')
													{
														err=true;
													}
												}

												instr+=";";
											}
											if(strToInt(tempStr)>line_num)
											{
												err=true;
											}
										}
										else
										{
											err=true;
										}
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
					if(ch!='\n' && ch!=' ')
					{
						tempStr+=ch;
					}
					
					if(ch==';' || ch=='\n' || ch==' ')
					{
						if(tempStr=="R1" || tempStr=="R2" || tempStr=="R3"
							|| tempStr=="R4" || tempStr=="R5" || tempStr=="R1;" 
							|| tempStr=="R2;" || tempStr=="R3;" || tempStr=="R4;" 
							|| tempStr=="R5;")
						{
							instr+=tempStr;
							done=true;
							if(instr[instr.length()-1]!=';')
							{
								if(ch==' ')
								{
									eatSpaces(file);
									file.get(ch);
									if(ch!=';' && ch!='\n')
									{
										err=true;
									}
								}

								instr+=";";
							}
						}
						else if(isLegalAdress(tempStr,'e'))
						{
							instr+=tempStr;
							done=true;
							if(instr[instr.length()-1]!=';')
							{
								if(ch==' ')
								{
									eatSpaces(file);
									file.get(ch);
									if(ch!=';' && ch!='\n')
									{
										err=true;
									}
								}

								instr+=";";
							}
						}
						else if(isLegalInt(tempStr,'e'))
						{
							instr+=tempStr;
							done=true;
							if(instr[instr.length()-1]!=';')
							{
								if(ch==' ')
								{
									eatSpaces(file);
									file.get(ch);
									if(ch!=';' && ch!='\n')
									{
										err=true;
									}
								}

								instr+=";";
							}
						}
						else
						{
							err=true;
						}
					}
				}break;

				case HLT :
				{
					if(ch==';' || ch=='\n' || ch==EOF)
					{
						instr+=";";
						done=true;
					}
					else
					{
						err=true;
					}
				}break;

				default: break;
			}
		}	
	}

	if(err)
	{
		return 1;
	}

	return 0;
}