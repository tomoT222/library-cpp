# library-cpp
to_omoT222のライブラリだよ

## EulerTour
頂点が1-indexedの木において

・どっかの頂点を根とする部分木内の頂点（辺）の値の合計

・根からどっかの頂点までの頂点（辺）の値の合計

・2頂点のLCA

が求められる。全てO（logN）だと思う。

```c++
  ll n; cin >> n;
	vector<ll> v(n + 1);
	vector<vector<P>> G(n + 1);
	rep2(i, n) { cin >> v[i]; } //1-indexed
	rep(i, n - 1) {
		ll a, b, c; cin >> a >> b >> c;
		G[a].push_back(P(b, c));
		G[b].push_back(P(a, c));
	}
	init(n, G, 1, v);
```
