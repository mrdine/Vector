#include <iostream>
#include <algorithm> // std::copy
#include <iterator>
#include <initializer_list> // std::initializer_list

/// === ITERATOR
template <typename T>
class MyIterator {
  public:
    //Below we have the iterator_traits common interface
    /// Difference type used to calculated distance between ITERATORS
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.

    using iterator = MyIterator< T >;
    using const_iterator = MyIterator< const T >;
    //deve ter begin(), end(), cbegin(), cend()

    //Construtor padrão
    MyIterator():
      current{nullptr}
      { /* empty */}

    //Construtor recebendo ponteiro
    MyIterator(pointer p):
      current{p}
      { /* empty */}

      /*
    //Construtor recebendo iterator
    MyIterator(iterator& it):
      {
        this->current = it.current;
      }
      */
    reference operator* ()
    {
      return *current;
    }

    reference operator= (iterator other)
    {
      this->current = other.current;
    }


    MyIterator operator++ ();
    MyIterator operator++ ( int );
    MyIterator operator-- ();
    MyIterator operator -- ( int );

    template<class V>
    friend MyIterator operator+(difference_type, MyIterator);
    template<class V>
    friend MyIterator operator+(MyIterator, difference_type);

    template<class V>
    friend MyIterator operator-(difference_type, MyIterator);
    template<class V>
    friend MyIterator operator-(MyIterator, difference_type);

  private:
    T *current;
  };


template < typename T >
class vector {

    public:

      using iterator = MyIterator< T >;
      using const_iterator = MyIterator< const T >;

      typedef T* pointer;

        //Construtor que serve como padrão e por tamanho
        vector( size_t count=0 ) :
            data{ new T[ 2*count ] },
            size{ count },
            capacity{ 2*count }
        { /* empty */ }

        //Construtorr que copia do vector source para esse vector
        vector( const vector& source )
            : size { source.size },
            capacity { source.capacity }
        {
             // [1] Alocar o espaço de dados.
             data = new T[ capacity ];
             // [2] Copiar os elementos do source para o atual (this).
             std::copy( &source.data[0], &source.data[size], data );
        }

        //Construtor que cria copiando os dados de um range
        vector(T* first, T* last)
        {
          if(first <= last)
          {
            this->data = new T[0];
            this->size = 0;
            this->capacity = 0;
          }
          else
          {
            std::copy(first, last, data);
          }
        }
        //Construtor a partir de lista inicializadora
        vector( std::initializer_list<T> ilist )
        {
          // determinar o menor tamanho para garantir que
          // não vamos gerar segfault.
          auto limit = std::min( ilist.size(), size);
          // Copiar os elementos do clone.
          std::copy ( ilist.begin(), ilist.begin()+limit, data );
        }

        //destrutor
        ~vector()
        {
            delete [] data;
        }

        //=== ITERATORS
        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

        //=== OPERATORS ////
        //Operador =, esse vector recebe rhs
        vector& operator=( const vector& rhs )
        {
          size = rhs.size;
          capacity = rhs.capacity;

          delete [] this->data;
          this->data = new T[ capacity ];

          std::copy(&rhs.data[0], &rhs.data[size], data);
        }

        //Operador []
        T& operator[](size_t pos)
        {
          return data[pos];
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
