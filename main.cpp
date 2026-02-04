#include "simulator.h"
int main(){
    Simulator sim(10, 15, 0.000012, 0.01, 0.01);
    sim.run(30000, 5);
    return 0;

}
