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
		string image = "x";
		//draw vertical
		for (int j = 0; j < sizeY; j++) 
		{
			//draw horizontal
			DrawnHex* drawnHex = new DrawnHex(image, hex[(i+1)*j]);
			//print hex old
			//cout <<i << j << drawHex(*drawnHex, i, j) << " ";
		}
        printHex(sizeY);
		cout << endl;
	}
}
string Map::drawHex(DrawnHex hex, int cordX, int cordY)
{
	hex.setcords(cordX, cordY);
	return 	hex.getImage();
}
void Map::printHex(int cols) {
    // Height and width of each hexagon
    int height = 3; // Height of one hexagon
    int width = 5;   // Width of one hexagon (including spaces)
    for (int i = 0; i < height; i++) 
    {
        //even lines print the top and bottom part odd print the middle
        if (i%2 == 0) {
            // Print the upper part of hexagons
            for (int c = 0; c < cols; ++c) {
                cout<<" " << "#";
                //width of hex minus num of printed spaced before
                for (int j = 0; j < width-2; j++) 
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
        else {
            // Print the middle part of hexagons
            for (int c = 0; c < cols; ++c) {
                cout<<"#";
                //Width minus spaces printed before and after
                for (int j = 0; j < width-3; j++)
                {
                    cout << " ";
                }
                cout << "#" << " ";
            }
            cout << endl;
        }
    }
}
