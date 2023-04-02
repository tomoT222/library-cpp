/*
1. table[0][i]を決める
2. table[i(>=1)][j]を遷移
3. 頑張る
*/
    vector<ll> res(n);
    for (int h = 0; h < n; h++) {
        cin >> res[h];
    }

    vector<vector<ll>> table(70, vector<ll>(n));
    for (int h = 0; h < n; h++) {
        table[0][res[h]] = h;
    }
    for (int i = 1; i < 70; i++) {
        for (int j = 0; j < n; j++) {
            table[i][j] = table[i - 1][table[i - 1][j]];
        }
    }
