#include "../include/simulation.hpp"
#include <random>

constexpr double r_etoile = 3.0;
constexpr double epsilon = 0.2;
constexpr double r_cut = 10.0;
constexpr double L = 42.0;
constexpr double conversion_force = 0.0004186;
constexpr double const_r = 0.00199;
constexpr int m_i = 18;
constexpr int T = 300;

constexpr int n_sym = 2;
constexpr int n_particules_total = 1000;
constexpr int n_dl = 3 * n_particules_total - 3;

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
    N_particules_local = n_particules_total;
    srand(0);
    for (int i = 0; i < n_particules_total; i++) {
        coord coord = {(rand() % 2) - 1, (rand() % 2) - 1, (rand() % 2) - 1};
        moment_cinetique.push_back(coord);
    }
    calculEnergieCinetique();
    rapport();
}

Simulation::~Simulation() {
}

double Simulation::distanceCarre(coord point1, coord point2) {
    return  (point1[0] - point2[0]) * (point1[0] - point2[0]) +
            (point1[1] - point2[1]) * (point1[1] - point2[1]) +
            (point1[2] - point2[2]) * (point1[2] - point2[2]);
}

coord Simulation::applyBox(coord particule, coord box) {
    coord part = {
        particule[0] + box[0],
        particule[1] + box[1],
        particule[2] + box[2]
    };
    return part;
}

void Simulation::rapport() {
    double rapport = sqrt(n_dl * const_r * T / energie_cinetique);
    for (int i = 0; i < n_particules_total; i ++) {
        coord co = {
            moment_cinetique[i][0] * rapport, 
            moment_cinetique[i][1] * rapport, 
            moment_cinetique[i][2] * rapport
        };
        moment_cinetique[i] = co;
    }
}

particuleList Simulation::getParticules() {
    return particules;
}

particuleList Simulation::getForces() {
    return forces;
}

double Simulation::getEnergieCinetique() {
    return energie_cinetique;
}

double Simulation::getEnergieMicro() {
    return energie_micro_systeme;
}

double Simulation::getTemperature() {
    return temperature;
}

void Simulation::run() {
    calculEnergieMicro();
    calculForces();
    calculEnergieCinetique();
    calculCentreMasse();
    calculMomentCinetique();
    calculTemperature();
}

void Simulation::calculEnergieMicro() {
    double r_etoile2 = r_etoile * r_etoile;

    double total = 0.0;
    for (coord box:boxes) {
        // std::cerr << apply_box(particules[0], box)[0] << "/" << apply_box(particules[0], box)[1] << "/" << apply_box(particules[0], box)[2] << std::endl;
        for (int i = 0; i < n_particules_total; i++) {
            for (int j = i+1; j < n_particules_total; j++) {
                // interraction of particle i of all the boxes
                double dist2_ij = distanceCarre(particules[i], applyBox(particules[j], box));
                if (dist2_ij < r_cut * r_cut) {
                    // uij calc
                    total += (pow((r_etoile2 / dist2_ij), 6) 
                                - 2 * pow((r_etoile2 / dist2_ij), 3));
                }
            }
        }
    }
    energie_micro_systeme = total * epsilon * 2;
}

void Simulation::calculForces() {
    double r_etoile2 = r_etoile * r_etoile;
    // std::cerr << boxes.size()/2 << std::endl;
    for (int i = 0; i < n_particules_total; i++) {
        coord forces_particule = {0, 0, 0};
        for (coord box:boxes) {
            for (int j = 0; j < n_particules_total; j ++) {
                // for every j particle in every boxes

                double dist2_ij = distanceCarre(particules[i], applyBox(particules[j], box));
            
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

void Simulation::calculEnergieCinetique() {
    double temp = 0.0;
    for (coord particule : moment_cinetique) {
        temp += particule[0] * particule[0] + particule[1] * particule[1] + particule[2] * particule[2];
    }
    temp /= m_i;
    energie_cinetique = (1 / (2 * conversion_force)) * temp;
}

void Simulation::calculTemperature() {
    temperature = (1 / (n_dl * const_r)) * energie_cinetique;
}   

void Simulation::calculCentreMasse() {
    double x = 0;
    double y = 0;
    double z = 0;
    for (coord particule : moment_cinetique) {
        x += particule[0];
        y += particule[1];
        z += particule[2];
    }
    cinetiqueCentremasse = {x, y, z};
}

void Simulation::calculMomentCinetique() {
    for (int i = 0; i < n_particules_total; i ++) {
        coord co = {
            moment_cinetique[i][0] - (cinetiqueCentremasse[0] / n_particules_total), 
            moment_cinetique[i][1] - (cinetiqueCentremasse[1] / n_particules_total), 
            moment_cinetique[i][2] - (cinetiqueCentremasse[2] / n_particules_total)
        };
        moment_cinetique[i] = co;
    }
    calculEnergieCinetique();
    rapport();
}