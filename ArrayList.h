#pragma once

#include <memory>

//arraylist template class
template <typename Type>
class ArrayList
{
private:

	static constexpr int CAPACITY_INCR = 100;

	std::unique_ptr<Type[]> m_arr = nullptr; //pointer to the array data
	int m_capacity = 0; //the current capacity of the array
	int m_size = 0; //number of elements actually stored in the array

public:

	//constructor sets the initial capacity of the arraylist
	explicit ArrayList(unsigned int capacity = CAPACITY_INCR);

	//copy constructor performs a deep copy of the data
	ArrayList(const ArrayList& other);

	//assignment operator performs a deep copy of the data
	ArrayList& operator=(const ArrayList& other);

	//default move constructor
	ArrayList(ArrayList&& arrayList) = default;

	//default move assignment operator
	ArrayList& operator=(ArrayList&& arrayList) = default;

	//destructor frees the arraylist memory
	~ArrayList();

	//returns pointer to first element
	Type* begin();
	
	//returns const pointer to first element
	const Type* begin() const;

	//returns pointer to past-the-end element
	Type* end();

	//returns const pointer to past-the-end element
	const Type* end() const;

	//access to the data through index
	Type& operator[](unsigned int index);

	//access to the data through index
	const Type& operator[](unsigned int index) const;

	//inserts a new element into the arraylist
	//if the current capacity is full, the array is reallocated
	void insert(const Type& value);

	//frees the arraylist memory, sets capacity to 0
	void clear();

	//sorts the elements in the arraylist into ascending order
	void sort();

	//returns the number of elements in the arraylist
	int getSize() const;
};

template<class Type>
inline ArrayList<Type>::ArrayList(unsigned int capacity)
{
	m_arr = std::make_unique<Type[]>(capacity);
	m_capacity = capacity;
	m_size = 0;
}

template<class Type>
inline ArrayList<Type>::ArrayList(const ArrayList<Type>& other)
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_arr = std::make_unique<Type[]>(m_capacity);

	for (int i = 0; i < m_size; ++i)
	{
		m_arr[i] = other.m_arr[i];
	}
}

template<class Type>
inline ArrayList<Type>& ArrayList<Type>::operator=(const ArrayList<Type>& other)
{
	if (m_arr != nullptr)
	{
		m_arr = nullptr;
	}

	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_arr = std::make_unique<Type[]>(m_capacity);

	for (int i = 0; i < m_size; ++i)
	{
		m_arr[i] = other.m_arr[i];
	}

	return *this;
}

template<class Type>
inline Type& ArrayList<Type>::operator[](unsigned int index)
{
	return m_arr[index];
}

template<class Type>
inline const Type& ArrayList<Type>::operator[](unsigned int index) const
{
	return m_arr[index];
}

template<class Type>
inline ArrayList<Type>::~ArrayList()
{
	clear();
}

template<typename Type>
inline Type* ArrayList<Type>::begin()
{
	return m_arr.get();
}

template<typename Type>
inline const Type* ArrayList<Type>::begin() const
{
	return m_arr.get();
}

template<typename Type>
inline Type* ArrayList<Type>::end()
{
	return m_arr.get() + m_size;
}

template<typename Type>
inline const Type* ArrayList<Type>::end() const
{
	return m_arr.get() + m_size;
}

template<class Type>
inline void ArrayList<Type>::insert(const Type& value)
{
	if (m_capacity > m_size)
	{
		m_arr[m_size] = value;
		m_size++;
	}
	else
	{
		std::unique_ptr<Type[]> newArr = std::make_unique<Type[]>(m_capacity + CAPACITY_INCR);

		for (int i = 0; i < m_size; ++i)
		{
			newArr[i] = m_arr[i];
		}

		newArr[m_size] = value;

		m_arr = std::move(newArr);

		m_size++;
		m_capacity += CAPACITY_INCR;
	}
}

template<class Type>
inline void ArrayList<Type>::clear()
{
	m_arr = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template<class Type>
inline void ArrayList<Type>::sort()
{
	for (int i = 0; i < m_size - 1; ++i)
	{
		int smallest = i;

		for (int j = i + 1; j < m_size; ++j)
		{
			if (m_arr[j] < m_arr[smallest])
			{
				smallest = j;
			}
		}

		if (i != smallest)
		{
			Type temp = m_arr[i];
			m_arr[i] = m_arr[smallest];
			m_arr[smallest] = temp;
		}
	}
}

template<class Type>
inline int ArrayList<Type>::getSize() const
{
	return m_size;
}


