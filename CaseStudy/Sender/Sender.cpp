#include<iostream>
#include<string>
#include"Sender.h"
using namespace std;
 
int main()
{
	string FileName = "../TestFootfallData.csv";
	string str=ReadAndCheckInputFile(FileName);
	if (str == "File Read successfully")
	{
		string s = ConvertToJson(FileName);
	}	
	else
		cout << str;   //Either File has invalid data or file does not exist
	getchar();
  return 0;
}
