﻿//test
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <cctype>
#include <algorithm>

struct Str_Num {
	std::string Table_name;
	int Num;
	int ID;
	std::string surname;
	std::string name;
	std::string second_name;
	int year;
	int pasport;
	int money;
	Str_Num* next = NULL;
	Str_Num* prev = NULL;
	Str_Num* right = NULL;

};

void create_table(std::string file_name, std::string Table_name, Str_Num **start, Str_Num **end) {
	file_name.push_back('.');
	file_name.push_back('t');
	file_name.push_back('x');
	file_name.push_back('t');
	const char * name = file_name.c_str();
	std::ifstream fin(name);
	Str_Num* start_tmp = new Str_Num();
	Str_Num* c = new Str_Num();
	c = start_tmp;
	while (fin.peek() != EOF)
	{
		c->Table_name = Table_name;
		fin >> c->Num;
		fin >> c->ID;
		fin >> c->surname;
		fin >> c->name;
		fin >> c->second_name;
		fin >> c->year;
		fin >> c->pasport;
		fin >> c->money;
		if (fin.peek() != EOF)
		{
			c->next = new Str_Num();
			c->next->prev = c;
			c = c->next;
		}
	}
	if ((*start)->Table_name == "") {
		(*start)->Table_name = start_tmp->Table_name;
		(*start)->Num = start_tmp->Num;
		(*start)->ID = start_tmp->ID;
		(*start)->surname = start_tmp->surname;
		(*start)->name = start_tmp->name;
		(*start)->second_name = start_tmp->second_name;
		(*start)->year = start_tmp->year;
		(*start)->pasport = start_tmp->pasport;
		(*start)->money = start_tmp->money;
		(*start)->next = start_tmp->next;
		(*start)->prev = start_tmp->prev;
	}
	else {
		(*end)->right = new Str_Num();
		(*end)->right = start_tmp;
		*end = (*end)->right;
	}
	fin.close();
}
int delete_table(std::string Table_name, Str_Num **start, Str_Num **end) {
	Str_Num* c_tmp = new Str_Num();
	Str_Num* c = new Str_Num();
	c = *start;
	c_tmp = *start;
	while (1)
	{
		if (c->Table_name != Table_name && c == *end)
		{
			return 0;
		}
		else if (c->Table_name == Table_name)
		{
			if (*start == c)
			{
				*start = (*start)->right;
				c->right = NULL;
				delete (c);
				return 1;
			}
			else
			{
				while (c_tmp->right != c)
				{
					c_tmp = c_tmp->right;
				}
				if (c == *end)
				{
					*end = c_tmp;
					(*end)->right = NULL;
					delete (c);
					return 1;
				}
				else
				{
					c_tmp->right = c->right;
					c->right = NULL;
					delete (c);
					return 1;
				}
			}
		}
		else
		{
			c = c->right;
		}
	}
}
int sort_table(std::string Table_name, Str_Num **start, Str_Num **end, int n) {
	Str_Num* tmp = new Str_Num();
	Str_Num* tmp_start = new Str_Num();
	Str_Num* tmp_end = new Str_Num();
	Str_Num* tmp_start_prev = new Str_Num();
	Str_Num* l = new Str_Num();
	Str_Num* r = new Str_Num();
	Str_Num* left = new Str_Num();
	Str_Num* right = new Str_Num();
	int mid_ID;
	std::string mid_str;
	int mid_num;

	tmp_start = *start;
	tmp_start_prev = *start;
	while (tmp_start->Table_name != Table_name) {
		tmp_start = tmp_start->right;
		if (tmp_start == *end&&tmp_start->Table_name != Table_name)
		{
			return 0;
		}
	}
	if (tmp_start == *start)
	{
		tmp_start_prev = NULL;
	}
	else
	{
		while (tmp_start_prev->right != tmp_start)
		{
			tmp_start_prev = tmp_start_prev->right;
		}
	}
	tmp_end = tmp_start;
	while (tmp_end->next != NULL)
	{
		tmp_end = tmp_end->next;
	}
	switch (n)
	{
	case 1: {
		std::stack <Str_Num*> st_table;

		st_table.push(tmp_end);
		st_table.push(tmp_start);
		do {
			left = st_table.top();
			st_table.pop();
			right = st_table.top();
			st_table.pop();

			mid_num = (left->Num + right->Num) / 2;
			tmp = tmp_start;
			while (tmp->Num != mid_num)
			{
				tmp = tmp->next;
			}
			mid_ID = tmp->ID;
			l = left;
			r = right;
			while (l->Num < r->Num)
			{
				while (l->ID < mid_ID) l = l->next;
				while (mid_ID < r->ID) r = r->prev;
				if ((l->Num <= r->Num) && l != r)
				{
					if (l == tmp_start && r == tmp_end) {
						if (l == *start)
						{
							*start = r;
						}
						if (l == *end)
						{
							*end = r;
						}
						tmp_start_prev->right = r;
						tmp_start = r;
						r->prev->next = l;
						l->next->prev = r;
						tmp_end = l;
						tmp = l->next;
						l->next = r->next;
						r->next = tmp;
						tmp = l->prev;
						l->prev = r->prev;
						r->prev = tmp;
					}
					else if (l == tmp_start) {
						tmp_start_prev->right = r;
						tmp_start = r;
						r->prev->next = l;
						l->next->prev = r;
						r->next->prev = l;
						tmp = l->next;
						l->next = r->next;
						r->next = tmp;
						tmp = l->prev;
						l->prev = r->prev;
						r->prev = tmp;
					}
					else if (r == tmp_end) {
						l->prev->next = r;
						r->prev->next = l;
						l->next->prev = r;
						tmp_end = l;
						tmp = l->next;
						l->next = r->next;
						r->next = tmp;
						tmp = l->prev;
						l->prev = r->prev;
						r->prev = tmp;
					}
					else
					{
						l->prev->next = r;
						r->prev->next = l;
						l->next->prev = r;
						r->next->prev = l;
						tmp = l->next;
						l->next = r->next;
						r->next = tmp;
						tmp = l->prev;
						l->prev = r->prev;
						r->prev = tmp;
					}
					tmp = l;
					l = r;
					r = tmp;
					if (l->next == r)
					{
						l->Num += l->next->Num;
						l->next->Num = l->Num - l->next->Num;
						l->Num = l->Num - l->next->Num;
					}
					else
					{
						l->Num = l->next->Num - 1;
						r->Num = r->prev->Num + 1;
					}
					l = l->next;
					r = r->prev;

				}
			}

			if (left->Num < r->Num)
			{
				st_table.push(r);
				st_table.push(left);
			}
			if (l->Num < right->Num)
			{
				st_table.push(right);
				st_table.push(l);
			}
		} while (st_table.size() != NULL);
	}
	case 2: {

	}
	case 3: {

	}
	case 4: {

	}
	default: {
		return 0;
	}
	}
}

int main() {
	Str_Num *start_tables = new Str_Num(), *end_tables = NULL, *tmp_tables = NULL;
	end_tables = start_tables;
	std::string name_table_tmp;
	std::string name_file_tmp;
	std::string a;
	std::cin >> a;
	std::cin >> name_file_tmp;
	std::cin >> name_table_tmp;
	create_table(name_file_tmp, name_table_tmp + '0', &start_tables, &end_tables);
	create_table(name_file_tmp, name_table_tmp + '1', &start_tables, &end_tables);
	create_table(name_file_tmp, name_table_tmp + '2', &start_tables, &end_tables);
	delete_table(name_table_tmp + '1', &start_tables, &end_tables);
	sort_table(name_table_tmp + '2', &start_tables, &end_tables, 1);
	return 0;
}