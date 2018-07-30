#pragma once

#include <iostream>
#include <fstream>	
#include <string>

using namespace std;

int* fcreatetable(int n);
int** fCreateTwoDimTable(int n);
bool checkIfTxt(string &name);
void f_createFile(string name, ofstream &file);
void f_openFile(string name, ifstream  &file);

template <class type>type * fCreateArr(int rows)
{
	type *t = nullptr;

	try {
		t = new type[rows];
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na tablice";
		exit(0);
	}
	return t;
}
template <class type>type **createTwoDimArray(int rows, int columns)
{
	type** t = nullptr;
	try {
		t = new type* [rows];
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na utworzenie tablicy";
		getchar();
		exit(0);
	}
	for (int i = 0; i < rows; i++)
	{
		try {
			t[i] = new type[columns];
		}
		catch (bad_alloc)
		{
			cout << "Brak miejsca na utworzenie tablicy";
			getchar();
			exit(0);
		}
	}
	return t;
}

template <class type> type getValuesFromFile(ifstream & inputStrm)
{
	type value;
	if (inputStrm.good())
	{
		inputStrm >> value;
		return value;
	}
	else
	{
		cout << "Nie mozna odczytac wartosci";
		system("pause");
		exit(1);
	}
}