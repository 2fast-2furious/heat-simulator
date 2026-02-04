#include "grid.h"

class Simulator {
    private:
        Grid current;
        Grid next;
        int rows, cols;
        double alpha = 0;  // Thermal diffusivity
        double dt = 10.0;     // Time step size
        double dx = 0.25;     // Spatial step size
        double heatingTemp = 200;
        double initTemp = 100;


    public:
        Simulator(int r, int c, double a, double timestep, double gridSpacing)
            : current(r, c), next(r, c), rows(r), cols(c),
            alpha(a), dt(timestep), dx(gridSpacing) {

            // Initialize both grids
            current.initTemp(initTemp);
            next.initTemp(initTemp);
        }

        void swapGrids() {
            // Efficiently swap the two grids
            std::swap(current, next);
        }

        Grid& getCurrentGrid() {
            return current;
        }

        void computeNextStep();

        void run(int numSteps, int saveInterval);

    };