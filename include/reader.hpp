#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>

using particuleList = std::vector<std::array<double, 3>>;
using coord = std::array<double, 3>;

class Reader {
private:    
    particuleList particules;

public:
    Reader(std::string pathToFile);
    particuleList getParticules();
    ~Reader();
};
