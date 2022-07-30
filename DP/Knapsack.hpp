//01ナップザック(nW)
ll n, W; ll w[345678], v[345678], dp[5000][23456];
void solve() {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j <= W; j++) {
			if (j < w[i]) {
				dp[i][j] = dp[i + 1][j];
			}
			else{
				dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - w[i]] + v[i]);
			}
		}
	}
	ll res = dp[0][W];
	return res;
}

//01ナップザックその2(n Σi  vi)
ll dp[201][654321]; ll n, W;
ll w[4321], v[4321];
ll solve() {
	fill(dp[0], dp[0] + 654321, INF);
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 654321; j++) {
			if (j < v[i]) {
				dp[i + 1][j] = dp[i][j];
			}
			else {
				dp[i + 1][j] = min(dp[i][j], dp[i][j - v[i]] + w[i]);
			}
		}
	}
	ll res = 0;
	for (int i = 0; i < 654321; i++) {
		if (dp[n][i] <= W) { res = i; }
	}
	return res;
}


//01ナップザックその3(n Σi wi)
ll dp[201][200003]; ll n, W;
ll w[4321], v[4321];
ll solve() {
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 200002; j++) {
			if (j < w[i]) {
				dp[i + 1][j] = dp[i][j];
			}
			else {
				dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
			}
		}
	}
	ll res = dp[n][W];
	return res;
}
