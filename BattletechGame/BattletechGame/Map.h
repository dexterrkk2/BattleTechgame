#pragma once
#include "Hex.h";
#include <vector>
using std::vector;
class Map 
{
public:
	void drawGrid(int sizeX, int sizeY,vector<vector<DrawnHex>> &drawnHexes);
	string drawHex(DrawnHex& hex, int cordX, int cordY);
	void printHex(int cols,int rows, vector<vector<DrawnHex>> &hex);
}; 