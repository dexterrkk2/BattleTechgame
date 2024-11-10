#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
#include "Map.h";
#include "Hex.h";
#include "Player.h"
int rollIDice() 
{
	int diceRoll = (rand() % 6) + 1;
	diceRoll += (rand() % 6) + 1;
	return diceRoll;
}
int getInt() 
{
	int temp;
	cin >> temp;
	while (!temp) 
	{
		cin.ignore(INT_MAX);
		cin.clear();
		cout << "Invalid Input: ";
		cin >> temp;
	}
	return temp;
}
void move(Player& player, DrawnHex drawnHex[][7])
{
	vector<DrawnHex> movePositions = player.CanMoveTo(drawnHex[player.row][player.col], drawnHex);
	for (int i = 0; i < movePositions.size(); i++) 
	{
		cout <<"Would you " <<i+1 <<" move to : "<< player.CanMoveTo(drawnHex[player.row][player.col], drawnHex)[i] << " ";
	}
	cout <<" Or " << movePositions.size() + 1 << "rotate ? ";
	int option = getInt();
	while (option > movePositions.size()+1 || option < 0) 
	{
		cout << "Invalid Input: ";
		option = getInt();
	}
	if (option > movePositions.size()) 
	{
		player.turnLeft();
	}
	else
	{
		cout << "Moved" << endl;
		drawnHex[player.row][player.col].getHex().eraseMech();
		player.SetPostiiton(movePositions[option - 1].getX(), (movePositions[option - 1].getY()));
		drawnHex[player.row][player.col].getHex().setMech(player.mech);
	}
}
int main() 
{
	
	Hex hex[7][7];
	Mech mech;
	mech.setSpeed(1);
	mech.setImage("Maa");
	Player player(2, 4, Direction::NORTH, mech);
	hex[player.row][player.col].setMech(mech);
	DrawnHex drawnHex[7][7];
	Map map;
	map.drawGrid(7, 7, hex, drawnHex);
	move(player, drawnHex);
	cout << hex[2][4].getImage() << endl;
	map.drawGrid(7, 7, hex, drawnHex);
	move(player, drawnHex);
	map.drawGrid(7, 7, hex, drawnHex);
	return 0;
}