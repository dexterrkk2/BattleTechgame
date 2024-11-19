#include "Player.h"
#include <vector>
#include <windows.h>
using std::vector;
vector<DrawnHex> FindTarget(vector<vector<DrawnHex>>& grid, Mech& playerMech)
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
				if (grid[i][j].getHex().getMech().getID() != playerMech.getID())
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
//returns a vector of positions the player can move
vector<DrawnHex> Player::CanMoveTo(DrawnHex position, vector<vector<DrawnHex>> grid)
{
    //creates vector of positions
    vector<DrawnHex> positions;
    //checks which direction player is and returns the directions based on that 
    if (facing == Direction::NORTH || facing == Direction::SOUTH)
    {
        //cout << "North" << endl;
        //checks in front of player to see if player is going to go out of bounds
        if (position.getX() < grid.size() - 1)
        {
            // returns the hex in front of the player based off where they are facing
            positions.push_back(grid[position.getX() + 1][position.getY()]);
        }
        //checks behind player to see if player is going to go out of bounds
        if (position.getX() > 0)
        {
            //returns the hex behind the player based off where they are facing
            positions.push_back(grid[position.getX() - 1][position.getY()]);
        }
    }
    else if (facing == Direction::NORTHEAST || facing == Direction::SOUTHWEST)
    {
        //cout << "NorthEast" << endl;
        //checks in front of player to see if player is going to go out of bounds
        if (position.getX() < 0 && position.getY() > 0)
        {
            // returns the hex in front of the player based off where they are facing
            positions.push_back(grid[position.getX() - 1][position.getY() - 1]);
        }
        //checks behind player to see if player is going to go out of bounds
        if (position.getX() > grid.size() - 1 && position.getY() < grid[0].size() - 1)
        {
            // returns the hex in behind the player based off where they are facing
            positions.push_back(grid[position.getX() + 1][position.getY() + 1]);
        }
    }
    else if (facing == Direction::EAST || facing == Direction::WEST)
    {
        //cout << "East" << endl;
        //checks in front of player to see if player is going to go out of bounds
        if (position.getY() < grid[0].size() - 1)
        {
            // returns the hex in front of the player based off where they are facing
            positions.push_back(grid[position.getX()][position.getY() + 1]);
        }
        //checks behind player to see if player is going to go out of bounds
        if (position.getY() > 0)
        {
            // returns the hex in behind player based off where they are facing
            positions.push_back(grid[position.getX()][position.getY() - 1]);
        }
    }
    else if (facing == Direction::SOUTHEAST || facing == Direction::NORTHWEST)
    {
        //cout << "NorthWest" << endl;
        //checks in front of player to see if player is going to go out of bounds
        if (position.getX() > 0 && position.getY() < grid[0].size() - 1)
        {
            // returns the hex in front of the player based off where they are facing
            positions.push_back(grid[position.getX() - 1][position.getY() + 1]);
        }
        //checks behind player to see if player is going to go out of bounds
        if (position.getX() < grid.size() - 1 && position.getY() > 0)
        {
            // returns the hex in behind player based off where they are facing
            positions.push_back(grid[position.getX() + 1][position.getY() - 1]);
        }
    }
    //return positions the player can move
    return positions;
}
void Player::Turn(vector<vector<DrawnHex>>& drawnHex, vector<DrawnHex> movePositions)
{
	//lets the player choose left or right to turn
	cout << "Would you like to turn 1) left or 2) right" << endl;
	//gets input and makes sure it is in range.
	int leftOrRight = getIntRange(0, 2);
	//turns left
	if (leftOrRight == 1)
	{
		turnLeft();
	}
	//turns right
	else
	{
		turnRight();
	}
	//changes the hexes beck to blue after player selected option
	for (int i = 0; i < movePositions.size(); i++)
	{
		drawnHex[movePositions[i].getX()][movePositions[i].getY()].setColor(FOREGROUND_BLUE);
	}
}
void Player::Move(vector<vector<DrawnHex>>& drawnHex, vector<DrawnHex> movePositions, int option)
{
	//cout << "Moved" << endl;
			//removes mech off the current tile
	int previousX = row;
	int previousY = col;
	//changes the hexes beck to blue after player selected option
	//moves the player to the hex
	SetPostiiton(movePositions[option - 1].getX(), (movePositions[option - 1].getY()));
	//sets the mech to the hex tile
	drawnHex[row][col].getHex().setMech(mech);
	drawnHex[previousX][previousY].getHex().eraseMech();
	//updates grid
}
void Player::fireWeapon(vector<vector<DrawnHex>>& drawnHex)
{
	vector<DrawnHex> targets = FindTarget(drawnHex, mech);
	//asks the player if they would like to attack them.
	for (int i = 0; i < targets.size(); i++)
	{
		cout << "Would you like to attack " << i + 1 << ": " << targets[i].getID() << " ";
	}
	//gets an input from the screen equal to number of targers
	int fireAt = getIntRange(0, targets.size());
	//fires at selected target
	mech.fireWeapon(drawnHex[targets[fireAt - 1].getX()][targets[fireAt - 1].getY()]);
	if (drawnHex[targets[fireAt - 1].getX()][targets[fireAt - 1].getY()].getHex().getMech().getWalk() == -1)
	{
		drawnHex[targets[fireAt - 1].getX()][targets[fireAt - 1].getY()].getHex().eraseMech();
	}

}
bool Player::killedTarget(vector<vector<DrawnHex>>& drawnHex) {
	vector<DrawnHex> targets = FindTarget(drawnHex, mech);
	if (targets.size() == 0)
	{
		return true;
	}
	//returns how many times the player has moved for other logic

	return false;
}
//takes the map gets where the player can move and lets the player choose to move there, or rotate to move somewhere else.
void Player::playerTurn(vector<vector<DrawnHex>>& drawnHex, Map& map, int sizex, int sizey)
{
	//cout << player.getMech().getID() << endl;
	//cout << "Your Walkspeed is " << player.getMech().walk() << endl;
	cout << "it's your turn " << name << endl;
	int amountMoved = 0;
	//allows player to move equal to their speed every turn
	for (int i = 0; i < mech.getWalk(); i++)
	{
		//gets the places the player can move
		vector<DrawnHex> movePositions = CanMoveTo(drawnHex[row][col], drawnHex);
		//sets the places the player can move to green
		for (int i = 0; i < movePositions.size(); i++)
		{
			drawnHex[movePositions[i].getX()][movePositions[i].getY()].setColor(FOREGROUND_GREEN);
		}
		//prints the hex grid
		map.printHex(sizex, sizey, drawnHex);
		//changes them back to blue after it's printed
		for (int i = 0; i < movePositions.size(); i++)
		{
			drawnHex[movePositions[i].getX()][movePositions[i].getY()].setColor(FOREGROUND_BLUE);
		}
		//prints the options of where to move
		for (int i = 0; i < movePositions.size(); i++)
		{
			cout << "Would you " << i + 1 << " move to : " << movePositions[i] << " ";
		}
		cout << movePositions.size() + 1 << " rotate ? ";
		//gets input
		int option = getIntRange(0, movePositions.size() + 1);
		//throws an exception if the player selects an option not there, and gets past the while loop reseting it.
		if (option > movePositions.size() + 1)
		{
			throw(option);
		}
		//houses the rotate logic
		if (option == movePositions.size() + 1)
		{
			Turn(drawnHex, movePositions);
		}
		//houses the move logic
		else
		{
			Move(drawnHex, movePositions, option);
			amountMoved++;
		}
	}
	//firing code
	setAmountMoved(amountMoved);
	fireWeapon(drawnHex);
	//gets enemy mechs
}