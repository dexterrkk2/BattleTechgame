#include <iostream>
#include <fstream>
#include <vector>
#include <string>
void createFile() 
{
    std::ofstream outFile("Mechinfo.txt"); // Creates the file
    if (outFile.is_open()) {
        outFile << "M1\n";
        outFile << "M2\n";
        outFile.close(); // Close the file
        std::cout << "File created\n";
    }
    else {
        std::cerr << "Unable to create file.\n";
    }
}
std::vector<std::string> readData() 
{
    // Step 2: Read from the file
    std::ifstream inFile("Mechinfo.txt"); // Open the file for reading
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file.\n";
    }

    std::vector<std::string> mech; // Variable to store the data
    std::string line;
    while (std::getline(inFile, line)) {
        mech.push_back(line); // Add line to the vector
    }
    inFile.close(); // Close the file
    return mech;
}
void printData(std::vector<std::string> mech) 
{
    // Step 3: Output the data stored in the variable
    std::cout << "Names stored in a variable:\n";
    for (const auto& mech : mech) {
        std::cout << mech << "\n";
    }
}
void inputOutput()
{
    createFile();
    std::vector<std::string> data = readData();
    printData(data);
}