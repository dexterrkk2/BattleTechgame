#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using std::vector;
using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
using std::cerr;
using std::getline;

void createFile() 
{
    ofstream outFile("Mechinfo.txt"); // Creates the file
    if (outFile.is_open()) {
        outFile << "M1\n";
        outFile << "M2\n";
        outFile.close(); // Close the file
        cout << "File created\n";
    }
    else {
        cerr << "Unable to create file.\n";
    }
}
inline vector<string> readData(string fileName) 
{
    // Step 2: Read from the file
    ifstream inFile(fileName); // Open the file for reading
    if (!inFile.is_open()) {
        cerr << "Unable to open file.\n";
    }

    vector<std::string> mechPieces; // Variable to store the data
    string line;
    while (getline(inFile, line)) {
        mechPieces.push_back(line); // Add line to the vector
    }
    inFile.close(); // Close the file
    return mechPieces;
}
void printData(vector<string> mech) 
{
    // Step 3: Output the data stored in the variable
    cout << "Names stored in a variable:\n";
    for (const auto& mech : mech) {
        cout << mech << "\n";
    }
}
void inputOutput(string fileName)
{
    createFile();
    vector<string> data = readData(fileName);
    printData(data);
}