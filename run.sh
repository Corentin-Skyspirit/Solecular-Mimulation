#!/bin/sh

cmake -B build -DCMAKE_BUILD_TYPE=Release
cd build
make
rm ../results.txt
./main ../particule > ../results.txt