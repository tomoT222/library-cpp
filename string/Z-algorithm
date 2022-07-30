	string s; cin >> s;
	vector<ll> z(s.size());
	z[0] = s.size();
	ll i = 1, j = 0;//i:今見ている点, j:何個一致しているか
	while (i < s.size()) {
		while (i + j < s.size() && s[j] == s[i + j]) { j++; } //違くなるまでループ
		z[i] = j;
		if (j == 0) {
			i++; continue;
		}
		ll k = 1;
		while (k < j && k + z[k] < j) {//絶対にはみ出さない
			z[i + k] = z[k]; k++;
		}
		i += k; j -= k;
	}
