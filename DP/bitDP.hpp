#include<bits/stdc++.h>
using ll = long long;
using namespace std;
const ll INF = 10000000000000000;
/* 入力 */
ll n, T;
ll cost[213456];

/* メモ再帰 */
ll dp[1 << 21];
ll rec(ll bit) {
    // すでに探索済みだったらリターン
    if (dp[bit] != -1) return dp[bit];

    // 答えを格納する変数
    int res = INF;
    for (int v = 0; v < n; v++) {
        //集合bitにvが含まれるか
        if ((bit & (1 << v)) != 0) {
            // bit の v を除いたもの
            ll prev_bit = bit & ~(1 << v);

            ll anscost = 0, rp = rec(prev_bit);
            
            
            
            // 再帰的に探索
            if (res > anscost) {
                res = anscost;
            }
        }
    }
    return dp[bit] = res; // メモしながらリターン
}

signed main() {
    // 入力
    cin >> n >> T;
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }

    // 初期値
    // テーブルを全部 -1 にしておく (-1 でなかったところは探索済)
    for (int bit = 0; bit < (1 << n); ++bit) dp[bit] = -1;
    dp[0] = 0;
    
    cout << rec((1 << n) - 1) << endl;
}
