//線分ABと線分CDの交差判定
struct point {
	ll x;
	ll y;

	bool operator<(const point& rhs) const { return x < rhs.x; };
	bool operator>(const point& rhs) const { return x > rhs.x; };
};
bool judge(point a, point b, point c, point d) {
	double s, t;
	s = (a.x - b.x) * (c.y - a.y) - (a.y - b.y) * (c.x - a.x);
	t = (a.x - b.x) * (d.y - a.y) - (a.y - b.y) * (d.x - a.x);
	if (s * t > 0) { return false; }
	s = (c.x - d.x) * (a.y - c.y) - (c.y - d.y) * (a.x - c.x);
	t = (c.x - d.x) * (b.y - c.y) - (c.y - d.y) * (b.x - c.x);
	if (s * t > 0) { return false; }
	return true;
}

//凸包
https://atcoder.jp/contests/agc021/submissions/30593360
