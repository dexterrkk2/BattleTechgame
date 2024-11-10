#pragma once
#include <vector>
using std::vector;
enum Direction { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };
enum  Direction operator++(enum Direction &d)
{
    if (d == NORTHWEST) 
    {
        d = NORTH;
    }
    else 
    {
        d= (enum Direction)(d + 1);
    }
    return d;
};
enum  Direction operator--(enum Direction& d)
{
    if (d == NORTH)
    {
        d = NORTHWEST;
    }
    else
    {
        d = (enum Direction)(d -1);
    }
    return d;
};
class Player {
public:
    int row, col;
    Direction facing;
    Mech mech;
    Player(int startRow, int startCol, Direction startFacing, Mech mech)
        : row(startRow), col(startCol), facing(startFacing), mech(mech) {}

    // Change facing direction (left or right)
    void turnLeft() 
    {
        --facing;
    }
    void turnRight() 
    {
        ++facing;
    }
    vector<DrawnHex> CanMoveTo(DrawnHex position, vector<vector<DrawnHex>> grid)
    {
        vector<DrawnHex> positions;
        if (facing == Direction::NORTH || facing == Direction::SOUTH) 
        {
            cout << "North"<<endl;
            if (position.getX() < grid.size()-1) 
            {
                positions.push_back(grid[position.getX() + 1][position.getY()]);
            }
            if (position.getX() > 0) 
            {
                positions.push_back(grid[position.getX() - 1][position.getY()]);
            }
        }
        else if (facing == Direction::NORTHEAST || facing == Direction::SOUTHWEST) 
        {
            cout << "NorthEast" << endl;
            if (position.getX() < 0 && position.getY()>0)
            {
                positions.push_back(grid[position.getX() - 1][position.getY() - 1]);
            }
            if (position.getX() > grid.size() - 1 && position.getY()<grid.size()-1)
            {
                positions.push_back(grid[position.getX() + 1][position.getY() + 1]);
            }
        }
        else if (facing == Direction::EAST || facing == Direction::WEST)
        {
            cout << "East" << endl;
            if (position.getY() < grid.size() - 1)
            {
                positions.push_back(grid[position.getX()][position.getY() + 1]);
            }
            if (position.getY() > 0)
            {
                positions.push_back(grid[position.getX()][position.getY() - 1]);
            }
        }
        else if (facing == Direction::SOUTHEAST || facing == Direction::NORTHWEST)
        {
            cout << "NorthWest" << endl;
            if (position.getX() > 0 && position.getY() < grid.size() - 1)
            {
                positions.push_back(grid[position.getX() -1][position.getY() + 1]);
            }
            if (position.getX() < grid.size() - 1 && position.getY() > 0)
            {
                positions.push_back(grid[position.getX() + 1][position.getY() - 1]);
            }
        }
        return positions;
    }
    void SetPostiiton(int row, int col) 
    {
        this->row = row;
        this->col = col;
    }
};