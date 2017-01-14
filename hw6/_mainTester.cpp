#include "requiredIncs.h"

int main(int argc, char** argv){

	const char* filename = argv[1];
	int option = atoi(argv[2]);

	cout << "------------------------\n";
	CPUProgramDyn myObj;
	--myObj; // error
	myObj+="One";
	myObj+="Two";
	myObj+="Three";
	cout << myObj <<endl;
	cout << myObj-- << endl;
	cout << --myObj << endl;
	myObj.ReadFile(filename);
	cout << myObj[0] <<endl;
	cout << myObj[myObj.size()-1] <<endl;
	cout << "------------------------\n";

	CPUProgramDyn myObj2;
	myObj2+="One";
	myObj2+="Two";
	myObj2+="Three";
	cout << (myObj + myObj2) << endl;
	cout << "------------------------\n";

	CPUProgramDyn myObj3;
	myObj3 = (myObj+myObj2);
	cout << myObj3(0,myObj3.size()-1) <<endl;
	cout << "------------------------\n";	

	return 0;
}