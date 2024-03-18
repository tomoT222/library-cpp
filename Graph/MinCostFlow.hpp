struct edge
{
    ll to, cap, cost, rev;
};

struct MinCostFlow
{
    int V;
    vector<vector<edge>> G;
    vector<ll> h; // ポテンシャル
    vector<ll> dist;
    vector<ll> prev_v, prev_e;
    MinCostFlow(int kV)
    {
        V = kV;
        G.resize(V);
        h.resize(V);
        dist.resize(V);
        prev_v.resize(V);
        prev_e.resize(V);
    }
    void add_edge(int from, int to, ll cap, ll cost)
    {
        G[from].push_back((edge){to, cap, cost, G[to].size()});
        G[to].push_back((edge){from, 0, -cost, G[from].size() - 1});
    }
    ll min_cost_flow(int s, int t, ll f)
    {
        ll res = 0;
        rep(i, V) { h[i] = 0; }
        while (f > 0)
        {
            // Dijkstra
            priority_queue<P, vector<P>, greater<P>> que;
            rep(i, V) { dist[i] = INF; }
            dist[s] = 0;
            que.push(P(0, s));
            while (!que.empty())
            {
                P p = que.top();
                que.pop();
                int v = p.second;
                if (dist[v] < p.first)
                {
                    continue;
                }
                for (int i = 0; i < G[v].size(); i++)
                {
                    edge e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to])
                    {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prev_v[e.to] = v;
                        prev_e[e.to] = i;
                        que.push(P(dist[e.to], e.to));
                    }
                }
            }
            if (dist[t] == INF)
            {
                return -1;
            }
            rep(v, V) { h[v] += dist[v]; }
            // s-t間最短路に沿って目一杯流す
            ll d = f;
            for (int v = t; v != s; v = prev_v[v])
            {
                d = min(d, G[prev_v[v]][prev_e[v]].cap);
            }
            f -= d;
            res += d * h[t];
            for (int v = t; v != s; v = prev_v[v])
            {
                edge &e = G[prev_v[v]][prev_e[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};
