//Danil Elgin DSAI 04
//Part of the graph class implementation is taken from the lab
//The implementation of the dfs and bfs functions are taken from the slides of the tutorial
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <limits>

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
template <typename V, typename D>
class Graph {
public:
    class Vertex {
    public:
        vector<Vertex*> adj;
        V name;
        D burns_tax;
        Vertex(V v, D cost) : name(v), burns_tax(cost) {};
        D key;
        Vertex* parent = nullptr;
        bool operator<(const Vertex& other) const {
            return key < other.key;
        }
    };

    class Edge {
    public:
        D cost;
        Vertex* from;
        Vertex* to;
        Edge(Vertex* from, Vertex* to) : from(from), to(to) {};
    };

    vector<Vertex*> vertices_l;
    vector<Edge*> edges_l;

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

    vector<Vertex*> vertices() {
        return vertices_l;
    }

    vector<Edge*> edges() {
        return edges_l;
    }

    Vertex* insert_vertex(V name, D cost) {
        Vertex* v = new Vertex(name, cost);
        vertices_l.push_back(v);
        return v;
    }

    Edge* insert_edge(Vertex* from, Vertex* to, D distance) {
        Edge* e = new Edge(from, to);
        e->cost = distance / (from->burns_tax + to->burns_tax);
        edges_l.push_back(e);
        from->adj.push_back(to);
        to->adj.push_back(from);
        return e;
    }

    Edge* get_edge(Vertex* from, Vertex* to) {
        for (auto e : edges_l) {
            if ((e->from == from && e->to == to) || (e->from == to && e->to == from)) return e;
        }
        return nullptr;
    }
    Vertex* get_vertex(V name) {
        for (auto v : vertices_l) {
            if (v->name == name) return v;
        }
        return nullptr;
    }

    int degree(Vertex* v) {
        return v->adj.size();
    }

    vector<Vertex*> adj(Vertex* v) {
        return v->adj;
    }
    void DanilElgin_msf_prim() {
        for (auto v : vertices_l) {
            v->key = numeric_limits<D>::max();
            v->parent = nullptr;
        }
        Minimum_binary_heap<Vertex*> min_heap;
        min_heap.build_min_heap(vertices_l);
        while (!min_heap.empty()) {
            Vertex* u = min_heap.heap_extract_min();
            if (u->key == numeric_limits<D>::max()) {
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Graph<string, double> graph;
    int n;
    cin >> n;
    string command;
    for (int i = 0; i < n; i++) {
        cin >> command;
        if (command == "ADD") {
            string name;
            double cost;
            cin >> name >> cost;
            graph.insert_vertex(name, cost);
        }
        else if (command == "CONNECT") {
            string name_1, name_2;
            double distance;
            cin >> name_1 >> name_2 >> distance;
            Graph<string, double>:: Vertex* u1, * u2;
            u1 = graph.get_vertex(name_1);
            u2 = graph.get_vertex(name_2);
            graph.insert_edge(u1, u2, distance);
        }
        else if (command == "PRINT_MIN") {
            graph.DanilElgin_msf_prim();
            for (auto v : graph.vertices()) {
                if (v->parent != nullptr) {
                    cout << v->parent -> name << ":" << v->name << " ";
                }
            }
            cout << endl;
        }
    }
}
