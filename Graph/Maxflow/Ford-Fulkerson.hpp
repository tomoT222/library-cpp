//ACLを使った方がいいよ
//O(F*E) 最大流量F 辺数E

//辺を表す構造体（行先、容量、逆辺）
struct edge { ll to, cap, rev; };

struct Maxflow {
	vector<vector<edge>> G; //グラフの隣接リスト表現
	vector<bool> used; //DESですでに調べたか

	Maxflow(ll V) {
		G.resize(V); used.resize(V);
	}

	//fromからtoへ向かう容量capの辺をグラフに追加する
	void add_edge(ll from, ll to, ll cap) {
		G[from].push_back({ to, cap, G[to].size() });
		G[to].push_back({ from, 0, G[from].size() - 1 });
	}
	//増加パスをDFSで探索
	ll dfs(ll v, ll t, ll f) {
		if (v == t) { return f; }
		used[v] = true;
		for (int i = 0; i < G[v].size(); i++) {
			edge& e = G[v][i];
			if (!used[e.to] && e.cap > 0) {
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
			//memset(used, 0, sizeof(used));
			rep(i, used.size()) { used[i] = 0; }
			ll f = dfs(s, t, INF);
			if (f == 0) { return flow; }
			flow += f;
		}
	}
};
