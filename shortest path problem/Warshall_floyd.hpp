//ワ―シャルフロイド法
//計算量O(|V|^3)
ll d[2134][2134];//コスト
void warshall_floyd(ll V) {
	for (int h = 0; h < V; h++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				d[i][j] = min(d[i][j], d[i][h] + d[h][j]);
			}
		}
	}
}
signed main() {
	for (int h = 0; h < 2134; h++) {
		for (int i = 0; i < 2134; i++) {
			d[h][i] = INF;
		}
	}
	return 0;
}
