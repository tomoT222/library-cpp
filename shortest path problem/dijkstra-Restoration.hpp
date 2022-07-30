const ll INF = 1000000000000;
ll pre[345678]; //最短路の直前の頂点
ll cost[3456][3456]; //cost[u][v]は辺e=(u,v)のコスト(残りINF)
ll d[345678]; //頂点sからの最短距離
bool used[345678]; //すでに使われたかのグラフ
void dijkstra(ll V, ll s) { //頂点数と始点
	fill(d, d + V, INF);
	fill(used, used + V, false);
	fill(pre, pre + V, -1);
	d[s] = 0;
	while (true) {
		int v = -1;
		//まだ使われていない頂点のうちの最小距離を探す
		for (int u = 0; u < V; u++) {
			if (!used[u] && (v == -1 || d[u] < d[v])) v = u;
		}
		if (v == -1) break;
		used[v] = true;
		for (int u = 0; u < V; u++) {
			if (d[u] > d[v] + cost[v][u]) {
				d[u] = d[v] + cost[v][u];
				pre[u] = v;
			}
		}
	}
}
//頂点tへの最短路
vector<ll> get_path(ll t) {
	vector<ll> path;
	for (; t != -1; t = pre[t]) path.push_back(t); //tがsになるまでpre[t]を追う
	//逆順に
	reverse(path.begin(), path.end());
	return path;
}
signed main() {
	for (int h = 0; h < 3456; h++) {
		for (int i = 0; i < 3456; i++) {
			cost[h][i] = INF;
		}
	}
}
