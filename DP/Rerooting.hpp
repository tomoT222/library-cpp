/* Rerooting: 全方位木 DP
	https://algo-logic.info/tree-dp/
	問題ごとに以下を書き換える
	- 型DPと単位元
	- 型DPに対する二項演算 merge
	- まとめたDPを用いて新たな部分木のDPを計算する add_root
	計算量: O(N)

	Rerooting G(N);
	G.add_edge(a,b); (0-indexed)
	G.build();
*/
struct Rerooting {
	/* start 問題ごとに書き換え */
	struct DP {  // DP の型
		ll ch; ll sm;
		DP(ll ch, ll sm) : ch(ch), sm(sm) {}
	};
	const DP identity = DP(0, 0);  // 単位元(末端の値は add_root(identity) になるので注意)
	function<DP(DP, DP)> merge = [](DP dp_cum, DP d) -> DP {
		// return DP(max(dp_cum.dp, d.dp));
		return DP(dp_cum.ch + d.ch, dp_cum.sm + d.sm);
	};
	function<DP(DP)> add_root = [](DP d) -> DP {
		return DP(d.ch + 1, d.sm + d.ch);
	};
	/* end 問題ごとに書き換え */
	// グラフの定義
	struct Edge {
		ll to;
	};
	using Graph = vector<vector<Edge>>;
	vector<vector<DP>> dp;  // dp[v][i]: vから出るi番目の有向辺に対応する部分木のDP
	vector<DP> ans;         // ans[v]: 頂点vを根とする木の答え
	Graph G;
	Rerooting(ll N) : G(N) {
		dp.resize(N);
		ans.assign(N, identity);
	}
	void add_edge(ll a, ll b) {
		G[a].push_back({ b });
	}
	void build() {
		dfs(0);            // 普通に木DP
		bfs(0, identity);  // 残りの部分木に対応するDPを計算
	}
	DP dfs(ll v, ll p = -1) {  // 頂点v, 親p
		DP dp_cum = identity;
		ll deg = G[v].size();
		dp[v] = vector<DP>(deg, identity);
		for (int i = 0; i < deg; i++) {
			ll u = G[v][i].to;
			if (u == p) continue;
			dp[v][i] = dfs(u, v);
			dp_cum = merge(dp_cum, dp[v][i]);
		}
		return add_root(dp_cum);
	}
	void bfs(ll v, const DP& dp_p, ll p = -1) {  // bfs だが、実装が楽なので中身は dfs になっている
		ll deg = G[v].size();
		for (int i = 0; i < deg; i++) {  // 前のbfsで計算した有向辺に対応する部分木のDPを保存
			if (G[v][i].to == p) dp[v][i] = dp_p;
		}
		vector<DP> dp_l(deg + 1, identity), dp_r(deg + 1, identity);  // 累積merge
		for (int i = 0; i < deg; i++) {
			dp_l[i + 1] = merge(dp_l[i], dp[v][i]);
		}
		for (int i = deg - 1; i >= 0; i--) {
			dp_r[i] = merge(dp_r[i + 1], dp[v][i]);
		}
		ans[v] = add_root(dp_l[deg]);  // 頂点 v の答え
		for (int i = 0; i < deg; i++) {  // 一つ隣の頂点に対しても同様に計算
			ll u = G[v][i].to;
			if (u == p) continue;
			bfs(u, add_root(merge(dp_l[i], dp_r[i + 1])), v);
		}
	}
};
