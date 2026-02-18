//Danil Elgin DSAI 04 
#include <iostream>
#include <vector>
using namespace std;
class CPU {
    private:
        int rank;
        string name;
    public:
    CPU(int rank, const string& name) {
        this->rank = rank;
        this->name = name;
    }

    int get_rank() const
    {
        return rank;
    }

    string get_name() const {
        return name;
    }
};
int select(vector<int>& ranks,int rank,  int upper, int low);
int median_medians(vector<int>& ranks, int upper, int low);
void sorting(vector<int>& ranks, int upper, int low);
int main() {
    int n;
    cin >> n;
    vector<int> ranks;
    vector<CPU> cpus;
    for(int i=0;i<n;i++) {
        int rank;
        string name;
        cin >> rank >> name;
        ranks.emplace_back(rank);
        cpus.emplace_back(rank, name);
    }
    int points = select(ranks, (ranks.size() / 2) + 1, ranks.size() - 1, 0);
    for(int i = 0; i < cpus.size(); i++) {
        if (cpus[i].get_rank() == points) {
            cout << cpus[i].get_name() << endl;
            break;
        }
    }
}
int select(vector<int>& ranks, int rank, int upper, int low) {
    int median = median_medians(ranks, upper, low);
    vector<int> left, right;
    for (int i = low; i <= upper; i++) {
        if (ranks[i] < median) {
            left.push_back(ranks[i]);
        }
        else if (ranks[i] > median) {
            right.push_back(ranks[i]);
        }
    }
    if (left.size() + 1 == rank) {
        return median;
    }
    else if (left.size() + 1 > rank) {
        return select(left, rank,left.size() - 1, 0);
    }
    else {
        return select(right, rank - left.size() - 1, right.size() - 1, 0);
    }
}
int median_medians(vector<int>& ranks, int upper, int low) {
    if ((upper - low + 1) <= 5) {
        sorting(ranks, upper, low);
        for(int j = low; j <= upper; j++){
        }
        if ((upper - low) % 2 != 0){
            return ranks[low + 1 + (upper - low) / 2];
        }
        return ranks[low + (upper - low) / 2];
    }
    vector<int> medians;
    int i = 0, j = 4;
    while (i < upper + 1){
        if (j > upper) {
            medians.push_back(median_medians(ranks, upper, i));
        }
        else {
            medians.push_back(median_medians(ranks, j, i));
        }
        i += 5;
        j += 5;
    }
    int median = median_medians(medians, medians.size() - 1, 0);
    return median;
}
void sorting(vector<int>& ranks, int upper, int low) {
    if (upper != low){
        for (int i = low; i < low + (upper - low) / 2 + 1; i++) {
            int min = 10000;
            int index = i;
            for (int j = i; j < low + (upper - low) + 1; j++) {
                if (min > ranks[j]) {
                    min = ranks[j];
                    index = j;
                }
            }
            int temp = ranks[i];
            ranks[i] = min;
            ranks[index] = temp;
    }
    }
}
