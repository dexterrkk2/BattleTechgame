#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
//gets a string from the player
inline string getPlayerName()
{
	string temp;
	cout << "Enter your name: ";
	cin >> temp;
	return temp;
}
//returns a random number from 1 to max
inline int randomNumber(int max)
{
	int randomNum = (rand() % max) + 1;
	return randomNum;
}
//takes in input and makes sure it is an int
inline int getInt()
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
//gets an int from the user based off the min and max
inline int getIntRange(int min, int max)
{
	int option = getInt();
	//rejects input that is not between min and max
	while (option <= min || option > max)
	{
		cout << "Invalid Input: ";
		option = getInt();
	}
	return option;
}