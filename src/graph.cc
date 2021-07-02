#include "graph.h"

// Explicit template instantiation
template class Graph<int>;
template class Graph<float>;
template class Graph<double>;


template <class T>
Graph<T>::Graph(int n) : Graph<T>::Graph(n, {}, false, false, false) {} // Delegating constructor -std=c++11

template <class T>
Graph<T>::Graph(int n, bool matrix, bool digraph, bool weighted) : Graph<T>::Graph(n, {}, matrix, digraph, weighted) {}

template <class T>
Graph<T>::Graph(int n, vector< Edge<T>> edges) : Graph<T>::Graph(n, edges, false, false, false) {}

template <class T>
Graph<T>::Graph(int n, vector< Edge<T>> edges, bool matrix, bool digraph, bool weighted) {
    this->Adjs = {};
    for(int i = 0; i < n; i++)
        this->Adjs.push_back( {} );
    
    this->Weights = {};
    for(int i = 0; i < n; i++)
        this->Weights.push_back( {} );
        
    if(matrix == true) {
        for(int i = 0; i < n; i++) {
            this->Mat.push_back( {} );
            for(int k = 0; k < n; k++)
                this->Mat[i].push_back( 0 );
        }
    }
    
    this->is_digraph = digraph;
    this->is_weighted = weighted;
    
    for(auto edge : edges) {
        this->add_edge(edge.u, edge.v, edge.w);
    }
}


template <class T>
int Graph<T>::get_V() {
    return this->Adjs.size();
}

template <class T>
int Graph<T>::get_degree(int v) {
    int size = this->Adjs.size();
    
    if(v < 0 || v >= size)
        return 0;
    
    return (int)this->Adjs[v].size();
}


template <class T>
vector<int> Graph<T>::get_adjs(int v) {
    int size = this->Adjs.size();
    
    if(v < 0 || v >= size)
        return {};
    
    return this->Adjs[v];
}

template <class T>
vector<T> Graph<T>::get_weights(int v) {
    int size = this->Weights.size();
    
    if(v < 0 || v >= size)
        return {};
    
    return this->Weights[v];
}

template <class T>
vector< Edge<T>> Graph<T>::get_edges() {
    int size = this->Adjs.size();
    
    vector< Edge<T>> edges = {};
    for(int u = 0; u < size; u++) {
        int degree = this->Adjs[u].size();
        for(int i = 0; i < degree; i++)
            if(this->is_digraph || u <= this->Adjs[u][i])
                edges.push_back( Edge<T>(u, this->Adjs[u][i], this->Weights[u][i]) );
    }
    
    return edges;
}


template <class T>
bool Graph<T>::has_edge(int u, int v) {
    int size = this->Adjs.size();
    
    if(u < 0 || u >= size || v < 0 || v >= size)
        return false;
    
    if((int)this->Mat.size() == size)
        return Mat[u][v] > 0;
    
    int n = this->get_degree(u);
    for(int i = 0; i < n; i++)
        if(this->Adjs[u][i] == v)
            return true;
        
    return false;
}

template <class T>
T Graph<T>::weight(int u, int v) {
    int size = this->Weights.size();
    
    if(u < 0 || u >= size || v < 0 || v >= size)
        return -1;
    
    if((int)this->Mat.size() == size)
        return Mat[u][v];
    
    int n = this->get_degree(u);
    for(int i = 0; i < n; i++)
        if(this->Adjs[u][i] == v)
            return this->Weights[u][i];
        
    return -1;
}


template <class T>
void Graph<T>::add_edge(int u, int v) {
    this->add_edge(u, v, 0);
}

template <class T>
void Graph<T>::add_edge(int u, int v, T w) {
    int size = this->Adjs.size();
    
    if(u < 0 || u >= size || v < 0 || v >= size)
        return ;
    
    this->Adjs[u].push_back( v );
    this->Weights[u].push_back( w );
        
    if((int)this->Mat.size() == size)
        this->Mat[u][v] = w;
    
    if(this->is_digraph == false) {
        this->Adjs[v].push_back( u );
        this->Weights[v].push_back( w );
        
        if((int)this->Mat.size() == size)
            this->Mat[v][u] = w;
    }
}
