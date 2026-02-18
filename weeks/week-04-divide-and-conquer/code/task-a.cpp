// Elgin Danil DSAI 04
#include <iostream>
#include <vector>
using namespace std;
int searching(int target, vector<int> v, int k, int low, int upper);
int main() {
    int n, k, m;
    cin >> n >> k;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        v.push_back(temp);
    }
    int current;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> current;
        cout << searching(current, v, k, 0, n - 1) << endl;
    }
}
int searching(int target, vector<int> v, int k, int low, int upper) {
    if (low > upper) {
        return -1;
    }
    if (low == upper) {
        if (v[low] == target) {
            return low;
        }
        return -1;
    }
    vector<int> points;
    points.clear();
    int mid = (upper - low) / k;
    points.push_back(low);
    for (int i = 1; i < k; i++) {
        points.push_back(low + mid * i);
    }
    points.push_back(upper);
    for (int i = 0; i < k; i++) {
        if (v[points[i]] == target) {
            return points[i];
        }
        if (v[points[i + 1]] == target) {
            return points[i + 1];
        }
        if (v[points[i]] < target && v[points[i + 1]] > target) {
            return searching(target, v, k, points[i] + 1, points[i + 1] - 1);
        }
    }
    return -1;
}
