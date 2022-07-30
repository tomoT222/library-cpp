# library-cpp
to_omoT222のライブラリだよ

## Tree/EulerTour.hpp
頂点が1-indexedの木において

・どっかの頂点を根とする部分木内の頂点（辺）の値の合計

・根からどっかの頂点までの頂点（辺）の値の合計

・任意の2頂点のパスの長さ

・2頂点のLCA

が求められる。全てO（logN）だと思う。

↓initまでの流れ

```c++
	ll n; cin >> n;
	vector<ll> v(n + 1);
	vector<vector<edge>> G(n + 1);
	rep2(i, n) { cin >> v[i]; } //1-indexed
	rep(i, n - 1) {
		ll a, b, c; cin >> a >> b >> c;
		G[a].push_back({b, c});
		G[b].push_back({a, c});
	}
	ET et(n, G, v);
	
	//checkする用
	ll q; cin >> q;
	rep(i, q) {
		string s; cin >> s;
		if (s == "v_update") {
			ll k, v; cin >> k >> v;
			et.v_update(k, v);
		}
		if (s == "e_update") {
			ll a, b, e; cin >> a >> b >> e;
			et.e_update(a, b, e);
		}
		if (s == "t_v_sum") {
			ll k; cin >> k; cout << et.t_v_sum(k) << endl;
		}
		if (s == "t_e_sum") {
			ll k; cin >> k; cout << et.t_e_sum(k) << endl;
		}
		if (s == "p_v_sum") {
			ll k; cin >> k; cout << et.p_v_sum(k) << endl;
		}
		if (s == "p_e_sum") {
			ll k; cin >> k; cout << et.p_e_sum(k) << endl;
		}
		if (s == "len") {
			ll a, b; cin >> a >> b; cout << et.len(a, b) << endl;
		}
		if (s == "LCA") {
			ll a, b; cin >> a >> b; cout << et.lca(a, b) << endl;
		}
	}
```
