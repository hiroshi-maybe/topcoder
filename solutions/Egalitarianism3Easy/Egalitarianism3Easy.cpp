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
 
 9/24/2017
 
 12:27-13:11 system test passed (226.98 pt)
 13:00 finally noticed noticed bit mask
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+630
 
 editorials for div1 easy (V<=50):
    - http://topcoder.g.hatena.ne.jp/kojingharang/20140822#1408683021
    - http://kmjp.hatenablog.jp/entry/2014/08/24/0900
 
 max clique problem:
  - https://ja.wikipedia.org/wiki/%E6%9C%80%E5%A4%A7%E3%82%AF%E3%83%AA%E3%83%BC%E3%82%AF%E5%95%8F%E9%A1%8C
 
 key:
  - brute-force all subsets of vertices
 
 summary:
  - V is small. Notice it soon 👎
 
 15:30-15:53 add solution that works in V<=50 (div1)
 
 submit solutions:
  - dfs instead of bit mask
    - https://community.topcoder.com/stat?c=problem_solution&rm=323325&rd=16061&pm=13376&cr=40035551
  - bit mask
    - https://community.topcoder.com/stat?c=problem_solution&rm=323336&rd=16061&pm=13376&cr=22933742
    - https://community.topcoder.com/stat?c=problem_solution&rm=323312&rd=16061&pm=13376&cr=22913297
 
 */

// solution that works for div1 too
int mx[11][11];
class Egalitarianism3Easy {
public:
  const int Inf=1e5;
  int maxCities(int V, vector<int> A, vector<int> B, vector<int> W) {
    REP(i,V)REP(j,V) mx[i][j]=i==j?0:Inf;
    REP(i,SZ(A)) {
      int u=A[i]-1,v=B[i]-1;
      mx[u][v]=mx[v][u]=W[i];
    }
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]=min(mx[i][j],mx[i][k]+mx[k][j]);
    int res=min(V,2);
    
    REP(u,V) {
      unordered_map<int,SETI> cnt;
      REP(v,V) {
        int d=mx[u][v];
        bool ok=true;
        FORR(w,cnt[d]) {
          if(mx[w][v]!=2*d) ok=false;
        }
        if(ok) cnt[d].emplace(v);
        res=max(res,SZ(cnt[d]));
      }
    }
    
    return res;
  }
};

class Egalitarianism3Easy_org {
  public:
  const int Inf=1e5;
  int maxCities(int V, vector<int> A, vector<int> B, vector<int> W) {
    REP(i,V)REP(j,V) mx[i][j]=i==j?0:Inf;
    REP(i,SZ(A)) {
      int u=A[i]-1,v=B[i]-1;
      mx[u][v]=mx[v][u]=W[i];
    }
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]=min(mx[i][j],mx[i][k]+mx[k][j]);
    int res=1;
    REP(mask, 1<<V) if(__builtin_popcount(mask)>1) {
      VI vs;
      REP(i,V) if(mask&(1<<i)) vs.push_back(i);
      assert(SZ(vs)>=2);
      int d=mx[vs[0]][vs[1]];
      bool ok=true;
      REP(i,SZ(vs))FOR(j,i+1,SZ(vs)) if(mx[vs[i]][vs[j]]!=d) ok=false;
      if(ok) res=max(res,SZ(vs));
    }
    
    return res;
  }
};

// CUT begin
ifstream data("Egalitarianism3Easy.sample");

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

bool do_test(int n, vector<int> a, vector<int> b, vector<int> len, int __expected) {
    time_t startClock = clock();
    Egalitarianism3Easy *instance = new Egalitarianism3Easy();
    int __result = instance->maxCities(n, a, b, len);
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
        int n;
        from_stream(n);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        vector<int> len;
        from_stream(len);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, a, b, len, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506281221;
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
        cout << "Egalitarianism3Easy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
