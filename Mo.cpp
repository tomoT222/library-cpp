struct Mo {
	int n;
	vector< pair< int, int > > lr;
 
	explicit Mo(int n) : n(n) {}
 
	void add(int l, int r) { /* [l, r) */
		lr.emplace_back(l, r);
	}
 
	template< typename AL, typename AR, typename EL, typename ER, typename O >
	void build(const AL& add_left, const AR& add_right, const EL& erase_left, const ER& erase_right, const O& out) {
		int q = (int)lr.size();
		int bs = n / min< int >(n, sqrt(q));
		vector< int > ord(q);
		iota(begin(ord), end(ord), 0);
		sort(begin(ord), end(ord), [&](int a, int b) {
			int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
			if (ablock != bblock) return ablock < bblock;
			return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
			});
		int l = 0, r = 0;
		for (auto idx : ord) {
			while (l > lr[idx].first) add_left(--l);
			while (r < lr[idx].second) add_right(r++);
			while (l < lr[idx].first) erase_left(l++);
			while (r > lr[idx].second) erase_right(--r);
			out(idx);
		}
	}
 
	template< typename A, typename E, typename O >
	void build(const A& add, const E& erase, const O& out) {
		build(add, add, erase, erase, out);
	}
};
 
 
 
 
int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	//cout << fixed << setprecision(15);
 
	ll n, q; cin >> n >> q;
	
	vector<ll> A(n);
	for (auto& a : A) { cin >> a; }
 
	Mo mo(n);
	rep(i, q) {
		ll a, b; cin >> a >> b;
		mo.add(a - 1, b);
	}
 
	vector<ll> cnt(1000001), ans(q);
	ll sum = 0;
	auto add = [&](ll i) { //足す前に0の時、種類数+1
		if (cnt[A[i]]++ == 0) ++sum;
	};
	auto erase = [&](ll i) { //引いた後に0の時、種類数-1
		if (--cnt[A[i]] == 0) --sum;
	};
	auto out = [&](int q) { //種類数を記録
		ans[q] = sum;
	};
 
	mo.build(add, erase, out);
	for (auto& p : ans) cout << p << "\n";
 
	return 0;
}
