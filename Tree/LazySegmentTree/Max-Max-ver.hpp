struct lazyseg {
	// 遅延評価セグメント木をソラで書きたいあなたに
	ll nn = 1; vector<ll> node, lazy;// 値配列、遅延配列

	lazyseg(ll n) {
		while (nn < n) { nn *= 2; }
		node.resize(nn * 2); lazy.resize(nn * 2);
	}

	void eval(ll k, ll l, ll r) {// k 番目のノードについて遅延評価を行う
		// 自ノード及び子ノードへの値の伝播
		if (lazy[k] != 0) {
			chmax(node[k], lazy[k]);
			// 子ノードは親ノードの 1/2 の範囲であるため、伝播のときは半分にする
			if (r - l > 1) {// 最下段かどうか
				chmax(lazy[2 * k + 1], lazy[k]);
				chmax(lazy[2 * k + 2], lazy[k]);
			}
			lazy[k] = 0;
		}
	}

	void add(ll a, ll b, ll x, ll k = 0, ll l = 0, ll r = -1) { // [a, b), x
		if (r < 0) { r = nn; }
		eval(k, l, r);// k 番目のノードに対して遅延評価を行う
		if (b <= l || r <= a) return; // 範囲外なら何もしない
		if (a <= l && r <= b) {// 完全に被覆→遅延配列に値を入れた後に評価
			chmax(lazy[k], x);
			eval(k, l, r);
		}
		else { // そうでないならば、子ノードの値を再帰的に計算して、計算済みの値をもらってくる
			add(a, b, x, 2 * k + 1, l, (l + r) / 2);
			add(a, b, x, 2 * k + 2, (l + r) / 2, r);
			node[k] = max(node[2 * k + 1], node[2 * k + 2]);
		} //これで自分の上の頂点の値配列が更新される。
	}

	ll getmax(ll a, ll b, ll k = 0, ll l = 0, ll r = -1) { // [a, b)
		if (r < 0) { r = nn; }
		if (b <= l || r <= a) return 0;
		eval(k, l, r);// 自分の遅延配列を自分の値配列や子の遅延配列に伝番
		if (a <= l && r <= b) return node[k];
		ll vl = getmax(a, b, 2 * k + 1, l, (l + r) / 2);
		ll vr = getmax(a, b, 2 * k + 2, (l + r) / 2, r);
		return max(vl, vr);
	}
};
