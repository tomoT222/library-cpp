//↓drkenさんのやつ
https://atcoder.jp/contests/agc021/submissions/30593360


struct Point {
	ll x, y;
};
bool operator<(const Point& a1, const Point& a2) {
	if (a1.x < a2.x) return true;
	if (a1.x > a2.x) return false;
	if (a1.y < a2.y) return true;
	return false;
}
//main関数内
	ll n; cin >> n; vector<Point> vec(n);
	rep(i, n) { cin >> vec[i].x >> vec[i].y; }
	sort(all(vec));
	//上側凸包
	vector<Point> up;
	rep(i, n) { //x座標の小さい順に
		Point a3 = vec[i];
		while (up.size() >= 2) {
			Point a2 = up[up.size() - 1]; up.pop_back();
			Point a1 = up[up.size() - 1];
			if ((a2.x - a1.x) * (a3.y - a2.y) - (a2.y - a1.y) * (a3.x - a2.x) < 0) { //時計回り
				up.push_back(a2); break;
			}
		}
		up.push_back(vec[i]);
	}
	/*rep(i, up.size()) {
		cout << up[i].x << ' ' << up[i].y << endl;
	}*/
	//下側凸包
	vector<Point> down;
	rep(i, n) { //x座標の小さい順に
		Point a3 = vec[i];
		while (down.size() >= 2) {
			Point a2 = down[down.size() - 1]; down.pop_back();
			Point a1 = down[down.size() - 1];
			if ((a2.x - a1.x) * (a3.y - a2.y) - (a2.y - a1.y) * (a3.x - a2.x) > 0) { //反時計回り
				down.push_back(a2); break;
			}
		}
		down.push_back(vec[i]);
	}
	/*rep(i, down.size()) {
		cout << down[i].x << ' ' << down[i].y << endl;
	}*/
