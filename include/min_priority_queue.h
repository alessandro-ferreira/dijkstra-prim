#ifndef __MIN_PRIORITY_QUEUE_H
#define __MIN_PRIORITY_QUEUE_H

#include <vector>

using std::vector;

const int IDX_NULL = -1;


template <typename T = int> // Class template argument deduction -std=c++17
class KeyValue {
    
    public:
    
        int key;
        T value;
        
        KeyValue(int key, T value) {
            this->key = key;
            this->value = value;
        }
};


template <typename T = int> 
class MinPriorityQueue {
    
    protected:
        
        int max_key;
    
    public:
     
        MinPriorityQueue(int max_key) {
            this->max_key = max_key;
        }
    
        virtual void insert_key(KeyValue<T> element) = 0;
        virtual void decrease_key(KeyValue<T> element) = 0;
        
        virtual KeyValue<T> extract_min() = 0;
        
        virtual int size() = 0;
        
};


template <typename T = int> 
class UnorderedArray : public MinPriorityQueue<T> {
    
    private:
        
        vector<int> indexes;
        vector< KeyValue<T>> keys;
    
    public:
        
        UnorderedArray(int max_key) ;
        
        void insert_key(KeyValue<T> element);
        void decrease_key(KeyValue<T> element);
        
        KeyValue<T> extract_min();
        
        int size();
};


template <typename T = int> 
class MinHeap : public MinPriorityQueue<T> {
    
    private:
        
        vector<int> indexes;
        vector< KeyValue<T>> keys;
        
    protected :
        
        void min_heapify(int index);
        void swap_keys(int idx1, int idx2) ;
    
    public:
        
        MinHeap(int max_key) ;
        
        void insert_key(KeyValue<T> element);
        void decrease_key(KeyValue<T> element);
        
        KeyValue<T> extract_min();
        
        int size();
        
        vector<T> get_heap();
};

#endif
