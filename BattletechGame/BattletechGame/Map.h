#pragma once
#include "Hex.h";
class Map 
{
public:
	void drawGrid(int sizeX, int sizeY, Hex hex[][7], DrawnHex drawnHex[][7]);
	string drawHex(DrawnHex hex, int cordX, int cordY);
	void printHex(int cols, DrawnHex hex[]);
};