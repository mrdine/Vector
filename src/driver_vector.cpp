/*
#include <iostream>
#include <algorithm> // std::copy

template < typename T >
class vector {

    public:
        vector( size_t count=0 ) :
            data{ new T[ 2*count ] },
            size{ count },
            capacity{ 2*count }
        {  }

        vector( const vector& source )
            : size { source.size },
            capacity { source.capacity }
        {
             // [1] Alocar o espaço de dados.
             data = new T[ capacity ];
             // [2] Copiar os elementos do source para o atual (this).
             std::copy( &source.data[0], &source.data[size], data );
        }

        vector& operator=( const vector& rhs )
        {
        }

        ~vector()
        {
            delete [] data;
        }



        void push_back( const T & value )
        {
            // Verificar se tem espaço para receber o novo elemento.
            if ( size == capacity )
            {
                std::cout << "[push_back] : capacity = " << capacity << ", estou dobrando...\n";
                reserve( ( capacity == 0 ) ? 1 : (2 * capacity) );
            }

            // Inserir normalmente.
            data[size++] = value;
            //*begin() = value;
        }

        /// Aumenta a capacidade de armazenamento do vector para o valor `new_cap` fornecido.
        void reserve( size_t new_cap )
        {
            // Se a capacidade nova < capacidade atual, não faço nada.
            if ( new_cap <= capacity ) return;

            // Passo 1: alocar nova memória com tamanho solicitado.
            T * temp = new T[ new_cap ];

            // Passo 2: copiar os dados da memória antiga para a nova.
            std::copy( &data[0], &data[size],  temp );
            //std::copy( begin(), end(), temp );

            // Passo 3: Liberar a memória antiga.
            delete[] data;

            // Passo 4: Redirecionar ponteiro para a nova (maior) memória.
            data = temp;

            // Passo 5: Atualizações internas.
            capacity = new_cap;
        }

        friend std::ostream& operator<<( std::ostream& os, const vector& v )
        {
            os << "[ ";
            std::copy( &v.data[0], &v.data[v.size], std::ostream_iterator<T>( os, " " ));
            os << "| ";
            std::copy( &v.data[v.size], &v.data[v.capacity], std::ostream_iterator<T>( os, " " ));
            os << "]";

            return os;
        }

    private:
        T * data; //!< Area de armazenamento.
        size_t size; //!< Número de elementos atualmente no vector.
        size_t capacity; //!< Capacidade máxima (atual) do vector.
};

int main()
{
    vector<int> v;

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
}
*/
