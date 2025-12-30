#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>

class Reader {
private:    
    std::vector<std::array<float, 3>> particules;

public:
    Reader(std::string pathToFile);
    std::vector<std::array<float, 3>> getParticules();
    ~Reader();
};
