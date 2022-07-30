//構文解析 how to
//<数>           number     :: = 数
//<括弧か数>     factor     :: = '(' < 四則演算の式 > ')' or <数>
//<乗算除算の式> term       :: = <括弧か数> (*or /) < 括弧か数 > (*or /) ...
//<四則演算の式> expression :: = <乗算除算の式> (+or -) < 乗算除算の式 > (+or -) ...
// 数字の列をパースして、その数を返す。
int expression(State&);
int number(State& begin) {
	int ret = 0;

	while (isdigit(*begin)) {
		ret *= 10;
		ret += *begin - '0';
		begin++;
	}

	return ret;
}
// 括弧か数をパースして、その評価結果を返す。
int factor(State& begin) {
	if (*begin == '(') {
		begin++; // '('を飛ばす。
		int ret = expression(begin);
		begin++; // ')'を飛ばす。
		return ret;
	}
	else {
		return number(begin);
	}
}
// 乗算除算の式をパースして、その評価結果を返す。
int term(State& begin) {
	int ret = factor(begin);

	for (;;) {
		if (*begin == '*') {
			begin++;
			ret *= factor(begin);
		}
		else if (*begin == '/') {
			begin++;
			ret /= factor(begin);
		}
		else {
			break;
		}
	}

	return ret;
}
// 四則演算の式をパースして、その評価結果を返す。
int expression(State& begin) {
	int ret = term(begin);

	for (;;) {
		if (*begin == '+') {
			begin++;
			ret += term(begin);
		}
		else if (*begin == '-') {
			begin++;
			ret -= term(begin);
		}
		else {
			break;
		}
	}

	return ret;
}
void solve() {
	int N;
	cin >> N;
	cin.ignore();
	for (int i = 0; i < N; i++) {
		string s;
		getline(cin, s);

		State begin = s.begin();
		int ans = expression(begin);
		cout << ans << endl;
	}
}
