#pragma once

template<typename T> class Array final
{

public:

	Array();
	Array(int capacity);
	~Array();

	//копирующ. конструктор, копирующ. присваивание, перемещ. конструктор, перемещ. присваивание
	Array(const Array& other);
	Array& operator =(Array other);
	void swap(Array& other);

	Array(Array&& other);
	//Array& operator =(Array&& other);

	int insert(const T& value);
	int insert(int index, const T& value);
	void remove(int index);
	
	const T& operator[](int index) const;
	T& operator[](int index);
	
	int size() const;
	int capacity() const;
	void double_capacity();
	class ConstIterator
	{
		friend class Array;

	public:

		ConstIterator(Array<T>* arr_ptr) : ConstIterator(arr_ptr, false)
		{

		}

		ConstIterator(Array<T>* arr_ptr, bool is_reversed)
		{
			array_ptr = arr_ptr;

			this->is_reversed = is_reversed;

			if (is_reversed)
			{
				current_position = (array_ptr->size_) - 1;
			}
			else
			{
				current_position = 0;
			}

		}

		const T& get() const
		{
			return *(array_ptr->pitems + current_position);
		}

		void next()
		{
			if (has_current())
			{
				if (!is_reversed) {
					current_position++;
				}
				else
				{
					current_position--;
				}
			}
		}

		bool has_current() const
		{
			if (!is_reversed) {
				return (current_position < (array_ptr->size_));
			}
			else
			{
				return (current_position >= 0);
			}

		}

		bool has_next() const
		{
			if (!is_reversed) {
				return (current_position < ((array_ptr->size_) - 1));
			}
			else
			{
				return (current_position > 0);
			}

		}

	protected:
		Array<T>* array_ptr;
		int current_position;
		bool is_reversed;
	};

	class Iterator : public ConstIterator
	{
		friend class Array;

	public:

		Iterator(Array<T>* array_ptr) : Iterator(array_ptr, false)
		{

		}

		Iterator(Array<T>* array_ptr, bool is_reversed) : ConstIterator(array_ptr, is_reversed)
		{

		}

		void set(const T& value) {

			(this->array_ptr->pitems + this->current_position)->~T();
			new(this->array_ptr->pitems + this->current_position) T(value);
		}

	};

	Iterator iterator()
	{
		return Iterator(this);
	}
	ConstIterator iterator() const 
	{
		return ConstIterator(this);
	}
	Iterator reverseIterator()
	{
		return Iterator(this, true);
	}
	ConstIterator reverseIterator() const
	{
		return ConstIterator(this, true);
	}

private:
	T* pitems;
	int size_;
	int capacity_;
	static constexpr int DEFAULT_CAPACITY = 8;
	static constexpr int CAPACITY_COEF = 2;
};

template <typename T> Array<T>::Array(): Array(DEFAULT_CAPACITY)
{

}

template <typename T> Array<T>::Array(int capacity)
{
	size_ = 0;
	capacity_ = capacity;

	pitems = (T*) malloc(sizeof(T) * capacity_);

}

template <typename T> Array<T>::~Array()
{
	for (int i = 0; i < size_; ++i)
	{
		(pitems+i)->~T();
	}

		free(pitems);
}

template <typename T> Array<T>::Array(const Array& other)
{
	size_ = other.size_;
	capacity_ = other.capacity_;

	pitems = (T*) malloc(sizeof(T) * capacity_);

	for (int i = 0; i < size_; ++i)
	{
		new (pitems + i) T(other.pitems[i]);
	}
}

template <typename T> Array<T>& Array<T>::operator=(Array<T> other)
{
	swap(other);

	return *this;
}

template <typename T> void Array<T>::swap(Array& other)
{
	std::swap(pitems, other.pitems); 
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
}

template <typename T> Array<T>::Array(Array&& other)
{
	pitems = other.pitems;
	size_ = other.size_;
	capacity_ = other.capacity_;

	other.pitems = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
}
/*
template <typename T> Array<T>& Array<T>::operator=(Array&& other)
{

	if (this != other)
	{
		for (int i = 0; i < size_; ++i)
		{
			pitems[i]->~T();
		}

		free(pitems);

		pitems = other.pitems;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.pitems = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	return *this;
}
*/

template <typename T> int Array<T>::insert(const T& value)
{
	if (size_ == capacity_)
	{
		double_capacity();
	}

	new(pitems + size_) T(value);
	++size_;

	return (size_ - 1);
}

template <typename T> int Array<T>::insert(int index, const T& value)
{
	if (size_ == capacity_)
	{
		double_capacity();
	}

	new(pitems + size_) T(std::move(*(pitems + size_ - 1))); // копирование, проверки на границе

	for (int i = size_ - 1; i > index; --i)
	{
		*(pitems + i) = std::move(pitems[i - 1]);
	}

	*(pitems + index) = value;
	++size_;

	return index;
}

template <typename T> void Array<T>::double_capacity()
{
	capacity_ = CAPACITY_COEF * capacity_;

	T* temp = pitems;

	pitems = (T*) malloc(sizeof(T) * capacity_);

	for (int i = 0; i < size_; ++i)
	{
		new (pitems + i) T(std::move(*(temp + i)));
		(temp + i)->~T();
	}

	free(temp);
}

template <typename T> void Array<T>::remove(int index)
{
	for (int i = index; i < size_ - 1; ++i)
	{
		*(pitems + i) = std::move(pitems[i + 1]);
	}
	(pitems + size_ - 1)->~T();
	--size_;

}

template <typename T> const T& Array<T>::operator[](int index) const
{
	return *(pitems+index);
}

template <typename T> T& Array<T>::operator[](int index)
{
	return *(pitems + index);
}

template <typename T> int Array<T>::size() const
{
	return size_;
}


template <typename T> int Array<T>::capacity() const
{
	return capacity_;
}
