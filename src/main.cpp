#include "../include/reader.hpp"

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        std::string path = argv[1];
        Reader reader = Reader(path);
        std::vector<std::array<float, 3>> points = reader.getPoints();

        for (int i = 0; i < points.size()-1; i ++) {
            std::array<float, 3> coords = points[i];
            std::cout << coords[0] << ", "
                      << coords[1] << ", "
                      << coords[2] << std::endl;
        }
        return 0;
    } else std::cout << "Need an path to particle file" << std::endl;
}
