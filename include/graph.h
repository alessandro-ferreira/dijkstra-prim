#ifndef __GRAPH_H
#define __GRAPH_H

#include <vector>

using std::vector;


template <typename T = int> // Class template argument deduction -std=c++17
class Edge {
    
    public:
        
        int u;
        int v;
        T w;
        
        Edge(int u, int v, T w) {
            this->u = u;
            this->v = v;
            this->w = w;
        }
};


template <typename T = int>
class Graph {
    
    private:
        
        vector< vector<T> > Mat;
        vector< vector<int> > Adjs;
        vector< vector<T> > Weights;
        bool is_digraph;
        bool is_weighted;
        
    
    public:
        
        Graph(int n);
        Graph(int n, bool matrix, bool digraph, bool weighted);
        
        Graph(int n, vector< Edge<T>> edges);
        Graph(int n, vector< Edge<T>> edges, bool matrix, bool digraph, bool weighted);
        
        int get_V();
        int get_degree(int v);
        
        vector<int> get_adjs(int v);
        vector<T> get_weights(int v);
        vector< Edge<T>> get_edges();
        
        bool has_edge(int u, int v);
        T weight(int u, int v);
        
        void add_edge(int u, int v);
        void add_edge(int u, int v, T w);
};

#endif
