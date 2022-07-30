## コンストラクタ
```c++
mf_graph<Cap> graph(int n) //n 頂点。Capは容量の型。O(n)
```

## いろいろ
```c++
int graph.add_edge(int from, int to, Cap cap); //fromからtoへ最大容量capの辺。何番目に追加された辺かを返す。O(1)

(1) Cap graph.flow(int s, int t);                 //頂点 s から t へ流せる量
(2) Cap graph.flow(int s, int t, Cap flow_limit); //頂点 s から t へ流量 flow_limit に達するまで流せる限り流し、流せた量を返す。

vector<bool> graph.min_cut(int s) //長さ n のvectorを返す。

struct mf_graph<Cap>::edge {
    int from, to;
    Cap cap, flow;
};
(1) mf_graph<Cap>::edge graph.get_edge(int i); //辺の状態。O(1)
(2) vector<mf_graph<Cap>::edge> graph.edges();

void graph.change_edge(int i, Cap new_cap, Cap new_flow); //流量変更。(1)
```
