#!/bin/sh

cmake -B build -DCMAKE_BUILD_TYPE=Release
cd build
make
rm ../results_0.txt
./main ../particule > ../results_0.txt
cd ..
python3 visu.py