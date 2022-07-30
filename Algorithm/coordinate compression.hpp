//ペンキの色　https://atcoder.jp/contests/joi2008ho/submissions/16272337

//入力
ll W, H, N; //W = 横, H = 縦, N = 棒の数
ll X1[1002], X2[1002], Y1[1002], Y2[1002];
 
//塗りつぶし用
bool fld[6010][6010];
 
//x1, x2を座標圧縮しその際の幅を返す
ll compress(ll * x1, ll * x2, ll w) {
	vector<ll> xs;
 
	for (int i = 0; i < N; i++) {
		for (int d = -1; d <= 1; d++) {
			ll tx1 = x1[i] + d, tx2 = x2[i] + d;
			if (0 <= tx1 && tx1 < w) { xs.push_back(tx1); }
			if (0 <= tx2 && tx2 < w) { xs.push_back(tx2); }
		}
	}
	sort(all(xs));
	xs.erase(unique(all(xs)), xs.end());
 
	for (int i = 0; i < N; i++) {
		x1[i] = find(all(xs), x1[i]) - xs.begin();
		x2[i] = find(all(xs), x2[i]) - xs.begin();
	}
 
	return xs.size();
}
ll dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };
void solve() {
	//座標圧縮
	W = compress(X1, X2, W);
	H = compress(Y1, Y2, H);
	//線のある部分を塗りつぶし
	memset(fld, 0, sizeof(fld));
	for (int i = 0; i < N; i++) {
		for (int y = Y1[i]; y <= Y2[i]; y++) {
			for (int x = X1[i]; x <= X2[i]; x++) {
				fld[y][x] = true;
			}
		}
	}
	//領域を数える
	ll ans = 0;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			if (fld[y][x]) { continue; }
			ans++;
			//幅優先探索
			queue<pair<ll, ll> > que;
			que.push(make_pair(x, y));
			while (!que.empty()) {
				ll sx = que.front().first, sy = que.front().second;
				que.pop();
				for (int i = 0; i < 4; i++) {
					ll tx = sx + dx[i], ty = sy + dy[i];
					if (tx < 0 || W <= tx || ty < 0 || H <= ty) { continue; }
					if (fld[ty][tx]) { continue; }
					que.push(make_pair(tx, ty));
					fld[ty][tx] = true;
				}
			}
		}
	}
	cout << ans << endl;
}
