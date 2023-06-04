//
// Created by marco-vb on 29-05-2023.
//

#ifndef TSP_HEAP_H
#define TSP_HEAP_H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<double, int> di;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;

#define INF 1e11

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

template <class T>
Heap<T>::Heap()
{
	H.push_back(nullptr);
}

template <class T>
bool Heap<T>::empty()
{
	return H.size() == 1;
}

template <class T>
T *Heap<T>::extractMin()
{
	auto x = H[1];
	H[1] = H.back();
	H.pop_back();
	if (H.size() > 1) heapifyDown(1);
	x->queueIndex = 0;
	return x;
}

template <class T>
void Heap<T>::insert(T *x)
{
	H.push_back(x);
	heapifyUp(H.size() - 1);
}

template <class T>
void Heap<T>::decreaseKey(T *x)
{
	heapifyUp(x->queueIndex);
}

template <class T>
void Heap<T>::heapifyUp(unsigned i)
{
	auto x = H[i];
	while (i > 1 && *x < *H[parent(i)]) {
		set(i, H[parent(i)]);
		i = parent(i);
	}
	set(i, x);
}

template <class T>
void Heap<T>::heapifyDown(unsigned i)
{
	auto x = H[i];
	while (true) {
		unsigned k = left(i);
		if (k >= H.size())
			break;
		if (k + 1 < H.size() && *H[k + 1] < *H[k])
			++k; // right child of i
		if (!(*H[k] < *x))
			break;
		set(i, H[k]);
		i = k;
	}
	set(i, x);
}

template <class T>
void Heap<T>::set(unsigned i, T *x)
{
	H[i] = x;
	x->queueIndex = i;
}

#endif //TSP_HEAP_H
