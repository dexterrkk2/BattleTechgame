#pragma once
#include "Hex.h";
#include <vector>
using std::vector;
class Map 
{
public:
	//takes in 2d vector reference and size of grid then assigns cords
	void drawGrid(int sizeX, int sizeY,vector<vector<DrawnHex>> &drawnHexes);
	//helper function that assigns the cords to the individual grid
	string drawHex(DrawnHex& hex, int cordX, int cordY);
	//prints the hex grid once logic is done
	void printHex(int cols,int rows, vector<vector<DrawnHex>> &hex);
}; 