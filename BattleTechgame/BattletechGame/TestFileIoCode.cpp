#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using std::string;

std::vector<std::string> readData(string fileName) 
{
    // Step 2: Read from the file
    std::ifstream inFile(fileName); // Open the file for reading
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file.\n";
    }

    std::vector<std::string> mechText; // Variable to store the data
    std::string line;
    while (std::getline(inFile, line)) {
        mechText.push_back(line); // Add line to the vector
    }
    inFile.close(); // Close the file
    return mechText;
}

