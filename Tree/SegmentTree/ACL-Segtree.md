https://atcoder.github.io/ac-library/document_ja/segtree.html

## コンストラクタ

```c++
(1) segtree<S, op, e> seg(int n)
(2) segtree<S, op, e> seg(vector<S> v)

//Range Min Query
int op(int a, int b) {
    return min(a, b);
}
int e() {
    return (int)(1e9);
}
segtree<int, op, e> seg(10);
```

## いろいろ

```c++
void seg.set(int p, S x) //a[p] に x を代入。O(logn)
S seg.get(int p)         //a[p] を返す。O(1)
S seg.prod(int l, int r) //op(a[l], ..., a[r - 1]) を返す。O(logn)
S seg.all_prod()         //op(a[0], ..., a[n - 1]) を返す。O(1)
```

