struct tree {//0-indexed

	ll n;
	vector<vector<ll>> G;

	tree(ll kn, vector<vector<ll>> kG) {
		n = kn; G = kG;
	}

	////木の直径
private:
	vector<ll> pre;
	ll bfs(ll root) {
		queue<ll> que; que.push(root);
		vector<bool> used(n); used[root] = true;
		pre.resize(n, 0); pre[root] = -1;
		while (!que.empty()) {
			ll q = que.front(); que.pop();
			rep(i, G[q].size()) {
				if (!used[G[q][i]]) {
					used[G[q][i]] = true;
					que.push(G[q][i]);
					pre[G[q][i]] = q;
				}
			}
			if (que.size() == 0) {
				return q;
			}
		}
	}

	vector<ll> get_diameter() {
		ll end_point = bfs(0);//直径の端点
		end_point = bfs(end_point);
		vector<ll> v; v.push_back(end_point);
		while (pre[end_point] != -1) {
			end_point = pre[end_point]; v.push_back(end_point);
		}
		return v;
	}

public:
	vector<ll> dia() {//木の直径のパス
		return get_diameter();
	}
	ll dia_size() {//木の直径の長さ
		return dia().size();
	}

	ll dia_ko() {//木の直径の個数
		vector<ll> diameter = get_diameter();
		ll ans = 0, sum = 0;
		if (diameter.size() % 2 == 1) {
			ll d = diameter.size() / 2;
			ll mid = diameter[d];//木の中心
			queue<ll> que, cnt; vector<bool> used(n); used[mid] = true;
			rep(i, G[mid].size()) {
				ll ko = 0;
				que.push(G[mid][i]); cnt.push(1);
				used[G[mid][i]] = true;
				while (!que.empty()) {
					ll q = que.front(), c = cnt.front(); que.pop(); cnt.pop();
					rep(i, G[q].size()) {
						if (!used[G[q][i]]) {
							used[G[q][i]] = true;
							que.push(G[q][i]); cnt.push(c + 1);
						}
					}
					if (c == d) {
						ko++;
					}
				}
				if (sum == 0) { sum += ko; }
				else { ans += sum * ko; sum += ko; }
			}
		}
		else {
			ll d = diameter.size() / 2 - 1;
			ll mid1 = diameter[d], mid2 = diameter[d + 1];//木の中心
			queue<ll> que, cnt; vector<bool> used(n); used[mid1] = true; used[mid2] = true;
			rep2(z, 2) {
				ll mid = mid1;
				if (z == 2) { mid = mid2; }
				ll ko = 0;
				que.push(mid); cnt.push(0);
				while (!que.empty()) {
					ll q = que.front(), c = cnt.front(); que.pop(); cnt.pop();
					rep(i, G[q].size()) {
						if (!used[G[q][i]]) {
							used[G[q][i]] = true;
							que.push(G[q][i]); cnt.push(c + 1);
						}
					}
					if (c == d) {
						ko++;
					}
				}
				if (sum == 0) { sum += ko; }
				else { ans += sum * ko; sum += ko; }
			}
		}
		return ans;
	}

};
