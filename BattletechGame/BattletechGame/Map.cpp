#include <iostream>
#include <windows.h>
#include "Hex.h"
#include "Map.h";
using std::cout;
using std::endl;
using std::string;
using std::cin;
using namespace std;
void Map::drawGrid(int sizeX, int sizeY, vector<vector<DrawnHex>> &drawnHex)
{
	for (int i = 0; i < sizeX; i++) 
	{
		//string image = "Maa";
		//draw vertical
        
		for (int j = 0; j < sizeY; j++) 
		{
			//draw horizontal
            drawHex(drawnHex[i][j], i, j);
            if (i > 0) 
            {
                drawnHex[i][j].setPointingTo(drawnHex[i - 1][j].getHex());
            }
            if (i == j - 1) {
                drawnHex[0][j].setPointingTo(drawnHex[1][j].getHex());
            }
		}
        printHex(sizeY, drawnHex[i]);
		//cout << endl;
	}
}
string Map::drawHex(DrawnHex& hex, int cordX, int cordY)
{
    //cout << "Set cords" << endl;
    //cout << cordX << cordY << endl;
    hex.setcords(cordX, cordY);
	return 	hex.getImage();
}
void Map::printHex(int cols, vector<DrawnHex> &hex) {
    // Height and width of each hexagon
    int height = 5; // Height of one hexagon
    int width = 8;   // Width of one hexagon (including spaces)
    for (int i = 0; i < height; i++) 
    {
        //even lines print the top and bottom part odd print the middle
        if (i%4 == 0) 
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Print the upper part of hexagons
            for (int c = 0; c < cols; ++c) 
            {
               
                SetConsoleTextAttribute(hConsole, hex[c].getColor());
                for (int j = 0; j < (width / 2)-2; j++)
                {
                    cout << " ";
                }
                cout << "---";
                //width of hex minus num of printed spaced before
                for (int j = 0; j < (width/2)-1; j++) 
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
        else if(i %4 == 2){
            //// Print the middle part of hexagons
            //for (int c = 0; c < cols; ++c) {
            //    cout<<" ";
            //    //Width minus spaces printed before and after
            //    for (int j = 0; j < (width/4)-1; j++)
            //    {
            //        cout << " ";
            //    }
            //    cout << hex[c].getImage();
            //    for (int j = 0; j < (width / 4)-1; j++)
            //    {
            //        cout << " ";
            //    }
            //    cout << " " << " ";
            //}
            //cout << endl;
        }
        else if(i%4 == 1)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            for (int c = 0; c < cols; ++c) 
            {
                SetConsoleTextAttribute(hConsole, hex[c].getColor());
                cout << " ";
                cout <<"/";
                //Width minus spaces printed before and after
                for (int j = 0; j < (width/2)-1; j++)
                {
                    cout << " ";
                }
                cout << "\\" << "  ";
            }
            cout << endl;
        }
        else {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            for (int c = 0; c < cols; ++c) {
                SetConsoleTextAttribute(hConsole, hex[c].getColor());
                cout << " ";
                cout << "\\";
                //Width minus spaces printed before and after
                for (int j = 0; j < (width / 4)-2; j++)
                {
                    cout << " ";
                }
                cout << hex[c].getImage();
                for (int j = 0; j < (width / 4)-2; j++)
                {
                    cout << " ";
                }
                cout << "/" << "  ";
            }
            cout << endl;

        }
    }
}