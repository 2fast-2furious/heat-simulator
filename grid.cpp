#include "grid.h"
#include <fstream>
#include <iostream>
#include <iomanip>

// Constructor
Grid::Grid(int r, int c) : rows(r), cols(c) {
    points.resize(rows);
    for(int i = 0; i < rows; i++) {
        points[i].resize(cols, 100.0);
    }
}

// Access methods
double& Grid::getTemp(int i, int j) {
    return points[i][j];
}

const double& Grid::getTemp(int i, int j) const {
    return points[i][j];
}

// Set temperature
void Grid::setTemp(int row, int col, double temp) {
    points[row][col] = temp;
}

void Grid::initTemp(double initTemp){
    for (auto& row : points) { // Iterate through each inner vector (row)
        for (auto& element : row) { // Iterate through each element in the row
            element = initTemp;
        }
    }
}

// Apply boundary conditions
void Grid::applyBoundaryConditions(double heatingTemp) {
    // Left edge (first column) - hot

    // Right edge (last column) - ambient/cool
    for(int i = 0; i < rows; i++) {
        points[i][cols - 1] = 100.0;
    }

    // Top edge (first row) - ambient/cool
    for(int j = 0; j < cols; j++) {
        points[0][j] = 100.0;
    }

    // Bottom edge (last row) - ambient/cool
    for(int j = 0; j < cols; j++) {
        points[rows - 1][j] = 100.0;
    }

    for(int i = 0; i < rows; i++) {
        points[i][0] = heatingTemp;
    }

    for(int i = 0; i < rows; i++) {
        points[i][1] = heatingTemp;
    }
}

// Utility methods
int Grid::getRows() const {
    return rows;
}

int Grid::getCols() const {
    return cols;
}

// Save grid to CSV file
void Grid::saveToCSV(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Write temperature data
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << std::fixed << std::setprecision(6) << points[i][j];
            if (j < cols - 1) {
                file << ",";  // Add comma between values
            }
        }
        file << "\n";  // Newline after each row
    }

    file.close();
    std::cout << "Saved grid to " << filename << std::endl;
}