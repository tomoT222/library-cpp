/*
L - ビ太郎の旅 (Bitaro's Travel)
https://atcoder.jp/contests/joisp2023/submissions/51397551
*/
  vector<vector<ll>> table_l(n+2, vector<ll>(20));
  vector<vector<ll>> table_r(n+2, vector<ll>(20));
  ll two = 1;
  rep(k,20){
    rep2(i,n){
      if(k==0){
        table_l[i][k] = vl[i];
        table_r[i][k] = vr[i];
      }
      else{
        if(i+two>n){
          table_l[i][k] = table_l[i][k-1];
          table_r[i][k] = table_r[i][k-1];
        }
        else{
          table_l[i][k] = max(table_l[i][k-1], table_l[i + two][k-1]);
          table_r[i][k] = min(table_r[i][k-1], table_r[i + two][k-1]);
        }
      }
    }
    if(k!=0){two*=2;}
  }
// ll Max = max(table_l[mid][logN[size]], table_l[l - (1 << logN[size])][logN[size]]);
// ll Min = min(table_r[r+1][logN[size]], table_r[mid - (1 << logN[size]) + 1][logN[size]]);
