#pragma once
#include "Mech.h"
#include <iostream>
#include <windows.h>
using std::string;
using std::ostream;
class Hex 
{
private:
	Mech mech;
	int color; 
public: 
	//returns mech
	Mech& getMech() 
	{
		return mech;
	}
	//returns hex back to blue and reassigns hex back to default
	void eraseMech() 
	{
		this->mech = Mech();
		//foreground blue is defined as an int in memory. 
		color = FOREGROUND_BLUE;
		//cout<<getID();
	}
	//changed color to red when this hex has a mech
	void setMech(Mech& mech) 
	{
		this->mech = mech;
		//foreground red is defined as an int in memory. 
		color = FOREGROUND_RED;
		//cout << getID() << endl;
	}
	//checks if this mech is active. a mech with a negative movespeed is not active
	bool hasmech() {
		if (mech.getWalk()>0)
		{
			return true;
		}
		return false;
	}
	//constructs hex
	Hex(Mech& mech): mech(mech)
	{
		color = FOREGROUND_BLUE;
	}
	//returns the mech id so it can be printed on hexes
	string getID() 
	{
		return mech.getID();
	}
	//sets color of hex
	void setColor(int i) 
	{
		color = i;
	}
	//returns color of hex
	int getColor() 
	{
		return color;
	}
};
class DrawnHex
{
private:
	//posiion information as well as assigned hex
	int x;
	int y;
	Hex& hex;
public:
	//constructs hex
	DrawnHex(Hex& hex): hex(hex)
	{
		x = 0;
		y = 0;
	}
	//decronstructs hex
	~DrawnHex() 
	{
		
	}
	//returns the image on the mech attached to the hex
	string getID() 
	{
		return hex.getID();
	}
	//sets the cords of this hex, to where it is on the grid
	void setcords(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	//gets x position on grid
	int	getX() 
	{
		return x;
	}
	//gets y position on grid
	int getY() 
	{
		return y;
	}
	//returns the hex referenced by this class
	Hex& getHex() 
	{
		return hex;
	}
	//sets the color of the hex 
	void setColor(int i) 
	{
		hex.setColor(i);
	}
	//returns hex color.
	int getColor()
	{
		return hex.getColor();
	}
	//gets the output for a drawn hex
	friend ostream& operator<<(ostream& os, DrawnHex hex) 
	{
		//gets position information
		os << "X position: " << hex.getX() << " Y position: " << hex.getY();
		return os;
	}
};