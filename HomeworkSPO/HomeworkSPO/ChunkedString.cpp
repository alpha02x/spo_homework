#include <iostream>
#include "ChunkedString.h"
#include "ListString.h"

using namespace std;

ChunkedString::ChunkedString(char* text)
{
	initialize_list(text);
}

void ChunkedString::reinitialize(char* text)
{
	delete_all_current_linked_list_members();
	initialize_list(text);
}

ChunkedString::~ChunkedString()
{
	delete_all_current_linked_list_members();
}

void ChunkedString::print_all()
{
	auto current = first_element_;
	while (current != head_)
	{
		std::cout << current->str;
		current = current->next;
	}
	std::cout << current->str;
}

int ChunkedString::get_length()
{
	int cntr = 0;
	bool brk = false;
	auto current = first_element_;
	while (true)
	{
		for (int i = 0; i < 10; i++)
		{
			if (!brk) cntr++;
			if (current->str[i] == '\0') brk = true;
		}
		current = current->next;
		if (brk) return cntr;
	}
}

char* ChunkedString::get_string()
{
	auto length = get_length();
	auto index = 0;
	char* result = new char[length];

	auto* current = first_element_;
	while (true)
	{
		for (int i = 0; i < 10; i++)
		{
			result[index] = current->str[i];
			if (current->str[i] == '\0')
			{
				return result;
			}
			index++;
		}
		current = current->next;
	}
}

ChunkedString* ChunkedString::get_substring(int begin_index, int length)
{
	if (begin_index < 0) return new ChunkedString(new char[1]{'\0'});

	auto full_length = get_length();
	if (begin_index > full_length - 1) return new ChunkedString(new char[1]{'\0'});

	auto chars_left = length;
	auto skipped_elems_count = begin_index / 10;
	auto current = first_element_;
	for (int i = 0; i < skipped_elems_count; i++)
	{
		current = current->next;
	}

	auto initialization_substring = new char[length + 1];
	auto is_index = 0;
	begin_index = begin_index - skipped_elems_count * 10;
	while (chars_left != 0)
	{
		for (int i = begin_index; i < 10; i++)
		{
			if (chars_left == 0) goto terminate_and_end;
			initialization_substring[is_index] = current->str[i];
			if (current->str[i] == '\0') goto end;

			is_index++;
			chars_left--;
		}
		current = current->next;
		begin_index = 0;
	}

terminate_and_end:
	initialization_substring[length] = '\0';
	return new ChunkedString(initialization_substring);
end:
	return new ChunkedString(initialization_substring);
}

void ChunkedString::initialize_list(char* text)
{
	auto input_string = new string(text);
	auto blocks_count = input_string->length() / 10 + 1;
	for (int j = 0; j < blocks_count; j++)
	{
		auto current_element = new ListString();
		auto substring = input_string->substr(10 * j, 10);
		for (int i = 0; i < substring.length(); i++)
		{
			current_element->str[i] = substring[i];
		}

		current_element->next = current_element;

		if (first_element_ == nullptr) first_element_ = current_element;
		if (head_ != nullptr)head_->next = current_element;
		head_ = current_element;
	}
}

void ChunkedString::delete_all_current_linked_list_members()
{
	auto current_element = first_element_;
	while (current_element->next != head_->next)
	{
		auto next_element = current_element->next;
		free(current_element);
		current_element = next_element;
	}
	free(current_element);
	first_element_ = nullptr;
}
