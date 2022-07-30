struct prim {
	//計算量O(|E|log|V|)
	//E=V^2の時にクラスカルよりちょっと速い、O(V^2)
	ll cost = 0;
	vector<bool> used;

	//P...(v,c)
	prim(ll n, vector<vector<P>>& G, ll root = 0) {
		used.resize(n + 1);
		used[root] = 1;
		priority_queue<P, vector<P>, greater<P>> q;
		for (auto p : G[root]) {
			ll v = p.first, c = p.second;
			if (!used[v]) {
				q.emplace(c, v);
			}
		}
		while (!q.empty()) {
			ll v, c; tie(c, v) = q.top(); q.pop();
			if (!used[v]) {
				used[v] = 1;
				cost += c;
				for (auto p : G[v]) {
					ll nv = p.first, nc = p.second;
					if (!used[nv]) {
						q.emplace(nc, nv);
					}
				}
			}
		}
	}
	ll get() {
		return cost;
	}
};
