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
	// Below we have the iterator_traits common interface
	typedef std::ptrdiff_t difference_type; //<! Difference type used to calculated distance between ITERATORS.
	typedef T value_type; //!< Value type the iterator points to.
	typedef T* pointer;   //!< Pointer to the value type.
	typedef T& reference; //!< Reference to the value type
	typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.

	/// Default constructor
	MyIterator( ):
	    current{nullptr}
	{ /* empty */}

	/// Constructor with a pointer parameter
	MyIterator( pointer p ): // precisa 6???????????
	    current{p}
	{ /* empty */}


	/// Copy constructor: copy iterator it to this iterator.
	/***
	 * \param it iterator to be used as source to initialize the elements of the iterator with.
	 */
	MyIterator( const MyIterator& it )
	{
	    this->current = it.current;
	}

	/// Attribution operator
	/***
	 * \param other iterator from rhs of attribution.
	 * \return lhs iterator, allowing chained attribution.
	 */
	MyIterator& operator=( const MyIterator& other ) // it1 = it2
	{
	    this->current = other.current;
	    return *this;
	}

	/// Dereference operator returning modifiable reference.
	/***
	 * \return reference to the object located at the position pointed by the iterator.
	 */
	reference operator*( void ) // *it = x
	{
	    return *current;
	}

	/// Dereference operator returning non-modifiable reference.
	/***
	 * \return reference to the object located at the position pointed by the iterator.
	 */
	const reference operator*( void ) const // x = *it // precisa dessa versão 8??????????
	{
	    return *current;
	}

	///?????????????????????? faltando
	//pointer operator->( void ) const // ????????????????????????????????? checar só copiei
	//{
	// assert( m_ptr != nullptr );
	// return m_ptr;
	//}


	MyIterator operator++( ) // ++it;
	{
	    pointer c = this->current;
	    this->current = c++;
	    return *this;
	}

	MyIterator operator++( int ) // it++;
	{
	    pointer c = this->current;
	    this->current = ++c;
	    return *this;
	}

	MyIterator operator--( ) // --it;
	{
	    pointer c = this->current;
	    this->current = c--;
	    return *this;
	}
	MyIterator operator--( int ) // it--;
	{
	    pointer c = this->current;
	    this->current = --c;
	    return *this;
	}
	/*
	MyIterator operator+( int s ) // ??????????????????????? assinatura diferente; tá sobrando?
	{
	    for(int i=0; i < s; i++)
		{
		    pointer c = this->current;
		    this->current = c++;
		}
	    return *this;
	}
	*/

	/// Operator difference between two iterators.
	/***
	 * \param rhs minuend iterator.
	 * \return Difference between two iterators.
	 */
	difference_type operator-( const MyIterator &rhs ) // it = it1-it2
	{
	    return current - rhs.current;
	}

	bool operator==( const MyIterator& other ) const
	{
	    return this->current == other.current;
	}

	bool operator!=( const MyIterator& other ) const
	{
	    if(this->current == other.current)
		{
		    return false;
		} else {return true;}

	}

	bool operator!= ( MyIterator& other ) const //????????????????????????????
	{
	    if(this->current == other.current)
		{
		    return false;
		} else {return true;}

	}

	bool operator<( const MyIterator& other ) //????????????????????????????
	{
	    if(this->current < other.current)
		{
		    return true;
		} else {
		return false;
	    }
	}

	bool operator<=( const MyIterator& other ) //????????????????????????????
	{
	    if(this->current <= other.current)
		{
		    return true;
		} else {return false;}
	}


	/// Return a iterator pointing to the n-th successor in the vector from it.
	/***
	 * \param n number of position to move
	 * \param it iterator you want operate
	 * \return n-th successor in the vector from it.
	 */
	friend MyIterator operator+( difference_type n, MyIterator it ) // n + it
	{
	    return it.current + n;
	}

	/// Return a iterator pointing to the n-th successor in the vector from it.
	/***
	 * \param n number of position to move
	 * \param it iterator you want operate
	 * \return n-th successor in the vector from it.
	 */
	friend MyIterator operator+( MyIterator it, difference_type n ) // it + n
	{
	    return it.current + n;
	}

	/// Return a iterator pointing to the n-th predecessor in the vector from it.
	/***
	 * \param n number of position to move
	 * \param it iterator you want operate
	 * \return n-th predecessor in the vector from it.
	 */
	friend MyIterator operator-( difference_type n, MyIterator it ) // n - it
	{
	    return it.current - n;
	}

	/// Return a iterator pointing to the n-th predecessor in the vector from it.
	/***
	 * \param n number of position to move
	 * \param it iterator you want operate
	 * \return n-th predecessor in the vector from it.
	 */
	friend MyIterator operator-( MyIterator it, difference_type n ) // it - n
	{
	    return it.current - n;
	}

    private:
	T *current;
    };


    template < typename T >
    class vector {

    public:

	using size_type = unsigned long; //!< The size type.
	using pointer = T*;   //!< Pointer to a value stored in the container.
	using reference = T&; //!< Reference to a value stored in the container.
	using const_reference = const T&; //!< Const reference to a value stored in the container.
	using iterator = MyIterator< T >;
	using const_iterator = MyIterator< const T >;


	//=== SPECIAL MEMBERS


	/// Default constructor: construct a empty vector with capacity count
	/***
	 * \param count size of vector to be initialize
	 */
	explicit vector( size_type count = 0 ) :
	    data{ new T[ count ] },
	    m_size{ 0 },
	    m_capacity{ count }
	{ /* empty */ }


	/// Copy constructor: copy vector source to this vector
	/***
	 * \param source vector to be used as source to initialize the elements of the vector with.
	 */
	vector( const vector& source )
	    : m_size { source.m_size },
	    m_capacity { source.m_capacity }
	{
	    // [1] Alocar o espaço de dados.
	    data = new T[ m_capacity ];
	    // [2] Copiar os elementos do source para o atual (this).
	    std::copy( &source.data[0], &source.data[m_size], data );
	}

  /*
   * Precisa???
  /// Move constructor: move this vector source to other vector
  vector(vector&& other):
      data{ other.data},
      m_capacity{ other.m_capacity},
      m_size{ other.m_size }
  {
    // resets the other vector
    other.m_size = 0;
    other.m_capacity = 0;
		other.data = nullptr;
  }
  */


	/// List constructor: Constructor from a initializer list
	/***
	 * \param ilist initializer list to initialize the elements of the vector with
	 */
	vector( std::initializer_list<T> ilist )
	{
	    // copy atributes from list
	    data = new T[ilist.size()];
	    m_size = ilist.size();
	    m_capacity = ilist.size(); // capacidade dobrada 1???????????? se não for arrumar no range constructor também

	    // Copy elements from list
	    std::copy ( ilist.begin(), ilist.end(), data ); // Pode 4???????????
	}


	/// Destructor
	~vector( void )
	{
	    delete [] data;
	}

	// 3?????????????????????????? faltando...
	// vector( vector && );


	/// Range constructor: Constructs the vector with the contents of the range [first, last) .
	/***
	 * \param first iterator pointing to the beginning of the range to copy the elements from.
	 * \param last iterator pointing to the end of the range to copy the elements from.
	 */
	//template< typename InputIt > /// 5????????? na pg 12 tem um template lá... pq????
	vector( iterator first, iterator last )
	{

	    // size_type dis = distance(first, last); // modifiquei 9?????????
	    size_type dis = last - first;

	    data = new T[2*dis];
	    m_capacity = 2*dis;
	    m_size = dis;

	    /* testes, apagar depois
	    std::cout << "\n\n size: " << dis << std::endl;
	    std::cout << "first: " << *first << std::endl;
	    std::cout << "last: " << *last << std::endl;
	    */
	    for( size_type i = 0; i < dis; i++ ){
		data[i] = *first;
		first++;
		//std::cout << "\n\n data[" << i << "]: " << data[i] << std::endl; // testes, apagar depois
	    }
	    //std::cout << "fim\n" << std::endl; // testes, apagar depois
	}

	//=== ITERATORS

	/// Returns an iterator pointing to the first item in the list.
	/***
	 * \return first item in the list.
	 */
	iterator begin( void )
	{
	    return iterator( &data[0] );
	}

	/// Returns an iterator pointing the position just after the last element of the list.
	/***
	 * \return position just after the last element of the list.
	 */
	iterator end( void )
	{
	    return iterator( &data[m_size] );
	}

	const_iterator cbegin( void ) const
	{
	    return const_iterator(data);
	}

	const_iterator cend( void ) const
	{
	    iterator endV(&data[m_size]);
	    const_iterator cendV = endV;
	    return cendV;
	}

	//=== OPERATORS

	/// Attribution Operator. Vector receve rhs.
	/***
	 * \param rhs vector from rhs of attribution.
	 * \return lhs vector, allowing chained attribution.
	 */
	vector& operator=( const vector& rhs )
	{
	    // copy atributes
	    m_size = rhs.m_size;
	    m_capacity = rhs.m_capacity;

	    delete [] this->data;
	    this->data = new T[ m_capacity ]; // reallocate new data

	    // copy data to the object that required the methold
	    std::copy(&rhs.data[0], &rhs.data[m_size], data);

	    return *this;
	}

  /// Move AssignOperator
  vector& operator=(vector&& other)
  {
    // Self-assignment detection
		if (&other == this)
			return *this;

		// Release any resource we're holding
		delete data;

		// Transfer ownership of a.m_ptr to m_ptr
		data = other.data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    // resets the other vector
    other.m_size = 0;
    other.m_capacity = 0;
		other.data = nullptr;

		return *this;
  }

  /// initializer_list assigment operator
  vector& operator=( std::initializer_list<T> ilist )
  {
    // resets vector
    delete data;
    // copy atributes from list
    data = new T[ilist.size()];
    m_size = ilist.size();
    m_capacity = ilist.size(); // capacidade dobrada 1???????????? se não for arrumar no range constructor também

    // Copy elements from list
    std::copy ( ilist.begin(), ilist.end(), data ); // Pode 4???????????
  }

	//Operador ==
	bool operator==( const vector& other ) const
	{
	    //Ponteiro para this->data
	    T* myData = data;
	    //Ponteiro para data do vector other
	    T* otherData = other.data;

	    //Se o tamanho do meu vector for igual ao do outro vector, então analisar cada valor do myData com a respectiva posição do otherData
	    if(m_size == other.m_size)
		{
		    //Contar até o ultimo elemento
		    size_type contador = 0;
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
		    size_type contador = 0;
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

	///=== CAPACITY METHODS

	//Retorna o tamanho do vector (tamanho do espaço preenchido)
	size_type size( void ) const
	{
	    return m_size;
	}

	//Retorna a capacidade total do vector
	size_type capacity( void ) const
	{
	    return m_capacity;
	}

	// Retorna true se o vector está vazio (m_size = 0), e false, caso contrário
	bool empty( void ) const
	{
	    if(this->m_size == 0)
		{
		    return true;
		} else {return false;}
	}


	///=== MODIFIERS METHODS
	//Retorna o numero de saltos do first até o last, se first > last, retorna negativamente o numero de saltos de last até first
	size_type distance( iterator first, iterator last ) // pq isso? 7???????????
	{
	    /*
	     * Lançando exceção quando não deveria
	     if(first < last)
	     {
	     size_type dis = 0;
	     iterator it;
	     for(it = first; it != last; it++)
	     {
	     dis++;
	     }
	     return dis;
	     }
	     else
	     {
	     throw std::invalid_argument("foi passado o first > last");
	     }
	    */
	    size_type dis = 0;
	    iterator it;
	    for(it = first; it != last; it++)
		{
		    dis++;
		}
	    return dis;

	}

	// Limpa todo o vetor (deve ser NULL?) e redefinindo m_size = 0
	void clear( void )
	{
      // limpa data
	    delete data;

      // Aloca a capacidade antiga do vector
      data = new T[ m_capacity ];

      m_size = 0;
	}

	//Insere elemento na frente do vector
	void push_front( const T& value )
	{

	    // Verificar se tem espaço para receber o novo elemento.
	    if ( m_size == m_capacity )
		{
		    std::cout << "[push_front] : capacity = " << m_capacity << ", estou dobrando...\n";
		    reserve( ( m_capacity == 0 ) ? 1 : (2 * m_capacity) );
		}

	    T* it = &data[m_size];

	    for(size_type i = 0; i < m_size; i++)
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
	void pop_front( void )
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
	void pop_back( void )
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
	iterator insert ( iterator position, const T& val )
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
		    size_type d = 0;
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

	// ?????????????????????????????? terminar
	template < typename InItr >
	iterator insert( iterator pos, InItr first, InItr last )
	{

	}

	// ????????????????????? falta um insert ver pg 12 l 43

	/// Aumenta a capacidade de armazenamento do vector para o valor `new_cap` fornecido.
	void reserve( size_type new_cap )
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
	void shrink_to_fit( void )
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

	/// Repreenche o vector com count vezes o valor value;
	void assign( size_type count, const T & value )
	{
	    m_size = count;
	    for(size_type i = 0; i < count; i++)
		{
		    data[i] = value;
		}
	}

	// ???????????????????????? assinatura diferente, pq?
	/// Repreenche o vetor com copia dos elementos na lista ilist
	void assign( std::initializer_list<T> ilist )
	{
	    //Reservar espaço, se não houver
	    reserve(ilist.size() * 2);
	    //Atribui novo tamanho do vector
	    m_size = ilist.size();

	    std::copy ( ilist.begin(), ilist.end(), data );


	}

	/// Repreenche o vector com copia dos elementos do range [first, last) (Não entendi)
	template < typename InItr >
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
	    for(size_type i = 0; i < m_size; i++)
		{
		    data[i] = *first;
		    first++;
		}

	}

	//Apaga um elemento do vector na posição dada pelo iterator it, se it < last_element, após a remoção os elementos a partir do sucessor do it serão deslocados, caso contrário (it == last_element), o valor será dito como NULL ou 0?
	iterator erase( iterator it )
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


	iterator erase( iterator first, iterator last )
	{
	    size_type apagados = 0;
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


	//=== ELEMENT ACCESS METHODS


	const T& back( void ) const
  {
    return data[m_size-1];
  }

	T& back( void )
	{
	    return data[m_size-1];
	}


	const T& front( void ) const
  {
    return data[0];
  }

	T& front( void )
	{
	    return data[0];
	}


	// Operador[], se o pos for menor que 0 ou maior que o tamanho do vector, é lançada uma exceção "out_of_range"
	T& operator[]( size_type pos )
	{
	    return data[pos];
	}

	const T& operator[]( size_type pos ) const
	{
	    const T& result = data[pos];
	    return result;
	}

	T& operator[](iterator it)
	{
	    return *it;
	}

	T& at( size_type pos )
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

	const T& at( size_type pos ) const
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

	//???????????????????????? tem dois data faltando pg 13 l63 e 64


	// Friend functions
	friend std::ostream& operator<<( std::ostream& os, const vector& v )
	{
	    os << "[ ";
	    std::copy( &v.data[0], &v.data[v.m_size], std::ostream_iterator<T>( os, " " ));
	    os << "| ";
	    std::copy( &v.data[v.m_size], &v.data[v.m_capacity], std::ostream_iterator<T>( os, " " ));
	    os << "]";

	    return os;
	}

	// ??????????????????/ falta friend function swap pg 13 l 68


    private:
	pointer data; //!< Data storage area for the dynamic array. // usar unique_ptr 2????????????
	size_type m_size; //!< Current vector size (or index past-last valid element.
	size_type m_capacity; //!< Vector’s storage capacity.

    }; // end class vector

} // end namespace sc
