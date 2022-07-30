//素数判定法
bool IsPrime(ll num) {
    if (num < 2) return false;
    else if (num == 2) return true;
    else if (num % 2 == 0) return false; // 偶数はあらかじめ除く
    double sqrtNum = sqrt(num);
    for (ll i = 3; i <= sqrtNum; i += 2) {
        if (num % i == 0) { // 素数ではない
            return false;
        }
    }
    // 素数である
    return true;
}
//約数の列挙
vector<ll> divisor(ll n) {
	vector<ll> res;
	for (ll i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			res.push_back(i);
			if (i != n / i) res.push_back(n / i);
		}
	}
	return res;
}
//素因数分解(P(a, ko[a]))
vector<P> prime_factor(ll n) {
	vector<P> res;
	for (ll i = 2; i * i <= n; i++) {
		ll cnt = 0;
		while (n % i == 0) { cnt++; n /= i; }
		if (cnt != 0) { res.push_back(P(i, cnt)); }
	}
	if (n != 1) { res.push_back(P(n, 1)); }
	return res;
}
//素因数分解２
map<ll, ll>prime_factor(ll n) {
	map<ll, ll> res;
	for (ll i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			++res[i];
			n /= i;
		}
	}
	if (n != 1) { res[n]++; }
	return res;
}
