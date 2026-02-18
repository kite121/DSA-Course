//Danil Elgin DSAI 04
//Part of the graph class implementation is taken from the lab
//The implementation of the dfs and bfs functions are taken from the slides of the tutorial
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;
template <typename V>
class Minimum_binary_heap {
    vector<V> data;
public:
    void build_min_heap(vector<V>& vec) {
        data = vec;
        if (data.size() <= 1) return;
        for (int i = data.size() / 2 - 1; i >= 0; i--) {
            min_heapify(i);
        }
    }
    void min_heapify(int i) {
        int l = Left(i);
        int r = Right(i);
        int smallest = i;
        if (l < data.size() && data[l]->key < data[smallest]->key) {
            smallest = l;
        }
        if (r < data.size() && data[r]->key < data[smallest]->key) {
            smallest = r;
        }
        if (smallest != i) {
            V v = data[i];
            data[i] = data[smallest];
            data[smallest] = v;
            min_heapify(smallest);
        }
    }
    int Left(int i) {
        return i * 2 + 1;
    }
    int Right(int i) {
        return i * 2 + 2;
    }
    V heap_extract_min() {
        if (data.empty()) throw runtime_error("Heap is empty");
        V min = data[0];
        data[0] = data[data.size() - 1];
        data.pop_back();
        min_heapify(0);
        return min;
    }
    bool empty() {
        return data.size() == 0;
    }
    int search(V& v) {
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] == v) return i;
        }
        return -1;
    }
    void heap_decrease_key(int i, double key) {
        if (key > data[i]->key) return;
        data[i]->key = key;
        while (i > 0 && data[i]->key < data[(i - 1) / 2]->key) {
            swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
};
template <typename V>
class Graph {
public:
    class Vertex {
    public:
        list<Vertex*> adj_in;
        list<Vertex*> adj_out;
        V value;
        Vertex(V v) : value(v) {};
        Vertex* repr;
        int rank;
        int size;
    };

    class Edge {
    public:
        Vertex* from;
        Vertex* to;
        Edge(Vertex* from, Vertex* to) : from(from), to(to) {};
    };

    int cycle = 0;
    list<Vertex*> vertices_l;
    list<Edge*> edges_l;

    ~Graph() {
        for (auto v : vertices_l) delete v;
        for (auto e : edges_l) delete e;
    }

    int num_vertices() {
        return vertices_l.size();
    }

    int num_edges() {
        return edges_l.size();
    }

    list<Vertex*> vertices() {
        return vertices_l;
    }

    list<Edge*> edges() {
        return edges_l;
    }

    Vertex* insert_vertex(V value) {
        Vertex* v = new Vertex(value);
        vertices_l.push_back(v);
        return v;
    }

    Edge* insert_edge(Vertex* from, Vertex* to) {
        Edge* e = new Edge(from, to);
        edges_l.push_back(e);
        from->adj_out.push_back(to);
        to->adj_in.push_back(from);
        return e;
    }

    Edge* get_edge(Vertex* from, Vertex* to) {
        if (from->adj_out.size() <= to->adj_in.size()) {
            for (auto it : from->adj_out) {
                if (it == to) {
                    for (auto e : edges_l) {
                        if (e->from == from && e->to == to) return e;
                    }
                }
            }
        }
        else {
            for (auto it : to->adj_in) {
                if (it == from) {
                    for (auto e : edges_l) {
                        if (e->from == from && e->to == to) return e;
                    }
                }
            }
        }
        return nullptr;
    }

    int Outdegree(Vertex* v) {
        return v->adj_out.size();
    }

    int Indegree(Vertex* v) {
        return v->adj_in.size();
    }

    list<Vertex*> out_edges(Vertex* v) {
        return v->adj_out;
    }

    list<Vertex*> in_edges(Vertex* v) {
        return v->adj_in;
    }
    void DanilELgin_msf_prim() {
        for (auto v : vertices_l) {
            v->key = numeric_limits<double
            >::max();
            v->parent = nullptr;
        }
        Minimum_binary_heap<Vertex*> min_heap;
        min_heap.build_min_heap(vertices_l);
        while (!min_heap.empty()) {
            Vertex* u = min_heap.heap_extract_min();
            if (u->key == numeric_limits<double>::max()) {
                u->key = 0;
            }
            for (auto adjacent : u->adj) {
                Edge* e = get_edge(u, adjacent);
                if (e) {
                    int index = min_heap.search(adjacent);
                    if (index != -1 && e->cost < adjacent->key) {
                        adjacent->key = e->cost;
                        adjacent->parent = u;
                        min_heap.heap_decrease_key(index, e->cost);
                    }
                }
            }
        }
    }
};
template <typename V, typename T>
class DSU {
public:
    void make_set(V& v) {
        v->repr = v;
        v->rank = 0;
        v->size = 1;
    }
    V find_set(V& v) {
        if (v->repr != v) {
            v->repr = find_set(v->repr);
        }
        return v->repr;
    }
    void union_set(V& v, V& w) {
        V v1 = find_set(v);
        V v2 = find_set(w);
        link(v1, v2);
    }
    void link(V& v, V& w) {
        if (v->rank > w->rank) {
            w->repr = v;
            v->size += w->size;
            v->rank = v->size / 2;
        }
        else {
            v->repr = w;
            w->size += v->size;
            w->rank = w->size / 2;
        }
    }
    void connected_components(Graph<T>& G) {
        for (auto v : G.vertices()) {
            make_set(v);
        }
        for (auto e : G.edges()) {
            if (find_set(e->from) != find_set(e->to)) {
                union_set(e->from, e->to);
            }
        }
    }
    bool same_component(V v, V w) {
        return find_set(v) == find_set(w);
    }
    int number_of_components(Graph<T>& G) {
        vector<V> comp;
        for (auto v : G.vertices()) {
            bool flag = true;
            for (auto j: comp) {
                if (find_set(v) == find_set(j)) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                comp.push_back(find_set(v));
            }
        }
        return comp.size();
    }

};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Graph<int> g;
    int m, n;
    cin >> m >> n;
    vector<Graph<int>::Vertex*> vertices(m + 1);
    for (int i = 1; i <= m; ++i) {
        vertices[i] = g.insert_vertex(i);
    }
    for (int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g.insert_edge(vertices[u], vertices[v]);
    }

    DSU<Graph<int>::Vertex*, int> set;
    set.connected_components(g);
    cout << set.number_of_components(g) << endl;
}
