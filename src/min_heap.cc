#include "min_priority_queue.h"
#include <iostream>

// Explicit template instantiation
template class MinHeap<int>;
template class MinHeap<float>;
template class MinHeap<double>;


template <class T>
MinHeap<T>::MinHeap(int max_key) : MinPriorityQueue<T>(max_key) {
    this->indexes = {};
    for(int i = 0; i <= this->max_key; i++)
        this->indexes.push_back( IDX_NULL );
    
    this->keys = {};
}


template <class T>
void MinHeap<T>::insert_key(KeyValue<T> element) {
    this->decrease_key(element);
}

template <class T>
void MinHeap<T>::decrease_key(KeyValue<T> element) {
    if(element.key < 0 || element.key > this->max_key)
        return ;
    
    int index = this->indexes[element.key];
    if(index == IDX_NULL) {
        index = this->keys.size();
        
        this->keys.push_back( element );
        this->indexes[element.key] = index;
    }
    else {
        this->keys[index] = element;
    }

    while(index > 0 && this->keys[index].value < this->keys[(index-1)/2].value) {
        this->swap_keys(index, (index-1)/2);
        index = (index-1)/2;
    }
    
#ifdef _DEBUG_PQ
    for(auto item : this->keys) 
        std::cout << "(" << item.key << "," << item.value << ") ";
    std::cout << std::endl;
#endif
}


template <class T>
KeyValue<T> MinHeap<T>::extract_min() {
    KeyValue<T> min = this->keys[0];
    this->indexes[min.key] = IDX_NULL;
    
    KeyValue<T> last = this->keys.back();
    this->keys.pop_back();
    
    if(this->keys.size() > 0) {
        this->indexes[last.key] = 0;
        this->keys[0] = last;
        this->min_heapify(0);
    }
    
    return min;
}


template <class T>
vector<T> MinHeap<T>::get_heap() {
    vector<T> heap = {};
    
    for(auto key : this->keys)
        heap.push_back(key.value);
    
    return heap;
}


template <class T>
int MinHeap<T>::size() {
    return this->keys.size();
}


template <class T>
void MinHeap<T>::min_heapify(int index) {
    int n = this->keys.size();
    
    int largest = index;
    for(int k : {2*index+1, 2*index+2})
        if(k < n && this->keys[k].value < this->keys[largest].value)
            largest = k;
        
    if(largest != index) {
        this->swap_keys(index, largest);
        this->min_heapify(largest);
    }
}

template <class T>
void MinHeap<T>::swap_keys(int idx1, int idx2) {
    KeyValue<T> aux = this->keys[idx1];
    this->keys[idx1] = this->keys[idx2];
    this->keys[idx2] = aux;
    
    this->indexes[ this->keys[idx1].key ] = idx1;
    this->indexes[ this->keys[idx2].key ] = idx2;
}
