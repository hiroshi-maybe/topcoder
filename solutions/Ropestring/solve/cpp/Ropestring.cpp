#include <sstream>
#include <string>
#include <vector>
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

typedef unsigned long long ull;
typedef long long ll;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)
#define SORT(c) sort((c).begin(),(c).end())

// 0:09 start
// 0:40 passed

class Ropestring {
public:
  string makerope(string const &s) {
    vector<int> evens;
    vector<int> odds;
    int dots = 0;

    int cons = 0;
    REP(i,s.size()) {
      if (s[i] == '-') {
	cons += 1;
      } else {
	dots += 1;

	if (cons == 0) { continue; }

	if (cons % 2 == 1) {
	  odds.push_back(cons);
	} else {
	  evens.push_back(cons);
	}
	cons = 0;
      }
    }
    if (cons>0) {
      if (cons % 2 == 1) {
	odds.push_back(cons);
      } else {
	evens.push_back(cons);
      }
    }

    SORT(evens);
    SORT(odds);

    string ans = "";
    for(int i=evens.size()-1;i>=0;--i) {
      if (i!=evens.size()-1) {
	ans += ".";
	dots-=1;
      }
      ans += rope(evens[i]);
    }

    if (dots>0 && evens.size()>0) {
      ans += ".";
      dots-=1;
    }
    
    for(int i=odds.size()-1;i>=0;--i) {
      if (i!=odds.size()-1) {
	ans += ".";
	dots-=1;
      }
      ans += rope(odds[i]);
    }

    REP(i,dots) {
      ans += ".";
    }

    return ans;
  }

  string rope(int n) {
    string r = "";
    REP(i,n) {
      r += "-";
    }

    return r;
  }
};
