#include "include/reader.hpp"
#include "include/simulation.hpp"

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        std::string path = argv[1];
        Reader reader = Reader(path);
        particuleList particules = reader.getParticules();

        Simulation simu = Simulation(particules);
        double energie = simu.energieMicro();
        std::cout << energie << std::endl;

        simu.calculForces();
        particuleList forces = simu.getForces();

        double totalx = 0.0;
        double totaly = 0.0;
        double totalz = 0.0;

        for (int i = 0; i < forces.size()-1; i ++) {
            coord dims = forces[i];
            totalx += dims[0];
            totaly += dims[1];
            totalz += dims[2];

            // std::cout << dims[0] << ", "
            //           << dims[1] << ", "
            //           << dims[2] << std::endl;
        }
        std::cout << totalx << "/" << totaly << "/" << totalz << std::endl;
        return 0;
    } else std::cout << "Need an path to particle file" << std::endl;
}
