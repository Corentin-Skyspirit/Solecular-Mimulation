#include "../include/simulation.hpp"

constexpr int N_particules_total = 1000;

Simulation::Simulation(particuleList particules_depart) {
    particules = particules_depart;
    N_particules_local = N_particules_total;
}

Simulation::~Simulation() {
}

double Simulation::distance_carre(coord point1, coord point2) {
    return  (point1[0] - point2[0]) * (point1[0] - point2[0]) +
            (point1[1] - point2[1]) * (point1[1] - point2[1]) +
            (point1[2] - point2[2]) * (point1[2] - point2[2]);
}

void Simulation::run() {

}

double Simulation::energieMicro() {
    double r_etoile = 9.0; // 3.0 au carré
    double epsilon = 0.2;

    double total = 0.0;
    double uij;

    for (int i = 0; i < N_particules_total; i++) {
        for (int j = i+1; j < N_particules_total; j++) {
            uij += epsilon * (pow((r_etoile / distance_carre(particules[i], particules[j])), 6) 
                        - 2 * pow((r_etoile / distance_carre(particules[i], particules[j])), 3));
            total += uij;
        }
    }
    return total * 4;
}

void Simulation::calculForces() {
    
}