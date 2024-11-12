#include "Player.h"
#include "Hex.h"
#include <vector>
#include <windows.h>
using std::vector;
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