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
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)

class GridSortMax {
public:
  string findMax(int n,
                 int m,
                 vector<int> &grid) {
    unordered_set < int > rset;
    unordered_set < int > cset;
    for(int x=1; x<=n*m; x++) {
      int p = find(grid.begin(),grid.end(), x) - grid.begin();

      int r1 = p / m;
      int c1 = p % m;

      int r2 = (x-1) / m;
      int c2 = (x-1) % m;

      if (r1!=r2 && (rset.find(r1)!=rset.end() || rset.find(r2)!=rset.end())) continue;
      if (c1!=c2 && (cset.find(c1)!=cset.end() || cset.find(c2)!=cset.end())) continue;

      if (r1!=r2) swapr(n,m,grid,r1,r2);
      if (c1!=c2) swapc(n,m,grid,c1,c2);

      rset.insert(r2);
      cset.insert(c2);
    }

    return sims(n,m,grid);
  }

  void swapr(int n, int m, vector <int> &grid, int r1, int r2) {
    REP(i, m) {
      swap(grid[r1*m+i], grid[r2*m+i]);
    }
  }
  void swapc(int n, int m, vector <int> &grid, int c1, int c2) {
    REP(i, n) {
      swap(grid[i*m+c1], grid[i*m+c2]);
    }
  }

  string sims(int n, int m, vector <int> &grid) {
    string str="";
    REP(i,n*m) {
      if (grid[i] == i+1) str.push_back('1');
      else str.push_back('0');
    }

    return str;
  }
};
