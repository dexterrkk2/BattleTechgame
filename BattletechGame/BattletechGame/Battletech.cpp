#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
#include "Map.h";
#include "Hex.h";
#include "Player.h"
#include "Mech.h"
#include "FileIO.h"
#include "PlayerInput.h"
//sets the size of the grid
const int sizex = 10;
const int sizey = 20;
void selectMech(Mech& mech)
{
	//creates enemy Mech
	cout << "Which mech would you like? ";
	int choices = getIntRange(0, 2);
	if (choices == 1)
	{
		mech = mech.makeMech("Urbanmech.txt");
	}
	else
	{
		mech = mech.makeMech("Commando.txt");
	}
}
//searches every hex for a hex with a mech on it


int main() 
{
	//inputOutput();
	srand(time(0));
	//sets the size of the hex 
	vector<vector<Hex>> hexes;
	Mech blankMech;
	Hex blankHex(blankMech);
	//blankMech.setImage("   ");
	//creates a vector of columns and then adds it to a vector to make rows
	for (int i = 0; i < sizex; i++)
	{
		vector<Hex>cols;
		for (int j = 0; j < sizey; j++)
		{
			cols.push_back(Hex(blankMech));
		}
		hexes.push_back(cols);
	}
	///cout << "not here" << endl;
	string playerName = getPlayerName();
	string enemyName = getPlayerName();
	Mech mech;
	Mech enemyMech;
	Player player(0, (sizey - 1)/2, Direction::NORTH, mech, playerName);
	Player enemyPlayer((sizex - 1), (sizey - 1)/2, Direction::NORTH, enemyMech, enemyName);
	/*cout << "Which mech would you like? ";*/
	/*int choices = getIntRange(0, 2);
	if (choices == 1)
	{
		mech = makeMech("Urbanmech.txt");
	}
	else
	{
		mech = makeMech("Commando.txt");
	}*/
	selectMech(mech);
	selectMech(enemyMech);
	while (enemyPlayer.getMech().getID() == player.getMech().getID()) 
	{
		cout << "Mechs cannot be the same" << endl;
		selectMech(enemyPlayer.getMech());
	}
	//sets what hex the player is on and their mech to the tile
	hexes[player.getRow()][player.getCol()].setMech(player.getMech());
	hexes[enemyPlayer.getRow()][enemyPlayer.getCol()].setMech(enemyPlayer.getMech());
	vector<Player> players = { player, enemyPlayer };
	//creates 2d vector
	vector<vector<DrawnHex>> drawnHex;
	//creates a vector of columns and then adds it to a vector to make rows
	for (int i = 0; i < sizex; i++)
	{
		vector<DrawnHex>cols;
		for (int j = 0; j < sizey; j++)
		{
			cols.push_back(DrawnHex(hexes[i][j]));
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
		bool turnCheck = false;
		do
		{
			player.playerTurn(drawnHex, map, sizex, sizey);
			turnCheck = player.killedTarget(drawnHex);
			if (turnCheck == true) 
			{
				cout<< player.getName()<<" Won" << endl;
				break;
			}
			enemyPlayer.playerTurn(drawnHex, map, sizex, sizey);
			turnCheck = enemyPlayer.killedTarget(drawnHex);
			if (turnCheck == true)
			{
				cout << "Player: " << enemyPlayer.getName() << " Won" << endl;
				break;
			}
		} while (!turnCheck);
	}
	//catches error
	catch (int x) 
	{
		//prints error message
		cout << "Error: selected an option that doesn't exist" << endl;
	}
	//cout << hexes[2][4].getID() << endl;
	return 0;
}