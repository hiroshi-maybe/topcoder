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

constexpr int MOD = 1e9+7;

/**

 10:06-11:23 time up
 
 cannot fix "a.out(2253,0x7fffccbf83c0) malloc: *** error for object 0x7fcc14c02880: pointer being freed was not allocated" error
 maybe vector shouldn't be pushed to queue?
 
 24:55-26:07 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/09/19/1000
 - 0<=p[i]<=i means we can take leaves first by iterating edges from e(N-1,p[N-1])
 - tree DP: count up from leaves
 
 https://community.topcoder.com/stat?c=problem_solution&rm=329238&rd=16802&pm=14392&cr=40382230
 https://community.topcoder.com/stat?c=problem_solution&rm=329230&rd=16802&pm=14392&cr=40251940
 - topdown tree DP
 - not sure why ∏{v[i]+1, v[i]∈adjacent vertices} works
  - got it. v[i] (number of sub tree) + 1 (option that we take no subtree rooted by v[i])
 
 http://codeforces.com/blog/entry/20935
 http://hamayanhamayan.hatenablog.jp/entry/2017/06/19/161741
 - tree DP
 
 10:00-10:42 understood the tree DP algorithm
 10:42-11:22 passed system test by copied recursive relation
 12:10-13:10 finally found a bug in my implementation. bug is in base case of recursive relation.
 14:00 found another bug in recursive relation. count up is wrong.
 14:57 passed by my own implementation
 
 Eventually count up was wrong. There are two points
 - When looking at another adjacent node, add 1 to count up a case where the node is not taken
 - Count up of combination is defined by recursive relation. Make sure counting is covering all the cases.
 
 // recursive relation in a graph rooted at `u`
 // cnt[u][0][j] = cnt[u][0][j-1]*(cnt[v][0]+1)
 // cnt[u][1][j] = cnt[u][0][j-1]*cnt[v][1] (this case was missing when mybit is 0) + cnt[u][1][j-1]*(cnt[v][0]+cnt[v][1]+1)

 Challenge of this problem
 - simplify by suming by bits separated
 - tree DP
 - count up comprehensively
 - easier to count up in recursive manner
 
 */

VI E[51];
LL cnt1[51][2];
LL cnt2[51][2];

int V;
VI W;

void dfs1(int u, int pre, int bit) {
  int mybit = ((W[u]>>bit)&1)!=0;
  
  int n=0;
  LL x0=!mybit, x1=mybit;
  if(mybit) {
    REP(i, SZ(E[u])) {
      int v=E[u][i];
      if(v==pre) continue;
      ++n;
      
      dfs1(v, u, bit);
      x1*=cnt1[v][1]+cnt1[v][0]+1, x1%=MOD;
    }
  } else {
    REP(i, SZ(E[u])) {
      int v=E[u][i];
      if(v==pre) continue;
      ++n;
      
      dfs1(v, u, bit);
      
      x1=x0*cnt1[v][1]+x1*(cnt1[v][1]+cnt1[v][0]+1), x1%=MOD;
      x0*=cnt1[v][0]+1, x0%=MOD;
    }
  }
  cnt1[u][0]=x0, cnt1[u][1]=x1;
}

void dfs2(int u, int pre, int bit) {
  int mybit = ((W[u]>>bit)&1)!=0;
  cnt2[u][mybit]=1;
  REP(i, SZ(E[u])) {
    int v=E[u][i];
    if(v==pre) continue;
    
    dfs2(v, u, bit);
    
    //if(!mybit) {
    //  cnt[u][0] *= 1+cnt[v][0];
    //  cnt[u][1] *= cnt[v][1];
    //} else {
    //  cnt[u][0] *= 0;//1+cnt[v][0];
    //  cnt[u][1] *= cnt[v][1] + cnt[v][0] + 1;
    //}
    
    // recursive relation in a graph rooted at `u`
    // cnt[u][0][j] = cnt[u][0][j-1]*(cnt[v][0]+1)
    // cnt[u][1][j] = cnt[u][0][j-1]*cnt[v][1] + cnt[u][1][j-1]*(cnt[v][0]+cnt[v][1]+1)
    
    LL a0 = cnt2[u][0],a1=cnt2[u][1];
    cnt2[u][0] = a0*(1+cnt2[v][0]);
    cnt2[u][1] = a0*cnt2[v][1]+a1*(cnt2[v][1] + cnt2[v][0] + 1);
  }
  
  if(cnt1[u][1]!=cnt2[u][1]) {
    dump4(u,pre,bit,mybit);
    dump2(cnt2[u][0],cnt2[u][1]);
    dump2(cnt1[u][0],cnt1[u][1]);
    assert(false);
  }
}

class SubtreeSum {
public:
  int getSum(vector<int> p, vector<int> x) {
    REP(i,51) E[i]={};
    W = x;
    V = SZ(x);
    LL res=0;
    REP(i,V-1) E[i+1].push_back(p[i]), E[p[i]].push_back(i+1);
    
    REP(i,32) {
      memset(cnt1,0,sizeof cnt1);
      memset(cnt2,0,sizeof cnt2);

      dfs1(0,-1,i);
//      dfs2(0,-1,i);
      
      LL tot = 0;
      REP(u,51) tot+=cnt1[u][1], tot%=MOD;
      res += (tot<<i)%MOD, res%=MOD;
    }
    
    return res;
  }
};
  
class SubtreeSum_org {
  public:
  VI E[51];
  int V;
  VI W;
  LL res;

  LL dfs(int u, int pre) {
    dump2(u,SZ(E[u]));
    LL v = W[u];
    LL vt = v;
    res += vt, res%=MOD;
    
    VI ws;
    queue<pair<int,VI>> Q;
    REP(i, SZ(E[u])) {
      int v=E[u][i];
      dump3(i,u,v);
      if(v!=pre) {
        int vtsub = dfs(v, u);
        vt |= vtsub;
        ws.push_back(vtsub);
        VI xs={i};
        Q.push(make_pair(vt|vtsub, xs));
      }
    }
    
    int ADJ = SZ(ws);
    dump2(Q.size(), ADJ);
    
    if(Q.empty()) return vt;
    while(true) {
      auto cur = Q.front(); Q.pop();
      res += cur.first, res%=MOD;
      if(SZ(cur.second)==ADJ) break;
      
      int last=cur.second.back();
      REP(i,ADJ) {
        if(i>last) {
          dump2(cur.first, SZ(cur.second));
          VI vs = cur.second; vs.push_back(i);
          dump2(cur.first, SZ(vs));
          Q.push(make_pair(cur.first|ws[i], vs));
        }
      }
    }
    return vt;
  }
  
  int getSum(vector<int> p, vector<int> x) {
    REP(i,51) E[i]={};
    W = x;
    V = SZ(x);
    dump(V);
    res=0;
    REP(i,V-1) E[i+1].push_back(p[i]), E[p[i]].push_back(i+1);

    dfs(1,-1);
    
    return res;
  }
};

// CUT begin
ifstream data("SubtreeSum.sample");

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

bool do_test(vector<int> p, vector<int> x, int __expected) {
    time_t startClock = clock();
    SubtreeSum *instance = new SubtreeSum();
    int __result = instance->getSum(p, x);
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
        vector<int> p;
        from_stream(p);
        vector<int> x;
        from_stream(x);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(p, x, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500138351;
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
        cout << "SubtreeSum (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
