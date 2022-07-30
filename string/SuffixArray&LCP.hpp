ll n, k;
ll r[654321]; //rank
ll tmp[654321]; //MAX_N
ll sa[654321];
ll lcp[654321];

//(rank[i],rank[i + k])と(rank[j], rank[j + k])を比較
bool comp(ll i, ll j) {
	if (r[i] != r[j]) { return r[i] < r[j]; }
	else {
		ll ri = i + k <= n ? r[i + k] : -1;
		ll rj = j + k <= n ? r[j + k] : -1;
		return ri < rj;
	}
}
//文字列Sの接尾辞配列を構築
void suffix(string S) {
	n = S.length();
	//最初は1文字、ランクは文字コード
	for (int i = 0; i <= n; i++) {
		sa[i] = i; r[i] = i < n ? (ll)S[i] : -1;
	}
	//k文字についてソートされているところから2k文字でソート
	for (k = 1; k <= n; k *= 2) {
		sort(sa, sa + n + 1, comp);
		//いったんtmpに次のrankを計算
		tmp[sa[0]] = 0;
		for (int i = 1; i <= n; i++) {
			tmp[sa[i]] = tmp[sa[i - 1]] + (comp(sa[i - 1], sa[i]) ? 1 : 0);
		}
		for (int i = 0; i <= n; i++) {
			r[i] = tmp[i];
		}
	}
}
bool contain(string S, string T) {//suffix(S)の後！
	ll a = 0, b = S.length();
	while (b - a > 1) {
		ll c = (a + b) / 2;
		// Sのsa[c]文字目から|T|文字とTを比較
		if (S.compare(sa[c], T.length(), T) < 0) { a = c; }
		else { b = c; }
	}
	return S.compare(sa[b], T.length(), T) == 0;
}
// 文字列Sとその接尾辞配列saを受け取り、高さ配列lcpに計算
void get_lcp(string S) {
	n = S.length();
	for (int i = 0; i <= n; i++) { r[sa[i]] = i; }
	ll h = 0; lcp[0] = 0;
	for (int i = 0; i < n; i++) {
		//文字列の中での位置iの接尾辞と、接尾辞配列中でその1つ前の接尾辞のLCPを求める
		ll j = sa[r[i] - 1];
		//hを先頭の分1減らし、後ろが一致しているだけ増やす
		if (h > 0) { h--; }
		for (; j + h < n && i + h < n; h++) {
			if (S[j + h] != S[i + h]) { break; }
		}
		lcp[r[i] - 1] = h;
	}
}
