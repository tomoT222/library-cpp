ll a[123456], w1[123456], w2[123456];
signed main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n, x; cin >> n >> x;
    // 前半 N/2 個を bit 全探索で全列挙する
    for (int i = 0; i < (1 << (n / 2)); i++) {
        ll sum = 0;
        for (int j = 0; j < (n / 2); j++) {
            if ((i / (1 << j)) % 2 == 0) sum += a[j];
        }
        w1[i] = sum;
    }

    // 後半 N - N/2 個を bit 全探索で全列挙する
    for (int i = 0; i < (1 << (n - (n / 2))); i++) {
        ll sum = 0;
        for (int j = 0; j < n - (n / 2); j++) {
            if ((i / (1 << j)) % 2 == 0) sum += a[j + (n / 2)];
    }
        w2[i] = sum;
    }

    // ソートしたうえで半分全列挙をする
    bool flag;
    sort(w1, w1 + (1 << (n / 2)));
    sort(w2, w2 + (1 << (n - (n / 2))));
    for (int i = 0; i < (1 << (n / 2)); i++) {
        ll rem = x - w1[i];
        ll pos1 = lower_bound(w2, w2 + (1 << (n - (n / 2))), rem) - w2;
        if (w2[pos1] == rem) flag = true;
    }
    if (flag == true) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
