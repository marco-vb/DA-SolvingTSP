//
// Created by marco-vb on 29-05-2023.
//

#ifndef TSP_HEAP_H
#define TSP_HEAP_H

#include <bits/stdc++.h>

using namespace std;

template <class T>
class Heap
{
	vector<T *> H;

	void heapifyUp(unsigned i);

	void heapifyDown(unsigned i);

	inline void set(unsigned i, T *x);

public:
	Heap();

	void insert(T *x);

	T *extractMin();

	void decreaseKey(T *x);

	bool empty();
};

#define parent(i) ((i) >> 1)
#define left(i) ((i) << 1)

#endif //TSP_HEAP_H
