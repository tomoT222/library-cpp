//適宜書き直してくれ

vector<ll> r1(350), r2(200005);
void r(ll a, ll b) {
	if (a / 320 == b / 320) {
		for (int i = a; i <= b; i++) {
			r2[i] = max(r2[i], b);
		}
		return;
	}

	ll an = (a + 319) / 320;
	for (int i = a; i < an * 320; i++) {
		r2[i] = max(r2[i], b);
	}
	ll last = an * 320;
	for (int i = an; i < b / 320; i++) {
		r1[i] = max(r1[i], b);
		last = (i + 1) * 320;
	}
	for (int i = last; i <= b; i++) {
		r2[i] = max(r2[i], b);
	}
}
