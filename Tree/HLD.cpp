/*
K - 虫取り
https://atcoder.jp/contests/iroha2019-day2/submissions/51190525
部分木加算　と　パスの和＆パスに対する更新
*/

// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_D
// のACコード。
// 0-indexed。セグメント木やHLD内でのクエリのadd,sumの処理の部分を適宜書き換える。
// main関数内ではp,cに値を入れて hld.init();hld.update();hld.query(); をする。

#include <bits/stdc++.h>
#define rep(i, x) for (int i = 0; i < x; i++)
using namespace std;

struct rsq
{
    int nn;
    vector<int> dat; // セグメント木を持つグローバル配列

    void init(int n_)
    {           // 初期化
        nn = 1; // 簡単のため、要素数を2のべき乗に
        while (nn < n_)
        {
            nn *= 2;
        }

        dat.resize(2 * nn);
        // 全ての値をINT_MAXに
        // for (int i = 0; i < 2 * nn - 1; i++) dat[i] = INT_MAX;
    }

    void add(int k, int a)
    { // k番目の値(0-indexed)をa増加させる
        k += nn - 1;
        dat[k] += a; // 葉の節点
        while (k > 0)
        { // 登りながら更新
            k = (k - 1) / 2;
            dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
        }
    }

    //[a, b)のsumを求める
    // kは節点の番号、l, rはその節点が[l, r)に対応づいていることを表す。
    // したがって外からはquery(a, b, 0, 0, nn)として呼ぶ。
    int query(int a, int b, int k = 0, int l = 0, int r = -1)
    {
        if (r < 0)
        {
            r = nn;
        }
        //[a, b)と[l, r)が交差しなければ、INT_MAX}
        //[a, b)が[l, r)を完全に含んでいれば、この節点の値
        if (r <= a || b <= l)
        {
            return 0;
        }
        if (a <= l && r <= b)
        {
            return dat[k];
        }
        else
        {
            int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return vl + vr;
        }
    }
};

struct HLD
{
private:
    int n;           // 頂点数
    vector<int> siz; // 部分木のサイズ
    vector<int> idx; // セグメント木におけるindex
    vector<int> A;   // 連結成分の最も浅い頂点
    vector<int> d;   // 深さ

public:
    vector<int> p;         // [main関数内] 親
    vector<vector<int>> c; // [main関数内] 子
    rsq seg;               // セグメント木
    HLD(int kn)
    {
        n = kn;
        p.resize(n, -1);
        c.resize(n);
        siz.resize(n);
        idx.resize(n);
        A.resize(n);
        d.resize(n);
    }

private:
    // 頂点 v を根とする部分木の要素数を求める
    int get_size(int v)
    {
        if (siz[v] != 0)
        {
            return siz[v];
        }

        siz[v] = 1;
        for (int i = 0; i < (int)c[v].size(); i++)
        {
            siz[v] += get_size(c[v][i]);
        }
        return siz[v];
    }

    vector<int> sections; // 分解した区間を1直線状に並べる

    // 分解 Decomposition
    void Dec(int v, int a)
    {
        idx[v] = sections.size();
        sections.emplace_back(v);
        A[v] = a;

        if (c[v].size() == 0)
        {
            return;
        }

        int M = 0, index = -1; // 部分木のサイズが最大の子（Heavyな頂点）
        for (int i = 0; i < (int)c[v].size(); i++)
        {
            if (M < get_size(c[v][i]))
            {
                M = get_size(c[v][i]);
                index = i;
            }
        }
        Dec(c[v][index], a);

        for (int i = 0; i < (int)c[v].size(); i++)
        {
            if (i != index)
            {
                Dec(c[v][i], c[v][i]);
            }
        }
    }

public:
    // [main関数内] 適宜書き換える
    void init()
    {
        seg.init(n);
        rep(i, n)
        {
            if (p[i] == -1)
            {
                Dec(i, i);
            }
        }
    }
    void update(int v, int a)
    {
        seg.add(idx[v], a);
    }

private:
    int depth(int v)
    {
        if (d[v] != 0)
        {
            return d[v];
        }
        if (p[v] == -1)
        {
            return 0;
        }
        return d[v] = 1 + depth(p[v]);
    }

public:
    // クエリ処理 ここを書き換える！！！
    int query(int u, int v)
    {
        vector<pair<int, int>> ret;
        while (A[u] != A[v])
        {
            if (depth(A[u]) > depth(A[v]))
            {
                swap(u, v);
            }
            // depth(A[u]) <= depth(A[v])
            ret.push_back({idx[A[v]], idx[v]});
            v = p[A[v]];
        }

        if (idx[u] > idx[v])
        {
            swap(u, v);
        }
        // idx[u] <= idx[v]
        ret.push_back({idx[u], idx[v]});

        ////////////////////////////////////////////////////////////
        //
        //     ここから問題ごとに書き換える
        //
        int sum = 0;
        rep(i, (int)ret.size())
        {
            sum += seg.query(ret[i].first, ret[i].second + 1);
        }

        return sum;
    }
};

int main()
{
    int n;
    cin >> n;
    HLD hld(n);
    rep(i, n)
    {
        int ko;
        cin >> ko;
        rep(j, ko)
        {
            int v;
            cin >> v;
            hld.p[v] = i;
            hld.c[i].emplace_back(v);
        }
    }

    hld.init();

    int q;
    cin >> q;
    rep(z, q)
    {
        int com;
        cin >> com;
        if (com == 0)
        {
            int v, w;
            cin >> v >> w;
            hld.update(v, w);
        }
        if (com == 1)
        {
            int v;
            cin >> v;
            cout << hld.query(0, v) << endl;
        }
    }
}
