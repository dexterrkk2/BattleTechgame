#include "Player.h"
#include <vector>
#include <windows.h>
using std::vector;

//finds tartgets for the player
vector<DrawnHex> FindTarget(vector<vector<DrawnHex>>& grid, Mech& playerMech)
{
	vector<DrawnHex> targets;
	//goes through each row of the grid
	for (int i = 0; i < grid.size(); i++)
	{
		//goes through each column
		for (int j = 0; j < grid[0].size(); j++)
		{
			//checks if grid at column i row j has a mech
			if (grid[i][j].getHex().hasmech())
			{
				//checks if mech is the player
				if (grid[i][j].getHex().getMech().getID() != playerMech.getID())
				{
					//adds to vector of targets
					targets.push_back(grid[i][j]);
				}
			}
		}
	}
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
			if (!grid[position.getX() + 1][position.getY()].getHex().hasmech()) 
			{
				// returns the hex in front of the player based off where they are facing
				positions.push_back(grid[position.getX() + 1][position.getY()]);
			}
        }
        //checks behind player to see if player is going to go out of bounds
        if (position.getX() > 0)
        {
			if (!grid[position.getX() - 1][position.getY()].getHex().hasmech())
			{
				//returns the hex behind the player based off where they are facing
				positions.push_back(grid[position.getX() - 1][position.getY()]);
			}
        }
    }
    else if (facing == Direction::NORTHEAST || facing == Direction::SOUTHWEST)
    {
        //cout << "NorthEast" << endl;
        //checks in front of player to see if player is going to go out of bounds
        if (position.getX() > 0 && position.getY() > 0)
        {
			if (!grid[position.getX() - 1][position.getY()-1].getHex().hasmech())
			{
				// returns the hex in front of the player based off where they are facing
				positions.push_back(grid[position.getX() - 1][position.getY() - 1]);
			}
        }
        //checks behind player to see if player is going to go out of bounds
        if (position.getX() < grid.size() - 1 && position.getY() < grid[0].size() - 1)
        {
			if (!grid[position.getX() + 1][position.getY()+1].getHex().hasmech())
			{
				// returns the hex in behind the player based off where they are facing
				positions.push_back(grid[position.getX() + 1][position.getY() + 1]);
			}
        }
    }
    else if (facing == Direction::EAST || facing == Direction::WEST)
    {
        //cout << "East" << endl;
        //checks in front of player to see if player is going to go out of bounds
        if (position.getY() < grid[0].size() - 1)
        {
			if (!grid[position.getX()][position.getY()+1].getHex().hasmech())
			{
				// returns the hex in front of the player based off where they are facing
				positions.push_back(grid[position.getX()][position.getY() + 1]);
			}
        }
        //checks behind player to see if player is going to go out of bounds
        if (position.getY() > 0)
        {
			if (!grid[position.getX()][position.getY()-1].getHex().hasmech())
			{
				// returns the hex ibehind player based off where they are facing
				positions.push_back(grid[position.getX()][position.getY() - 1]);
			}
        }
    }
    else if (facing == Direction::SOUTHEAST || facing == Direction::NORTHWEST)
    {
        cout << "NorthWest" << endl;
        //checks in front of player to see if player is going to go out of bounds
        if (position.getX() > 0 && position.getY() < grid[0].size() - 1)
        {
			if (!grid[position.getX() - 1][position.getY() + 1].getHex().hasmech())
			{
				// returns the hex in front of the player based off where they are facing
				positions.push_back(grid[position.getX() - 1][position.getY() + 1]);
			}
        }
        //checks behind player to see if player is going to go out of bounds
        if (position.getX() < grid.size() - 1 && position.getY() > 0)
        {
			if (!grid[position.getX() + 1][position.getY()-1].getHex().hasmech())
			{
				// returns the hex behind player based off where they are facing
				positions.push_back(grid[position.getX() + 1][position.getY() - 1]);
			}
        }
    }
    return positions;
}

//changes the direction the player is facing which changes where they can move
//also resets the color of hexes the player can move to back to blue
void Player::Turn(vector<vector<DrawnHex>>& drawnHex, vector<DrawnHex> movePositions)
{
	cout << "Would you like to turn 1) left or 2) right" << endl;
	//gets input and makes sure it is in range.
	int leftOrRight = getIntRange(0, 2);
	if (leftOrRight == 1)
	{
		turnLeft();
	}
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

//changes player positions to where the player has selected, and changes where the mech is on the grid
void Player::Move(vector<vector<DrawnHex>>& drawnHex, vector<DrawnHex> movePositions, int option)
{
	int previousX = row;
	int previousY = col;
	//moves the player to the hex
	SetPostiiton(movePositions[option - 1].getX(), (movePositions[option - 1].getY()));
	//sets the mech to the hex tile
	drawnHex[row][col].getHex().setMech(mech);
	drawnHex[previousX][previousY].getHex().eraseMech();
}

//takes the player mech and fires it's weapons at the enemy mech.
void Player::fireWeapon(vector<vector<DrawnHex>>& drawnHex, Player& enemy)
{
	vector<DrawnHex> targets = FindTarget(drawnHex, mech);
	//asks the player if they would like to attack the targets returned and picks which one.
	for (int i = 0; i < targets.size(); i++)
	{
		cout << "Would you like to attack " << i + 1 << ": " << targets[i].getID() << " ";
	}
	//gets an input from the screen equal to number of targers
	int fireAt = getIntRange(0, targets.size());
	//fires at selected target
	mech.fireWeapon(*this, enemy);
	//updates map after the enemy has been fired at
	drawnHex[enemy.getRow()][enemy.getCol()].getHex().setMech(enemy.mech);
}

//checks if the player has targets left if they don't returns true, if they do returns false 
bool Player::killedTarget(vector<vector<DrawnHex>>& drawnHex) {
	vector<DrawnHex> targets = FindTarget(drawnHex, mech);
	if (targets.size() == 0)
	{
		return false;
	}
	return true;
}

//takes the map gets where the player can move and lets the player choose to move there, or rotate to move somewhere else.
void Player::playerTurn(vector<vector<DrawnHex>>& drawnHex, Map& map, int sizex, int sizey, Player& enemy)
{
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
		cout << movePositions.size() + 2 << " display mech stats ";

		//gets input
		int option = getIntRange(0, movePositions.size() + 2);

		//throws an exception if the player selects an option not there, and gets past the while loop reseting it.
		if (option > movePositions.size() + 2)
		{
			throw(option);
		}

		//houses the rotate logic
		else if (option == movePositions.size() + 1)
		{
			Turn(drawnHex, movePositions);
		}
		else if (option == movePositions.size() + 2) 
		{
			mech.displayMech();
			i--;
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
	fireWeapon(drawnHex, enemy);
}