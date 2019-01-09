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
typedef vector < VI > VVI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/*
 
 12/9/2017
 
 SRM 725
 
 9:00-9:42 system test passed (117.38 pt)
 
 12/10/2017
 
 23:00-23:15 add C(64,5) 5 nested loop solution
 23:30-23:45 add bipartite matching solution
 
 Editorial:
  - http://hamko.hatenadiary.jp/entry/2017/12/10/032659
   - 5 nested loops to pick up 5 out of all Rooks (= C(64,5))
  - http://kmjp.hatenablog.jp/entry/2017/12/11/0900
   - 9^8 DFS
  - https://twitter.com/hamko_intel/status/939565787357917184
   - C(64,5)
   - bipartite matching (flow)
   - 9^8
   - next_permutation
   - bit DP
   - adhoc
 
 12/17/2017
 
 If order to pick up Rook matters, search space is P(64,5) ≈9*10^8. This is a bit expensive.
 Actually order doesn't matter. We can just go through R in fixed order (like ascnedent order r=0..7).
 If time to compute `r` remaining rows, `c` remaining columns and `x` rooks is defined,...
   T(r,c,x)
 = 8*T(r-1,c-1,x-1) + T(r-1,c,x)
 < 9*T(r-1,c,x)
 
 That means T(8,8,5) <9^8 ≈4*10^7
 This brute-force search works.
 
 18:21- Add brute-force solution inspired by @kmjp's editorial.
 
 Summary:
  - Submit code had a bug of unnecessary assertion though, system test passed
   - I could not re-submit because server did not respond. Eventually unrated.
  - My original solution of greedy has no proof of correctness 👎
 
 */

class FiveRooks {
public:
  vector<string> B;
  VI res;
  void dfs(int r, int mask, VI &cur) {
    if(__builtin_popcount(mask)==5) {
      res=cur;
      return;
    }
    if(r==8) return;
    dfs(r+1,mask,cur);
    
    REP(c,8) if(B[r][c]=='R'&&(mask&(1<<c))==0) {
      cur.push_back(r);
      cur.push_back(c);
      dfs(r+1,mask|(1<<c),cur);
      cur.pop_back();
      cur.pop_back();
    }
  }
  
  vector<int> find(vector<string> B) {
    this->B=B;
    VI cur;
    dfs(0,0,cur);
    assert(SZ(res)==10);
    return res;
  }
};

const int MAX_V=16;
class MaxBipartiteMatching {
public:
  int match[MAX_V];
  
  MaxBipartiteMatching(int V) : V(V) {}
  void addEdge(int u, int v) {
    assert(u<V&&v<V);
    E[u].push_back(v);
    E[v].push_back(u);
  }
  
  int solve() {
    int res=0;
    memset(match, -1, sizeof(match));
    for(int u=0; u<V; ++u) if(match[u]<0) {
      memset(viz,0,sizeof viz);
      res+=dfs(u);
    }
    
    return res;
  }
private:
  int V;
  vector<int> E[MAX_V];
  bool viz[MAX_V];
  
  // find augmenting path in residual network
  bool dfs(int u) {
    viz[u]=true;
    for(auto v : E[u]) {
      int w=match[v];
      if(w<0||(!viz[w]&&dfs(w))) {
        match[v]=u;
        match[u]=v;
        return true;
      }
    }
    return false;
  }
};

// Bipartite matching, 16*64 time
class FiveRooks_matching {
public:
  vector<int> find(vector<string> B) {
    MaxBipartiteMatching M(16);
    REP(i,8)REP(j,8) if(B[i][j]=='R') M.addEdge(i,8+j);
    int mm=M.solve();
    assert(mm>4);
    
    VI res;
    REP(i,8) if(M.match[i]>=0) {
      res.push_back(i);
      res.push_back(M.match[i]-8);
      if(SZ(res)==10) break;
    }
    
    assert(SZ(res)==10);
    return res;
  }
};

// O(C(N,5)*5) time (<4*10^7), N=number of rooks.
class FiveRooks_comb {
public:
  vector<int> find(vector<string> B) {
    VI res;
    
    vector<II> xs;
    REP(i,8)REP(j,8) if(B[i][j]=='R') xs.emplace_back(i,j);
    
    int N=SZ(xs);
    REP(i0,N)FOR(i1,i0+1,N)FOR(i2,i1+1,N)FOR(i3,i2+1,N)FOR(i4,i3+1,N) {
      VI is={i0,i1,i2,i3,i4};
      SETI rs,cs;
      FORR(i,is) rs.emplace(xs[i].first),cs.emplace(xs[i].second);
      
      if(SZ(rs)==5&&SZ(cs)==5) {
        VI res;
        FORR(i,is) res.push_back(xs[i].first),res.push_back(xs[i].second);
        assert(SZ(res)==10);
        return res;
      }
    }
    
    assert(false);
    return {};
  }
};

// greedy, O(5*8*lg 8) time
class FiveRooks_greedy {
  public:
  vector<int> find(vector<string> B) {
    VI res;
    set<II> rs,cs;
    REP(i,8) {
      int cnt=0;
      REP(j,8) cnt+=B[i][j]=='R';
      if(cnt>0)rs.emplace(cnt,i);
    }
    REP(j,8) {
      int cnt=0;
      REP(i,8) cnt+=B[i][j]=='R';
      if(cnt>0)cs.emplace(cnt,j);
    }

    while(SZ(res)<10) {
      auto rit=rs.begin();
      auto cit=cs.begin();
      assert(rit!=rs.end()&&cit!=cs.end());
      
      if(rit->first<=cit->first) {
        int r=rit->second;
        II pp={-1,-1};
        FORR(p,cs) {
          int j=p.second;
          if(B[r][j]=='R') {
            pp=p;
            break;
          }
        }
        if(pp.first==-1) {
          rs.erase(rit);
          continue;
        }
        cs.erase(pp);
        rs.erase(rit);
        res.push_back(r);
        res.push_back(pp.second);
      } else {
        int c=cit->second;
        II pp={-1,-1};
        FORR(p,rs) {
          int i=p.second;
          if(B[i][c]=='R') {
            pp=p;
            break;
          }
        }
        if(pp.first==-1) {
          cs.erase(cit);
          continue;
        }
        rs.erase(pp);
        cs.erase(cit);
        res.push_back(pp.second);
        res.push_back(c);
      }
    }
    
//    dumpAR(res);
    assert(SZ(res)==10);
    return res;
  }
};

// CUT begin
ifstream data("FiveRooks.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<string> board, vector<int> __expected) {
    time_t startClock = clock();
    FiveRooks *instance = new FiveRooks();
    vector<int> __result = instance->find(board);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
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
        vector<string> board;
        from_stream(board);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512838810;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FiveRooks (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
