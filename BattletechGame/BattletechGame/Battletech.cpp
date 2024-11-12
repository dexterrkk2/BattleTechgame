#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
#include "Map.h";
#include "Hex.h";
#include "Player.h"
//sets the size of the grid
const int sizex = 7;
const int sizey = 12;
//rolls 2d6 and gets the value
int rollIDice() 
{
	int diceRoll = (rand() % 6) + 1;
	diceRoll += (rand() % 6) + 1;
	return diceRoll;
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
vector<DrawnHex> FindTarget(vector<vector<DrawnHex>>& grid, Mech playerMech)
{
	vector<DrawnHex> targets;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j].getHex().hasmech())
			{
				if (grid[i][j].getHex().getMech().getImage() != playerMech.getImage())
				{
					targets.push_back(grid[i][j]);
				}
			}
		}
	}
	return targets;
}
//takes the map gets where the player can move and lets the player choose to move there, or rotate to move somewhere else.
void PlayerTurn(Player& player, vector<vector<DrawnHex>> drawnHex, Map map)
{
	int amountMoved =0;
	//gets the places the player can move
	vector<DrawnHex> movePositions = player.CanMoveTo(drawnHex[player.row][player.col], drawnHex);
	//sets the places the player can move to green
	for (int i = 0; i < movePositions.size(); i++)
	{
		drawnHex[movePositions[i].getX()][movePositions[i].getY()].setColor(FOREGROUND_GREEN);
	}
	//prints the hex grid
	map.printHex(sizey, sizex, drawnHex);
	//prints the options of where to move
	for (int i = 0; i < movePositions.size(); i++) 
	{
		cout <<"Would you " <<i+1 <<" move to : "<< movePositions[i] << " ";
	}
	cout << movePositions.size() + 1 << " rotate ? ";
	cout<< " " << movePositions.size() + 2 << " fire ? ";
	//gets input
	int option = getInt();
	//rejects input that is not between 1 and the number of options
	while (option <= 0 ||option > movePositions.size()+2) 
	{
		cout << "Invalid Input: ";
		option = getInt();
	}
	//throws an exception if the player selects an option not there, and gets past the while loop reseting it.
	if (option > movePositions.size() + 2) 
	{
		throw(option);
	}
	//houses the rotate logic
	if (option == movePositions.size()+1 ) 
	{
		//lets the player choose left or right to turn
		cout << "Would you like to turn 1) left or 2) right" << endl;
		//gets input and makes sure it is in range.
		int leftOrRight = getInt();
		while (leftOrRight <= 0 || leftOrRight > 2)
		{
			cout << "Invalid Input: ";
			leftOrRight = getInt();
		}
		//turns left
		if (leftOrRight == 1) 
		{
			player.turnLeft();
		}
		//turns right
		else 
		{
			player.turnRight();
		}
		//changes the hexes beck to blue after player selected option
		for (int i = 0; i < movePositions.size(); i++)
		{
			drawnHex[movePositions[i].getX()][movePositions[i].getY()].setColor(FOREGROUND_BLUE);
		}
	}
	else if (option > movePositions.size() + 1) 
	{
		vector<DrawnHex> targets = FindTarget(drawnHex, player.getMech());
		for (int i = 0; i < targets.size(); i++)
		{
			cout << "Would you like to attack " << i + 1 << ": " << targets[i].getImage() << " ";
		}
		int fireAt = getIntRange(0, targets.size()); 
		player.getMech().fireWeapon(targets[fireAt - 1]);
	}
	//houses the move logic
	else
	{
		//cout << "Moved" << endl;
		//removes mech off the current tile
		drawnHex[player.row][player.col].getHex().eraseMech();
		//changes the hexes beck to blue after player selected option
		for (int i = 0; i < movePositions.size(); i++)
		{
			drawnHex[movePositions[i].getX()][movePositions[i].getY()].setColor(FOREGROUND_BLUE);
		}
		//moves the player to the hex
		player.SetPostiiton(movePositions[option - 1].getX(), (movePositions[option - 1].getY()));
		//gets how many times player has moved
		amountMoved++;
		//sets the mech to the hex tile
		drawnHex[player.row][player.col].getHex().setMech(player.mech);
		//updates grid
		map.drawGrid(sizex, sizey, drawnHex);
	}
	//returns how many times the player has moved for other logic
	player.setAmountMoved(amountMoved);
}

int main() 
{
	//sets the size of the hex 
	Hex hexes[sizex][sizey];
	Mech mech;
	//creates enemy Mech
	Mech enemyMech;
	//mechs default to -1 so we know if it is active or not
	mech.setSpeed(1);
	enemyMech.setSpeed(2);
	//sets the text that will appear on the hex. as well as mech name
	mech.setImage("Maa");
	enemyMech.setImage("FBI");
	//constructs player and sets their direction to north
	Player player(0, sizey-1, Direction::NORTH, mech);
	//sets what hex the player is on and their mech to the tile
	hexes[player.row][player.col].setMech(mech);
	hexes[0][1].setMech(enemyMech);
	hexes[0][2].setMech(enemyMech);
	//creates 2d vector
	vector<vector<DrawnHex>> drawnHex;
	//creates a vector of columns and then adds it to a vector to make rows
	for (int i = 0; i < sizex; i++)
	{
		vector<DrawnHex>cols;
		for (int j = 0; j < sizey; j++)
		{
			cols.push_back(*new DrawnHex(hexes[i][j]));
		}
		drawnHex.push_back(cols);
	}
	//creates the map
	Map map;
	//draws the grid
	map.drawGrid(sizex, sizey, drawnHex);
	//tries moving fails if player picks a number too large, and it passes the while loop. 
	try 
	{
		PlayerTurn(player, drawnHex, map);
	}
	//catches error
	catch (int x) 
	{
		//prints error message
		cout << "Error: selected an option that doesn't exist" << endl;
	}
	//cout << hexes[2][4].getImage() << endl;
	PlayerTurn(player, drawnHex, map);
	PlayerTurn(player, drawnHex, map);
	PlayerTurn(player, drawnHex, map);
	return 0;
}