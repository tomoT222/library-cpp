// Euler Tour
//refer to : EulerTourのお勉強 - maspyのHP
///////////////1-indexedにして！！！！！！！！！！！！！
struct rsq {
	ll nn;
	vector<ll> dat; //セグメント木を持つグローバル配列

	void init(ll n, vector<ll> v) {
		nn = 1; //簡単のため、要素数を2のべき乗に
		while (nn < n)nn *= 2;

		dat.resize(2 * nn);
		rep(i, v.size()) { update(i, v[i]); }
	}

	void update(ll k, ll a) { //k番目の値(0-indexed)をaに変更
		k += nn - 1; dat[k] = a; //葉の節点
		while (k > 0) { //登りながら更新
			k = (k - 1) / 2;
			dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
		}
	}

	//[a, b)の最小値を求める
	ll query(ll a, ll b, ll k = 0, ll l = 0, ll r = -1) {
		if (r < 0) { r = nn; }
		if (r <= a || b <= l) { return 0; }
		if (a <= l && r <= b) { return dat[k]; }
		else {
			ll vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			ll vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return vl + vr;
		}
	}
};
struct rmq {
	ll nn;
	vector<P> dat; //セグメント木を持つグローバル配列

	void init(ll n_, vector<P> v) { //初期化
		nn = 1; //簡単のため、要素数を2のべき乗に
		while (nn < n_)nn *= 2;

		dat.resize(2 * nn);
		for (int i = 0; i < 2 * nn - 1; i++) dat[i] = P(INF, 0);
		rep(i, v.size()) { update(i, v[i]); }
	}

	void update(ll k, P a) { //k番目の値(0-indexed)をaに変更
		k += nn - 1; dat[k] = a; //葉の節点
		while (k > 0) { //登りながら更新
			k = (k - 1) / 2;
			dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
		}
	}

	//[a, b)の最小値のあるindexを求める
	P query(ll a, ll b, ll k = 0, ll l = 0, ll r = -1) {
		if (r < 0) { r = nn; }
		if (r <= a || b <= l) { return P(INF, 0); }
		if (a <= l && r <= b) { return dat[k]; }
		else {
			P vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			P vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return min(vl, vr);
		}
	}
};
struct ET {
	//private

	//public
	ll n, root;
	vector<vector<P>> G;//to, cost
	vector<ll> v;//頂点の値
	vector<ll> e;//辺の値(indexは子の方、1はない)

	vector<ll> in, out;
	vector<ll> hen;//サイトでいう"辺"（たぶん）点の番号
	vector<ll> vs;//蟻本のLCAで載っている配列
	vector<ll> par;

	//rsq初期化用
	vector<ll> v_sum1;//サイトでいう"頂点の合計"(部分木)
	vector<ll> e_sum1;//サイトでいう"辺の合計"(部分木)
	vector<ll> v_sum2;//サイトでいう"頂点の合計"(path)
	vector<ll> e_sum2;//サイトでいう"辺の合計"(path)
	vector<P> dep;

	//1-indexed！！
	void init(ll kn, vector<vector<P>> kG, ll kroot = 1, vector<ll> kv = {}) {
		n = kn; G = kG; root = kroot; v = kv;
		e.resize(n + 1); in.resize(n + 1); out.resize(n + 1); par.resize(n + 1);
		dfs(root);
		rep(i, hen.size()) {
			if (hen[i] > 0) {
				v_sum1.push_back(v[hen[i]]);
				v_sum2.push_back(v[hen[i]]);
			}
			else {
				v_sum1.push_back(0);//足し算だから0
				v_sum2.push_back(0 - v[0 - hen[i]]);
			}
		}
		rep(i, hen.size()) {
			if (hen[i] > 1) {
				e_sum1.push_back(e[hen[i]]);
				e_sum2.push_back(e[hen[i]]);
			}
			else {
				e_sum1.push_back(0);//足し算だから0
				e_sum2.push_back(0 - e[0 - hen[i]]);
			}
		}
		rep(i, hen.size()) {
			if (i == 0) { dep.push_back(P(0, i)); }
			else if (hen[i] > 0) { dep.push_back(P(dep[i - 1].first + 1, i)); }
			else { dep.push_back(P(dep[i - 1].first - 1, i)); }
		}
	}
	void dfs(ll k) {
		in[k] = hen.size(); hen.push_back(k); vs.push_back(k);
		rep(i, G[k].size()) {
			if (G[k][i].first == par[k]) { continue; }
			e[G[k][i].first] = G[k][i].second;
			par[G[k][i].first] = k;
			dfs(G[k][i].first);
			vs.push_back(k);
		}
		out[k] = hen.size(); hen.push_back(0 - k);
	}

	//in,outと辺が見れる、作っちゃった
	void checker1() {
		rep2(i, n) {
			cout << i << ' ' << in[i] << ' ' << out[i] << endl;
		}
		rep(i, hen.size()) {
			cout << i << ' ' << hen[i] << endl;
		}
	}

	rsq rv1, rv2;
	rsq re1, re2;
	rmq rd;//depth
};
ET et;
//1-indexed！！
//kv[0]=0;(1-indexedで)
//ll a,b,c; cin>>a>>b>>c; if(a>b){swap(a,b);} G[a].push_back(P(b, c));
void init(ll kn, vector<vector<P>> kG, ll kroot = 1, vector<ll> kv = {}) {
	et.init(kn, kG, kroot, kv);
	et.rv1.init(kn * 2, et.v_sum1); et.rv2.init(kn * 2, et.v_sum2);
	et.re1.init(kn * 2, et.e_sum1); et.re2.init(kn * 2, et.e_sum2);
	et.rd.init(kn * 2, et.dep);
}
//////////値の変更
//頂点の値の変更
void v_update(ll k, ll v) {
	et.rv1.update(et.in[k], v);
	et.rv2.update(et.in[k], v); et.rv2.update(et.out[k], 0 - v);
}
//辺の値の変更
void e_update(ll k, ll e) {//kは辺の2つの頂点の内、根から遠いほうの頂点番号？
	et.re1.update(et.in[k], e);
	et.re2.update(et.in[k], e); et.re2.update(et.out[k], 0 - e);
}
//////////部分木クエリ
//頂点の値の合計
ll t_v_sum(ll k) {//頂点kが根の部分木、O(セグメント木)
	return et.rv1.query(et.in[k], et.out[k]);
}
//辺の値の合計
ll t_e_sum(ll k) {//頂点kが根の部分木、O(セグメント木)
	return et.re1.query(et.in[k] + 1, et.out[k]);
}
//////////根からある頂点iまでのパス
//頂点の値の合計
ll p_v_sum(ll k) {//root~k
	return et.rv2.query(0, et.in[k] + 1);
}
//辺の値の合計
ll p_e_sum(ll k) {//root~k
	return et.re2.query(1, et.in[k] + 1);
}
//////////LCA
ll lca(ll a, ll b) {//頂点a,bのLCA
	if (et.in[a] > et.in[b]) { swap(a, b); }
	return et.vs[et.rd.query(et.in[a], et.in[b] + 1).second];
}
