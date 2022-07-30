#include<bits/stdc++.h>
using ll = long long;
using namespace std;

vector<ll> topo(vector<vector<ll>>& G, vector<ll>& indegree, ll V) {
	vector<ll> sorted_vertices;

	queue<ll> que;
	for (int i = 0; i < V; i++) {
		if (indegree[i] == 0) {
			que.push(i);
		}
	}

	while (que.empty() == false) {
		ll v = que.front();
		que.pop();

		for (int i = 0; i < G[v].size(); i++) {
			ll u = G[v][i];
			indegree[u] -= 1;
			if (indegree[u] == 0) que.push(u);
		}
		sorted_vertices.push_back(v);
	}

	return sorted_vertices;
}

signed main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	//cout << fixed << setprecision(15);

	//input
	ll V, E; cin >> V >> E;

	vector<vector<ll>> G(V);
	vector<ll> indegree(V);
	for (int i = 0; i < E; i++) {
		ll u, v; cin >> u >> v;
		G[u].push_back(v);
		indegree[v] += 1;
	}

	vector<ll> sorted_vertices = topo(G, indegree, V);

	for (int i = 0; i < sorted_vertices.size(); i++) {
		cout << sorted_vertices[i] << endl;
	}

    return 0;
}
