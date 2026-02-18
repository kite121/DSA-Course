//Danil Elgin DSAI 04
//Part of the graph class implementation is taken from the lab.
//The implementation of the dfs and bfs functions are taken from the slides of the tutorial
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

template <typename V, typename E>
class Graph {
public:
    class Edge;
    class Vertex {
    public:
        list<Edge*> adj_in;
        list<Edge*> adj_out;
        V index;
        Vertex(V index) : index(index) {};
        string color;
        Vertex* parent;
        int d;
    };

    class Edge {
    public:
        Vertex* from;
        Vertex* to;
        Edge(Vertex* from, Vertex* to, E capacity, E flow) : from(from), to(to), capacity(capacity), flow(flow) {};
        E capacity;
        E flow;
    };

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

    const list<Vertex*>& vertices() {
        return vertices_l;
    }

    const list<Edge*>& edges() {
        return edges_l;
    }

    Vertex* insert_vertex(V index) {
        Vertex* v = new Vertex(index);
        vertices_l.push_back(v);
        return v;
    }

    Edge* insert_edge(Vertex* from, Vertex* to, E capacity, E flow) {
        Edge* e = new Edge(from, to, capacity, flow);
        edges_l.push_back(e);
        from->adj_out.push_back(e);
        to->adj_in.push_back(e);
        return e;
    }

    Edge* get_edge(Vertex* from, Vertex* to) {
        for (auto e : edges_l) {
            if (e->from == from && e->to == to) return e;
        }
        return nullptr;
    }
    Vertex* get_vertex(V index) {
        for (auto v : vertices_l) {
            if (v->index == index) return v;
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
    void ElginDanil_bfs(Vertex* s) {
        for (auto v : vertices_l) {
            v->color = "WHITE";
            v->d = -1;
            v->parent = nullptr;
        }
        s->color = "WHITE";
        s->d = 0;
        s->parent = nullptr;
        list<Vertex*> my_queue;
        my_queue.push_back(s);
        while (!my_queue.empty()) {
            Vertex* v = my_queue.front();
            my_queue.pop_front();
            for (auto e : v->adj_out) {
                Vertex* w = e->to;
                if (e->capacity > 0 && w->color == "WHITE") {
                    w->color = "GRAY";
                    w->d = v->d + 1;
                    w->parent = v;
                    my_queue.push_back(w);
                }
            }
            v->color = "BLACK";
        }
    }
};
class helper {
    public:
    int start;
    int size;

};
class augmenting_path {
    public:
    int number_of_vertices;
    int min_capacity;
    vector<Graph<int, int>::Vertex*> vertices;
    augmenting_path() {
        number_of_vertices = 0;
        min_capacity = INT_MAX;
    }
};
template <typename V, typename E>
Graph<V, E> construct_residual_network(Graph<V, E>& graph) {
    Graph<V, E> residual_network;
    vector<typename Graph<V, E>::Vertex*> vec(graph.num_vertices() + 1);
    for (auto v: graph.vertices()) {
        vec[v->index] = residual_network.insert_vertex(v->index);
    }
    for (auto e: graph.edges()) {
        residual_network.insert_edge(vec[e->from->index], vec[e->to->index], e->capacity - e->flow, 0);
        if (e->flow > 0) {
            residual_network.insert_edge(vec[e->to->index], vec[e->from->index], e->flow, 0);
        }
    }
    return residual_network;
}
template <typename V, typename E>
augmenting_path find_augmenting_path(Graph<V, E>& graph, typename Graph<V, E>::Vertex*& last) {
    typename Graph<V, E>::Vertex* current = last;
    if (current->parent == nullptr) return augmenting_path();
    augmenting_path path;
    while (current != nullptr) {
        path.number_of_vertices += 1;
        if (current->parent != nullptr) {
            E capacity = graph.get_edge(current->parent, current)->capacity;
            path.min_capacity = min(path.min_capacity, capacity);
        }
        path.vertices.push_back(current);
        current = current->parent;
    }
    return path;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Graph<int, int> graph;
    vector<Graph<int, int>::Vertex*> ver(n + 1);
    for (int i = 1; i <= n; i++) {
        ver[i] = graph.insert_vertex(i);
    }
    int u, v, c, f;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> c >> f;
        Graph<int, int>::Vertex* u1 = ver[u];
        Graph<int, int>::Vertex* v1 = ver[v];
        graph.insert_edge(u1, v1, c, f);
    }
    Graph<int, int> residual_network = construct_residual_network(graph);
    residual_network.ElginDanil_bfs(residual_network.get_vertex(1));
    Graph<int, int>::Vertex* n1 = residual_network.get_vertex(n);
    augmenting_path path = find_augmenting_path(residual_network, n1);
    if (path.number_of_vertices == 0) {
        cout << "NO PATH";
    }
    else {
        cout << path.number_of_vertices << " " << path.min_capacity << endl;
        for (auto it = path.vertices.rbegin(); it != path.vertices.rend(); ++it) {
            cout << (*it)->index << " ";
        }
        cout << endl;
    }
    return 0;
}
