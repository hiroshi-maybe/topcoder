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
#include <unordered_map>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)
#define EXIST(s,e) ((s).find(e)!=(s).end())

// 0:40 start
// 0:59 end

class Arrfix {
public:
  int mindiff(vector<int> &A,
              vector<int> const &B,
              vector<int> const &F) {
    
    map<int,int> f;
    FORR(n,F) {
      f[n]++;
    }

    int dif = 0;
    int remainF = F.size();

    vector<bool> reps;
    REP(i,A.size()) {
      reps.push_back(false);
    }
    REP(i,A.size()) {
      int a = A[i];
      int b = B[i];

      if (a==b) { continue; }
      if (f[b]) {
	f[b]-=1;
	remainF-=1;
	A[i] = b;
	reps[i] = true;
      } else {
	dif += 1;
      }
    }

    REP(i,A.size()) {
      int a = A[i];
      int b = B[i];

      if (!reps[i] && a==b && f[b]) {
	f[b]-=1;
	remainF-=1;
	reps[i] = true;
      }
    }

    return max(dif, remainF);
  }
};
