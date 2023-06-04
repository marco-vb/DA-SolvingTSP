/**
 * @file Heap.h
 * @brief This file contains the declaration and implementation of the Heap class.
 */

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

/**
 * @class Heap
 * @brief Represents a binary min-heap.
 * @tparam T The type of elements stored in the heap.
 */
template <class T>
class Heap
{
    vector<T*> H;       ///< The heap container.

    /**
     * @brief Performs the heapify-up operation to maintain the min-heap property.
     * @param i The index of the element to heapify-up.
     */
    void heapifyUp(unsigned i);

    /**
     * @brief Performs the heapify-down operation to maintain the min-heap property.
     * @param i The index of the element to heapify-down.
     */
    void heapifyDown(unsigned i);

    /**
     * @brief Updates the element at the given index in the heap.
     * @param i The index of the element to update.
     * @param x The new element.
     */
    inline void set(unsigned i, T* x);

public:
    /**
     * @brief Default constructor for Heap.
     */
    Heap();

    /**
     * @brief Inserts an element into the heap.
     * @param x The element to insert.
     */
    void insert(T* x);

    /**
     * @brief Extracts the minimum element from the heap.
     * @return The minimum element.
     */
    T* extractMin();

    /**
     * @brief Decreases the key of an element in the heap.
     * @param x The element whose key needs to be decreased.
     */
    void decreaseKey(T* x);

    /**
     * @brief Checks if the heap is empty.
     * @return True if the heap is empty, False otherwise.
     */
    bool empty();
};

/**
 * @brief Macro for calculating the parent index of a heap element.
 * @param i The index of the element.
 * @return The parent index of the element.
 */
#define parent(i) ((i) >> 1)

/**
 * @brief Macro for calculating the left child index of a heap element.
 * @param i The index of the element.
 * @return The left child index of the element.
 */
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
T* Heap<T>::extractMin()
{
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if (H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void Heap<T>::insert(T* x)
{
    H.push_back(x);
    heapifyUp(H.size() - 1);
}

template <class T>
void Heap<T>::decreaseKey(T* x)
{
    heapifyUp(x->queueIndex);
}

template <class T>
void Heap<T>::heapifyUp(unsigned i)
{
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)])
    {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void Heap<T>::heapifyDown(unsigned i)
{
    auto x = H[i];
    while (true)
    {
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
void Heap<T>::set(unsigned i, T* x)
{
    H[i] = x;
    x->queueIndex = i;
}

#endif //TSP_HEAP_H
