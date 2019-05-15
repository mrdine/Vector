
#include <iostream>
#include "../include/vector.h"



//int main()
//{
    //vector<int> v;
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

    /*
    //Testa o constructor de range
    vector<int> d(10);
    for(int i=0; i<10; i++)
    {
      d[i] = i+1;
    }

    vector<int> k(5);
    for(int i=0; i<10; i++)
    {
      k[i] = i+1;
    }

    //Testa o iterator
    vector<int>::iterator it;
    it = d.begin();
    std::cout<< d.distance(d.begin(), d.end()) << std::endl;
    vector<int> x(k.begin(), k.end());

    std::cout << x[4] << std::endl;

    //Testa o begin() e end()
    for(auto it = d.begin(); it != d.end(); it++)
    {
      std::cout << *it << std::endl;
    }
    */

    /*
    //Testa o empty(), size() e capacity();
    vector<int> e(10);
    for(int i=0; i<10; i++)
    {
      e[i] = i+1;
    }

    vector<int> vazio;
    std::cout << vazio.empty() << " ," <<  e.empty() << std::endl;

    std::cout << e.size() << " ," << e.capacity() << std::endl;
    */

    //Testa o push_front()
    /*
    vector<int> h(5);
    for(int i=0; i<5; i++)
    {
      h[i] = i+1;
    }

    for(int i=0; i<h.size(); i++)
    {
      std::cout << h[i] << std::endl;
    }
    std::cout << " " << std::endl;

    h.push_front(7);

    for(int i=0; i<h.size(); i++)
    {
      std::cout << h[i] << std::endl;
    }
    std::cout << " " << std::endl;

    // Testa o push_back()
    h.push_back(7);

    for(int i=0; i<h.size(); i++)
    {
      std::cout << h[i] << std::endl;
    }
    std::cout << " " << std::endl;

    // Testando eraser()
    vector<int>::iterator il = h.begin();
    h.erase(il++);

    for(int i=0; i<h.size(); i++)
    {
      std::cout << h[i] << std::endl;
    }
    std::cout << " " << std::endl;

    // Testando o pop_front()
    h.pop_front();

    for(int i=0; i<h.size(); i++)
    {
      std::cout << h[i] << std::endl;
    }
    std::cout << " " << std::endl;

    h.push_front(7);

    for(int i=0; i<h.size(); i++)
    {
      std::cout << h[i] << std::endl;
    }
    std::cout << " " << std::endl;

    // Testando operadores == e !=
    vector<int> eq {1,2,3,4,5};
    vector<int> differ{1,2,3,4,5};
    //Por initializer_list não está dando certo
    bool ue = eq == differ;
    std::cout << ue << std::endl;

    vector<int>bla(3);
    bla[0] = 1;
    bla[1] = 2;
    bla[2] = 3;
    vector<int>ble = bla;
    ue = ble == bla;
    std::cout << ue << std::endl;
    std::cout << eq.size() << ", " << differ.size() << std::endl;
    */

    // testa o insert()
    /*
    vector<int>ins;
    for(auto i{0}; i<10; i++)
    {
      ins.push_back(i+1);
    }

    vector<int>::iterator itsert = ins.end();

    for(auto i{0}; i<10; i++)
    {
      std::cout << ins[i] << std::endl;
    }

    ins.insert(itsert, 11);

    for(auto i{0}; i<11; i++)
    {
      std::cout << ins[i] << std::endl;
    }
    */

    // Testa o assign()
    /*
    ins.assign(7,7);

    for(auto i{0}; i<7; i++)
    {
      std::cout << ins[i] << std::endl;
    }
    std::cout << ins.size() << std::endl;


    vector<int>noovo(10);
    for(auto i{0}; i<10; i++)
    {
      noovo.push_back(i+1);
    }
    //vector<int>::iterator be = noovo.begin();
    //vector<int>::iterator en = noovo.end();

    vector<int>ola(10);
    //ola.insert(be, en);
    for(auto i{0}; i<10; i++)
    {
      std::cout << ola[i] << std::endl;
    }

    ola.assign({1,2,3,4,5,6,7});
    for(auto i{0}; i<10; i++)
    {
      std::cout << ola[i] << std::endl;
    }
    */
    /*
    //Testa o shrink_to_fit()

    vector<int> shrink(10);
    std::cout << shrink.capacity() << std::endl;
    for(auto i{0}; i<10; i++)
    {
      shrink[i] = i+1;
    }

    std::cout << shrink.capacity() << std::endl;
    std::cout << shrink.size() << std::endl;
    shrink.shrink_to_fit();
    std::cout << shrink.capacity() << std::endl;



    shrink.erase(shrink.begin(), shrink.end());
    std::cout << shrink.size() << std::endl;
    */
//}
