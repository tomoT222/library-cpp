//int par[213456];//親
//int depth[213456];//木の深さ
ll par[213456];//親
ll depth[213456];//木の深さ
//n要素で初期化
void init(ll n) {
	for (int i = 0; i <= n; i++) {
		par[i] = i;
		depth[i] = 0;
	}
}
//木の根を求める
ll find(ll x) {
	if (par[x] == x) {
		return x;
	}
	else {
		return par[x] = find(par[x]);
	}
}
//xとyの属する集合を併合
void unite(ll x, ll y) {
	x = find(x); y = find(y);
	if (x == y) { return; }
	if (depth[x] < depth[y]) {
		par[x] = y;
	}
	else {
		par[y] = x;
		if (depth[x] == depth[y])depth[x]++;
	}
}
//xとyが同じ集合に属するか否か
bool same(ll x, ll y) {
	return find(x) == find(y);
}
struct edge { ll u, v, cost; };
bool comp(const edge& e1, const edge& e2) {
	return e1.cost < e2.cost;
}
edge es[313456];
ll kruskal(ll V, ll E) { //頂点数と辺数
	sort(es, es + E, comp); //edge.costが小さい順にソート
	init(V); //Union-Findの初期化
	ll res = 0;
	for (int i = 0; i < E; i++) {
		edge e = es[i];
		if (!same(e.u, e.v)) {
			unite(e.u, e.v);
			res += e.cost;
		}
	}
	return res;
}
