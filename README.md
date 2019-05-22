# Vector





To compile, follow these steps:

    mkdir build: this creates a new directory in which the compilation output will be stored, including the executable.
    cd build: just moves into the directory created in the step above.
    cmake -G "Unix Makefiles" ..: asks cmake to create the Makefile based on the script found in CMakeLists.txt, one level up.
    cmake --build .: triggers the compiling process.
    ./vector: run all tests


Obs: dá conflito manter a pasta include/gtest e rodar com o gtest local. Mudar o nome antes de complicar usando o cmake.

to compile with local gtest manually, follow these steps:

	g++ -Wall -std=c++11 src/main.cpp -L lib -I include -l gtest -l gtest_main -l pthread -o vector.out
