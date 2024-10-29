#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
#include "Map.h";
#include "Hex.h";
int rollIDice() 
{
	int diceRoll = (rand() % 6) + 1;
	diceRoll += (rand() % 6) + 1;
	return diceRoll;
}
int main() 
{
	Hex hex[50];
	Map map;
	map.drawGrid(7, 7, hex);
	return 0;
}