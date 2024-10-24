#include "Tile.h";
#include <iostream>
using std::string;
#pragma once
class Hex :public Tile 
{
private:
	Hex* pointingTo;
public: 
	void Rotate(Hex& hex);
	Hex() 
	{
		pointingTo = this;
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
	DrawnHex(string image, Hex hex) 
	{
		this->image = image;
		this->hex = hex;
		x = 0;
		y = 0;
	}
	string getImage() 
	{
		return image;
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