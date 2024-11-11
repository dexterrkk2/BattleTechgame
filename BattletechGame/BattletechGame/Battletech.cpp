#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
#include "Map.h";
#include "Hex.h";
#include "Player.h"
const int sizex = 7;
const int sizey = 12;
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
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid Input: ";
		cin >> temp;
	}
	return temp;
}
void move(Player& player, vector<vector<DrawnHex>> drawnHex, Map map)
{
	vector<DrawnHex> movePositions = player.CanMoveTo(drawnHex[player.row][player.col], drawnHex);
	for (int i = 0; i < movePositions.size(); i++) 
	{
		cout <<"Would you " <<i+1 <<" move to : "<< movePositions[i] << " ";
	}
	cout <<" Or " << movePositions.size() + 1 << "rotate ? ";
	int option = getInt();
	while (option <= 0 ||option > movePositions.size()+1) 
	{
		cout << "Invalid Input: ";
		option = getInt();
	}
	if (option > movePositions.size()) 
	{
		cout << "Would you like to move 1) left or 2) right" << endl;
		int leftOrRight = getInt();
		while (leftOrRight <= 0 || leftOrRight > 2)
		{
			cout << "Invalid Input: ";
			leftOrRight = getInt();
		}
		if (leftOrRight == 1) 
		{
			player.turnLeft();
		}
		else 
		{
			player.turnRight();
		}
	}
	else
	{
		cout << "Moved" << endl;
		drawnHex[player.row][player.col].getHex().eraseMech();
		player.SetPostiiton(movePositions[option - 1].getX(), (movePositions[option - 1].getY()));
		drawnHex[player.row][player.col].getHex().setMech(player.mech);
		map.drawGrid(sizex, sizey, drawnHex);
	}
}
int main() 
{
	Hex hexes[sizex][sizey];
	Mech mech;
	mech.setSpeed(1);
	mech.setImage("Maa");
	Player player(0, sizey-1, Direction::NORTH, mech);
	hexes[player.row][player.col].setMech(mech);
	vector<vector<DrawnHex>> drawnHex;
	for (int i = 0; i < sizex; i++)
	{
		vector<DrawnHex>cols;
		for (int j = 0; j < sizey; j++)
		{
			cols.push_back(*new DrawnHex(hexes[i][j]));
		}
		drawnHex.push_back(cols);
	}
	Map map;
	map.drawGrid(sizex, sizey, drawnHex);
	move(player, drawnHex, map);
	//cout << hexes[2][4].getImage() << endl;
	move(player, drawnHex, map);
	move(player, drawnHex, map);
	move(player, drawnHex, map);
	return 0;
}