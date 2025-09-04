#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// Function to precompute prime status for indices 1 through n (inclusive)
vector<bool> sieve(int n) {
    vector<bool> isPrime(n+1, true);
    if(n >= 0) isPrime[0] = false; // though we are not using 0 index
    if(n >= 1) isPrime[1] = false; // 1 is not prime
    for (int i = 2; i * i <= n; i++) {
        if(isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

// The main function that solves the problem
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    // Maximum N from constraints is 500; precompute prime status for indices up to 500
    const int MAXN = 500;
    vector<bool> isPrime = sieve(MAXN);

    while(T--) {
        int N, M, K;
        cin >> N >> M >> K;

        // dp[i][j] : number of ways to form an i-digit special number with remainder j mod M
        vector<vector<long long>> dp(N+1, vector<long long>(M, 0));

        // Handle base: first digit (i = 1) is non-prime index so uses non-prime digits but cannot be 0
        // Non-prime digits include: {0,1,4,6,8,9}, but for i=1, cannot be 0
        vector<int> nonPrimeDigits = {1,4,6,8,9};
        // For later non-prime positions, 0 is allowed, so include it
        vector<int> nonPrimeDigitsLater = {0,1,4,6,8,9};
        
        // Prime digits allowed: {2,3,5,7}
        vector<int> primeDigits = {2,3,5,7};

        // Initialize for first digit (position 1, which is a non-prime index always)
        for (int d : nonPrimeDigits) {
            dp[1][d % M] = (dp[1][d % M] + 1) % MOD;
        }

        // Build dp from digit 2 to N
        for (int pos = 2; pos <= N; pos++) {
            // Choose allowed digits based on whether the position is prime valued or not
            vector<int> allowed;
            if(isPrime[pos]) {
                allowed = primeDigits;
            } else {
                allowed = nonPrimeDigitsLater;
            }
            
            for (int r = 0; r < M; r++) {
                if(dp[pos-1][r] == 0) continue;
                for (int d : allowed) {
                    int newR = (r * 10 + d) % M;
                    dp[pos][newR] = (dp[pos][newR] + dp[pos-1][r]) % MOD;
                }
            }
        }

        cout << dp[N][K] << "\n";
    }

    return 0;
}