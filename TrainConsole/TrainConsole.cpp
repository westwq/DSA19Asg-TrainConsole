// TrainConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Dictionary.h"
#include <string>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;

void displayMenu();
void loadData();
list<string> loadFile(string);
void loadStations();
void loadRoutes();
void loadInterchanges();
void loadFares();
void displayLine();
void displayStation();
void searchRoute();
void searchShortestRoute();

const string PATH = "data\\Simple\\";

Dictionary stations;

int main()
{
	loadData();

	while (true)
	{
		displayMenu();
		cout << "Enter option or Q/q to quit: ";
		char option;
		cin >> option;
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//cin.ignore();

		switch (option)
		{
			case '1':
				displayLine(); break;
			case '2':
				displayStation(); break;
			case '3':

			case '4':
				searchRoute(); break;
				break;
			case '6':
				searchShortestRoute(); break;
			case 'Q':
			case 'q':
				cout << "Goodbye!" << endl;
				goto endloop;
			default:
				cout << ">>>>>>>>>>>> Invalid input <<<<<<<<<<<<" << endl;
		};
	}

	endloop:
	system("PAUSE");
	return 0;
}

void loadData()
{
	loadStations();
	loadRoutes();
	loadInterchanges();
	loadFares();
}

void loadStations()
{
	list<string> contents = loadFile(PATH + "Stations.csv");

	for (std::list<string>::iterator it = contents.begin(); it != contents.end(); ++it) {
		string token[2];
		int i = 0;
		stringstream iss(*it);
		while (getline(iss, token[i++], ','));
		stations.add(token[0], token[1]);
	}
}

void loadRoutes()
{
	list<string> contents = loadFile(PATH + "Routes.csv");

	for (std::list<string>::iterator it = contents.begin(); it != contents.end(); ++it) {
		string frm;
		string to;
		string dist;
		stringstream iss(*it);
		stringstream iss2(*(++it));
		getline(iss, frm, ',');
		while (getline(iss, to, ',') && getline(iss2, dist, ','))
		{
			stations.addEdge(frm, to, stoi(dist));
			frm = to;
		}
	}
}

void loadInterchanges()
{
	list<string> contents = loadFile(PATH + "Interchanges.csv");

	for (std::list<string>::iterator it = contents.begin(); it != contents.end(); ++it) {
		string line = *it;
		string token[10];
		int size = 0;
		stringstream iss(line);
		while (getline(iss, token[size++], ',')); //loaded all connecting stations at interchange
		
		//adding edge for interchange
		for (int i = 0; i < --size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				stations.addEdge(token[i], token[j], 0);
			}
		}
	}

	stations.print();
}

void loadFares()
{
	list<string> contents = loadFile(PATH + "Fares.csv");

	for (std::list<string>::iterator it = contents.begin(); it != contents.end(); ++it) {

	}
}

list<string> loadFile(string file)
{
	ifstream infile;
	list<string> lines;
	string line;

	infile.open(file);
	while (getline(infile,line))
	{
		lines.push_back(line);
	}

	infile.close();

	return lines;
}

void displayMenu()
{
	cout << "======== MRT Console ========" << endl;
	cout << "(1) Display all stations of a line" << endl;
	cout << "(2) Display station information" << endl;
	cout << "(3) Add new station" << endl;
	cout << "(4) Search for a route" << endl;
	cout << "(5) Add new line" << endl;
	cout << "(6) Search for shortest route" << endl;
	cout << "(7) Search for 3 feasible routes" << endl;
}

void displayLine()
{

}

void displayStation()
{

}

void searchRoute()
{

}

void searchShortestRoute()
{

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
