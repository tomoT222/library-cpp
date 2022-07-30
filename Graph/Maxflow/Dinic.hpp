//辺を表す構造体（行先、容量、逆辺）
struct edge { ll to, cap, rev; };
 
vector<edge> G[100005]; //グラフの隣接リスト表現
ll level[100005]; // sからの距離
ll iter[100005];// どこまで調べ終わったか
 
//fromからtoへ向かう容量capの辺をグラフに追加する
void add_edge(ll from, ll to, ll cap) {
	G[from].push_back({ to, cap, G[to].size() });
	G[to].push_back({ from, 0, G[from].size() - 1 });
}
// sからの最短距離をBFSで計算する
void bfs(ll s) {
	memset(level, -1, sizeof(level));
	queue<ll> que;
	level[s] = 0;
	que.push(s);
	while (!que.empty()) {
		ll v = que.front(); que.pop();
		for (int i = 0; i < G[v].size(); i++) {
			edge& e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0) {
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}
//増加パスをDFSで探索
ll dfs(ll v, ll t, ll f) {
	if (v == t) { return f; }
	for (ll& i = iter[v]; i < G[v].size(); i++) {
		edge& e = G[v][i];
		if (e.cap > 0 && level[v] < level[e.to]) {
			ll d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
//sからtへの最大流を求める
ll max_flow(ll s, ll t) {
	ll flow = 0;
	for (;;) {
		bfs(s);
		if (level[t] < 0) { return flow; }
		memset(iter, 0, sizeof(iter));
		ll f;
		while ((f = dfs(s, t, INF)) > 0) {
			flow += f;
		}
	}
}
