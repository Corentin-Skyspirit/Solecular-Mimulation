#include "include/reader.hpp"
#include "include/simulation.hpp"

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        std::string path = argv[1];
        Reader reader = Reader(path);
        particuleList particules = reader.getParticules();

        Simulation simu = Simulation(particules);
        simu.calculEnergieMicro();
        std::cerr << simu.getEnergieMicro() << std::endl;

        simu.calculForces();
        particuleList forces = simu.getForces();

        simu.calculEnergieCinetique();
        double cinetique = simu.getEnergieCinetique();

        simu.calculTemperature();
        double temperature = simu.getTemperature();

        double totalx = 0.0;
        double totaly = 0.0;
        double totalz = 0.0;

        for (int i = 0; i < forces.size(); i ++) {
            coord dims = forces[i];
            totalx += dims[0];
            totaly += dims[1];
            totalz += dims[2];
        }
        
        for (int i = 0; i < particules.size(); i ++) {
            coord particule = particules[i];
            std::cout << particule[0] << ", "
                      << particule[1] << ", "
                      << particule[2] << "\n";
        }
        std::cerr << totalx << "/" << totaly << "/" << totalz << std::endl;
        std::cerr << particules.size() << " - " << forces.size() << std::endl;
        std::cerr << "Energie cinetique : " << cinetique << " - Temperature : " << temperature << std::endl;
        for (int k = 0; k < 100; k++) {
            simu.run();
            std::cerr 
            << "Energie cinetique : " << simu.getEnergieCinetique() 
            << " - Energie potentielle : " << simu.getEnergieMicro() 
            << " - Energie totale : " << simu.getEnergieCinetique() + simu.getEnergieMicro()
            << " - Temperature : " << simu.getTemperature() 
            << std::endl;
        }
        return 0;
    } else std::cerr << "Need an path to particle file" << std::endl;
}
