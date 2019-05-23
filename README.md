
Esse projeto é uma classe template de uma estrutura de dados do tipo lista, implementando um array dinâmico baseado no std::vector da STL.

Para compilar usando o cmake, siga as instruções:

     $ mkdir build: this creates a new directory in which the compilation output will be stored, including the executable.

     $ cd build: just moves into the directory created in the step above.

     $ cmake -G "Unix Makefiles" ..: asks cmake to create the Makefile based on the script found in CMakeLists.txt, one level up.

     $ cmake --build .: triggers the compiling process.

     $ ./vector: run all tests


- Para compilar manualmente com um gtest local, siga as instruções:

  $ g++ -Wall -std=c++11 src/main.cpp -L lib -I include -l gtest -l gtest_main -l pthread -o vector.out


Autores:
	Daniel do Nascimento Gomes
	Karine Piacentini Coelho da Costa