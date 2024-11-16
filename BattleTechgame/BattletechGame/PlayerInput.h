#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
string getPlayerName()
{
	string temp;
	cout << "Enter your name: ";
	cin >> temp;
	return temp;
}
int randomNumber(int max)
{
	int randomNum = (rand() % max) + 1;
	return randomNum;
}
//takes in input and makes sure it is an int
int getInt()
{
	int temp;
	cin >> temp;
	while (!temp)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid Input: ";
		cin >> temp;
	}
	return temp;
}
int getIntRange(int min, int max)
{
	int option = getInt();
	//rejects input that is not between 1 and the number of options
	while (option <= min || option > max)
	{
		cout << "Invalid Input: ";
		option = getInt();
	}
	return option;
}