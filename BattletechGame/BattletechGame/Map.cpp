#include <iostream>
#include <windows.h>
#include "Hex.h"
#include "Map.h";
using std::cout;
using std::endl;
using std::string;
using std::cin;
using namespace std;

//populates the hex grid with cordinates
void Map::SetGrid(int sizeX, int sizeY, vector<vector<DrawnHex>> &drawnHex)
{
    //runs it equal to number of rows
	for (int i = 0; i < sizeX; i++) 
	{
        //runs it equal to number of columns
        for (int j = 0; j < sizeY; j++)
		{
			//sets the cords of the hex
            drawnHex[i][j].setcords(i,j);
		}
	}
}

void printUpperHex(int& width) 
{
    //prints half the spaces needed for spacing
    for (int j = 0; j < (width / 2) - 2; j++)
    {
        cout << " ";
    }
    //prints the top of the hexagon
    cout << "---";
    //prints the other half of the spaces
    for (int j = 0; j < (width / 2) - 1; j++)
    {
        cout << " ";
    }
}
void printMiddleHex(int& width) 
{
    cout << " ";
    cout << "/";
    //prints spaces based off width of hex and the items printed before and after
    for (int j = 0; j < (width / 2) - 1; j++)
    {
        cout << " ";
    }
    //to print one \ you need an escape letter aka \ 
    cout << "\\" << "  ";
}
void printLowerHex(const int& width, string image) 
{
    cout << " ";
    //to print one \ you need an escape letter aka \ 
    cout << "\\";
    //prints spaces based off width of hex and the items printed before and after
    for (int j = 0; j < (width / 4) - 2; j++)
    {
        cout << " ";
    }
    //gets the image from the mech that lives on the hex code. If none prints three spaces 
    cout << image;
    //prints the other half of the spaces
    for (int j = 0; j < (width / 4) - 2; j++)
    {
        cout << " ";
    }
    cout << "/" << "  ";
}

//prints the hexes of the grid based off size and color they need to be.
void Map::printHex(int rows, int cols, vector<vector<DrawnHex>> &hex) {
    // Height and width of each hexagon
    int height = 5; 
    int width = 8;  
    //runs this equal to number of rows
    for (int q = 0; q < rows; q++) 
    {
        //prints the number of lines in each hexagon
        for (int i = 0; i < height; i++)
        {
            //prints the top and bottom of the hexagon
            if (i % 4 == 0)
            {
                //takes cout output
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                //prints for the number of hexagons in column
                for (int c = 0; c < cols; ++c)
                {
                    //sets output to the color of the hex from the hex 2d vector
                    SetConsoleTextAttribute(hConsole, hex[q][c].getColor());
                    printUpperHex(width);
                }
                cout << endl;
            }
            //used to print the middle, now just prints nothing to make sure it lines up
            else if (i % 4 == 2) 
            {
            }
            //prints the middle part of the hexagon
            else if (i % 4 == 1)
            {
                //takes cout output
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                //prints for the number of hexagons
                for (int c = 0; c < cols; ++c)
                {
                    //sets output to hex color
                    SetConsoleTextAttribute(hConsole, hex[q][c].getColor());
                    printMiddleHex(width);
                }
                cout << endl;
            }
            //prints the bottom of the hexagon
            else 
            {
                //takes in output
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                //prints for the number of hexagons in column
                for (int c = 0; c < cols; ++c) {
                    //sets output to hex color
                    SetConsoleTextAttribute(hConsole, hex[q][c].getColor());
                    printLowerHex(width, hex[q][c].getID());
                }
                //goes to next line
                cout << endl;
            }
        }
    }
}