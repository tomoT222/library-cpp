//BIT
struct BIT {
	// 計算量は共にO(logN)
	// [1, n]
	ll n, two = 1;
	vector<ll> bit;
	BIT(ll kn) {
		n = kn + 1;
		while(two * 2 <= n) {
			two *= 2; // n以下の最小の2べき
		}
		bit.resize(n);
	}
	ll sum(ll i) { // iまでの和
		ll s = 0;
		while (i > 0) {
			s += bit[i]; i -= i & -i;
		}
		return s;
	}
	void add(ll i, ll x) { // iの値にxを加える
		while (i <= n) {
			bit[i] += x; i += i & -i;
		}
	}
	ll LowerBound(ll w) { // v1+v2+...+vx >= w となる最小のxを求める
		if (w <= 0) return 0;
		ll x = 0;
		for(int k = two; k > 0; k /= 2) {
			if(x + k <= n && bit[x + k] <= w){
				w -= bit[x + k];
				x += k;
			}
		}
		return x + 1;
	}
};
