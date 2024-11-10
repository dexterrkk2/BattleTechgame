#include "Tile.h";
#include "Mech.h"
#include <iostream>
using std::string;
#pragma once
class Hex :public Tile 
{
private:
	Hex* pointingTo;
	Mech mech;
public: 
	void Rotate(Hex& hex);
	Mech getMech() 
	{
		return mech;
	}
	bool hasmech() {
		if (mech.walk() >0)
		{
			return true;
		}
		return false;
	}
	void setMech(Mech mech) {
		this->mech = mech;
	}
	Hex() 
	{
		pointingTo = this;
	}
	string getImage() {
		return mech.getImage();
	}
};
class DrawnHex
{
private:
	string image;
	int x;
	int y;
	Hex hex;
public:
	DrawnHex(Hex hex= *new Hex())
	{
		this->image = hex.getImage();
		this->hex = hex;
		x = 0;
		y = 0;
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
};