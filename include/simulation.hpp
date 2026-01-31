#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <array>

using particuleList = std::vector<std::array<double, 3>>;
using coord = std::array<double, 3>;

class Simulation {
private:
    int N_particules_local;
    double energie_micro_systeme;
    particuleList particules;
    std::vector<particuleList> n_sym;
    particuleList forces;

    double distance_carre(coord point1, coord point2);
public:
    Simulation(particuleList particules_depart);
    ~Simulation();

    particuleList getParticules();
    particuleList getForces();
    
    void run();
    double energieMicro();
    void calculForces();
};
