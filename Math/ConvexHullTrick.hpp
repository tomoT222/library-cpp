// 直線の傾きA と 最小値クエリで問われる値x がどちらも単調の時に deque で O(N)
struct ConvexHullTrick
{
private:
    struct F
    {
        // 直線 Ax + B
        ll a, b;
        F(ll a, ll b) : a(a), b(b) {}
    };

    deque<F> deq;

    // f2が最小値をとる可能性があるか判定
    bool check(F &f1, F &f2, F &f3)
    {
        return (f2.a - f1.a) * (f3.b - f2.b) >= (f2.b - f1.b) * (f3.a - f2.a);
    }

    // 直線 f1 の x における y座標
    ll f(F &f1, ll x)
    {
        return f1.a * x + f1.b;
    }

public:
    // 直線 Ax+B を追加
    void add_line(ll a, ll b)
    {
        F f1 = F(a, b);
        while (deq.size() >= 2 && check(deq[deq.size() - 2], deq[deq.size() - 1], f1))
        {
            deq.pop_back();
        }
        deq.push_back(f1);
    }

    // x における最小値を取得
    ll query(ll x)
    {
        // 先頭が最小値でなければ取り除く
        while (deq.size() >= 2 && f(deq[0], x) >= f(deq[1], x))
        {
            deq.pop_front();
        }
        return f(deq[0], x);
    }
};
