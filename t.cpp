#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
	FILE *in;
	char buff[512];
string input;
cout << "enter command: " << endl;
getline(cin,input);
cout << "THIS IS YPUR INPUT: " << input << endl;
	if(!(in = popen(input.c_str(), "r"))){
		return 1;
	}
		else
		{
			cout << "YES";
		}
	while(fgets(buff, sizeof(buff), in)!=NULL){

		cout << buff;
	}
	pclose(in);

	return 0;
}
