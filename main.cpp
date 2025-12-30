#include "include/reader.hpp"
#include "include/simulation.hpp"

using particuleList = std::vector<std::array<float, 3>>;

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        std::string path = argv[1];
        Reader reader = Reader(path);
        particuleList particules = reader.getParticules();

        Simulation simu = Simulation(particules);
        double energie = simu.energieMicro();
        std::cout << energie << std::endl;

        // for (int i = 0; i < particules.size()-1; i ++) {
        //     std::array<float, 3> coords = particules[i];
        //     std::cout << coords[0] << ", "
        //               << coords[1] << ", "
        //               << coords[2] << std::endl;
        // }
        return 0;
    } else std::cout << "Need an path to particle file" << std::endl;
}
