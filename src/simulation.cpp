#include "../include/simulation.hpp"

constexpr double r_etoile = 3.0;
constexpr double epsilon = 0.2;
constexpr double L = 42.0;

constexpr int N_particules_total = 1000;

Simulation::Simulation(particuleList particules_depart) {
    int cpt = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                std::cerr << "id = " << cpt++ << " for " << x << y << z << " box" << std::endl;
                if (x == y == z == 0) {
                    boxes.push_back(particules_depart);
                }
                else {
                    // omg 4 for complexity, hopefully it's just for the init
                    particuleList box;
                    for (coord particule: particules_depart){
                        box.push_back({particule[0] + (L * x), particule[1] + (L * y), particule[2] + (L * z)});
                    }
                    boxes.push_back(box);
                }
            }
        }
    }
    N_particules_local = N_particules_total;
}

Simulation::~Simulation() {
}

double Simulation::distance_carre(coord point1, coord point2) {
    return  (point1[0] - point2[0]) * (point1[0] - point2[0]) +
            (point1[1] - point2[1]) * (point1[1] - point2[1]) +
            (point1[2] - point2[2]) * (point1[2] - point2[2]);
}

particuleList Simulation::getParticules() {
    return boxes[13]; // the 0 0 0 particles box
}

particuleList Simulation::getForces() {
    return forces;
}

void Simulation::run() {

}

double Simulation::energieMicro() {
    double r_etoile2 = r_etoile * r_etoile;

    double total = 0.0;
    for (particuleList particules: boxes) {
        for (int i = 0; i < N_particules_total; i++) {
            for (int j = i+1; j < N_particules_total; j++) {

                double dist2_ij = distance_carre(particules[i], particules[j]);
                // uij calc
                energie_micro_systeme += epsilon * (pow((r_etoile2 / dist2_ij), 6) 
                            - 2 * pow((r_etoile2 / dist2_ij), 3));
                total += energie_micro_systeme;
            }
        }
    }
    energie_micro_systeme = total * 4;
    return energie_micro_systeme;
}

void Simulation::calculForces() {
    double r_etoile2 = r_etoile * r_etoile;
    particuleList particules = boxes[13];
    for (int i = 0; i < N_particules_total; i++) {
        for (int j = 0; j < N_particules_total; j ++) {

            coord forces_particule;
            double dist2_ij = distance_carre(particules[i], particules[j]);
            if (dist2_ij == 0) {
                forces_particule = {0, 0, 0};
            } else {
                // forces computing
                for (int dim = 0; dim < 3; dim++) {
                    // for every dimensions (x, y and z)
                    forces_particule[dim] = -48 * epsilon * 
                        (pow((r_etoile2 / dist2_ij), 6) 
                        - pow((r_etoile2 / dist2_ij), 3))
                        * ((particules[i][dim] - particules[j][dim]) / dist2_ij);
                }
            }
            forces.push_back(forces_particule);
        }
    }
}