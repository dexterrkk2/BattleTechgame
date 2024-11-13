#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ofstream outFile("Mechinfo.txt"); // Creates the file
    if (outFile.is_open()) {
        outFile << "M1\n";
        outFile << "M2\n";
        outFile.close(); // Close the file
        std::cout << "File created\n";
    } else {
        std::cerr << "Unable to create file.\n";
        return 1;
    }

    // Step 2: Read from the file
    std::ifstream inFile("Mechinfo.txt"); // Open the file for reading
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file.\n";
        return 1;
    }

    std::vector<std::string> mech; // Variable to store the data
    std::string line;
    while (std::getline(inFile, line)) {
        mech.push_back(line); // Add line to the vector
    }
    inFile.close(); // Close the file

    // Step 3: Output the data stored in the variable
    std::cout << "Names stored in a variable:\n";
    for (const auto& mech : mech) {
        std::cout << mech << "\n";
    }

    return 0;
}
