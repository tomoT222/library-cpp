ll V; //頂点数
vector<ll> G[MAX_V];  //グラフの隣接リスト表現
vector<ll> rG[MAX_V]; //辺の向きを逆にしたグラフ
vector<ll> vs;        //帰りがけ順の並び
bool used[MAX_V];     //すでに調べたか
ll cmp[MAX_V]; //属する強連結成分のトポロジカル順序

void add_edge(int from, int to) {
	G[from].push_back(to);
	rG[to].push_back(from);
}
void dfs(int v) {
	used[v] = true;
	rep(i, G[v].size()) {
		if (!used[G[v][i]]) { dfs(G[v][i]); }
	}
	vs.push_back(v);
}
void rdfs(int v, int k) {
	used[v] = true; cmp[v] = k;
	rep(i, rG[v].size()) {
		if (!used[rG[v][i]]) { rdfs(rG[v][i], k); }
	}
}
ll scc() {
	memset(used, 0, sizeof(used));
	vs.clear();
	rep(v, V) {
		if (!used[v]) { dfs(v); }
	}
	memset(used, 0, sizeof(used));
	ll k = 0;
	for (int i = vs.size() - 1; i >= 0; i--) {
		if (!used[vs[i]]) { rdfs(vs[i], k++); }
	}
	return k;
}
