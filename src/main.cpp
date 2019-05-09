#include <iostream>
#include "vector.h"

int main()
{
    vector<int> v;
    /*
    for( auto i{0} ; i < 20 ; i++ )
    {
        v.push_back( i+1 );
        std::cout << ">>> Array v1: " << v << std::endl;
    }

    {
        vector<int> v2{v};

        std::cout << "\n\n>>> Array v2: " << v2 << std::endl;

        v2.push_back( 100 );
    }

    v.push_back( 200 );
    std::cout << "\n\n>>> Array v1: " << v << std::endl;
    */

    /*
    //Testa a atribuição
    vector<int> c(10);
    for(int i=0; i<10; i++)
    {
      c[i] = i;
    }

    std::cout << c[7] << std::endl;

    v = c;

    std::cout << v[7] << std::endl;
    */

    //Testa o constructor de range
    vector<int> d(10);
    for(int i=0; i<10; i++)
    {
      d[i] = i;
    }

    //vector<int> x(d, std::end(d));

    //Testa o iterator
    vector<int>::iterator it;
    it = d.begin();
    std::cout << *it << std::endl;
}