#pragma once
#include <iostream>

#include "ListString.h"

using namespace std;

class ChunkedString
{
public:
	ChunkedString(char* text);

	~ChunkedString();

	void reinitialize(char* text);

	void print_all();

	int get_length();

	char* get_string();

	ChunkedString* get_substring(int begin_index, int length);


private:
	ListString* first_element_;
	ListString* head_;

	void initialize_list(char* text);

	void delete_all_current_linked_list_members();
};
