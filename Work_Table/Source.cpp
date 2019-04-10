//test
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
	std::string ID;
	std::string surname;
	std::string name;
	std::string second_name;
	std::string year;
	int pasport;
	std::string money;
	Str_Num* next = NULL;
	Str_Num* prev = NULL;
	Str_Num* right = NULL;

};

std::string return_Str_Num(Str_Num *c, int n) {
	switch (n)
	{
	case 1: {
		return c->ID;
	}
	case 2: {
		std::string data;
		data = c->surname;
		std::transform(data.begin(), data.end(), data.begin(), std::tolower);
		return data;
	}
	case 3: {
		return c->year;
	}
	case 4: {
		return c->money;
	}
	}
}

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
			return 1;
		}
		else if (c->Table_name == Table_name)
		{
			if (*start == c)
			{
				*start = (*start)->right;
				c->right = NULL;
				delete (c);
				return 0;
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
					return 0;
				}
				else
				{
					c_tmp->right = c->right;
					c->right = NULL;
					delete (c);
					return 0;
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
	std::string mid_data;
	std::string mid_str;
	int mid_num;
	tmp_start = *start;
	tmp_start_prev = *start;
	if (!(1 <= n && n <= 4))
	{
		return 2;
	}
	while (tmp_start->Table_name != Table_name) {
		tmp_start = tmp_start->right;
		if (tmp_start == *end&&tmp_start->Table_name != Table_name)
		{
			return 1;
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
		//std::string dg= "ID";
		mid_data = return_Str_Num(tmp, n);
		l = left;
		r = right;
		while (l->Num < r->Num) {
			while (return_Str_Num(l, n) < mid_data) l = l->next;
			while (mid_data < return_Str_Num(r, n)) r = r->prev;
			if ((l->Num <= r->Num)) {
				if (l == tmp_start && r == tmp_end) {
					if (l == *start)
					{
						*start = r;
					}
					else
					{
						tmp_start_prev->right = r;
					}
					if (l == *end)
					{
						*end = r;
					}
					tmp_start = r;
					tmp_end = l;
					if (l->next == r)
					{
						l->next = r->next;
						r->prev = l->prev;
						l->prev = r;
						r->next = l;
					}
					else
					{
						r->prev->next = l;
						l->next->prev = r;
						tmp = l->next;
						l->next = r->next;
						r->next = tmp;
						tmp = l->prev;
						l->prev = r->prev;
						r->prev = tmp;
					}
				}
				else if (l == tmp_start) {
					if (l == *start)
					{
						*start = r;
					}
					else
					{
						tmp_start_prev->right = r;
					}

					tmp_start = r;
					r->next->prev = l;
					if (l->next == r)
					{
						l->next = r->next;
						r->prev = l->prev;
						l->prev = r;
						r->next = l;
					}
					else
					{
						r->prev->next = l;
						l->next->prev = r;
						tmp = l->next;
						l->next = r->next;
						r->next = tmp;
						tmp = l->prev;
						l->prev = r->prev;
						r->prev = tmp;
					}
				}
				else if (r == tmp_end) {
					if (l == *end)
					{
						*end = r;
					}
					tmp_end = l;
					l->prev->next = r;
					if (l->next == r)
					{
						l->next = r->next;
						r->prev = l->prev;
						l->prev = r;
						r->next = l;
					}
					else
					{
						r->prev->next = l;
						l->next->prev = r;

						tmp = l->next;
						l->next = r->next;
						r->next = tmp;
						tmp = l->prev;
						l->prev = r->prev;
						r->prev = tmp;
					}
				}
				else
				{
					l->prev->next = r;
					r->next->prev = l;
					if (l->next == r)
					{
						l->next = r->next;
						r->prev = l->prev;
						l->prev = r;
						r->next = l;
					}
					else
					{
						r->prev->next = l;
						l->next->prev = r;
						tmp = l->next;
						l->next = r->next;
						r->next = tmp;
						tmp = l->prev;
						l->prev = r->prev;
						r->prev = tmp;
					}
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
	return 0;
}
int delrec(std::string Table_name, Str_Num **start, Str_Num **end, int n) {
	Str_Num* c_tmp = new Str_Num();
	Str_Num* c_tmp_prev = new Str_Num();
	Str_Num* c = new Str_Num();
	std::string answer;
	c = *start;
	c_tmp = *start;
	while (1)
	{
		if (c->Table_name != Table_name && c == *end)
		{
			return 1;
		}
		else if (c->Table_name == Table_name)
		{
			c_tmp = c;
			while (1)
			{
				if (c_tmp->next == NULL && c_tmp->Num != n)
				{
					return 3;
				}
				else if (c_tmp->Num == n)
				{
					if (c_tmp==*start)
					{
						if (c_tmp->next==NULL)
						{
							while (true)
							{
								std::cout << "This will delete the table: " << c_tmp->Table_name << std::endl << "Print \"Y\" or \"N\"";
								std::cin >> answer;
								while (std::cin.peek() != '\n')
								{
									std::cin >> answer;
								}
								if (answer == "Y")
								{
									system("cls");
									*start = (*start)->right;
									c_tmp->right = NULL;
									delete(c_tmp);
									return 0;
								}
								else if (answer == "N")
								{
									system("cls");
									return 0;
								}
								else
								{
									system("cls");
									std::cout << "Error" << std::endl << "Try typing the answer again" << std::endl;
								}
							}
						}
						else
						{
							c_tmp->next->right = c_tmp->right;
							c_tmp->next->prev = NULL;
							c_tmp->right = NULL;
							*start = c_tmp->next;
							c_tmp->next = NULL;
							delete(c_tmp);
							system("cls");
							return 0;
						}

					}
					else if(c_tmp==*end)
					{
						c_tmp_prev = *start;
						while (c_tmp_prev->next != c_tmp)
						{
							c_tmp_prev = c_tmp_prev->prev;
						}
						c_tmp_prev->right = c_tmp->next;
						//move END

					}
					else if (c_tmp==c)
					{
						//move start_table
					}
					else
					{
						//easy dell
					}
				}
				else
				{
					c_tmp = c_tmp->next;
				}
			}
		}
		else
		{
			c = c->right;
		}
	}
}//
//GG
int main() {
	Str_Num *start_tables = new Str_Num(), *end_tables = NULL, *tmp_tables = NULL;
	end_tables = start_tables;
	std::string name_table="";
	std::string name_file="";
	std::string a="";
	int error_ID;
	std::string answer="";
	std::string namber_field="";
	//std::cin >> a;
	//std::cin >> name_file;
	//std::cin >> name_table;
	//delete_table(name_table + '1', &start_tables, &end_tables);
	//sort_table(name_table + '2', &start_tables, &end_tables, 2);
	while (true)
	{
		std::cin >> a;
		if (a=="create")
		{
			if (std::cin.peek() == '\n')
			{
				system("cls");
				std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
			}
			else
			{
				std::cin >> name_file;
				if (std::cin.peek() == '\n')
				{
					system("cls");
					std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
				}
				else
				{
					std::cin >> name_table;
					tmp_tables = start_tables;
					answer = "";
					while (std::cin.peek() != '\n')
					{
						std::cin >> answer;
					}
					if (answer != "")
					{
						system("cls");
						std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
					}
					else
					{
						while (tmp_tables->Table_name != name_table && tmp_tables != end_tables)
						{
							tmp_tables = tmp_tables->right;
						}
						if (tmp_tables->Table_name != name_table && tmp_tables == end_tables)
						{
							create_table(name_file, name_table, &start_tables, &end_tables);
						}
						else
						{
							while (true)
							{
								std::cout << "The table with the same name exists." << std::endl << "Remove the current table and write a new one?" << std::endl;
								std::cin >> answer;
								while (std::cin.peek() != '\n')
								{
									std::cin >> answer;
								}
								if (answer == "Y")
								{
									delete_table(name_table, &start_tables, &end_tables);
									create_table(name_file, name_table, &start_tables, &end_tables);
									system("cls");
								}
								else if (answer == "N")
								{
									system("cls");
								}
								else
								{
									system("cls");
									std::cout << "Error" << std::endl << "Try typing the answer again" << std::endl;
								}
							}
						}
					}
				}
			}
		}
		else if (a=="delete")
		{
			if (std::cin.peek() == '\n')
			{
				system("cls");
				std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
			}
			else
			{
				std::cin >> name_table;
				answer = "";
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				if (answer != "")
				{
					system("cls");
					std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
				}
				else
				{
					while (tmp_tables->Table_name != name_table && tmp_tables != end_tables)
					{
						tmp_tables = tmp_tables->right;
					}
					if (tmp_tables->Table_name != name_table && tmp_tables == end_tables)
					{
						system("cls");
						std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
					}
					else
					{
						while (true)
						{
							std::cout << "Are you sure you want to delete the table?" << std::endl;
							std::cin >> answer;
							while (std::cin.peek() != '\n')
							{
								std::cin >> answer;
							}
							if (answer == "Y")
							{
								if (delete_table(name_table, &start_tables, &end_tables))
								{
									system("cls");
									std::cout << "A table with that name does not exist";
								}
								else
								{
									system("cls");
								}
							}
							else if (answer == "N")
							{
								system("cls");
							}
							else
							{
								system("cls");
								std::cout << "Error" << std::endl << "Try typing the answer again" << std::endl;
							}
						}
					}
				}
			}
		}
		else if (a == "sort")
		{
			if (std::cin.peek() == '\n')
			{
				system("cls");
				std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
			}
			else
			{
				std::cin >> name_table;
				answer = "";
				if (std::cin.peek() == '\n')
				{
					system("cls");
					std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
				}
				else
				{
					std::cin >> namber_field;
					if (!("1" <= namber_field && namber_field <= "4"))
					{
						system("cls");
						std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
					}
					else
					{
						answer = "";
						while (std::cin.peek() != '\n')
						{
							std::cin >> answer;
						}
						if (answer != "")
						{
							system("cls");
							std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;

						}
						else
						{
							int namber = namber_field[0] - '0';
							if (sort_table(name_table, &start_tables, &end_tables, namber))
							{
								system("cls");
								std::cout << "A table with that name does not exist";
							}
							else
							{
								system("cls");
							}
						}
					}
				}
			}
		}
		else if (a=="dellrec")
		{
			
		}
		else if (a=="search")
		{

		}
		else if(a=="join")
		{

		}
		else if(a=="save")
		{

		}
		else if (a=="write")
		{

		}
		else if (a=="exit")
		{
			break;
		}
		else
		{
			system("cls");
			std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
		}
	}
	return 0;
}