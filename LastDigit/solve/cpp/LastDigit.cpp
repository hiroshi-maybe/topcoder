#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <utility>
#include <set>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long ll;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)

class LastDigit {
public:
  ll sumup(ll x) {
    ll s = 0;
    while (x > 0) {
      s += x;
      x /= 10;
    }

    return s;
  }
  
  ll findX(ll S) {
    ll s = 0;
    ll e = 1000000000L * 1000000000;
    ll mid = 0;

    while (s<e) {
      mid = (s + e) >> 1;
      ll sum = sumup(mid);
      if (sum==S) { return mid; }
      if (sum<S) s = mid+1;
      if (sum>S) e = mid;
    }

    return -1;    
  }
};
