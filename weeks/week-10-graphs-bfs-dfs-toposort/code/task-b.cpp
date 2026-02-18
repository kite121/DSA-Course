//Danil Elgin DSAI 04
//Part of the graph class implementation is taken from the lab
//The implementation of the dfs and bfs functions are taken from the slides of the tutorial
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

template <typename V>
class Graph {
public:
    class Vertex {
    public:
        list<Vertex*> adj_in;
        list<Vertex*> adj_out;
        V value;
        int index;
        Vertex(V v, int index) : value(v), index(index) {};
        string color;
        Vertex* parent;
        int start;
        int finish;
        int d;
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

    Vertex* insert_vertex(V value, int index) {
        Vertex* v = new Vertex(value, index);
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
                if (e->color == "WHITE") {
                    e->color = "GRAY";
                    e->d = v->d + 1;
                    e->parent = v;
                    my_queue.push_back(e);
                }
            }
            v->color = "BLACK";
        }
    }
    void ElginDanil_dfs() {
        for (auto it : vertices_l) {
            it->color = "WHITE";
            it->parent = nullptr;
        }
        int time = 0;
        for (auto it : vertices_l) {
            if (it->color == "WHITE") {
                ElginDanil_dfs_visit(it, time);
            }
        }
    }

    void ElginDanil_dfs_visit(Vertex* v, int& time) {
        time++;
        v->start = time;
        v->color = "GRAY";
        for (auto it : v->adj_out) {
            if (it->color == "WHITE") {
                it->parent = v;
                ElginDanil_dfs_visit(it, time);
            }
            if (it->color == "GRAY") {
                cycle = 1;
                return;
            }
        }
        v->color = "BLACK";
        time++;
        v->finish = time;
    }

    list<Vertex*> ElginDanil_topsort() {
        list<Vertex*> tops;
        ElginDanil_dfs();
        if (cycle == 1) {
            return tops;
        }

        for (auto it : vertices_l) {
            tops.push_back(it);
        }

        tops.sort([](const Vertex* v1, const Vertex* v2) {
            return v1->finish > v2->finish;
        });

        return tops;
    }
};
class helper {
    public:
    int start;
    int size;

};
int main() {
    Graph<int> graph;
    int n, r;
    cin >> n >> r;
    vector<Graph<int>::Vertex*> v(n);
    int digit;
    for (int i = 0; i < n; i++) {
        cin >> digit;
        v[i] = graph.insert_vertex(digit, i);
    }
    for (int i = 0; i < n; i++) {
        if (v[i]->value >= 0) {
            graph.insert_edge(v[i], v[v[i]->value]);
        }
    }
    vector p(n, 0);
    int root;
    for (int i = 0; i < r; i++) {
        cin >> root;
        graph.ElginDanil_bfs(v[root]);
        for (auto it : graph.vertices()) {
            if (it->color == "BLACK") {
                p[it->index] = 1;
            }
        }
    }
    vector<helper> output;
    helper help;
    help.size = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] == 1) {
            if (help.size != 0) {
                output.push_back(help);
            }
            help.size = 0;
        }
        if (p[i] == 0) {
            if (help.size == 0) {
                help.start = i;
            }
            help.size++;
        }
    }
    if (help.size != 0) {
        output.push_back(help);
    }
    cout << output.size() << endl;
    for (int i = 0; i < output.size(); i++) {
        cout << output[i].start << " " << output[i].size << endl;
    }
    return 0;
}
