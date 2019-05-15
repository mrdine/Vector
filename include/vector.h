#include <iostream>
#include <algorithm> // std::copy
#include <iterator>
#include <initializer_list> // std::initializer_list
#include <stdexcept>

namespace sc {


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

    MyIterator& operator= (const MyIterator& other)
    {
      this->current = other.current;
      return *this;
    }


    bool operator== (const MyIterator& other) const
    {
      return this->current == other.current;
    }

    bool operator!= (const MyIterator& other) const
    {
      if(this->current == other.current)
      {
        return false;
      } else {return true;}

    }

    bool operator!= (MyIterator& other) const
    {
      if(this->current == other.current)
      {
        return false;
      } else {return true;}

    }


    MyIterator operator+(int s)
    {
      for(int i=0; i < s; i++)
      {
        pointer c = this->current;
        this->current = c++;
      }
      return *this;
    }

    MyIterator operator++ ()
    {
      pointer c = this->current;
      this->current = c++;
      return *this;
    }

    MyIterator operator++ ( int )
    {
      pointer c = this->current;
      this->current = ++c;
      return *this;
    }

    MyIterator operator-- ()
    {
      pointer c = this->current;
      this->current = c--;
      return *this;
    }
    MyIterator operator -- ( int )
    {
      pointer c = this->current;
      this->current = --c;
      return *this;
    }

    bool operator<(const MyIterator& other)
    {
      if(this->current < other.current)
      {
        return true;
      } else {return false;}
    }

    bool operator<=(const MyIterator& other)
    {
      if(this->current <= other.current)
      {
        return true;
      } else {return false;}
    }

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

    private:
        T * data; //!< Area de armazenamento.
        size_t m_size; //!< Número de elementos atualmente no vector.
        size_t m_capacity; //!< Capacidade máxima (atual) do vector.

    public:

      using iterator = MyIterator< T >;
      using const_iterator = MyIterator< const T >;



      typedef T* pointer;

      //Construtor que serve como padrão e por tamanho
      vector( size_t count=0 ) :
          data{ new T[ 2*count ] },
          m_size{ count },
          m_capacity{ 2*count }
      { /* empty */ }

      //Construtorr que copia do vector source para esse vector
      vector( const vector& source )
          : m_size { source.m_size },
          m_capacity { source.m_capacity }
      {
           // [1] Alocar o espaço de dados.
           data = new T[ m_capacity ];
           // [2] Copiar os elementos do source para o atual (this).
           std::copy( &source.data[0], &source.data[m_size], data );
      }

      //Construtor que cria copiando os dados de um range
      vector(iterator first, iterator last)
      {
        size_t dis = distance(first, last);
        data = new T[2*dis];
        m_capacity = 2*dis;

        for(size_t i = 0; i < dis; i++)
        {
          data[i] = *first;
          first++;
        }
      }
      //Construtor a partir de lista inicializadora
      vector( std::initializer_list<T> ilist )
      {
        // determinar o menor tamanho para garantir que
        // não vamos gerar segfault.
        auto limit = std::min( ilist.size(), m_size);
        // Copiar os elementos do clone.
        data = new T[2*ilist.size()];
        m_size = ilist.size();
        m_capacity = 2*ilist.size();

        std::copy ( ilist.begin(), ilist.begin()+limit, data );
      }

      //destrutor
      ~vector()
      {
          delete [] data;
      }


      //=== ITERATORS

      iterator begin() const
      {
        return iterator(data);
      }

      iterator end() const
      {
        iterator endV(&data[m_size]);
        return endV;
      }

      const_iterator cbegin() const
      {
        return const_iterator(data);
      }

      const_iterator cend() const
      {
        iterator endV(&data[m_size]);
        const_iterator cendV = endV;
        return cendV;
      }

      //=== OPERATORS ////

      //Operador =, esse vector recebe rhs
      vector& operator=( const vector& rhs )
      {
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;

        delete [] this->data;
        this->data = new T[ m_capacity ];

        std::copy(&rhs.data[0], &rhs.data[m_size], data);
      }


      //Operador ==
      bool operator==(const vector& other) const
      {
        //Ponteiro para this->data
        T* myData = data;
        //Ponteiro para data do vector other
        T* otherData = other.data;
        //Se o tamanho do meu vector for igual ao do outro vector, então analisar cada valor do myData com a respectiva posição do otherData
        if(m_size == other.m_size)
        {
          //Contar até o ultimo elemento
          size_t contador = 0;
          while(contador < m_size)
          {
            //Se o valor do myData for diferente do otherData na respectiva posição, então retornar false
            if(myData[contador] != otherData[contador])
            {
              return false;
            }
            contador++;
          }
          return true;
        } else {return false;}
      }

      //Operador !=
      bool operator !=(const vector& other) const
      {
        //Ponteiro para this->data
        T* myData = data;
        //Ponteiro para data do vector other
        T* otherData = other.data;
        //Se o tamanho do meu vector for igual ao do outro vector, então analisar cada valor do myData com a respectiva posição do otherData
        if(m_size == other.m_size)
        {
          //Contar até o ultimo elemento
          size_t contador = 0;
          while(contador < m_size)
          {
            //Se o valor do myData for diferente do otherData na respectiva posição, então retornar true
            if(*myData != *otherData)
            {
              return true;
            }
            myData++;
            otherData++;
            contador++;
          }
          return false;
        } else {return true;}
      }

      ///=== CAPACTIY METHODS

      //Retorna true se o vector está vazio (m_size = 0), e false, caso contrário
      bool empty() const
      {
        if(this->m_size == 0)
        {
          return true;
        } else {return false;}
      }

      //Retorna o tamanho do vector (tamanho do espaço preenchido)
      size_t size() const
      {
        return m_size;
      }

      //Retorna a capacidade total do vector
      size_t capacity() const
      {
        return m_capacity;
      }

      /// ELEMENT ACCESS METHOS

      //Operador[], se o pos for menor que 0 ou maior que o tamanho do vector, é lançada uma exceção "out_of_range"
      T& operator[](size_t pos)
      {
          return data[pos];
      }

      const T& operator[](size_t pos) const
      {
          const T& result = data[pos];
          return result;
      }

      T& at(size_t pos)
      {
        if(pos >= 0 && pos < m_size)
        {
          return data[pos];
        }
        else
        {
          throw std::out_of_range("out of range");
        }
      }

      const T& at(size_t pos) const
      {
        if(pos >= 0 && pos < m_size)
        {
          const T result = data[pos];
          return result;
        }
        else
        {
          throw std::out_of_range("out of range");
        }
      }

      T& operator[](iterator it)
      {
        return *it;
      }

      T& front() const
      {
        return data[0];
      }

      T& back() const
      {
        return data[m_size-1];
      }

      /// MODIFIERS METHODS
      //Retorna o numero de saltos do first até o last, se first > last, retorna negativamente o numero de saltos de last até first
      size_t distance(iterator first, iterator last)
      {
        size_t dis = 0;
        iterator it = first;
        if(last < first)
        {
          return dis;
        }
        else
        {
          while(it != last)
          {
            dis += 1;
            it++;
          }
          return dis/2 + 1 ;
        }
      }

      //Limpa todo o vetor (deve ser NULL?) e redefinindo m_size = 0
      void clear()
      {
        for(auto i = 0; i < m_size; i++)
        {
          data[i] = NULL;
        }
        m_size = 0;
      }

      //Insere elemento na frente do vector
      void push_front(const T& value)
      {

        // Verificar se tem espaço para receber o novo elemento.
        if ( m_size == m_capacity )
        {
            std::cout << "[push_front] : capacity = " << m_capacity << ", estou dobrando...\n";
            reserve( ( m_capacity == 0 ) ? 1 : (2 * m_capacity) );
        }

        T* it = &data[m_size];

        for(size_t i = 0; i < m_size; i++)
        {
          *it = *(it-1);
          it--;
        }

        //Inserir na posição normalmente
        data[0] = value;
        //Somar 1 ao tamanho
        m_size++;
      }

      //Insere elemento atrás do vector
      void push_back( const T& value )
      {
          // Verificar se tem espaço para receber o novo elemento.
          if ( m_size == m_capacity )
          {
              std::cout << "[push_back] : capacity = " << m_capacity << ", estou dobrando...\n";
              reserve( ( m_capacity == 0 ) ? 1 : (2 * m_capacity) );
          }

          // Inserir normalmente.
          data[m_size] = value;
          // Somar 1 ao tamanho
          m_size++;
      }

      //Apaga o primeiro elemento do vector apenas deslocando menos uma posição a partir do segundo elemento até o ultimo
      void pop_front()
      {
        //Apaga somente se o vector não for vazio
        if(m_size > 0)
        {
          //Ponteiro que aponta para o segundo elemento do vector
          T* ptr = data+1;
          //Deslocar menos uma posição do segundo elemento até o ultimo;
          while(ptr != data+(m_size))
          {
            *(ptr-1) = *ptr;
            ptr++;
          }
          //Reduz tamanho do vector
          m_size--;
        }
      }

      //Apaga o ultimo elemento do vector
      void pop_back()
      {
        //Apagar apenas se o tamanho do vector for maior que 0
        if(m_size > 0)
        {
        //Destroi (atribuindo 0?) o ultimo elemento
        data[m_size-1] = 0;

        //Reduz o tamanho
        m_size--;
        }
      }

      /// Inserir elemento numa posição especifica
      iterator insert (iterator position, const T& val)
      {
        //reservar espaço para inserçao
        if ( m_size == m_capacity )
        {
            std::cout << "[push_back] : capacity = " << m_capacity << ", estou dobrando...\n";
            reserve( ( m_capacity == 0 ) ? 1 : (2 * m_capacity) );
        }

        if(position == this->begin())
        {
          //Realocar os elementos
          T* count =  data+(m_size-1);
          while(count >= data)
          {
            *(count+1) = *count;
            count--;
          }
          data[0] = val;
          m_size++;

          return position;
        }
        else
        {
          size_t d = 0;
          //Saber a posição para inserir o lemento no data
          for(iterator it = this->begin();it != position; it++)
          {
            d++;
          }

          T* count = data+(m_size-1);
          while(count >= data + (d-1))
          {
            *(count+1) = *count;
            count--;
          }

          data[d-1] = val;
          m_size++;

          iterator inserted(data+(d-1));
          return inserted;
        }
      }

      template < typename InItr>
      iterator insert( iterator pos, InItr first, InItr last )
      {

      }

      /// Repreenche o vector com count vezes o valor value;
      void assign( size_t count, const T & value )
      {
        m_size = count;
        for(size_t i = 0; i < count; i++)
        {
          data[i] = value;
        }
      }

      /// Repreenche o vector com copia dos elementos do range [first, last) (Não entendi)
      template < typename InItr>
      void assign( InItr first, InItr last )
      {
        //Contar distancia entre first e last
        int siz = 0;
        InItr count = first;
        while (count != last)
        {
          siz++;
          count++;
        }

        //Atribuir novo tamanho do vector
        m_size = siz;

        //Repreencher o vector
        for(size_t i = 0; i < m_size; i++)
        {
          data[i] = *first;
          first++;
        }

      }

      /// Repreenche o vetor com copia dos elementos na lista ilist
      void assign( std::initializer_list<T> ilist )
      {
        //Reservar espaço, se não houver
        reserve(ilist.size() * 2);
        //Atribui novo tamanho do vector
        m_size = ilist.size();

        std::copy ( ilist.begin(), ilist.end(), data );


      }


      /// Aumenta a capacidade de armazenamento do vector para o valor `new_cap` fornecido.
      void reserve( size_t new_cap )
      {
          // Se a capacidade nova < capacidade atual, não faço nada.
          if ( new_cap <= m_capacity ) return;

          // Passo 1: alocar nova memória com tamanho solicitado.
          T * temp = new T[ new_cap ];

          // Passo 2: copiar os dados da memória antiga para a nova.
          std::copy( &data[0], &data[m_size],  temp );
          //std::copy( begin(), end(), temp );

          // Passo 3: Liberar a memória antiga.
          delete[] data;

          // Passo 4: Redirecionar ponteiro para a nova (maior) memória.
          data = temp;

          // Passo 5: Atualizações internas.
          m_capacity = new_cap;
      }

      // Remove a capacidade não usada de memória, transforma a capacidade em size()
      void shrink_to_fit()
      {
        //Alocar nova memória com capacidade de size()
        T * temp = new T[m_size];
        //Copiar dados para nova memória
        std::copy(&data[0], &data[m_size], temp);
        //Deletar antiga memória
        delete[] data;
        //Atribuir nova memória e nova capacidade
        data = temp;
        m_capacity = m_size;
      }



      //Apaga um elemento do vector na posição dada pelo iterator it, se it < last_element, após a remoção os elementos a partir do sucessor do it serão deslocados, caso contrário (it == last_element), o valor será dito como NULL ou 0?
      iterator erase(iterator it)
      {
        //Iterador para a posição do ultimo elemento
        iterator last_element = data+(m_size-1);
        //Se it < last_element, então deslocar menos uma posição os valores começando do it++ até last_element, e então reduzir o size (tamanho) do vector
        if(it < last_element)
        {
            T* ptr = &(*it);
            while(ptr < data+(m_size-1))
            {
              *ptr = *(ptr+1);
              ptr++;
            }

          m_size--;
          return it;
        }
        //Se it == last_element, apenas deletar o valor (atribuindo 0?) e reduzindo o tamanho do vector
        else if(it == last_element)
        {

          *(data + m_size-1) = T();

          m_size--;
          return this->end();
        }
        else
        {
          throw std::out_of_range("out of range");
        }
      }


      iterator erase(iterator first, iterator last)
      {
        size_t apagados = 0;
        if(first < last)
        {
          //conta quantos serão apagados
          iterator it = first;
          while(it != last)
          {
            apagados++;
            it++;
          }
          it = first;
          //Realoca os elementos
          while(last != this->end())
          {
            *it = *last;
            last++;
            it++;
          }
          m_size = m_size - apagados;
          return first;
        }
        else
        {
          throw std::range_error("last < first");
        }
      }

      friend std::ostream& operator<<( std::ostream& os, const vector& v )
      {
          os << "[ ";
          std::copy( &v.data[0], &v.data[v.m_size], std::ostream_iterator<T>( os, " " ));
          os << "| ";
          std::copy( &v.data[v.m_size], &v.data[v.m_capacity], std::ostream_iterator<T>( os, " " ));
          os << "]";

          return os;
      }

};
}
