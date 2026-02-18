// Danil Elgin DSAI 04
#include <iostream>
#include <vector>
using namespace std;
class Node {
public:
    int data;
    Node* previous_value;
    int value;
};
int main() {
    int n, m;
    cin >> n >> m;
    Node nodes[n][m];
    int table[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
        }
    }
    nodes[0][0].data = table[0][0];
    nodes[0][0].previous_value = nullptr;
    for (int i = 1; i < n; i++) {
        nodes[i][0].data = table[i][0] + nodes[i - 1][0].data;
        nodes[i][0].previous_value = &nodes[i - 1][0];
        nodes[i][0].value = table[i - 1][0];
    }
    for (int i = 1; i < m; i++) {
        nodes[0][i].data = table[0][i] + nodes[0][i - 1].data;
        nodes[0][i].previous_value = &nodes[0][i - 1];
        nodes[0][i].value = table[0][i - 1];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (nodes[i - 1][j].data > nodes[i][j - 1].data) {
                nodes[i][j].data = nodes[i][j - 1].data + table[i][j];
                nodes[i][j].previous_value = &nodes[i][j - 1];
                nodes[i][j].value = table[i][j - 1];
            }
            else {
                nodes[i][j].data = nodes[i - 1][j].data + table[i][j];
                nodes[i][j].previous_value = &nodes[i - 1][j];
                nodes[i][j].value = table[i - 1][j];
            }
        }
    }
    int path[n + m + 1];
    Node* helper = &nodes[n - 1][m - 1];
    path[0] = table[n - 1][m - 1];
    int counter = 1;
    while (true) {
        if (helper->previous_value == nullptr) {
            break;
        }
        path[counter] = helper->value;
        helper = helper->previous_value;
        counter++;
    }
    cout << nodes[n - 1][m - 1].data << endl;
    for (int i = counter - 1; i >= 0; i--) {
        cout << path[i] << " ";
    }
}
