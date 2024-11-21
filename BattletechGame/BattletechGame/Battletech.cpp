#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::tolower;
#include "Map.h";
#include "Hex.h";
#include "Player.h"
#include "Mech.h"
#include "FileIO.h"
#include "PlayerInput.h"
#include <cctype>
//sets the size of the grid
const int sizex = 7;
const int sizey = 12;
//takes in a reference to a player mech and sets it to a mech from a file
void selectMech(Mech& mech)
{
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
int main() 
{
	//seeds random
	srand(time(0)); 
	vector<vector<Hex>> hexes;
	Mech blankMech;
	Hex blankHex(blankMech);
	//creates a vector of columns and then adds it to a vector to make rows based on size defined up top
	for (int i = 0; i < sizex; i++)
	{
		//creates new vector for each column
		vector<Hex>cols;
		for (int j = 0; j < sizey; j++)
		{
			//adds a new mech to each hex then adds hex to each column
			cols.push_back(Hex(blankMech));
		}
		//pushes column back to vector of columns. 
		hexes.push_back(cols);
	}
	//gets name for both players
	string playerName = getPlayerName();
	string enemyName = getPlayerName();
	//creates blank mech for both players
	Mech mech;
	Mech enemyMech;
	//creates player objects for both players
	Player player(0, (sizey - 1)/2, Direction::NORTH, mech, playerName);
	Player enemyPlayer((sizex - 1), (sizey - 1)/2, Direction::NORTH, enemyMech, enemyName);
	//takes in players mechs and updates them. Works because player has reference to these mechs
	selectMech(mech);
	selectMech(enemyMech);
	//checks if they picked the same mech and changes first letter to a lower case to distinguish them 
	if (enemyPlayer.getMech().getID() == player.getMech().getID()) 
	{
		cout << "because you picked the same mech setting yours to lower case" << endl;
		string lowerCase = enemyPlayer.getMech().getID();
		lowerCase[0] = tolower(lowerCase[0]);
		enemyMech.setID(lowerCase);
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
	map.SetGrid(sizex, sizey, drawnHex);
	//tries moving fails if player picks a number too large, and it passes the while loop that resets it. 
	try 
	{
		bool turnCheck = false;
		//runs the game
		do
		{
			//runs the first player's turn
			player.playerTurn(drawnHex, map, sizex, sizey, enemyPlayer);
			//checks if enemy died
			turnCheck = player.killedTarget(drawnHex);
			if (!turnCheck) 
			{
				//prints which player won and exits game
				cout<< player.getName()<<" Won" << endl;
				break;
			}
			//runs the second players turn
			enemyPlayer.playerTurn(drawnHex, map, sizex, sizey, player);
			turnCheck = enemyPlayer.killedTarget(drawnHex);
			if (!turnCheck)
			{
				cout << "Player: " << enemyPlayer.getName() << " Won" << endl;
				break;
			}
		//does this as long as both mechs are alive
		} while (turnCheck);
	}
	//catches error
	catch (int x) 
	{
		//prints error message
		cout << "Error: selected an option that doesn't exist" << endl;
	}
	return 0;
}