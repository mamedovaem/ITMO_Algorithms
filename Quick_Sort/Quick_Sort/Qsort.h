#pragma once

constexpr int INSERT_THRESHOLD = 16;

template<typename T, typename Compare> void qsort(T* first, int size, Compare comp)
{

	while(size > INSERT_THRESHOLD)
	{
		 int index = partition(first, size, comp);
		 if (index < size - index - 1)
		 {
			 qsort(first, index + 1, comp);
			 first = first + index + 1;
			 size = size - index - 1;
		 }
		 else 
		 {
			 qsort(first + index + 1, size - index - 1, comp);
			 size = index + 1;
		 }
	}

	insert_sort(first, size, comp);
}

template<typename T, typename Compare> T* get_pivot(T* first, int size, Compare comp)
{ 
		T* last = first + (size-1);
		T* middle = first + (size) / 2 ;

		if (comp(*first, *middle) && comp(*middle, *last) || comp(*last, *middle) && comp(*middle, *first))
		{
			return middle;
		}
		else if (comp(*first, *middle) && comp(*last, *first) || comp(*first, *last) && comp(*middle, *first))
		{
			return first;
		}
		else
		{
			return last;
		}
	}


template<typename T, typename Compare> int partition(T* first, int size, Compare comp)
{
		T pivot = *(get_pivot(first, size, comp));
		int i = 0;
		int j = size - 1;

		do
		{
			while (comp(*(first + i), pivot))
			{
				i++;
			}
			while (comp(pivot, *(first + j)))
			{
				j--;
			}

			if (i <= j)
			{
				std::swap(*(first + i), *(first + j));
				i++;
				j--;
			}


		} while (i <= j);

		return j;
}

template<typename T, typename Compare> void insert_sort(T* first, int size, Compare comp)
{
	int i, j;

	for (i = 1; i < size; i++)
	{
		T temp = std::move(*(first + i));

		for (j = i - 1; (j >= 0) && (comp(temp, *(first + j))); j--)
		{
			*(first + j + 1) = std::move(*(first + j));
		}

		*(first + j + 1) = std::move(temp);
	}
}
