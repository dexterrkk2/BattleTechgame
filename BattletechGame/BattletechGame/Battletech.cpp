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
	Hex hex[7][7];
	Mech mech;
	mech.setSpeed(1);
	mech.setImage("Maa");
	hex[3][5].setMech(mech);
	DrawnHex drawnHex[7][7];
	Map map;
	map.drawGrid(7, 7, hex, drawnHex);
	return 0;
}