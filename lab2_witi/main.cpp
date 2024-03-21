#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Task {
    int id;
    int time;
    int weight;   
    int deadline;
};

bool isLexicographicallySmaller(const vector<Task>& a, const vector<Task>& b) {
    for (int i = 0; i < min(a.size(), b.size()); i++) {
        if (a[i].id != b[i].id) {
            return a[i].id < b[i].id;
        }
    }
    return a.size() < b.size();
}

int main() {
    Task arr[100];
    ifstream load("data.txt");
    int n, c;
    string s;
    string s1[11] = { "data.10:", "data.11:","data.12:","data.13:","data.14:","data.15:","data.16:","data.17:","data.18:","data.19:","data.20:" };

    for (int iter = 0; iter < 11; iter++) {
        while (s != s1[iter]) {
            load >> s;
        }
        cout << "=" << s <<"=" << endl;
        load >> n;
        for (int i = 0; i < n; i++) {
            arr[i].id = i + 1;
            load >> arr[i].time >> arr[i].weight >> arr[i].deadline;
        }
        sort(arr, arr + n, [](const Task& a, const Task& b) {
            return a.id < b.id;
        });
        int N = 1 << n;
        vector<int> F(N, INT_MAX);
        vector<vector<Task>> task_order(N);

        F[0] = 0;
        for (int set = 1; set < N; set++) {
            c = 0;
            for (int i = 0, b = 1; i < n; i++, b *= 2) {
                if (set & b) {
                    c += arr[i].time;
                }
            }
            for (int k = 0, b = 1; k < n; k++, b *= 2) {
                if (set & b) {
                    int cost = F[set - b] + arr[k].weight * max(c - arr[k].deadline, 0);
                    if (cost < F[set] || (cost == F[set] && isLexicographicallySmaller(task_order[set - b], task_order[set]))) {
                        F[set] = cost;
                        task_order[set] = task_order[set - b];
                        task_order[set].push_back(arr[k]);
                    }
                }
            }
        }
        cout << "Opt val: " << F[N - 1] << endl;
        cout << "Order:" << endl;
        for (const auto& task : task_order[N - 1]) {
            cout << task.id <<" ";
        }
        cout << "\n\n";
    }
    load.close();
}