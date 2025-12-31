#include "../include/reader.hpp"

Reader::Reader(std::string pathTofile) {
    std::string line;
    std::ifstream file (pathTofile);
    if (file.is_open()) {
        while (getline (file, line)) {
            if (line.size() > 20) {
                std::stringstream ss(line);

                int ignore;
                coord coords;

                ss >> ignore;
                ss >> coords[0];
                ss >> coords[1];
                ss >> coords[2];

                particules.push_back(coords);

                // std::cout << coords[0] << ", "
                //           << coords[1] << ", "
                //           << coords[2] << std::endl;
            }
        }
        file.close();
    }

    else std::cout << "Unable to open file" << std::endl; 
}

particuleList Reader::getParticules() {
    return particules;
}

Reader::~Reader() {};