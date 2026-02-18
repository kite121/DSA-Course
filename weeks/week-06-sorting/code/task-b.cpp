//Danil Elgin DSAI 04
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
class point {
public:
    point(double x, double y): x(x), y(y) {
        length = sqrt(x*x + y*y);
    }
    double x;
    double y;
    double length;
};
template <typename T>
void DanilElgin_bubble_srt(vector<T>& initial) {
    bool swap = true;
    while (swap) {
        swap = false;
        for (int i = 1; i < initial.size(); i++) {
            if (initial[i - 1].length > initial[i].length) {
                swap = true;
                T temp = initial[i - 1];
                initial[i -1] = initial[i];
                initial [i] = temp;
            }
        }
    }
}
template <typename T>
void DanilElgin_bucket_srt(vector<vector<T>>& initial) {
    for (int i = 0; i < initial.size(); i++) {
        if (!initial[i].empty()) {
            DanilElgin_bubble_srt<T>(initial[i]);
            for (int j = 0; j < initial[i].size(); j++) {
                cout << fixed << setprecision(4) << initial[i][j].x << " "
                << initial[i][j].y << endl;
            }
        }
    }
}
int main() {
    int bucket_size;
    cin >> bucket_size;
    double x, y;
    vector<vector<point>> buckets(bucket_size * 2);
    for (int i = 0; i < bucket_size; i++) {
        cin >> x >> y;
        point point_t(x, y);
        buckets[(int)(point_t.length * bucket_size)].push_back(point_t);
    }
    DanilElgin_bucket_srt(buckets);
}
