#include<iostream>
#include<vector>
#include<string.h>
#include<fstream>
#include <sstream>
#include "jsoncons-0.156.0/include/jsoncons/json.hpp"
#include "jsoncons-0.156.0/include/jsoncons/jsoncons_ext/csv/csv.hpp"

using namespace jsoncons;
using namespace std;

//Returns true if s is a number else false
bool checkEachEntry(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]) == false)
			return false;
	}	
	return true;
}

bool is_file_open(string FileName)
{
	ifstream f(FileName.c_str());
	return f.good();
}

string ReadAndCheckInputFile(string FileName)
{
	bool flag = true;
	string s;
	if (is_file_open(FileName))
	{
		ifstream csvFile;
		csvFile.open(FileName);
		string line;
		getline(csvFile, line); // skip the 1st line
		while (getline(csvFile, line))
		{
			if (line.empty()) // skip empty lines:
			{
				//cout << "empty line!" << endl;
				continue;
			}
			istringstream iss(line);
			string lineStream;
			vector <string> row;
			while (getline(iss, lineStream, ','))
			{
				row.push_back(lineStream);
			}

			for (auto i = row.begin(); i != row.end(); ++i)
			{
				//cout << *i << " ";
				if(!checkEachEntry(*i))
				{
					flag = false;
					//cout << "File has some Invalid Data\n";
					s= "File has some Invalid Data";
					return s;
				}
			}
		}
		csvFile.close();
		if (flag == true)
		{
			return "File Read successfully";
		}
	}
	else
		return "File does not exist";
	return " ";
}

string ConvertToJson(string CSVFileName)
{
	std::ifstream is(CSVFileName);

	csv::csv_options options;
	options.assume_header(true)
		.trim(true)
		.ignore_empty_values(true)
		.column_types("string,string,string,string,string,string,string");
	ojson tasks = csv::decode_csv<ojson>(is, options);
	std::cout << "\n" << pretty_print(tasks) << "\n\n";
	return "CSV File converted to Json format";
}
