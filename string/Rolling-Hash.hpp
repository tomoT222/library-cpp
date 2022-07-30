typedef unsigned long long ull;
const ull  B = 100000007; //ハッシュの基数

// aはbに含まれているか？
bool contain(string a, string b, ll k) {
	int al = a.length(), bl = b.length();
	if (al > bl) { return false; }

	// Bのal乗を計算
	ull t = 1;
	for (int i = 0; i < al; i++) { t *= B; }

	// aとbの最初のal文字に関するハッシュ値を計算
	ull ah = 0, bh = 0;
	for (int i = 0; i < al; i++) { ah = ah * B + a[i]; }
	for (int i = 0; i < al; i++) { bh = bh * B + b[i]; }

	//bの場所を1つずつ進めながらハッシュ値をcheck
	for (int i = k + 1; i + al < bl; i++) {
		if (ah == bh) { return true; } // bのi文字目からのal文字が一致
		if (i + al < bl) { bh = bh * B + b[i + al] - b[i] * t; }
	}
	return false;
}
