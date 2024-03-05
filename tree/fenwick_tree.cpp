#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int LSB(int x){
    return x & (-x);
}

int getSumTill(int index, const int* tree){

    int value = 0;
    while(index > 0){
        value += tree[index];
        index -= LSB(index);
    }
    return value;
}

void update(int index, int N, int update_val, int* tree){

    while(index <= N){
        tree[index] += update_val;
        index += LSB(index);
    }
}

int main(){

    int N, Q, U;
    cin >> N >> Q >> U;

    auto arr = new int[N+1];
    auto tree = new int[N+1];
    auto lsb = new int[N+1];
    auto dp = new int[N+1];
    vector<pair<int, int>> ranges;

    for(int i = 0; i <= N; i++) {
        tree[i] = 0;
        dp[i] = 0;
    }

    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
        dp[i] = arr[i] + dp[i-1];
    }

    for(int i = 1; i <= N; i++){
        tree[i] += arr[i];
        tree[i+LSB(i)] += tree[i];
    }

    int a, b, sum, i = Q;
    while(i > 0){
        cin >> a >> b;
        ranges.emplace_back(a, b);
        assert(a > 0 && b > 0 && a <= N && b <= N);

        sum = (a <= b ? getSumTill(b, tree) - getSumTill(a-1, tree) : 0);

        cout << "Fenwick Tree Sum from [" << a << ", " << b << "]: " << sum << "\n";
        cout << "DP Sum from [" << a << ", " << b << "]: " << (dp[b] - dp[a-1]) << "\n";

        i -= 1;
    }

    while(U > 0){
        cin >> a >> b;
        assert(a > 0 && a <= N);
        update(a, N, b, tree);
        arr[a] += b;
        U -= 1;
    }

    for(i = 1; i <= N; i++)
        dp[i] = arr[i] + dp[i-1];

    i = Q;
    while(i > 0){

        auto range = ranges.at(i-1);
        a = range.first;
        b = range.second;

        sum = (a <= b ? getSumTill(b, tree) - getSumTill(a-1, tree) : 0);

        cout << "Fenwick Tree Sum from [" << a << ", " << b << "]: " << sum << "\n";
        cout << "DP Sum from [" << a << ", " << b << "]: " << (dp[b] - dp[a-1]) << "\n";

        i -= 1;
    }

    free(arr);
    free(tree);
    free(lsb);
    free(dp);
    return 0;
}
