//Danil Elgin DSAI 04
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class helper {
public:
    int frequency = 0;
    int data;
    vector<int> indexes;
};
template<class T>
void DanilElgin_count_srt(vector<T>& initial, int maximum) {
    vector<int> frequency(1001, 0);
    vector<T> change(initial.size());
    for (int i = 0; i < initial.size(); i++) {
        ++frequency[initial[i].data];
    }
    for (int i = 1; i < frequency.size(); i++) {
        frequency[i] += frequency[i - 1];
    }
    for (int i = 0; i < initial.size(); i++) {
        change[frequency[initial[i].data] - 1] = initial[i];
        --frequency[initial[i].data];
    }
    swap(initial, change);
}
//DanilElgin_bucket_srt
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<helper> v(1001);
    vector<int> unique_numbers;
    int maximum = 1;
    for (int i = 0; i < n; i++) {
        int digit;
        cin >> digit;

        if (v[digit].frequency == 0) {
            unique_numbers.push_back(digit);
            v[digit].data = digit;
        }

        v[digit].indexes.push_back(i);
        v[digit].frequency += 1;
        maximum = max(maximum, v[digit].frequency);
    }
    vector<vector<helper>> buckets(maximum + 1);
    for (int num : unique_numbers) {
        buckets[v[num].frequency].push_back(v[num]);
    }
    for (int freq = 1; freq <= maximum; freq++) {
        if (!buckets[freq].empty()) {
            DanilElgin_count_srt(buckets[freq], maximum);
            for (const auto& el : buckets[freq]) {
                for (int idx : el.indexes) {
                    cout << el.data << " " << idx << "\n";
                }
            }
        }
    }

    return 0;
}

