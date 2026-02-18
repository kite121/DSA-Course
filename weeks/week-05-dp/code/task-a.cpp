// Danil Elgin DSAI 04
// BubblesSort algorithm was taken from the first lab
#include <iostream>
#include <vector>
using namespace std;
void bubbleSort(vector<int>& f, vector<int>& s, vector<int>& p, int n) {
    bool swap = true;
    while (swap) {
        swap = false;
        for (int i = 1; i < n; i++) {
            if (f[i - 1] > f[i]) {
                swap = true;
                int temp_f = f[i - 1];
                int temp_s = s[i - 1];
                int temp_p = p[i - 1];
                s[i - 1] = s[i];
                s[i] = temp_s;
                p[i - 1] = p[i];
                p[i] = temp_p;
                f[i - 1] = f[i];
                f[i] = temp_f;
            }
        }
    }
}
int maximum_profit(vector<int>& finish, vector<int>& start,
    vector<int>& cost, int point, vector<int>& check) {
    if (check[point] != 0) {
        return check[point];
    }
    int max_index = -1;
    for (int i = point - 1; i >= 0; i--) {
        if (finish[i] <= start[point]) {
            max_index = i;
            break;
        }
    }
    if (max_index == -1) {
        check[point] = max(cost[point], maximum_profit(finish, start, cost, point - 1, check));
    }
    else {
        check[point] = max(cost[point] + maximum_profit(finish, start, cost, max_index, check),
   maximum_profit(finish, start, cost, point - 1, check));
    }
    return check[point];
}
int main() {
    int n;
    cin >> n;
    vector<int> s(n), p(n), f(n), check(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        check[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    bubbleSort(f, s, p, n);
    check[0] = p[0];
    maximum_profit(f, s, p, n - 1, check);
    int maximum = -1;
    for (int i = 0; i < n; i++) {
        maximum = max(maximum, check[i]);
    }
    cout << maximum << endl;
    return 0;
}
