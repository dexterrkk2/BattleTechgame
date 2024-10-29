#pragma once
#include "Hex.h";
class Map 
{
public:
	void drawGrid(int sizeX, int sizeY, Hex hex[]);
	string drawHex(DrawnHex hex, int cordX, int cordY);
};