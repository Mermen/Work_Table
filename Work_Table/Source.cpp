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
	std::string pasport;
	std::string money;
	Str_Num* next = nullptr;
	Str_Num* prev = nullptr;
	Str_Num* right = nullptr;

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
		std::string data;
		data = c->name;
		std::transform(data.begin(), data.end(), data.begin(), std::tolower);
		return data;
	}
	case 4: {
		std::string data;
		data = c->second_name;
		std::transform(data.begin(), data.end(), data.begin(), std::tolower);
		return data;
	}
	case 5: {
		return c->year;
	}
	case 6: {
		return c->pasport;
	}
	case 7: {
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
	if ((*start) == nullptr) {
		*start = new Str_Num();
		*start = start_tmp;
		*end = start_tmp;
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
				c->right = nullptr;
				if (c == *end)
				{
					*end = nullptr;
				}
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
					(*end)->right = nullptr;
					delete (c);
					return 0;
				}
				else
				{
					c_tmp->right = c->right;
					c->right = nullptr;
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
	std::string mid_data="";
	int mid_data_num = 0;
	int mid_num=0;
	tmp_start = *start;
	tmp_start_prev = *start;
	/*
	if (!(1 <= n && n <= 4))
	{
		return 2;
	}
	*/
	while (tmp_start->Table_name != Table_name) {
		tmp_start = tmp_start->right;
		if (tmp_start == *end&&tmp_start->Table_name != Table_name)
		{
			return 1;
		}
	}
	if (tmp_start == *start)
	{
		tmp_start_prev = nullptr;
	}
	else
	{
		while (tmp_start_prev->right != tmp_start)
		{
			tmp_start_prev = tmp_start_prev->right;
		}
	}
	tmp_end = tmp_start;
	while (tmp_end->next != nullptr)
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
		{
			mid_num = (left->Num + right->Num) / 2;
			tmp = tmp_start;
			while (tmp->Num != mid_num)
			{
				tmp = tmp->next;
			}
			if (n == 2)
			{
				mid_data = return_Str_Num(tmp, n);
			}
			else
			{
				mid_data_num = std::stoi(return_Str_Num(tmp, n));
			}
			l = left;
			r = right;
			while (l->Num < r->Num)
			{
				if (n==2)
				{
					while (return_Str_Num(l, n) < mid_data) l = l->next;
					while (mid_data < return_Str_Num(r, n)) r = r->prev;
				}
				else
				{
					while (std::stoi(return_Str_Num(l, n)) < mid_data_num) l = l->next;
					while (mid_data_num < std::stoi(return_Str_Num(r, n))) r = r->prev;
				}
				if ((l->Num <= r->Num))
				{

					if (l==r)
					{

					}
					else if (l == tmp_start && r == tmp_end) 
					{
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
					else if (l == tmp_start)
					{
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
					if (left == l && right == r)
					{
						tmp = left;
						left = right;
						right = tmp;
					}
					else if (left == l)
					{
						left = r;
					}
					else if (right == r)
					{
						right = l;
					}
					tmp = l;
					l = r;
					r = tmp;
					if (l==r)
					{

					}
					else if (l->next == r)
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
					if (l->next!=nullptr)
					{
						l = l->next;
					}
					if (r->prev != nullptr) 
					{
						r = r->prev;
					}

				}

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
int del_rec(std::string Table_name, Str_Num **start, Str_Num **end, int n) {
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
				if (c_tmp->next == nullptr && c_tmp->Num != n)
				{
					return 3;
				}
				else if (c_tmp->Num == n)
				{
					if (c_tmp==*start)
					{
						if (c_tmp->next==nullptr)
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
									if (c_tmp == *end)
									{
										*end = (*start)->right;
									}
									c_tmp->right = nullptr;
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
							if (c_tmp == *end)
							{
								*end = c_tmp->next;
							}
							c_tmp->next->right = c_tmp->right;
							c_tmp->next->prev = nullptr;
							c_tmp->right = nullptr;
							*start = c_tmp->next;
							c_tmp->next = nullptr;
							delete(c_tmp);
							c_tmp = *start;
							while (c_tmp != nullptr)
							{
								c_tmp->Num--;
								c_tmp = c_tmp->next;
							}
							system("cls");
							return 0;
						}
					}
					else if(c_tmp==*end)
					{
						c_tmp_prev = *start;
						while (c_tmp_prev->right != c_tmp)
						{
							c_tmp_prev = c_tmp_prev->right;
						}
						//move END
						if (c_tmp->next==nullptr)
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
									c_tmp_prev->right = nullptr;
									*end = c_tmp_prev;
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
							c_tmp_prev->right = c_tmp->next;
							c_tmp = c_tmp->next;
							c_tmp->prev->next = nullptr;
							delete(c_tmp->prev);
							c_tmp->prev = nullptr;
							*end = c_tmp;
							while (c_tmp != nullptr)
							{
								c_tmp->Num--;
								c_tmp = c_tmp->next;
							}
							return 0;
						}

					}
					else if (c_tmp==c)
					{
						c_tmp_prev = *start;
						while (c_tmp_prev->right != c_tmp)
						{
							c_tmp_prev = c_tmp_prev->right;
						}
						if (c_tmp->next == nullptr)
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
									c_tmp_prev->right = c_tmp->right;
									c_tmp->right = nullptr;
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
							c_tmp_prev->right = c_tmp->next;
							c_tmp->next->right = c_tmp->right;
							c_tmp->right = nullptr;
							c_tmp->next->prev = nullptr;
							c_tmp->next = nullptr;
							delete(c_tmp);
							c_tmp = c_tmp_prev->right;
							while (c_tmp != nullptr)
							{
								c_tmp->Num--;
								c_tmp = c_tmp->next;
							}
							return 0;
						}
					}
					else
					{
						c_tmp_prev = c;
						while (c_tmp_prev->right != c_tmp)
						{
							c_tmp_prev = c_tmp_prev->right;
						}
						c_tmp_prev->next = c_tmp->next;
						c_tmp->next = nullptr;
						c_tmp_prev->next->prev = c_tmp->prev;
						c_tmp->prev = nullptr;
						delete(c_tmp);
						c_tmp = c_tmp_prev->next;
						while (c_tmp != nullptr)
						{
							c_tmp->Num--;
							c_tmp = c_tmp->next;
						}
						return 0;
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
int search_rec(std::string Table_name, Str_Num **start, Str_Num **end, std::string letter, int n)
{
	Str_Num* c = new Str_Num();
	c = *start;
	if (!(1 <= n && n <= 7))
	{
		return 2;
	}
	int flag = 0;
	std::string answer;
	while (1)
	{
		if (c->Table_name != Table_name && c == *end)
		{
			return 1;
		}
		else if (c->Table_name == Table_name)
		{
			while (true)
			{
				if (c == nullptr)
				{
					if (flag)
					{
						std::cout << "\n";
						std::cout << "Enter any message";
						std::cout << "\n";
						std::cin >> answer;
						while (std::cin.peek()!='\n')
						{
							std::cin >> answer;
						}
						return 0;
					}
					else
					{
						return 3;
					}
				}
				else if (return_Str_Num(c, n) == letter)
				{
					for (int i = 1; i < 8; i++)
					{
						std::cout << return_Str_Num(c, i) << " ";
					}
					std::cout << "\n";
					flag = 1;
					c = c->next;
				}
				else
				{
					c = c->next;
				}
			}

		}
		else
		{
			c = c->right;
		}
	}
}
int join_table(std::string Table_name_1, std::string Table_name_2, std::string Table_name_new, Str_Num **start, Str_Num **end)//name1!=name2
{
	Str_Num* table_1 = new Str_Num();
	Str_Num* table_2 = new Str_Num();
	Str_Num* table_tmp = new Str_Num();
	Str_Num* table_tmp_tmp = new Str_Num();
	table_1 = *start;
	table_2 = *start;
	table_tmp = *start;
	table_tmp_tmp = *start;
	std::string answer="";
	while (true)
	{
		if(table_1->Table_name != Table_name_1 && table_1 == *end)
		{
			return 1;
		}
		else if (table_1->Table_name == Table_name_1)
		{
			while (true)
			{
				if (table_2->Table_name != Table_name_2 && table_2 == *end)
				{
					return 1;
				}
				else if (table_2->Table_name == Table_name_2)
				{
					table_tmp = *start;
					while (true)
					{
						
						if (table_tmp->Table_name != Table_name_new && table_tmp == *end)
						{
							table_tmp = *start;
							table_tmp_tmp = *start;
							if (table_tmp->Table_name == Table_name_1)
							{
								*start = (*start)->right;
								table_1->right = nullptr;
								if (table_1 == *end)
								{
									*end = *start;
								}
							}
							else
							{
								while (table_tmp->right->Table_name != Table_name_1)
								{
									table_tmp = table_tmp->right;
								}
								if (table_1 == *end)
								{
									*end = table_tmp;
								}
								table_tmp->right = table_tmp->right->right;
								table_1->right = nullptr;
							}
							table_tmp_tmp = *start;
							if (table_tmp_tmp->Table_name == Table_name_2)
							{
								*start = (*start)->right;
								table_2->right = nullptr;
								if (table_2 == *end)
								{
									*end = *start;
								}
							}
							else
							{
								while (table_tmp_tmp->right->Table_name != Table_name_2)
								{
									table_tmp_tmp = table_tmp_tmp->right;
								}
								if (table_2 == *end)
								{
									*end = table_tmp_tmp;
								}
								table_tmp_tmp->right = table_tmp_tmp->right->right;
								table_2->right = nullptr;
							}
							if ((*start)==nullptr)
							{
								*start = table_1;
								*end = table_1;
								table_tmp = table_1;
								while (table_tmp->next != nullptr)
								{
									table_tmp->Table_name = Table_name_new;
									table_tmp = table_tmp->next;
								}
								table_2->prev = table_tmp;
								table_tmp->next = table_2;
								table_tmp = table_tmp->next;
								while (table_tmp != nullptr)
								{
									table_tmp->Table_name = Table_name_new;
									table_tmp->Num = table_tmp->prev->Num + 1;
									table_tmp = table_tmp->next;
								}
								system("cls");
								return 0;
							}
							else
							{
								(*end)->right = table_1;
								*end = (*end)->right;
								table_tmp = table_1;
								while (table_tmp->next != nullptr)
								{
									table_tmp->Table_name = Table_name_new;
									table_tmp = table_tmp->next;
								}
								table_2->prev = table_tmp;
								table_tmp->next = table_2;
								while (table_tmp->next != nullptr)
								{
									table_tmp->Table_name = Table_name_new;
									table_tmp->Num = table_tmp->prev->Num + 1;
									table_tmp = table_tmp->next;
								}
								system("cls");
								return 0;
							}

						}
						else if (table_tmp->Table_name == Table_name_new)
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
									if (table_tmp==table_1)
									{
										if ((*start)->Table_name== Table_name_2)
										{
											*start = (*start)->right;
											table_2->right = nullptr;
											while (table_tmp->next!=nullptr)
											{
												table_tmp = table_tmp->next;
											}
											table_tmp->next = table_2;
											table_2->prev = table_tmp;
											table_tmp = table_tmp->next;
											while (table_tmp != nullptr)
											{
												table_tmp->Num = table_tmp->prev->Num + 1;
												table_tmp->Table_name = table_tmp->prev->Table_name;
												table_tmp = table_tmp->next;
											}
										}
										else
										{
											while (table_tmp_tmp->right->Table_name!= Table_name_2)
											{
												table_tmp_tmp = table_tmp_tmp->right;
											}
											if (table_2==*end)
											{
												*end = table_tmp_tmp;
											}
											table_tmp_tmp->right = table_tmp_tmp->right->right;
											table_2->right = nullptr;
											while (table_tmp->next != nullptr)
											{
												table_tmp = table_tmp->next;
											}
											table_tmp->next = table_2;
											table_2->prev = table_tmp;
											table_tmp = table_tmp->next;
											while (table_tmp != nullptr)
											{
												table_tmp->Num = table_tmp->prev->Num + 1;
												table_tmp->Table_name = table_tmp->prev->Table_name;
												table_tmp = table_tmp->next;
											}
										}
									}
									else
									{
										if ((*start)->Table_name == Table_name_1)
										{
											*start = (*start)->right;
											table_1->right = nullptr;
											while (table_tmp->next != nullptr)
											{
												table_tmp = table_tmp->next;
											}
											table_tmp->next = table_1;
											table_1->prev = table_tmp;
											table_tmp = table_tmp->next;
											while (table_tmp != nullptr)
											{
												table_tmp->Num = table_tmp->prev->Num + 1;
												table_tmp->Table_name = table_tmp->prev->Table_name;
												table_tmp = table_tmp->next;
											}
										}
										else
										{
											while (table_tmp_tmp->right->Table_name != Table_name_1)
											{
												table_tmp_tmp = table_tmp_tmp->right;
											}
											if (table_1 == *end)
											{
												*end = table_tmp_tmp;
											}
											table_tmp_tmp->right = table_tmp_tmp->right->right;
											table_1->right = nullptr;
											while (table_tmp->next != nullptr)
											{
												table_tmp = table_tmp->next;
											}
											table_tmp->next = table_1;
											table_1->prev = table_tmp;
											table_tmp = table_tmp->next;
											while (table_tmp != nullptr)
											{
												table_tmp->Num = table_tmp->prev->Num + 1;
												table_tmp->Table_name = table_tmp->prev->Table_name;
												table_tmp = table_tmp->next;
											}
										}
									}
									system("cls");
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
							table_tmp = table_tmp->right;
						}
					}
				}
				else
				{
					table_2 = table_2->right;
				}
			}
		}
		else
		{
			table_1 = table_1->right;
		}

	}
}
int save_table(std::string file_name, std::string Table_name, Str_Num** start, Str_Num** end)
{
	file_name.push_back('.');
	file_name.push_back('t');
	file_name.push_back('x');
	file_name.push_back('t');
	const char* name = file_name.c_str();
	std::ofstream fout(name);
	Str_Num* c = new Str_Num();
	c = *start;

	while (1)
	{
		if (c->Table_name != Table_name && c == *end)
		{
			return 1;
		}
		 else if (c->Table_name == Table_name)
		{
			std::ofstream fout(name);
			while (c != nullptr)
			{
				fout << c->Num<<" ";
				for (int i = 1; i <= 7; i++)
				{
					fout << return_Str_Num(c, i);
					if (i!=7)
					{
						fout << " ";
					} 
				}
				if (c->next!=nullptr)
				{
					fout << std::endl;
				}
				c = c->next;
			}
			fout.close();
			return 0;
		}
		 else
		{
			c = c->right;
		}
	}
}
int write_in_table(std::string Table_name, Str_Num** start, Str_Num** end, int num, int n_field)
{
	Str_Num* c = new Str_Num();
	c = *start;
	std::string messаge_p;
	std::string answer = "";
	while (1)
	{
		if (c->Table_name != Table_name && c == *end)
		{
			return 1;
		}
		else if (c->Table_name == Table_name)
		{
			while (true)
			{

				if (c->Num != num && c->next == nullptr)
				{
					return 2;
				}
				else if (c->Num == num)
				{
					if (n_field == 1 || n_field == 5 || n_field == 6 || n_field == 7)
					{
						system("cls");
						std::cout << "Can enter only a number" << std::endl;
						std::cin >> messаge_p;
						answer = "";
						while (std::cin.peek() != '\n')
						{
							std::cin >> answer;
						}
						if (answer != "")
						{
							return 3;
						}
						else
						{
							for (int i = 0; i < messаge_p.size(); i++)
							{
								if (!('0' <= messаge_p[i] && messаge_p[i] <= '9'))
								{
									return 3;
								}
							}
							switch (n_field)
							{
							case 1: {
								c->ID = messаge_p;
								return 0;
							}
							case 5: {
								c->year = messаge_p;
								return 0;
							}
							case 6: {
								c->pasport = messаge_p;
								return 0;
							}
							case 7: {
								c->money = messаge_p;
								return 0;
							}
							}
						}
					}
					else
					{
						system("cls");
						std::cout << "Can enter only a word" << std::endl;
						std::cin >> messаge_p;
						answer = "";
						while (std::cin.peek() != '\n')
						{
							std::cin >> answer;
						}
						if (answer != "")
						{
							return 3;
						}
						else
						{
							for (int i = 0; i < messаge_p.size(); i++)
							{
								if ('0' <= messаge_p[i] && messаge_p[i] <= '9')
								{
									return 3;
								}
							}
							switch (n_field)
							{
							case 2: {
								c->surname = messаge_p;
								return 0;
							}
							case 3: {
								c->name = messаge_p;
								return 0;
							}
							case 4: {
								c->second_name = messаge_p;
								return 0;
							}
							}
						}
					}
				}
				else
				{
					c = c->next;
				}
			}

		}
		else
		{
			c = c->right;
		}
	}
	return 0;
}
//GG
int main() {
	Str_Num *start_tables = nullptr, *end_tables = nullptr, *tmp_tables = nullptr;
	end_tables = start_tables;
	std::string name_table = "";
	std::string name_table_1 = "";
	std::string name_table_2 = "";
	std::string name_table_new = "";
	std::string name_file = "";
	std::string a = "";
	std::string answer = "";
	std::string number_field = "";
	int number_rec = 0;
	int ERROR = 0;
	std::string letter="";
	while (true)
	{
		std::cin >> a;
		if (a == "create")
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
						if (tmp_tables == nullptr)
						{
							create_table(name_file, name_table, &start_tables, &end_tables);
							system("cls");
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
								system("cls");
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
										break;
									}
									else if (answer == "N")
									{
										system("cls");
										break;
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
		}
		else if (a == "delete")
		{
			if (start_tables == nullptr)
			{
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				system("cls");
				std::cout << "First create at least one table" << std::endl;
			}
			else {

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
										break;
									}
									else
									{
										system("cls");
										break;
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
		}
		else if (a == "sort")
		{
			if (start_tables == nullptr)
			{
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				system("cls");
				std::cout << "First create at least one table" << std::endl;
			}
			else {
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
						std::cin >> number_field;
						if (!("1" <= number_field && number_field <= "4")||number_field.size()>1)
						{
							while (std::cin.peek() != '\n')
							{
								std::cin >> answer;
							}
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
								int number = number_field[0] - '0';
								switch (number)
								{
								case 3: {
									number = 5;
									break;
								}
								case 4: {
									number = 7;
									break;
								}
								default: {
									break;
								}
								}
								if (sort_table(name_table, &start_tables, &end_tables, number))
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
		}
		else if (a == "delrec")
		{
			if (start_tables == nullptr)
			{
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				system("cls");
				std::cout << "First create at least one table" << std::endl;
			}
			else 
			{
				if (std::cin.peek() == '\n')
				{
					system("cls");
					std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
				}
				else
				{
					std::cin >> name_table;
					if (std::cin.peek() == '\n')
					{
						system("cls");
						std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
					}
					else
					{
						std::cin >> number_rec;
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
							if (ERROR = del_rec(name_table, &start_tables, &end_tables, number_rec))
							{
								switch (ERROR)
								{
								case 1: {
									system("cls");
									std::cout << "A table with that name does not exist" << std::endl;
								}
								case 3: {
									system("cls");
									std::cout << "A record with that number does not exist" << std::endl;
								}
								}
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
		else if (a == "search")
		{
			if (start_tables == nullptr)
			{
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				system("cls");
				std::cout << "First create at least one table" << std::endl;
			}
			else
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
						std::cin >> number_field;
						if (!("1" <= number_field && number_field <= "7") || number_field.size() > 1)
						{
							while (std::cin.peek() != '\n')
							{
								std::cin >> answer;
							}
							system("cls");
							std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
						}
						else
						{
							if (std::cin.peek() == '\n')
							{
								system("cls");
								std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
							}
							else
							{
								std::cin >> letter;
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
									int number = number_field[0] - '0';
									if (ERROR = search_rec(name_table, &start_tables, &end_tables, letter, number))
									{
										switch (ERROR)
										{
										case 1: {
											system("cls");
											std::cout << "A table with that name does not exist" << std::endl;
										}
										case 3: {
											system("cls");
											std::cout << "A record with that letter does not exist" << std::endl;
										}
										}
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

			}
		}
		else if (a == "join")
		{
			if (start_tables == nullptr)
			{
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				system("cls");
				std::cout << "First create at least one table" << std::endl;
			}
			else
			{
				if (std::cin.peek() == '\n')
				{
					system("cls");
					std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
				}
				else
				{
					std::cin >> name_table_1;
					answer = "";
					if (std::cin.peek() == '\n')
					{
						system("cls");
						std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
					}
					else
					{
						std::cin >> name_table_2;
						answer = "";
						if (std::cin.peek() == '\n')
						{
							system("cls");
							std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
						}
						else
						{
							std::cin >> name_table_new;
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
								if (name_table_1 == name_table_2)
								{
									system("cls");
									std::cout << "Error" << std::endl << "Only different tables can be combined" << std::endl;
								}
								else
								{
									if (join_table(name_table_1, name_table_2, name_table_new, &start_tables, &end_tables))
									{
										system("cls");
										std::cout << "A table with that name does not exist";
										
									}
									else
									{
										system("cls");
										
									}
									system("cls");
								}
							}
						}
					}
				}
			}
		}
		else if (a == "save")
		{
			if (start_tables == nullptr)
			{
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				system("cls");
				std::cout << "First create at least one table" << std::endl;
			}
			else
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
						std::cin >> name_file;
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
							if (save_table(name_file,name_table,&start_tables,&end_tables))
							{
								system("cls");
								std::cout << "A table with that name does not exist" << std::endl;
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
		else if (a == "write")
		{
			if (start_tables == nullptr)
			{
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				system("cls");
				std::cout << "First create at least one table" << std::endl;
			}
			else
			{
				if (std::cin.peek() == '\n')
				{
					system("cls");
					std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
				}
				else
				{
					std::cin >> name_table;
					if (std::cin.peek() == '\n')
					{
						system("cls");
						std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
					}
					else
					{
						std::cin >> number_rec;
						if (std::cin.peek()!=' ')
						{
							while (std::cin.peek() != '\n')
							{
								std::cin >> answer;
							}
							system("cls");
							std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
						}
						if (std::cin.peek() == '\n')
						{
							system("cls");
							std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
						}
						else
						{
							std::cin >> number_field;
							if (!("1" <= number_field && number_field <= "7") || number_field.size() > 1)
							{
								while (std::cin.peek() != '\n')
								{
									std::cin >> answer;
								}
								system("cls");
								std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
							}
							else
							{
								if (std::cin.peek() != '\n')
								{
									while (std::cin.peek() != '\n')
									{
										std::cin >> answer;
									}
									system("cls");
									std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
								}
								else
								{
									if (ERROR=write_in_table(name_table,&start_tables,&end_tables,number_rec,number_field[0]-'0'))
									{
										switch (ERROR)
										{
										case 1:
										{
											system("cls");
											std::cout << "A table with that name does not exist" << std::endl;
										}
										case 2:
										{
											system("cls");
											std::cout << "A record with that name does not exist" << std::endl;
										}
										case 3:
										{
											system("cls");
											std::cout << "Invalid new entry format" << std::endl;
										}
										}
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
			}
		}
		else if (a == "show")
		{
			if (start_tables == nullptr)
			{
				while (std::cin.peek() != '\n')
				{
					std::cin >> answer;
				}
				system("cls");
				std::cout << "First create at least one table" << std::endl;
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
					std::cout << std::endl;
					tmp_tables = start_tables;
					while (tmp_tables != nullptr)
					{
						std::cout << tmp_tables->Table_name;
						tmp_tables = tmp_tables->right;
						std::cout << std::endl;
					}
				}
			}
		}
		else if (a == "exit")
		{
			break;
		}
		else
		{
			while (std::cin.peek() != '\n')
			{
				std::cin >> answer;
			}
			system("cls");
			std::cout << "Error" << std::endl << "Try typing the command again" << std::endl;
		}
	}
	return 0;
}