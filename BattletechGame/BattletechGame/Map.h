#pragma once
#include "Hex.h";
#include <vector>
using std::vector;
class Map 
{
public:
	//takes in 2d vector reference and size of grid then assigns cords
	void SetGrid(int sizeX, int sizeY,vector<vector<DrawnHex>> &drawnHexes);
	//prints the hex grid once logic is done
	void printHex(int cols,int rows, vector<vector<DrawnHex>> &hex);
}; 