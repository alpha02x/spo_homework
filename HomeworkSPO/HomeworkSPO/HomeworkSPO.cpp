// HomeworkSPO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ChunkedString.h"

using namespace std;

int main()
{
	int bi, length = 0;
	
	char * input = new char[4096];
	cout << "Enter string:\n";
	cin.getline(input, sizeof(char) * 4096);
	auto cs = new ChunkedString(input);

	std::cout << "Select command:\n"
		<< "1 - print string\n"
		<< "2 - enter new string\n"
		<< "3 - print string length\n"
		<< "4 - get substring\n"
		<< "q - leave\n";
	
	string read_key;
	while (read_key[0] != 'q')
	{
		cin >> read_key;
		switch (read_key[0])
		{
		case '1':
			cs->print_all();
			break;
		case '2':
			cout << "Enter string:\n";
			cin.ignore();
			cin.getline(input, sizeof(char) * 4096);
			cs->reinitialize(input);
			break;
		case '3':
			cout << cs->get_length();
			break;
		case '4':
			cout << "Enter begin index:\n";
			cin >> input;
			bi = atoi(input);
			cout << "Enter length:\n";
			cin >> input;
			length = atoi(input);
			cs->get_substring(bi, length)->print_all();
			break;
		default:
			break;
		}
		cout << "\n";
	}
}
