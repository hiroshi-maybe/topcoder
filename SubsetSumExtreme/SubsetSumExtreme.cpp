#include <fstream> // for greed plugin
#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;

// type alias
typedef long long LL;

typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

int F,B;
double memo[15][5000]; // 5000 > 2^12 (block state), 15 > 12 (maximum die)
VI use[12];
VI block;

/**
 
 7/10/2017
 
 9:20-9:53 time up
 10:12 pause
 20:35 resume
 20:50 try memoized recursion to make optimal choice
 21:30 passed samples and system test
 
 Recursive relation was correct. should have decided to use top-down DP to get optimal solution easily.
 
 23:41 read editorials
 - http://beet-aizu.hatenablog.com/entry/2016/11/16/002730
 - top down DP
  - https://community.topcoder.com/stat?c=problem_solution&rd=16832&rm=329433&cr=23062614&pm=14440
 - bottom up DP
  - https://community.topcoder.com/stat?c=problem_solution&rd=16832&rm=329432&cr=23330595&pm=14440
  - https://community.topcoder.com/stat?c=problem_solution&rd=16832&rm=329438&cr=40280632&pm=14440
  - http://kmjp.hatenablog.jp/entry/2016/11/19/1100
 
 7/11/2017
 
 24:20-24:50 read editorials again
 
 */

double dfs(int x, int mask) {
  if (memo[x][mask]>=0) return memo[x][mask];
  
  double res=0.0;
  REP(i,F) {
    double minr=numeric_limits<double>::max();
    FORR(u,use[i]) {
      if((u&mask)==0) minr = min(minr, dfs(x+1, mask|u));
    }
    if (minr!=numeric_limits<double>::max()) res += minr;
    else {
      int sum=0;
      REP(i,B) if((mask&(1<<i))==0) {
        sum+=block[i];
      }
      res += (double)sum/pow(F,x);
    }
  }

  return memo[x][mask]=res;
}

// O(B^2*2^B*F) time
class SubsetSumExtreme {
public:
  double getExpectation(vector<int> _block, vector<int> face) {
    F=SZ(face), B=SZ(_block);
    REP(i,15) fill(memo[i],memo[i]+5000,-1.0);
    block = _block;
    REP(i,12) use[i].clear();
    for(int mask=0; mask<(1<<B); ++mask) {
      int sum=0;
      REP(i,B) if(mask&(1<<i)) sum+=block[i];
      
      REP(i,F) if(face[i]==sum) use[i].push_back(mask);
    }
    
    return dfs(1,0);
  }
};

// wrong solution!!
class SubsetSumExtreme_bottomup {
public:
  int cnt[15][5000];
  double getExpectation(vector<int> block, vector<int> face) {
    int F=SZ(face), B=SZ(block);
    memset(cnt, 0, sizeof cnt);
    REP(i,12) use[i].clear();
    for(int mask=0; mask<(1<<B); ++mask) {
      int sum=0;
      REP(i,B) if(mask&(1<<i)) sum+=block[i];
      
      REP(i,F) if(face[i]==sum) use[i].push_back(mask);
    }
    
    double res=0.0;
    cnt[0][0]=1;
    REP(x,12) {
      for(int mask=0; mask<(1<<B); ++mask) {
        if(cnt[x][mask]==0) continue;
        
        bool ok=false;
        REP(i,F) {
          FORR(u,use[i]) {
            if((u&mask)==0) {
              cnt[x+1][u|mask]+=cnt[x][mask];
              ok=true;
            }
          }
        }
        //assert(x!=0);
        if(!ok) {
          int sum=0;
          REP(i,B) if((mask&(1<<i))==0) sum+=block[i];
          dump4(x,mask,sum,cnt[x][mask]);
          res += (double)sum*(double)cnt[x][mask]/pow(F,x);
          dump(res);
        }
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("SubsetSumExtreme.sample");

string next_line() {
  string s;
  getline(data, s);
  return s;
}

template <typename T> void from_stream(T &t) {
  stringstream ss(next_line());
  ss >> t;
}

void from_stream(string &s) {
  s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
  int len;
  from_stream(len);
  ts.clear();
  for (int i = 0; i < len; ++i) {
    T t;
    from_stream(t);
    ts.push_back(t);
  }
}

template <typename T>
string to_string(T t) {
  stringstream s;
  s << t;
  return s.str();
}

string to_string(string t) {
  return "\"" + t + "\"";
}

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> block, vector<int> face, double __expected) {
  time_t startClock = clock();
  SubsetSumExtreme *instance = new SubsetSumExtreme();
  double __result = instance->getExpectation(block, face);
  double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
  delete instance;
  
  if (double_equal(__expected, __result)) {
    cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
    return true;
  }
  else {
    cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
    cout << "           Expected: " << to_string(__expected) << endl;
    cout << "           Received: " << to_string(__result) << endl;
    return false;
  }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
  int cases = 0, passed = 0;
  while (true) {
    if (next_line().find("--") != 0)
      break;
    vector<int> block;
    from_stream(block);
    vector<int> face;
    from_stream(face);
    next_line();
    double __answer;
    from_stream(__answer);
    
    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;
    
    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(block, face, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1499703609;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2);
  set<int> cases;
  bool mainProcess = true;
  for (int i = 1; i < argc; ++i) {
    if ( string(argv[i]) == "-") {
      mainProcess = false;
    } else {
      cases.insert(atoi(argv[i]));
    }
  }
  if (mainProcess) {
    cout << "SubsetSumExtreme (1000 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
