#include <iostream>
#include <set>
#include <cassert>

using namespace std;
int N, *freq, *freq_sum, **dp;

int main(){

    cin >> N;
    freq = new int[N];
    freq_sum = new int[N];
    dp = new int*[N];

    for(int i = 0; i < N; i++) {
        cin >> freq[i];
        dp[i] = new int[N];
        dp[i][i] = freq[i];
    }

    freq_sum[0] = freq[0];
    for(int i = 1; i < N; i++)
        freq_sum[i] = freq[i] + freq_sum[i-1];

    int cost;
    for(int l = 1; l < N; l++){
        for(int i = 0; i < N-l; i++){

            dp[i][i+l] = INT_MAX;
            auto c = (i > 0 ? freq_sum[i+l]-freq_sum[i-1] : freq_sum[i+l]);

            for(int k = 0; k <= l; k++){

                cost = (k > 0 ? dp[i][i+k-1] : 0);
                cost += (k < l ? dp[i+k+1][i+l] : 0);
                cost += c;

                if(cost < dp[i][i+l])
                    dp[i][i+l] = cost;
            }
        }
    }

    cout << "Optimal Binary Search Tree Cost " << dp[0][N-1] << "\n";

    free(freq);
    free(freq_sum);
    free(dp);

    return 0;
}