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
    double energie_cinetique;
    double temperature;
    particuleList particules;
    particuleList particules_loc;
    particuleList moment_cinetique;
    std::vector<coord> boxes;
    particuleList forces;

    double distanceCarre(coord point1, coord point2);
    coord applyBox(coord particule, coord box);
    particuleList momentCinetique();
public:
    Simulation(particuleList particules_depart);
    ~Simulation();

    particuleList getParticules();
    particuleList getForces();
    double getEnergieMicro();
    double getEnergieCinetique();
    double getTemperature();
    
    void run();
    double calculEnergieMicro();
    void calculForces();
    double calculEnergieCinetique();
    double calculTemperature();
};
