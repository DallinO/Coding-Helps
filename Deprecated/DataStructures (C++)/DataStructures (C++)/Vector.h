#pragma once

namespace Custom
{
	template<typename T>
	class Vector
	{
	public:
		Vector();
		Vector(size_t size);
		Vector(size_t size, const T& value);
		Vector(const Vector<T>& rhs);
		Vector(Vector<T>&& rhs) noexcept;
		~Vector();

		Vector& operator = (const Vector& rhs)
		{
			if (this != &rhs)
			{

				T* newData = new T[rhs._size];

				for (size_t i = 0; i < rhs._size; ++i)
				{
					newData[i] = rhs._data[i];
				}

				delete[] _data;
				_data = newData;
				_size = rhs._size;
				_capacity = rhs._capacity;
			}
			return *this;
		}

		bool operator == (const Vector& rhs) const
		{
			if (_size != rhs._size)
				return false;
			for (size_t i = 0; i < _size; ++i)
			{
				if (_data[i] != rhs._data[i])
					return false;
			}

			return true;
		}
		
		bool operator != (const Vector& rhs) const { return !(*this == rhs); }

		T& operator [] (int i) { return _data[i]; }
		const T& operator[] (int i) const { return _data[i]; }

		void reserve(size_t new_capacity)
		{
			if (new_capacity > _capacity)
			{
				T* new_block = new T[new_capacity];
				for (size_t i = 0; i < _size; ++i)
				{
					new_block[i] = _data[i];
				}

				delete[] _data;
				_data = new_block;
				_capacity = new_capacity;
			}
		}

		void shrink_to_fit()
		{
			if (_capacity > _size)
			{
				T* new_block = new T[_size];
				for (size_t i = 0; i < _size; ++i)
				{
					new_block[i] = _data[i];
				}

				delete[] _data;
				_data = new_block;
				_capacity = _size;
			}
		}

		void clear()
		{
			for (size_t i = 0; i < _size; ++i)
			{
				_data[i].~T();
			}

			_size = 0;
		}

		void push_back(T element)
		{
			if (_size >= _capacity)
			{
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			}
			_data[_size] = element;
			++_size;
		}

		T pop_back()
		{
			if (_size < 0)
			{
				_data[--_size].~T();
			}
		}

		T& front() { return _data[0]; }
		const T& front() const { return _data[0]; }
		T& back() { return _data[_size - 1]; }
		const T& back() const { return _data[_size - 1]; }

		T& at(int i)
		{
			if (i >= 0 && i < _size)
			{
				return _data[i];
			}
			else
			{
				throw std::out_of_range("Element out of range.");
			}
		}

		class Iterator;
		Iterator begin() { return Iterator(_data); }
		Iterator end() { return Iterator(_data + _size); }

		bool empty() { return _size == 0; }

		size_t size() { return _size; }
		size_t capacity() { return _capacity; }
		T* data() { return _data; }

	private:
		T* _data;
		size_t _size;
		size_t _capacity;
	};

	template<typename T>
	class Vector<T>::Iterator
	{
	public:
		Iterator(T* p) : p(p) {}

		T& operator * () const 
		{
			return *p;
		}

		T* operator -> () const
		{
			return p;
		}

		Iterator& operator ++()
		{
			++p;
			return *this;
		}

		Iterator operator ++(int)
		{
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator == (const Iterator& rhs) const
		{
			return p == rhs.p;
		}
		
		bool operator != (const Iterator& rhs) const
		{
			return p != rhs.p;
		}

	private:
		T* p;
	};

	/***********************************
	* DEFUALT CONSTRUCTOR
	***********************************/
	template<typename T>
	inline Vector<T>::Vector()
	{
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}


	/***********************************
	* CONSTRUCTOR /W CAPACITY
	***********************************/
	template<typename T>
	inline Vector<T>::Vector(size_t size)
	{
		_data = new T[size];
		_size = size;
		_capacity = size;
	}


	/***********************************
	* CONSTRUCTOR /W SIZE & VALUE
	***********************************/
	template<typename T>
	inline Vector<T>::Vector(size_t size, const T& value)
	{
		_data = new T[size];
		_size = size;
		_capacity = size;

		for (size_t i = 0; i < size; ++i)
		{
			_data[i] = value;
		}
	}


	/***********************************
	* COPY CONSTRUCTOR
	***********************************/
	template<typename T>
	inline Vector<T>::Vector(const Vector<T>& rhs)
	{
		_data = new T[rhs._capacity];
		_size = rhs.size;
		_capacity = rhs._capacity;

		for (size_t i = 0; i < rhs._size; ++i)
		{
			_data[i] = rhs._data[i];
		}
	}


	/***********************************
	* MOVE CONSTRUCTOR
	***********************************/
	template<typename T>
	inline Vector<T>::Vector(Vector<T>&& rhs) noexcept
	{
		_data = rhs._data;
		_size = rhs._size;
		_capacity = rhs._capacity;

		rhs._data = nullptr;
		rhs._size = 0;
		rhs._capacity = 0;
	}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		delete[] _data;
		_data = nullptr;
	}
}