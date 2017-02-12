/****************************************
*Emmanuel Banjo
*Honeywell C++ Coding Challenge
*****************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

/**********Function Declaration*************/
void printStringBuffer(vector<string> &buffer, int size);
vector<string> fileStringBuffer(std::ifstream &file, char *fileName);
int posOfString(int pos, vector<string> &a, vector<string> &b);



/**********Function Implementation**********/
void printStringBuffer(vector<string> &buffer, int size)
{
	for(int i = 0; i < size; i++)
	{
		std::cout << buffer[i] << endl;
	}
}

vector<string> fileStringBuffer(std::ifstream &file, char *fileName)
{
	vector<string> temp;
	std::string inString;

	file.open(fileName);
	while(file)
	{
		getline(file, inString);
		temp.push_back(inString);
	}

	file.close();

	return temp;
}

int posOfString(int pos, vector<string> &a, vector<string> &b)
{
	for(int i = 0; i < b.size(); i++)
	{
		if(b[i] == a[pos])
		{
			return i;
		}
	}
}

int main(int argc, char *argv[])
{
	//Check if there is a valid file to be read
	if(argv[1] == NULL)
	{
		std::cout << "Please enter a file to read" << std::endl;
		exit(1);
	}

	std::ifstream infile;
	
	std::cout << "Reading from the file" << std::endl;
	
	vector<string> v = fileStringBuffer(infile, argv[1]); //Buffer holding lines from file
	vector<string> comp; //Buffer holding each unique occurence of line 
	vector<int> freq; //Buffer holding integer values of line occurences

	bool isPresent;

	for(int i = 0; i < v.size()-1; i++)
	{
		isPresent = (std::find(comp.begin(), comp.end(), v[i]) != comp.end());

		if(!isPresent)
		{	
			//std::cout << "String not found, appending string to compare vector" << std::endl;
			comp.push_back(v[i]);
			freq.push_back(1);
		}
		else
		{
			//std::cout << "Same string found" << std::endl;
			int position = posOfString(i, v, comp);
			freq[position]++;
		}
	}
	
	//printStringBuffer(comp, comp.size()); //Debugging..show the vector of unique strings

	for(int i = 0; i < freq.size(); i++)
	{
		std::cout << freq[i] << " " << comp[i] << std::endl;
	}

	return 0;
}