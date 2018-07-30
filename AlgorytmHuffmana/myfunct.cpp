#include "myfunct.h"


int* fcreatetable(int n)
{
	int *t = nullptr;

	try {
		t = new int[n];
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na tablice";
		exit(0);
	}
	return t;
}

int **createTwoDimArray(int rows, int columns) 
{
	int **t = nullptr;
	try {
		t = new int *[rows];
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
			t[i] = new int[columns];
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
int** fCreateTwoDimTable(int n)
{
	int **t = nullptr;

	try {
		t = new int*[n];
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na tablice";
		exit(0);
	}
	return t;
}

bool checkIfTxt(string &name)
{


	if (name.substr(name.find_last_of(".") + 1) == "txt")
		return true;
	else
	{
		cout << "zle rozszerzenie pliku";
		return false;
	}
}

void f_createFile(string name, ofstream &file)
{
	if (checkIfTxt(name) == false)
	{
		exit(0);
	}

	file.open(name);
	if (!file)
	{
		cout << "Nie mozna utworzyc pliku";
		exit(0);

	}

}

void f_openFile(string name, ifstream  &file)
{
	if (checkIfTxt(name) == false)
	{
		exit(0);
	}
	if (!file)
	{
		cout << "Nie mozna otworzyc pliku";
		exit(0);
		getchar();
	}
	file.open(name);
}
