#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include "myfunct.h"
using namespace std;

struct Node
{
	char letter;
	double frequency;
	Node *left, *right;
};

/**
* funkcja tworzy nowy wierzcholek i dolacza do niego przekazane wierzcholki
* @param tree		nowy wezel
* @param ch			znak wierzcholka
* @param freq		czestotliwosc wystepowania znaku
* @param l			"lewe" dziecko
* @param p			prawe dziecko
*/
Node* newNode(char ch, double freq, Node* l, Node* r)
{
	Node* tree = new Node();

	tree->letter = ch;
	tree->frequency = freq;
	tree->left = l;
	tree->right = r;

	return tree;
}

struct compare
{
	bool operator()(Node* l, Node* r)
	{
		return l->frequency > r->frequency;
	}
};

/**
* funkcja rekurencyjna pokonujaca drzewo w poszukiwaniu lisci i wypisaniu kodow dla kazdego z nich
* @param root		korzen drzewa
* @param code		string zawierajacy droge przebyta po drzewie
* @param outStrm	strumien wyjsciowy
*/
void traverseTree(Node* root, string code, ofstream &outStrm)
{
	if (root == NULL)
		return;

	// znalezlismy lisc, poniewaz wierzcholek nie ma dzieci
	if (!root->left && !root->right)
		outStrm<<root->letter<<": "<< code<<endl;

	traverseTree(root->left, code + "0",outStrm);
	traverseTree(root->right, code + "1",outStrm);
}

/**
* algorytm huffmana tworzacy drzewo
* @param arrSize	rozmair tablic zawierajacych czestotliwosc i znaki
* @param arrChars	tablica ze znakami
* @param arrFreq	tablica z czestotliwoscia wystepowania znakow
* @param root		wskaznik do korzenia drzewa
*/
void Huffman(int arrSize, char* arrChars, double* arrFreq, ofstream &outStrm)
{
	Node* root;
	priority_queue<Node*, vector<Node*>, compare> nodesQueue;
	// dla kazdej litery tworzymy lisc i dodajemy go do kolejki
	for (int i=0;i<arrSize;i++)
		nodesQueue.push(newNode(arrChars[i], arrFreq[i], NULL, NULL));

	//dopoki pozostalo wiecej niz 1 drzewo
	while (nodesQueue.size() != 1)
	{
		//"pobieramy" dwa wierzcholki z najmniejszym prawdopodobienstwem
		Node *left = nodesQueue.top(); nodesQueue.pop();
		Node *right = nodesQueue.top();	nodesQueue.pop();

		//tworzymy nowe drzewo, z prawdopodobienstwem bedacym suma
		//prawdopodobienstwa jego dzieci
		double sum = left->frequency + right->frequency;
		nodesQueue.push(newNode('\0', sum, left, right));
	}
	root = nodesQueue.top();
	traverseTree(root, "", outStrm);

}
void readFile(int arrSize, char* lettArr, double* freqArr, ifstream& inputStrm)
{
	inputStrm.clear();
	inputStrm.seekg(0);
	for (int i = 0;i < arrSize;i++)
	{
		lettArr[i] = getValuesFromFile<char>(inputStrm);
		freqArr[i] = getValuesFromFile <double> (inputStrm);
	}
}
void getNumOfLetters(int &arrSize, ifstream& inputStrm)
{
	string line;
	arrSize = 0;
	while (getline(inputStrm, line))
		++arrSize;
}

int main()
{
	ifstream inputStream;
	ofstream outputStream;
	int numOfLetters=0;
	char* letterArray=nullptr;
	double* frequencyArray=nullptr;

	f_openFile("data.txt", inputStream);
	f_createFile("output.txt", outputStream);
	getNumOfLetters(numOfLetters, inputStream);

	letterArray=fCreateArr<char>(numOfLetters);
	frequencyArray=fCreateArr<double>(numOfLetters);

	readFile(numOfLetters, letterArray, frequencyArray, inputStream);
	Huffman(numOfLetters, letterArray, frequencyArray, outputStream);

	inputStream.close();
	outputStream.close();
	delete[] letterArray;
	delete[] frequencyArray;
	system("pause");
	return 0;
}