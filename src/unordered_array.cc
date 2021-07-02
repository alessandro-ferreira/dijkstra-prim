#include "min_priority_queue.h"
#include <iostream>

// Explicit template instantiation
template class UnorderedArray<int>;
template class UnorderedArray<float>;
template class UnorderedArray<double>;


template <class T>
UnorderedArray<T>::UnorderedArray(int max_key) : MinPriorityQueue<T>(max_key) {
    this->indexes = {};
    for(int i = 0; i <= this->max_key; i++)
        this->indexes.push_back( IDX_NULL );
    
    this->keys = {};
}


template <class T>
void UnorderedArray<T>::insert_key(KeyValue<T> element) {
    this->decrease_key(element);
}

template <class T>
void UnorderedArray<T>::decrease_key(KeyValue<T> element) {
    if(element.key < 0 || element.key > this->max_key)
        return ;
    
    int index = this->indexes[element.key];
    if(index == IDX_NULL) {
        this->indexes[element.key] = this->keys.size();
        this->keys.push_back( element );
    }
    else {
        this->keys[index] = element;
    }
    
#ifdef _DEBUG_PQ
    for(auto item : this->keys) 
        std::cout << "(" << item.key << "," << item.value << ") ";
    std::cout << std::endl;
#endif
}

template <class T>
KeyValue<T> UnorderedArray<T>::extract_min() {
    int min_key = -1;
    
    for(int i = 0; i <= this->max_key; i++) {
        if(this->indexes[i] != IDX_NULL &&
            (min_key == -1 || this->keys[ this->indexes[i] ].value < this->keys[ this->indexes[min_key] ].value))
            min_key = i;
    }
    
    KeyValue<T> min = this->keys[ this->indexes[min_key] ];
    int index = this->indexes[min.key];
    this->indexes[min.key] = IDX_NULL;
    
    this->keys[index] = this->keys.back();
    this->keys.pop_back();
    if(index < this->size())
        this->indexes[ this->keys[index].key ] = index;
    
    return min;
}

template <class T>
int UnorderedArray<T>::size() {
    return this->keys.size();
}
