/*
k-d tree のお手軽実装について by tatyam
https://trap.jp/post/1489/
N - ビルの建設
https://atcoder.jp/contests/past202004-open/submissions/50942515
*/

using ll = long long;
using T = array<int, 3>;

void chmin(int &a, int b) { if(a>b){a=b;} }
void chmax(int &a, int b) { if(a<b){a=b;} }

struct kdTree{
  using Iter = vector<T>::iterator;
  kdTree *l = nullptr, *r = nullptr;
  int xmin = INT_MAX, xmax = INT_MIN, ymin = INT_MAX, ymax = INT_MIN;
  ll sum=0;
  kdTree(Iter begin, Iter end){
    for(auto p = begin; p != end; p++){
      auto [x, y, w] = *p;
      chmin(xmin, x); chmax(xmax, x); chmin(ymin, y); chmax(ymax, y);
      sum += w;
    }
    const int size = int(end - begin);
    if(size <= 1){return;}
    Iter cen = begin + size / 2;
    if(unsigned(xmax - xmin) > unsigned(ymax - ymin)){
      nth_element(begin, cen, end, [](T &a, T &b){ return (a[0] < b[0]); });
    }
    else{
      nth_element(begin, cen, end, [](T &a, T &b){ return (a[1] < b[1]); });
    }
    l = new kdTree(begin, cen);
    r = new kdTree(cen, end);
  }
  ll get(int x, int y){
    if(x < xmin || y < ymin){ return 0; }
    if(xmax <= x && ymax <= y){ return sum; }
    return l->get(x,y) + r->get(x,y);
  }
};
