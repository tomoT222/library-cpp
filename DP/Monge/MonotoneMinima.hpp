// https://atcoder.jp/contests/colopl2018-final-open/submissions/40292416

vector<ll> a;
vector<ll> ans;

void MonotoneMinima(int il, int ir, int jl, int jr)
{
    if (il >= ir)
    {
        return;
    }
    int mid = (il + ir) / 2;
    int pos = -1;
    ll mi = INF;
    for (int j = jl; j < jr; j++)
    {
        if (chmin(mi, a[j] + (ll)(j - mid) * (ll)(j - mid)))
        {
            pos = j;
        }
    }
    ans[mid] = mi;
    MonotoneMinima(il, mid, jl, pos + 1);
    MonotoneMinima(mid + 1, ir, pos, jr);
}
