//ベルマンフォード法
//計算量O(|V||E|)
const ll INF = 100000000000000;
//頂点fromから頂点toへのコストcostの辺
struct edge { ll from, to, cost; };
edge es[345678]; //辺
ll d[345678]; //最短距離
//Vは頂点数、Eは辺数
//s番目の頂点から各頂点への最短距離を求める
void Bellman_Ford(ll V, ll E, ll s) {
	for (int i = 0; i <= V; i++) d[i] = INF;
	d[s] = 0;
	while (true) {
		bool update = false;
		for (int i = 0; i < E; i++) {
			edge e = es[i];
			if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
				d[e.to] = d[e.from] + e.cost;
				update = true;
			}
		}
		if (!update)break;
	}
}
//trueなら負の経路が存在する
bool find_negative_loop(ll V, ll E) { //Vは頂点数、Eは辺数
	memset(d, 0, sizeof(d));
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < E; j++) {
			edge e = es[j];
			if (d[e.to] > d[e.from] + e.cost) {
				d[e.to] = d[e.from] + e.cost;
				//n回目にも更新があるなら負の経路が存在
				if (i == V - 1)return true;
			}
		}
	}
	return false;
}
