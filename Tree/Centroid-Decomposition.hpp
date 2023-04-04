/*
CF Ciel the Commander
https://codeforces.com/contest/321/submission/197610872
AC 木の問題
https://atcoder.jp/contests/yahoo-procon2018-final-open/submissions/40323778
*/

//重心分解
struct CD {
	//0-index
	//蟻本参照
	//距離がk以下の頂点の組の数
	//count_pairs関数をいじる

	ll n, k;
	vector<vector<edge>> G;
	vector<bool> centroid;
	vector<ll> subtree_size;

	CD(ll kn, ll kk, vector<vector<edge>> kG) {
		n = kn; k = kk; G = kG;
		centroid.resize(n); subtree_size.resize(n);
	}

	ll ans; //答え

	//部分木のサイズ(subtree_size)を計算する再帰関数
	ll compute_subtree_size(ll v, ll p) {
		ll c = 1;
		rep(i, G[v].size()) {
			ll w = G[v][i].to;
			if (w == p || centroid[w]) { continue; }
			c += compute_subtree_size(w, v);
		}
		return subtree_size[v] = c;
	}

	// 重心となる頂点を探す再帰関数。tは連結成分の大きさ。
	// P(最大の部分木の頂点数、頂点番号)
	P search_centroid(ll v, ll p, ll t) {
		P res = P(INF, -1);
		ll s = 1, m = 0;
		rep(i, G[v].size()) {
			ll w = G[v][i].to;
			if (w == p || centroid[w]) { continue; }
			chmin(res, search_centroid(w, v, t));
			chmax(m, subtree_size[w]);
			s += subtree_size[w];
		}
		chmax(m, t - s);
		chmin(res, P(m, v));
		return res;
	}

	// 部分木に含まれる全頂点の重心までの距離を列挙する再帰関数
	void enumurate_paths(ll v, ll p, ll d, vector<ll>& ds) {
		ds.push_back(d);
		rep(i, G[v].size()) {
			ll w = G[v][i].to;
			if (w == p || centroid[w]) { continue; }
			enumurate_paths(w, v, d + G[v][i].cost, ds);
		}
	}

	// 和がk以下となる組の個数を求める
	ll count_pairs(vector<ll>& ds) {
		ll res = 0;
		sort(all(ds));
		ll j = ds.size();
		rep(i, ds.size()) {
			while (j > 0 && ds[i] + ds[j - 1] > k) { --j; }
			res += j - (j > i ? 1 : 0); //自分自身とのペアは除く
		}
		return res / 2;
	}

	// 頂点vが属する部分木に関して、重心を探し木を分割し問題を解く再帰関数
	void solve_subproblem(ll v) {
		// 重心となるsを探す
		compute_subtree_size(v, -1);
		ll s = search_centroid(v, -1, subtree_size[v]).second;
		centroid[s] = true;

		// (1):頂点sにより分割した部分木の中に関して数える
		rep(i, G[s].size()) {
			if (centroid[G[s][i].to]) { continue; }
			solve_subproblem(G[s][i].to);
		}

		// (2),(3):頂点sを通る頂点の組みに関して数える
		vector<ll> ds;
		ds.push_back(0); // 頂点sの分
		rep(i, G[s].size()) {
			if (centroid[G[s][i].to]) { continue; }
			vector<ll> tds;
			enumurate_paths(G[s][i].to, s, G[s][i].cost, tds);
			ans -= count_pairs(tds); //重複して数えてしまう分を予め引いておく
			ds.insert(ds.end(), all(tds));
		}
		ans += count_pairs(ds);
		centroid[s] = false;
	}

	void solve() {
		ans = 0; solve_subproblem(0);
		cout << ans << endl;
	}
};
