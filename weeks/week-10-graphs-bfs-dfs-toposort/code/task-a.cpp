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
        Vertex(V v) : value(v) {};
        string color;
        Vertex* parent;
        int start;
        int finish;
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
        for (auto it : vertices_l) {
            if (it->value == value) {
                return it;
            }
        }
        Vertex* v = new Vertex(value);
        vertices_l.push_back(v);
        return v;
    }

    Edge* insert_edge(Vertex* from, Vertex* to) {
        for (auto it : edges_l) {
            if (it->from == from && it->to == to) {
                return it;
            }
        }
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

    void dfs() {
        for (auto it : vertices_l) {
            it->color = "WHITE";
            it->parent = nullptr;
        }
        int time = 0;
        for (auto it : vertices_l) {
            if (it->color == "WHITE") {
                dfs_visit(it, time);
            }
        }
    }

    void dfs_visit(Vertex* v, int& time) {
        time++;
        v->start = time;
        v->color = "GRAY";
        for (auto it : v->adj_out) {
            if (it->color == "WHITE") {
                it->parent = v;
                dfs_visit(it, time);
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

    list<Vertex*> topsort() {
        list<Vertex*> tops;
        dfs();
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

int main() {
    Graph<char> graph;
    int n;
    cin >> n;
    string word_1;
    string word_2;
    cin >> word_1;
    if (n == 1) {
        for (int j = 0; j < word_1.length(); j++) {
            graph.insert_vertex(word_1[j]);
        }
    }
    bool check = true;
    for (int i = 1; i < n; i++) {
        cin >> word_2;
        if (word_1.length() >= word_2.length()) {
            bool flag = false;
            for (int j = 0; j < word_2.length(); j++) {
                if (word_1[j] == word_2[j]) {
                    graph.insert_vertex(word_2[j]);
                }
                else if (!flag) {
                    flag = true;
                    auto first = graph.insert_vertex(word_1[j]);
                    auto second = graph.insert_vertex(word_2[j]);
                    graph.insert_edge(first, second);
                }
                else {
                    graph.insert_vertex(word_1[j]);
                    graph.insert_vertex(word_2[j]);
                }
            }
            if (!flag && word_1.length() > word_2.length()) {
                check = false;
                break;
            }
            for (int z = word_2.length(); z < word_1.length(); z++) {
                graph.insert_vertex(word_1[z]);
            }
        }
        else {
            bool flag = false;
            for (int j = 0; j < word_1.length(); j++) {
                if (word_1[j] == word_2[j]) {
                    graph.insert_vertex(word_2[j]);
                }
                else if (!flag) {
                    flag = true;
                    auto first = graph.insert_vertex(word_1[j]);
                    auto second = graph.insert_vertex(word_2[j]);
                    graph.insert_edge(first, second);
                }
                else {
                    graph.insert_vertex(word_1[j]);
                    graph.insert_vertex(word_2[j]);
                }
            }
            for (int z = word_1.length(); z < word_2.length(); z++) {
                graph.insert_vertex(word_2[z]);
            }
        }
        word_1 = word_2;
    }
    auto list = graph.topsort();
    if (list.empty() || !check) {
        cout << "Doh";
    }
    else {
        for (auto it : list) {
            cout << it->value;
        }
    }
    return 0;
}
