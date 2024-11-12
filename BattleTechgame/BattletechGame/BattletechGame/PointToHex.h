#pragma once
#include <iostream>
#include <vector>
#include <string>

// Define the size of the grid
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 10;

enum class Direction { NORTH, EAST, SOUTH, WEST };

struct Hex {
    int row;
    int col;
    bool isBlocked;
};

class HexGrid {
public:
    std::vector<std::vector<Hex>> grid;

    // Initialize the grid and set all hexes to unblocked by default
    HexGrid() {
        grid.resize(GRID_HEIGHT, std::vector<Hex>(GRID_WIDTH));
        for (int row = 0; row < GRID_HEIGHT; ++row) {
            for (int col = 0; col < GRID_WIDTH; ++col) {
                grid[row][col] = { row, col, false };
            }
        }
    }

    // Method to block a specific hex
    void blockHex(int row, int col) {
        if (isWithinBounds(row, col)) {
            grid[row][col].isBlocked = true;
        }
    }

    // Check if a hex is blocked
    bool isHexBlocked(int row, int col) {
        return isWithinBounds(row, col) && grid[row][col].isBlocked;
    }

    // Check if row and col are within bounds
    bool isWithinBounds(int row, int col) {
        return row >= 0 && row < GRID_HEIGHT && col >= 0 && col < GRID_WIDTH;
    }
};

class Player {
public:
    int row, col;
    Direction facing;

    Player(int startRow, int startCol, Direction startFacing)
        : row(startRow), col(startCol), facing(startFacing) {}

    // Change facing direction (left or right)
    void turnLeft() {
        facing = (facing == Direction::NORTH) ? Direction::WEST : static_cast<Direction>((int)facing - 1);
    }

    void turnRight() {
        facing = (facing == Direction::WEST) ? Direction::NORTH : static_cast<Direction>((int)facing + 1);
    }
};

class Arrow {
public:
    HexGrid* grid;

    Arrow(HexGrid* hexGrid) : grid(hexGrid) {}

    // Display the arrow's path based on player's direction
    void displayPath(Player& player) {
        std::cout << "Arrow Path from (" << player.row << ", " << player.col << ") facing ";
        printDirection(player.facing);
        std::cout << ":\n";

        int row = player.row;
        int col = player.col;

        // Move in the direction the player is facing
        for (int i = 0; i < 5; ++i) { // Example path length of 5 steps
            if (!grid->isWithinBounds(row, col) || grid->isHexBlocked(row, col)) {
                std::cout << "Blocked at (" << row << ", " << col << ")\n";
                break;
            }
            std::cout << "  -> HexStruct (" << row << ", " << col << ")\n";

            switch (player.facing) {
            case Direction::NORTH: row--; break;
            case Direction::EAST: col++; break;
            case Direction::SOUTH: row++; break;
            case Direction::WEST: col--; break;
            }
        }
    }

    // Helper to print direction as text
    void printDirection(Direction dir) {
        switch (dir) {
        case Direction::NORTH: std::cout << "NORTH"; break;
        case Direction::EAST: std::cout << "EAST"; break;
        case Direction::SOUTH: std::cout << "SOUTH"; break;
        case Direction::WEST: std::cout << "WEST"; break;
        }
    }
};