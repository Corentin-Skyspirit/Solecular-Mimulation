#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <array>

using particuleList = std::vector<std::array<float, 3>>;
using coord = std::array<float, 3>;

class Simulation {
private:
    int N_particules_local;
    particuleList particules;
    particuleList forces;

    double distance_carre(coord point1, coord point2);
public:
    Simulation(particuleList particules_depart);
    ~Simulation();

    void run();
    double energieMicro();
    void calculForces();
};
