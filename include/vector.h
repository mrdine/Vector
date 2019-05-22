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
	MyIterator( pointer p ): 
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
	const reference operator*( void ) const // x = *it
	{
	    return *current;
	}


	/// arrow operator: return a pointer to the location in the vector the it points to.
	/***
	 * \return pointer
	 */
	pointer operator->( void ) const
	{
	    assert( current != nullptr );
	    return current;
	}

	/// Pre-increment operator: increment iterator on one unit
	/***
	 * \return iterator incremented on one unit
	 */
	MyIterator operator++( void ) // ++it;
	{
	    this->current++;
	    return *this;
	}

	/// Pos-increment operator: increment iterator on one unit
	/***
	 * \param int only to differentiate from pre-increment operator.
	 * \return iterator before incrementation
	 */
	MyIterator operator++( int ) // it++;
	{

	    MyIterator tmp (current); // create temporary iterator
	    this->current++; // increment iterator
	    return tmp; // return it before incrementation
	}

	/// Pre-decrement operator: decrement iterator on one unit
	/***
	 * \return iterator decremented on one unit
	 */
	MyIterator operator--( void ) // --it;
	{
	    this->current--;
	    return *this;
	}

	/// Pos-decrement operator: decrement iterator on one unit
	/***
	 * \param int only to differentiate from pre-decrement operator.
	 * \return iterator before decrementation
	 */
	MyIterator operator--( int ) // it--;
	{
	    MyIterator tmp (current); // create temporary iterator
	    this->current--; // decrement iterator
	    return tmp; // return it before decrementation
	}


	/// Operator difference between two iterators.
	/***
	 * \param rhs minuend iterator.
	 * \return Difference between two iterators.
	 */
	difference_type operator-( const MyIterator &rhs ) // it = it1-it2
	{
	    return current - rhs.current;
	}

	/// Equity relational operator. 
	/***
	 * \param other iterator to be compare with.
	 * \return true if both iterators refer to the same location within the vector, and false otherwise.
	 */
	bool operator==( const MyIterator& other ) const // it1 == it2
	{
	    return this->current == other.current; 
	}

	/// Difference relational operator. 
	/***
	 * \param other iterator to be compare with.
	 * \return true if both iterators refer to a different location within the vector, and false otherwise.
	 */
	bool operator!= ( const MyIterator& other ) const // it1 != it2
	{
	    return this->current != other.current;
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


	/// Destructor
	~vector( void )
	{
	    delete [] data;
	}


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


	/// List constructor: Constructor from a initializer list
	/***
	 * \param ilist initializer list to initialize the elements of the vector with
	 */
	vector( std::initializer_list<T> ilist )
	{
	    // copy atributes from list
	    data = new T[ilist.size()];
	    m_size = ilist.size();
	    m_capacity = ilist.size();

	    // Copy elements from list
	    std::copy ( ilist.begin(), ilist.end(), data );
	}


	/// Range constructor: Constructs the vector with the contents of the range [first, last) .
	/***
	 * \param first iterator pointing to the beginning of the range to copy the elements from.
	 * \param last iterator pointing to the end of the range to copy the elements from.
	 */
	template< typename InputIt >
	vector( InputIt first, InputIt last )
	{

	    size_type dis = last - first;

	    data = new T[dis];
	    m_capacity = dis;
	    m_size = dis;

	    for( size_type i = 0; i < dis; i++ ){
		data[i] = *first;
		first++;
	    }
	}

	//=== ITERATORS

	/// Returns an iterator pointing to the first item in the list.
	/***
	 * \return first item in the list.
	 */
	iterator begin( void ) const
	{
	    return iterator( &data[0] );
	}

	/// Returns an iterator pointing the position just after the last element of the list.
	/***
	 * \return position just after the last element of the list.
	 */
	iterator end( void ) const
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
	/***
	 * \param
	 * \return
	 */
	vector& operator=( vector&& other )
	{
	    // Self-assignment detection
	    if (&other == this)
		return *this;

	    // Release any resource we're holding
	    delete[] data;

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
	    delete [] data;

	    // copy atributes from list
	    data = new T[ilist.size()];
	    m_size = ilist.size();
	    m_capacity = ilist.size();

	    // Copy elements from list
	    std::copy ( ilist.begin(), ilist.end(), data );
	}

	///=== CAPACITY METHODS

	/// Returns the number of elements in the vector.
	/***
	 * \return Vector size.
	 */
	size_type size( void ) const
	{
	    return m_size;
	}

	/// Return the internal storage capacity of the array.
	/***
	 * \return Vector storage capacity.
	 */
	size_type capacity( void ) const
	{
	    return m_capacity;
	}

	/// Return if the vector is empty or not.
	/***
	 * \return true if the container contains no elements, and false otherwise.
	 */
	bool empty( void ) const
	{
	    // Return true if vector is empty (m_size = 0)
	    if( this->m_size == 0 ) {
		return true;
	    } else {
		return false;
	    }
	}


	///=== MODIFIERS METHODS

	// Limpa todo o vetor (deve ser NULL?) e redefinindo m_size = 0
	void clear( void )
	{
	    // limpa data
	    delete[] data;

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
		if(m_capacity < count)
		{
			reserve(count);
		}

		// limpa o vector
		delete [] data;
		// aloca o espaço necessario
		data = new T[count];
		// restitui o tamanho
		m_size = count;

		// preenche o vector com o count
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


	//=== Friend functions
	/// Insertion operator: print vector to a output stream
	/***
	 * \return ostream object.
	 */
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
	friend void swap ( vector<T>& vec1, vector<T>& vec2 )
	{

	}

    private:
	pointer data; //!< Data storage area for the dynamic array.
	size_type m_size; //!< Current vector size (or index past-last valid element.
	size_type m_capacity; //!< Vector’s storage capacity.

    }; // end class vector


    /// Equity relational operator: checks if contents of lhs and rhs are equal.
    /***
     * \param lhs left hand side vector to be compare with.
     * \param rhs right hand side vector to be compare with.
     * \return true if vectors have the same size and each element in lhs compares equal with the element in rhs at the same position, false otherwise.
     */
    template <typename T>
    bool operator==( const vector<T>& lhs, const vector<T>& rhs )
    {
	if( lhs.size() != rhs.size() ){
	    return false;
	}

	for( auto i = 0; i< lhs.size(); i++ ){
	    if( lhs[i] != rhs[i]){
		return false;
	    }
	}

	return true;
    }

    
    /// Difference relational operator: checks if contents of lhs and rhs are different.
    /***
     * \param lhs left hand side vector to be compare with.
     * \param rhs right hand side vector to be compare with.
     * \return true if vectors have not the same size or there is a least one element in lhs that compares different with the element in rhs at the same position, false if they compare equal.
     */
    template <typename T>
    bool operator!=( const vector<T>& lhs, const vector<T>& rhs )
    {
	if( lhs.size() != rhs.size() ){
	    return true;
	}

	for( auto i = 0; i< lhs.size(); i++ ){
	    if( lhs[i] != rhs[i]){
		return true;
	    }
	}

	return false;

    }

} // end namespace sc
