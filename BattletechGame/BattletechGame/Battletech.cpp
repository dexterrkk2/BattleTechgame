#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
#include "Map.h";
#include "Hex.h";
#include "Player.h"
#include "Mech.h"
//sets the size of the grid
const int sizex = 7;
const int sizey = 12;
int randomNumber(int max) 
{
	int randomNum = (rand() % max) + 1;
	return randomNum;
}
//rolls 2d6 and gets the value

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

//searches every hex for a hex with a mech on it
vector<DrawnHex> FindTarget(vector<vector<DrawnHex>>& grid, Mech playerMech)
{
	vector<DrawnHex> targets;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			//checks if grid at column i row j has a mech
			if (grid[i][j].getHex().hasmech())
			{
				//checks if mech is the player
				if (grid[i][j].getHex().getMech().getImage() != playerMech.getImage())
				{
					//adds to vector
					targets.push_back(grid[i][j]);
				}
			}
		}
	}
	//returns targets
	return targets;
}
//takes the map gets where the player can move and lets the player choose to move there, or rotate to move somewhere else.
void PlayerTurn(Player& player, vector<vector<DrawnHex>> drawnHex, Map map)
{
	cout << "it's your turn " << player.getName() << endl;
	int amountMoved = 0;
	//allows player to move equal to their speed every turn
	for(int i=0; i< player.getMech().getSpeed(); i++)
	{
		//gets the places the player can move
		vector<DrawnHex> movePositions = player.CanMoveTo(drawnHex[player.getRow()][player.getCol()], drawnHex);
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
			cout << "Would you " << i + 1 << " move to : " << movePositions[i] << " ";
		}
		cout << movePositions.size() + 1 << " rotate ? ";
		//gets input
		int option = getIntRange(0, movePositions.size()+1);
		//throws an exception if the player selects an option not there, and gets past the while loop reseting it.
		if (option > movePositions.size() + 1)
		{
			throw(option);
		}
		//houses the rotate logic
		if (option == movePositions.size() + 1)
		{
			//lets the player choose left or right to turn
			cout << "Would you like to turn 1) left or 2) right" << endl;
			//gets input and makes sure it is in range.
			int leftOrRight = getIntRange(0, 2);
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
		//houses the move logic
		else
		{
			//cout << "Moved" << endl;
			//removes mech off the current tile
			drawnHex[player.getRow()][player.getCol()].getHex().eraseMech();
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
			drawnHex[player.getRow()][player.getCol()].getHex().setMech(player.getMech());
			//updates grid
			map.drawGrid(sizex, sizey, drawnHex);
		}
	}
	//firing code
	//gets enemy mechs
	vector<DrawnHex> targets = FindTarget(drawnHex, player.getMech());
	//asks the player if they would like to attack them.
	for (int i = 0; i < targets.size(); i++)
	{
		cout << "Would you like to attack " << i + 1 << ": " << targets[i].getImage() << " ";
	}
	//gets an input from the screen equal to number of targers
	int fireAt = getIntRange(0, targets.size());
	//fires at selected target
	player.getMech().fireWeapon(targets[fireAt - 1]);
	//returns how many times the player has moved for other logic
	player.setAmountMoved(amountMoved);
	}
int main() 
{
	//sets the size of the hex 
	vector<vector<Hex>> hexes;
	Limb parts[6];
	Mech blankMech;
	Hex blankHex(blankMech);
	//creates a vector of columns and then adds it to a vector to make rows
	for (int i = 0; i < sizex; i++)
	{
		vector<Hex>cols;
		for (int j = 0; j < sizey; j++)
		{
			cols.push_back(*new Hex(blankMech));
		}
		hexes.push_back(cols);
	}
	cout << "not here" << endl;
	Mech mech(parts);
	//creates enemy Mech
	Mech enemyMech(parts);
	//mechs default to -1 so we know if it is active or not
	mech.setSpeed(2);
	enemyMech.setSpeed(2);
	//sets the text that will appear on the hex. as well as mech name
	mech.setImage("Maa");
	enemyMech.setImage("FBI");
	Player player(randomNumber(sizex - 1), randomNumber(sizey - 1), Direction::NORTH, mech, "Robert");
	Player enemyPlayer(randomNumber(sizex - 1), randomNumber(sizey - 1), Direction::NORTH, enemyMech, "Saul");
	//constructs player and sets their direction to north
	//sets what hex the player is on and their mech to the tile
	hexes[player.getRow()][player.getCol()].setMech(mech);
	hexes[enemyPlayer.getRow()][enemyPlayer.getCol()].setMech(enemyMech);
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
	PlayerTurn(enemyPlayer, drawnHex, map);
	PlayerTurn(player, drawnHex, map);
	PlayerTurn(enemyPlayer, drawnHex, map);
	return 0;
}