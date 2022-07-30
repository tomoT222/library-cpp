//0-indexed
struct UnionFind {
	vector<ll> par;
	vector<ll> depth;
	vector<ll> Size;
	ll tree_ko = 0;

	UnionFind(ll n = 1) {
		init(n);
	}

	void init(ll n) {
		par.resize(n); depth.resize(n); Size.resize(n);
		tree_ko = n;
		for (int i = 0; i < n; i++) {
			par[i] = i;
			depth[i] = 0;
			Size[i] = 1;
		}
	}
	ll find(ll x) {
		if (par[x] == x) {
			return x;
		}
		else {
			return par[x] = find(par[x]);
		}
	}
	void unite(ll x, ll y) {
		x = find(x); y = find(y);
		if (x == y) { return; }
		tree_ko--;
		if (depth[x] < depth[y]) {
			par[x] = y; Size[y] += Size[x];
		}
		else {
			par[y] = x; Size[x] += Size[y];
			if (depth[x] == depth[y])depth[x]++;
		}
	}
	bool same(ll x, ll y) {
		return find(x) == find(y);
	}
	ll sz(ll x) {
		return Size[find(x)];
	}
	ll ko() {
		return tree_ko;
	}
};
