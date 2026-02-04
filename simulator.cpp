#include "simulator.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/stat.h>

void Simulator::computeNextStep() {
    // Calculate coefficient: alpha * dt / dx^2
    double coeff = alpha * dt / (dx * dx);

    // Update interior points only
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            // Get current temperature and neighbors
            double T_center = current.getTemp(i, j);
            double T_left   = current.getTemp(i, j-1);
            double T_right  = current.getTemp(i, j+1);
            double T_top    = current.getTemp(i-1, j);
            double T_bottom = current.getTemp(i+1, j);

            // Finite Difference Method formula
            // T_new = T_old + coeff * (sum_of_neighbors - 4*T_old)
            double laplacian = T_left + T_right + T_top + T_bottom - 4.0 * T_center;
            double newTemp = T_center + coeff * laplacian;
            next.setTemp(i, j, newTemp);
        }
    }
}

void Simulator::run(int numSteps, int saveInterval) {
    // Create temp directory if it doesn't exist
    struct stat info;
    if (stat("temp", &info) != 0) {
        // Directory doesn't exist, create it
        #ifdef _WIN32
            mkdir("temp");
        #else
            mkdir("temp", 0755);
        #endif
        std::cout << "Created 'temp' directory" << std::endl;
    }

    // Apply initial boundary conditions
    current.applyBoundaryConditions(heatingTemp);

    // Save initial state
    std::cout << "Starting simulation for " << numSteps << " steps..." << std::endl;
    current.saveToCSV("temp/grid_000000.csv");

    // Main simulation loop
    for (int step = 1; step <= numSteps; step++) {
        computeNextStep();
        next.applyBoundaryConditions(heatingTemp);
        swapGrids();

        // Print progress every 100 steps
        if (step % 100 == 0) {
            std::cout << "Step " << step << " / " << numSteps << std::endl;
        }

        // Save to CSV at specified intervals
        if (step % saveInterval == 0) {
            // Generate filename with zero-padded step number
            std::ostringstream filename;
            filename << "temp/grid_" << std::setfill('0') << std::setw(6) << step << ".csv";
            current.saveToCSV(filename.str());
        }
    }

    std::cout << "Simulation complete!" << std::endl;
}