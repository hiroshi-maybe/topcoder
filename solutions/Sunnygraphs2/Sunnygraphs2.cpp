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

/**
 
 7/23/2017
 
 16:25-17:15 give up
 
 21:50-22:05 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/06/07/0900
  - adjacent matrix and floyd-warhall
 - http://pekempey.hatenablog.com/entry/2016/05/31/051609
 - http://ry0u.github.io/blog/2016/05/31/srm691-d2m-sunnygraphs2/
  - separate graphs into connected components by union-found
  - find cycle length by dfs passing depth
 - https://apps.topcoder.com/wiki/display/tc/SRM+691
  - find cycles by iterative dfs
 
 res=0
 All the vertices are connected? res += 1
 Suppose we have n cycles (C[i] vertices in a cycle,i=0..n-1) and x nodes outside cycles
 res += ∏ { 2^C[i]-1, i=0..<n } * 2^x
 
 22:05-22:37 add solution (implemented by myself)
 23:34 add solution by Floyd-Warshall and adjacent matrix solution
 
 Summary
 - idea was close though, I couldn't figure out how to handle vertices outside cycle (*x part above)
 - it was not good to try to count up invalid cases first
 
 */

// solution inspired by http://kmjp.hatenablog.jp/entry/2016/06/07/0900
// Floyd-Warshall and adjacent matrix
class Sunnygraphs2 {
public:
  int P[51][51];
  long long count(vector<int> a) {
    int V=SZ(a);
    REP(i,V) P[i][a[i]]=1, P[i][i]=1;
    // floyd-warshall
    REP(k,V)REP(i,V)REP(j,V) P[i][j]|=P[i][k]&P[k][j];
    
    LL res=1;
    SETI done;
    REP(u,V) if(!done.count(u)) {
      int cnt=1;
      done.insert(u);
      REP(v,V) if(v!=u && P[u][v] && P[v][u]) done.insert(v), ++cnt;
      if(cnt>1) res *= (1LL<<cnt)-1;
      else res*=2LL;
    }
    
    int con=1;
    REP(i,V) P[a[i]][i]=1;
    REP(k,V)REP(i,V)REP(j,V) P[i][j]|=P[i][k]&P[k][j];
    REP(i,V)REP(j,V) con&=P[i][j];
    
    return res + con;
  }
};

class Sunnygraphs2_org {
public:
  int E[51];
  int viz[51];
  int V;
  int uf[51]={0};
  int find(int u) { return uf[u]==u ? u : uf[u]=find(uf[u]); }
  void unite(int p1, int p2) {
    int r1=find(p1),r2=find(p2);
    uf[r1]=r2;
  }
  int comps() {
    REP(i,V) uf[i]=i;
    REP(u,V) unite(u,E[u]);
    SETI S;
    REP(u,V) S.insert(find(u));
    return SZ(S);
  }
  
  int dfs(int u) {
    if(viz[u]) return u;
    viz[u]=true;
    return dfs(E[u]);
  }
  long long count(vector<int> a) {
    V=SZ(a);
    REP(i,V) E[i]=a[i];
    
    VI C; SETI done;
    REP(u,V) {
      if(done.count(u)) continue;
      memset(viz, 0, sizeof viz);
      int v = dfs(u);
      
      // cycle
      if (u==v) {
        int vs=0;
//        cout << u << ":";
        REP(i,V) if(viz[i]) {
          ++vs, done.insert(i);
//          cout << i << ",";
        }
//        cout << "(" << vs << ")" << endl;
        C.push_back(vs);
      }
    }
    
    LL res=1LL<<(V-SZ(done));
    FORR(vs,C) res*=(1LL<<vs)-1LL;
    if (comps()==1) ++res;
    return res;
  }
};

/*
class Sunnygraphs2 {
  public:
  int uf[51];
  int find(int u) { return uf[u]==u ? u : uf[u]=find(uf[u]); }
  void unite(int p1, int p2) {
    int r1=find(p1),r2=find(p2);
    uf[r1]=r2;
  }
  long long count(vector<int> a) {
    int V=SZ(a);
    REP(i,V) uf[i]=i;
    REP(i,V) {
      unite(i,a[i]);
    }
    
    MAPII M;
    REP(u,V) ++M[find(u)];
    
    if(SZ(M)==1) return (LL)pow(2,V);
    
    LL tot=0LL;
    FORR(kvp,M) {
      LL x=kvp.second;
      tot += (LL)pow(2,x)-1LL;
      dump2(kvp.first,x);
    }
    
    return (LL)pow(2,V)-tot;
  }
};*/

// CUT begin
ifstream data("Sunnygraphs2.sample");

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

bool do_test(vector<int> a, long long __expected) {
    time_t startClock = clock();
    Sunnygraphs2 *instance = new Sunnygraphs2();
    long long __result = instance->count(a);
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
        vector<int> a;
        from_stream(a);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500852302;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Sunnygraphs2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
