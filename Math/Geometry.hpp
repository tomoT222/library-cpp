////////////////////----------     表現     ----------////////////////////

//aが正か0か負か
int sign(ld a) {
	if (a < -EPS) return -1;
	else if (a > EPS) return 1;
	else return 0;
}
//点
struct Point {
	ld x, y;
	Point operator + (const Point& p)const noexcept { return { x + p.x, y + p.y }; }
	Point operator - (const Point& p)const noexcept { return { x - p.x, y - p.y }; }
	Point operator * (const ld k)const noexcept { return { x * k, y * k }; }
	Point operator / (const ld k)const noexcept { return { x / k, y / k }; }
	Point& operator += (const Point& p)noexcept { x += p.x; y += p.y; return *this; }
	Point& operator -= (const Point& p)noexcept { x -= p.x; y -= p.y; return *this; }
	bool operator < (const Point& p)const noexcept { return (x != p.x ? x < p.x : y < p.y); }
	bool operator == (const Point& p)const noexcept { return (sign(x - p.x) == 0 && sign(y - p.y) == 0); }

	ld abs()const noexcept { return sqrt(x * x + y * y); }
	ld norm()const noexcept { return x * x + y * y; }
};
using VP = std::vector<Point>;
//ベクトル
typedef Point Vector;
//線分
struct Segment {
	Point p1, p2;
};
//直線
typedef Segment Line;
//円
class Circle {
public:
	Point c; ld r;
	Circle(Point c = Point(), ld r = 0.0) :c(c), r(r) {}
};
//多角形
struct Polygon {
	int n;
	VP ps;
	Polygon(int n_ = 0) :n(n_), ps(n_) {}
	Polygon(VP ps_) :n(ps_.size()), ps(ps_) {}
	Point& operator[](int n) { return ps[n]; }
};

////////////////////----------     点・線分・直線     ----------////////////////////

//内積と外積
ld dot(Vector a, Vector b) { return (a.x * b.x + a.y * b.y); }
ld cross(Vector a, Vector b) { return (a.x * b.y - a.y * b.x); }

//a -> b -> cの進み方
int dir(Point a, Point b, Point c) {
	b -= a; c -= a;
	if (sign(cross(b, c)) == 1)return 1;//counter clockwise
	else if (sign(cross(b, c)) == -1)return -1;//clockwise
	else {
		//直線上の3点
		if (sign(dot(b, c)) == -1)return 2;//b-a-c or c-a-b
		else if (b.norm() < c.norm())return -2;//a-b-c or c-b-a or a == b
		else return 0;//a-c-b or b-c-a or a == c or b == c
	}
}

//点が直線上
bool onLine(Point a, Line l) { return abs(dir(l.p1, a, l.p2)) != 1; }
//線分の交差判定
bool intersect(Segment a, Segment b) {
	return (dir(a.p1, a.p2, b.p1) * dir(a.p1, a.p2, b.p2) <= 0 && dir(b.p1, b.p2, a.p1) * dir(b.p1, b.p2, a.p2) <= 0);
}

//2つの直線の関係
int Line_place(Line l1, Line l2) {
	if (onLine(l1.p1, l2) && onLine(l1.p2, l2))return 1;//一致
	else if (sign(cross(l1.p2 - l1.p1, l2.p2 - l2.p1)) == 0)return 2;//平行
	else if (sign(dot(l1.p2 - l1.p1, l2.p2 - l2.p1)) == 0)return 3;//直交
	else return 0;
}
//垂線の足
Point project(Point p, Line l) {
	Vector base = l.p2 - l.p1;
	ld r = dot(p - l.p1, base) / base.norm();
	return l.p1 + base * r;
}
//lを軸にしてpと線対称な点
Point reflect(Point p, Line l) { return project(p, l) * ld(2) + p; }

//////////-----  距離  -----//////////
ld distPP(Point a, Point b) { return (a - b).abs(); }
ld distPL(Point p, Line l) { return abs(cross(l.p2 - l.p1, p - l.p1) / (l.p2 - l.p1).abs()); }
ld distLL(Line l1, Line l2) {
	if (Line_place(l1, l2) != 2)return 0;
	else return distPL(l1.p1, l2);
}
ld distPS(Point p, Segment s) {
	if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return (p - s.p1).abs();
	if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return (p - s.p2).abs();
	return distPL(p, s);
}
ld distSS(Segment s1, Segment s2) {
	if (intersect(s1, s2)) { return 0.0; }
	return min(min(distPS(s1.p1, s2), distPS(s1.p2, s2)), min(distPS(s2.p1, s1), distPS(s2.p2, s1)));
}

//線分or直線の交点
Point CrossPointSS(Segment s1, Segment s2) {
	Vector base = s2.p2 - s2.p1;
	ld d1 = abs(cross(base, s1.p1 - s2.p1));
	ld d2 = abs(cross(base, s1.p2 - s2.p1));
	ld t = d1 / (d1 + d2);
	return s1.p1 + (s1.p2 - s1.p1) * t;
}

////////////////////----------     円     ----------////////////////////

//円と円の距離
ld distCC(Circle c, Circle d) {
	ld di = (c.c - d.c).abs();
	return (sign(di - abs(c.r - d.r)) == 1 ? max(di - c.r - d.r, ld(0.0)) : abs(c.r - d.r) - di);//? 内部ではない : 内部
}
//円と直線の交点
VP CrossPointCL(Circle c, Line l) {
	VP res;
	if (sign(distPL(c.c, l) - c.r) == 1) { return res; }

	Vector pr = project(c.c, l);
	Vector e = (l.p2 - l.p1) / (l.p2 - l.p1).abs();
	ld base = sqrt(c.r * c.r - (pr - c.c).norm());
	res.push_back(pr + e * base);
	if (sign(distPL(c.c, l) - c.r) == -1) { res.push_back(pr - e * base); }
	return res;
}
Vector polar(ld a, ld r) { return Point({ cos(r) * a, sin(r) * a }); }
//円と円の交点
VP CrossPointCC(Circle c1, Circle c2) {
	VP res;
	if (sign(distCC(c1, c2)) != 0)return res;

	ld d = (c1.c - c2.c).abs();
	ld a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
	Vector p = c2.c - c1.c;
	ld t = atan2(p.y, p.x);

	res.push_back(c1.c + polar(c1.r, t + a));
	res.push_back(c1.c + polar(c1.r, t - a));
	return res;
}

////////////////////----------     多角形     ----------////////////////////

//多角形の面積
ld PolygonArea(Polygon& po) {
	ld a = 0;
	for (int i = 0; i < po.n; i++) a += cross(po[i], po[(i + 1) % po.n]);
	return a / ld(2);
}
//点の内包
int PointContains(Point p, Polygon g) {
	bool x = false;
	for (int i = 0; i < g.n; i++) {
		Point a = g.ps[i] - p, b = g.ps[(i + 1) % g.n];
		if (abs(cross(a, b)) < EPS && dot(a, b) < EPS) return 1; //ON
		if (a.y > b.y) { swap(a, b); }
		if (a.y < EPS && b.y > EPS && cross(a, b) > EPS) { x = !x; }
	}
	return (x ? 2 : 0); //IN or OUT
}
//凸包
Polygon Convex_hull(VP s) {
	VP u, l;
	Polygon res;
	if (s.size() < 3) {
		res.n = s.size(); res.ps = s;
		return l;
	}

	sort(s.begin(), s.end());
	u.push_back(s[0]);
	u.push_back(s[1]);
	l.push_back(s[s.size() - 1]);
	l.push_back(s[s.size() - 2]);
	for (int i = 2; i < s.size(); i++) {
		for (int n = u.size(); n >= 2 && dir(u[n - 2], u[n - 1], s[i]) != -1; n--) {
			u.pop_back();
		}
		u.push_back(s[i]);
	}
	for (int i = s.size() - 3; i >= 0; i--) {
		for (int n = l.size(); n >= 2 && dir(l[n - 2], l[n - 1], s[i]) != -1; n--) {
			l.pop_back();
		}
		l.push_back(s[i]);
	}
	reverse(l.begin(), l.end());
	for (int i = u.size() - 2; i >= 1; i--) { l.push_back(u[i]); }

	res.n = l.size(); res.ps = l;
	return res;
}

//凸包
https://atcoder.jp/contests/agc021/submissions/30593360
