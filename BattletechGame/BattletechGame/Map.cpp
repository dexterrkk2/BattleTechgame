#include <iostream>
#include "Hex.h"
#include "Map.h";
using std::cout;
using std::endl;
using std::string;
using std::cin;
void Map::drawGrid(int sizeX, int sizeY, Hex* hex)
{
	for (int i = 0; i < sizeX; i++) 
	{
		//draw vertical
		for (int j = 0; j < sizeY; j++) 
		{
			//draw horizontal
			string image = "" + ((i+1) * j);
			DrawnHex* drawnHex = new DrawnHex(image, hex[(i+1)*j]);
			cout << drawHex(*drawnHex, i, j);
		}
		cout << endl;
	}
}
string Map::drawHex(DrawnHex hex, int cordX, int cordY)
{
	hex.setcords(cordX, cordY);
	return 	hex.getImage();
}