//BIT
struct BIT {
	//計算量は共にO(logN)
	//[1, nn]
	vector<ll> bit; ll nn;
	BIT(ll n) {
		nn = n + 1;
		bit.resize(nn);
	}
	ll sum(ll i) {//iまでの和
		ll s = 0;
		while (i > 0) {
			s += bit[i]; i -= i & -i;
		}
		return s;
	}
	void add(ll i, ll x) {//iの値にxを加える
		while (i <= nn) {
			bit[i] += x; i += i & -i;
		}
	}
};
