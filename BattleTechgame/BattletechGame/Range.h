#pragma once
#include <iostream>
#include <cmath>

// Function to calculate distance
inline int calculateRange(int startRow, int startCol, int targetRow, int targetCol) {
    return std::sqrt((abs(startRow - targetRow)) + std::abs(startCol - targetCol));
}
