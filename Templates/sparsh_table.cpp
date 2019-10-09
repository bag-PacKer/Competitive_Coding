#include<bits/stdc++.h>
using namespace std;
/*
Range sum query
Provided with an integer array Arr of length N, answer Q queries:
given L and R, 0 ≤ L, R < N, find ArrL + ArrL + 1 + … + ArrR.
N and Q are up to 105, |Arri| ≤ 109.
*/
const int k = 16;
const int N = 1e5;
const int ZERO = 0; // ZERO + x = x + ZERO = x (for any x)

long long table[N][k + 1]; // k + 1 because we need to access table[r][k]
int Arr[N];

int main()
{
    int n, L, R, q;
    cin >> n; // Input array size where we need to perform range query
    for(int i = 0; i < n; i++)
        cin >> Arr[i];

    // build Sparse Table
    for(int i = 0; i < n; i++)
        table[i][0] = Arr[i]; // basic stap
    //Function is associative: a + (b + c) = (a + b) + c
    for(int j = 1; j <= k; j++) {
        // table[i][j] has sum of element Arr[i]+Arr[i+1]+ ... + Arr[i+2^j - 1]
        for(int i = 0; i <= n - (1 << j); i++)
            table[i][j] = table[i][j - 1] + table[i + (1 << (j - 1))][j - 1]; // Sum is associative, so this operation is meaningful
        //Instade of sum there can be any operation which is Associative.
    }

    cin >> q; // number of queries
    for(int i = 0; i < q; i++) {
        cin >> L >> R; // boundaries of next query, 0-indexed
        long long answer = ZERO;//ZERO is neutral element for calculating sum, this is depend on function
        // took the binary representation to cover L to R range
        for(int j = k; j >= 0; j--) {
            if(L + (1 << j) - 1 <= R) {
                answer = answer + table[L][j];
                L += 1 << j; // instead of having L', we increment L directly
            }
        }
        cout << answer << endl; // Final answer
    }
    return 0;
}
