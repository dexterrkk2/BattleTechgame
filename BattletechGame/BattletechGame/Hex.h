#include "Tile.h";
#include "Mech.h"
#include <iostream>
#include <windows.h>
using std::string;
using std::ostream;
#pragma once
class Hex :public Tile 
{
private:
	Hex* pointingTo;
	Mech mech;
	int color; 
public: 
	void Rotate(Hex& hex);
	Mech getMech() 
	{
		return mech;
	}
	void eraseMech() 
	{
		this->mech = *new Mech();
		color = FOREGROUND_BLUE;
		//cout<<getImage();
	}
	void setMech(Mech& mech) 
	{
		this->mech = mech;
		color = FOREGROUND_RED;
		//cout << getImage() << endl;
	}
	bool hasmech() {
		if (mech.walk() >0)
		{
			return true;
		}
		return false;
	}
	Hex() 
	{
		pointingTo = this;
		color = FOREGROUND_BLUE;
	}
	string getImage() 
	{
		return mech.getImage();
	}
	Hex* getPointingTo() 
	{
		return pointingTo;
	}
	void setColor(int i) 
	{
		color = i;
	}
	int getColor() 
	{
		return color;
	}
};
class DrawnHex
{
private:
	string image;
	int x;
	int y;
	Hex& hex;
public:
	DrawnHex(Hex& hex): hex(hex)
	{
		this->image = hex.getImage();
		x = 0;
		y = 0;
	}
	~DrawnHex() 
	{
		
	}
	string getImage() 
	{
		return hex.getImage();
	}
	void setImage(string image) 
	{
		this->image = image;
	}
	void setcords(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int	getX() 
	{
		return x;
	}
	int getY() 
	{
		return y;
	}
	void setPointingTo(Hex& hex) 
	{
		hex.Rotate(hex);
	}
	Hex& getHex() 
	{
		return hex;
	}
	void setColor(int i) 
	{
		hex.setColor(i);
	}
	int getColor()
	{
		return hex.getColor();
	}
	friend ostream& operator<<(ostream& os, DrawnHex hex) 
	{
		os << "X position: " << hex.getX() << " Y position: " << hex.getY() << " has mech: " << hex.hex.hasmech();
		return os;
	}
};