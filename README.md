# Vector





To compile, follow these steps:

    mkdir build: this creates a new directory in which the compilation output will be stored, including the executable.
    cd build: just moves into the directory created in the step above.
    cmake -G "Unix Makefiles" ..: asks cmake to create the Makefile based on the script found in CMakeLists.txt, one level up.
    cmake --build .: triggers the compiling process.
    ./vector: run all tests


