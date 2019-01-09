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
 
 11/19/2017
 
 9:11-9:30 analysis
 9:30-9:46 1WA (262.23 pt)
 10:26-10:36 fixed a bug. If any isolated vertex exists, result is undetermined
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+584
  - http://kmjp.hatenablog.jp/entry/2013/07/11/0900
  - http://torus711.hatenablog.com/entry/20130710/p1
  - https://topcoder.g.hatena.ne.jp/firewood/20130726/1374859460
 
 Key:
  - if all the vertices are NOT connected, -1
  - otherwise diameter of the graph is result
 
 Summary:
  - slow to reduce to graph diameter problem
  - mistake in analysis about connected component 👎
   - it complicated the problem and algorithm design
  - pay more attention to problem statement to understand edge cases and invalid cases
  - it's important to remember some important subproblems like graph diameter in this problem
 
 */
int mx[51][51];
class Egalitarianism {
public:
  int V;
  vector<string> G;
  int maxDifference(vector<string> G, int D) {
    this->G=G;
    this->V=SZ(G);
    
    const int Inf=1e4;
    REP(i,V)REP(j,V) {
      if(i==j) mx[i][j]=0;
      else mx[i][j]=G[i][j]=='Y'?1:Inf;
    }
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]=min(mx[i][j],mx[i][k]+mx[k][j]);
    
    int d=0;
    REP(i,V)REP(j,V) {
      if (mx[i][j]>=Inf) return -1;
      d=max(d,mx[i][j]);
    }
    return d*D;
  }
};

int viz[51];
class Egalitarianism_org {
  public:
  int V;
  vector<string> G;
  void dfs(int u) {
    if(viz[u]) return;
    viz[u]=true;
    REP(v,V) if(G[u][v]=='Y') dfs(v);
  }
  int maxDifference(vector<string> G, int D) {
    this->G=G;
    this->V=SZ(G);
    ZERO(viz);
    REP(i,V) if(count(G[i].begin(),G[i].end(),'Y')==0) return -1;
    int x=-1;
    REP(i,V) if(viz[i]==0) {
      x=i;
      dfs(x);
      break;
    }
//    if(x==-1) return -1;
//    dump(V);
//    dumpAR(viz);
    REP(i,V) if(viz[i]==0) return -1;

    const int Inf=1e4;
    REP(i,V)REP(j,V) {
      if(i==j)mx[i][j]=0;
      else mx[i][j]=G[i][j]=='Y'?1:Inf;
//      if(i<j&&G[i][j]=='Y') dump2(i,j);
    }
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]=min(mx[i][j],mx[i][k]+mx[k][j]);
    
    int d=0;
    REP(i,V)REP(j,V) if(mx[i][j]<Inf) d=max(d,mx[i][j]);
//    dump(d);
    return d*D;
  }
};

// CUT begin
ifstream data("Egalitarianism.sample");

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

bool do_test(vector<string> isFriend, int d, int __expected) {
    time_t startClock = clock();
    Egalitarianism *instance = new Egalitarianism();
    int __result = instance->maxDifference(isFriend, d);
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
        vector<string> isFriend;
        from_stream(isFriend);
        int d;
        from_stream(d);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(isFriend, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1511111504;
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
        cout << "Egalitarianism (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
