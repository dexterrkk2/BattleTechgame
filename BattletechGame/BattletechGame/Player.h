#pragma once
#include <vector>
#include "Map.h"
#include "PlayerInput.h";
#include "Mech.h"
using std::vector;
//defines directions as enums, 0-7
enum Direction { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };
//overloads ++ operator to work for directions
inline enum  Direction operator++(enum Direction& d)
{
    //lopps back to beginning of enums
    if (d == NORTHWEST)
    {
        d = NORTH;
    }
    //cycles through directions
    else
    {
        d = (enum Direction)(d + 1);
    }
    return d;
};
//overloads -- operator to work for directions
inline enum  Direction operator--(enum Direction& d)
{
    //lopps back to end of enums
    if (d == NORTH)
    {
        d = NORTHWEST;
    }
    //cycles through directions
    else
    {
        d = (enum Direction)(d - 1);
    }
    return d;
};
class Player 
{
private:
    int row, col;
    Direction facing;
    Mech& mech;
    string name;
public:
    Player(int startRow, int startCol, Direction startFacing, Mech& mech, string name)
        : row(startRow), col(startCol), facing(startFacing), mech(mech), name(name) {}
    // Change facing direction (left or right)
    void turnLeft() 
    {
        //directions defined as they would be on a compass. Turning left is the same as going counterclockwise on a compass
        --facing;
    }
    void turnRight() 
    {
        //directions defined as they would be on a compass. Turning left is the same as going clockwise on a compass
        ++facing;
    }
    //defines where a player can move and returns a vector of places h
    vector<DrawnHex> CanMoveTo(DrawnHex position, vector<vector<DrawnHex>> grid);
    //sets position of player
    void SetPostiiton(int row, int col) 
    {
        this->row = row;
        this->col = col;
    }
    //sends how far the player had moved last turn to the mech
    void setAmountMoved(int amountMoved) 
    {
        mech.setMoved(amountMoved);
    }
    int getRow() 
    {
        return row;
    }
    int getCol() 
    {
        return col; 
    }
    string getName() 
    {
        return name;
    }
    Mech& getMech() 
    {
        return mech;
    }
    void setMech(Mech& mech) 
    {
        this->mech = mech;
    }
    void playerTurn(vector<vector<DrawnHex>>& drawnHex, Map& map, int sizex, int sizey);
    void Move(vector<vector<DrawnHex>>& drawnHex, vector<DrawnHex> movePositions, int option);
    void Turn(vector<vector<DrawnHex>>& drawnHex, vector<DrawnHex> movePositions);
    void fireWeapon(vector<vector<DrawnHex>>& drawnHex);
    bool killedTarget(vector<vector<DrawnHex>>& drawnHex);
};