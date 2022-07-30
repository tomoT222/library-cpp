//O(ElogV)
//const ll INF = 10000000000000;
//struct edge { ll to, cost; };
//typedef pair<ll, ll>P; //firstは最短距離、secondは頂点番号

//負の辺は本当にないですか？？？

ll d[213456];//始点sから終点tまでのコストd[t]
vector<edge> G[213456];//コスト
void dijkstra(ll s) {
	//greater<P>を指定→firstが小さい順
	priority_queue<P, vector<P>, greater<P> >que;
	fill(d, d + 213456, INF);//←TLE気を付ける
	d[s] = 0; que.push(P(0, s));
	while (!que.empty()) {
		P p = que.top(); que.pop();
		int v = p.second;
		if (d[v] < p.first) { continue; }
		for (int i = 0; i < G[v].size(); i++) {
			edge e = G[v][i];
			if (d[e.to] > d[v] + e.cost) {
				d[e.to] = d[v] + e.cost;
				que.push(P(d[e.to], e.to));
			}
		}
	}
}
