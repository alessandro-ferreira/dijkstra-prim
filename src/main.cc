#include "graph.h"
#include "min_priority_queue.h"

#include <chrono>
#include <iostream>
#include <random>

using std::cout;
using std::endl;

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::milliseconds;

const int MAX_WEIGHT = 1000;
const int INF = 0x3F3F3F3F;

template <typename T = int>
Graph<T> generate_random_graph(int V, int E, bool digraph=false, bool weighted=false, bool dense=true) {
    Graph<T> G = Graph<T>(V, dense, digraph, weighted);
    
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    
    std::uniform_int_distribution<> dist(0, V-1); // define the range
    
    while(E) {
        int u = dist(gen);
        int v = dist(gen);
        T w = 0;

        if(u == v || G.has_edge(u, v))
            continue ;
        
        if(weighted) {
            if constexpr (std::is_same_v<T, int>) {
                std::uniform_int_distribution<> distw(0, MAX_WEIGHT);
                w = distw(gen);
            }
            else {
                std::uniform_real_distribution<T> distw(0, MAX_WEIGHT);
                w = distw(gen);
            }
        }
        
        G.add_edge(u, v, w);
        
        E--;
    }

    return G;
}


template <typename T = int>
T dijkstra(Graph<T> G, int s, int t, bool heap=true){
    int n = G.get_V();
    
    T* d = new T[n];
    for(int i = 0; i < n; i++)
        d[i] = INF;
    
    MinPriorityQueue<T>* Q;
    if(heap)
        Q = new MinHeap<T>(n);
    else
        Q = new UnorderedArray<T>(n);
    
    d[s] = 0;
    Q->insert_key( KeyValue<T>(s, d[s]) );

    while(Q->size()) {
        KeyValue<T> min = Q->extract_min();
        int u = min.key;
#ifdef _DEBUG_MAIN
        cout << u << " " << d[u] << " - ";
#endif
        
        auto adjs = G.get_adjs(u);
        auto weight = G.get_weights(u);
        
        for(int i = 0; i < G.get_degree(u); i++) {
            auto v = adjs[i];
            if(d[v] > d[u] + weight[i]) {
                d[v] = d[u] + weight[i];
                Q->decrease_key( KeyValue<T>(v, d[v]) );
            }
        }
    }
    
    return d[t];
}


template <typename T = int>
T prim(Graph<T> G, int r, bool heap=true){
    int n = G.get_V();
    
    T* d = new T[n];
    bool* in = new bool[n];
    for(int i = 0; i < n; i++)
        d[i] = INF, in[i] = false;
    
    MinPriorityQueue<T>* Q;
    if(heap)
        Q = new MinHeap<T>(n);
    else
        Q = new UnorderedArray<T>(n);
    
    d[r] = 0;
    Q->insert_key( KeyValue<T>(r, d[r]) );

    T mst_weight = 0;
    while(Q->size()) {
        KeyValue<T> min = Q->extract_min();
        int u = min.key;
#ifdef _DEBUG_MAIN
        cout << u << " " << d[u] << " - ";
#endif
        mst_weight += d[u];
        in[u] = true;
        
        auto adjs = G.get_adjs(u);
        auto weight = G.get_weights(u);
        
        for(int i = 0; i < G.get_degree(u); i++) {
            auto v = adjs[i];
            if(not in[v] && d[v] > weight[i]) {
                d[v] = weight[i];
                Q->decrease_key( KeyValue<T>(v, d[v]) );
            }
        }
    }
    
    return mst_weight;
}


template<typename T=void, class Fn, typename... Args>
double measure_execution_time(Fn fn, Args... args) {
    auto t1 = high_resolution_clock::now();
    if constexpr (std::is_same_v<T, void>)
        fn(args...);
    else 
        cout << fn(args...) << endl;
    auto t2 = high_resolution_clock::now();
    
    duration<double, std::milli> ms_double = t2 - t1;
    
    return ms_double.count();
}


int main() {
    
    int V_sparse = 75000; // 50000 75000 100000
    int E_sparse = 10000000;

    int V_dense = 10000; // 8000 10000 12000
    int E_dense = 20000000;
    
    // Cormen Fig 24.6
    Graph dijkstra_example = Graph(5, false, true, true);
    dijkstra_example.add_edge(0, 1, 10); // s t 10
    dijkstra_example.add_edge(0, 4, 5); // s y 5
    dijkstra_example.add_edge(1, 2, 1); // t x 1
    dijkstra_example.add_edge(1, 4, 2); // t y 2
    dijkstra_example.add_edge(2, 3, 4); // x z 4
    dijkstra_example.add_edge(3, 0, 7); // z s 7
    dijkstra_example.add_edge(3, 2, 6); // z x 6
    dijkstra_example.add_edge(4, 1, 3); // y t 3
    dijkstra_example.add_edge(4, 3, 2); // y z 2
    
    cout << "-- dijkstra example --" << endl;
    cout << dijkstra(dijkstra_example, 0, 4) << endl;           // O(ElogV)
    cout << dijkstra(dijkstra_example, 0, 4, false) << endl;    // O(V^2)
        
    auto G_sparse = generate_random_graph<float>(V_sparse, E_sparse, true, true, false);
    cout << "-- dijkstra sparse graph generated --" << endl;

    cout << measure_execution_time<float>(dijkstra<float>, G_sparse, 0, V_sparse-1, true) << "ms" << endl;
    cout << measure_execution_time<float>(dijkstra<float>, G_sparse, 0, V_sparse-1, false) << "ms" << endl;
    
    auto G_dense = generate_random_graph<float>(V_dense, E_dense, true, true, true);
    cout << "-- dijkstra dense graph generated --" << endl;

    cout << measure_execution_time<float>(dijkstra<float>, G_dense, 0, V_dense-1, true) << "ms" << endl;
    cout << measure_execution_time<float>(dijkstra<float>, G_dense, 0, V_dense-1, false) << "ms" << endl;
    
    // Cormen Fig 23.5
    Graph prim_example = Graph(9, false, false, true);
    prim_example.add_edge(0, 1, 4); // a b 4
    prim_example.add_edge(0, 7, 8); // a h 8
    prim_example.add_edge(1, 2, 8); // b c 8
    prim_example.add_edge(1, 7, 11); // b h 11
    prim_example.add_edge(2, 3, 7); // c d 7
    prim_example.add_edge(2, 5, 4); // c f 4
    prim_example.add_edge(2, 8, 2); // c i 2
    prim_example.add_edge(3, 4, 9); // d e 9
    prim_example.add_edge(3, 5, 14); // d f 14
    prim_example.add_edge(4, 5, 10); // e f 10
    prim_example.add_edge(5, 6, 2); // f g 2
    prim_example.add_edge(6, 7, 1); // g h 1
    prim_example.add_edge(6, 8, 6); // g i 6
    prim_example.add_edge(7, 8, 7); // h i 7    
    
    cout << "-- prim example --" << endl;
    cout << prim(prim_example, 0) << endl;          // O(ElogV)
    cout << prim(prim_example, 0, false) << endl;   // O(V^2)
    
    G_sparse = generate_random_graph<float>(V_sparse, E_sparse, false, true, false);
    cout << "-- prim sparse graph generated --" << endl;
    
    cout << measure_execution_time<float>(prim<float>, G_sparse, 0, true) << "ms" << endl;
    cout << measure_execution_time<float>(prim<float>, G_sparse, 0, false) << "ms" << endl;
    
    G_dense = generate_random_graph<float>(V_dense, E_dense, true, true, true);
    cout << "-- prim dense graph generated --" << endl;
    
    cout << measure_execution_time<float>(prim<float>, G_dense, 0, true) << "ms" << endl;
    cout << measure_execution_time<float>(prim<float>, G_dense, 0, false) << "ms" << endl;
    
    return 0;
}


// 
