#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {
private:
    int rows;
    int cols;
    std::vector<std::vector<double>> points;

public:
    Grid(int r, int c);

    double& getTemp(int i, int j);
    const double& getTemp(int i, int j) const;

    void setTemp(int row, int col, double temp);
    void applyBoundaryConditions(double heatingTemp);

    int getRows() const;
    int getCols() const;

    void initTemp(double initTemp);
    void saveToCSV(const std::string& filename) const;
};

#endif
