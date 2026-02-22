#include "../include/simulation.hpp"

constexpr double r_etoile = 3.0;
constexpr double epsilon = 0.2;
constexpr double r_cut = 10.0;
constexpr double L = 42.0;
constexpr double conversion_force = 0.0004186;

constexpr int n_sym = 2;
constexpr int N_particules_total = 1000;

Simulation::Simulation(particuleList particules_depart) {
    int cpt = 0;
    for (int x = -n_sym + 1; x <= n_sym - 1; x++) {
        for (int y = -n_sym + 1; y <= n_sym - 1; y++) {
            for (int z = -n_sym + 1; z <= n_sym - 1; z++) {
                coord box = {x * L, y * L, z * L};
                boxes.push_back(box);
                std::cerr << "id = " << cpt++ << " for " << x << y << z << " box" << std::endl;
            }
        }
    }
    particules = particules_depart;
    particules_loc = particules_depart;
    N_particules_local = N_particules_total;
}

Simulation::~Simulation() {
}

double Simulation::distance_carre(coord point1, coord point2) {
    return  (point1[0] - point2[0]) * (point1[0] - point2[0]) +
            (point1[1] - point2[1]) * (point1[1] - point2[1]) +
            (point1[2] - point2[2]) * (point1[2] - point2[2]);
}

coord Simulation::apply_box(coord particule, coord box) {
    coord part = {
        particule[0] + box[0],
        particule[1] + box[1],
        particule[2] + box[2]
    };
    return part;
}

particuleList Simulation::getParticules() {
    return particules;
}

particuleList Simulation::getForces() {
    return forces;
}

void Simulation::run() {

}

double Simulation::energieMicro() {
    double r_etoile2 = r_etoile * r_etoile;

    double total = 0.0;
    for (coord box:boxes) {
        // std::cerr << apply_box(particules[0], box)[0] << "/" << apply_box(particules[0], box)[1] << "/" << apply_box(particules[0], box)[2] << std::endl;
        for (int i = 0; i < N_particules_total; i++) {
            for (int j = i+1; j < N_particules_total; j++) {
                // interraction of particle i of all the boxes
                double dist2_ij = distance_carre(particules[i], apply_box(particules[j], box));
                if (dist2_ij < r_cut * r_cut) {
                    // uij calc
                    total += (pow((r_etoile2 / dist2_ij), 6) 
                                - 2 * pow((r_etoile2 / dist2_ij), 3));
                }
            }
        }
    }
    energie_micro_systeme = total * epsilon * 2;
    return energie_micro_systeme;
}

void Simulation::calculForces() {
    double r_etoile2 = r_etoile * r_etoile;
    std::cerr << boxes.size()/2 << std::endl;
    for (int i = 0; i < N_particules_total; i++) {
        coord forces_particule = {0, 0, 0};
        for (coord box:boxes) {
            for (int j = 0; j < N_particules_total; j ++) {
                // for every j particle in every boxes

                double dist2_ij = distance_carre(particules[i], apply_box(particules[j], box));
            
                if (dist2_ij > 0 and dist2_ij < r_cut * r_cut) {
                    // forces computing
                    for (int dim = 0; dim < 3; dim++) {
                        // for every dimensions (x, y and z)
                        forces_particule[dim] += -48 * epsilon * 
                            (pow((r_etoile2 / dist2_ij), 6) 
                            - pow((r_etoile2 / dist2_ij), 3))
                            * ((particules[i][dim] - particules[j][dim]) / dist2_ij);
                    }
                }
            }
        }
        forces.push_back(forces_particule);
    }
}