rep(A, (1 << n)) {
    vector<ll> sep = { };
    rep(B, n) {
        if ((A & (1 << B)) > 0) {
            sep.push_back(B);
        }
    }
    // if (sep.size() == 0) { continue; }

}
