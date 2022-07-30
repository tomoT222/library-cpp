struct rmq2 {
	ll nn;
	vector<ll> dat;

	rmq2(ll n = 1) {
		init(n);
	}
	void init(ll n_) { //初期化
		nn = 1; //簡単のため、要素数を2のべき乗に
		while (nn < n_)nn *= 2;
		dat.resize(2 * nn);
	}
	void update(ll k, ll a) { //k番目の値(0-indexed)をaに変更
		k += nn - 1; dat[k] = a; //葉の節点
		while (k > 0) { //登りながら更新
			k = (k - 1) / 2;
			dat[k] = max(dat[k * 2 + 1], dat[k * 2 + 2]);
		}
	}
	//[a, b)の最大値を求める
	//kは節点の番号、l, rはその節点が[l, r)に対応づいていることを表す。
	//したがって外からはquery(a, b, 0, 0, nn)として呼ぶ。
	ll query(ll a, ll b, ll k, ll l, ll r) {
		//[a, b)と[l, r)が交差しなければ、0
		//[a, b)が[l, r)を完全に含んでいれば、この節点の値
		if (r <= a || b <= l) { return 0; }
		if (a <= l && r <= b) { return dat[k]; }
		else {
			ll vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			ll vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return max(vl, vr);
		}
	}
};
