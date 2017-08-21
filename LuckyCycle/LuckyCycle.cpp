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
 
 8/20/2017
 
 15:36-15:55 (352.99 pt)
 17:10-17:15 add edge of another direction and pass system test
 
 editorials:
  - http://kmjp.hatenablog.jp/entry/2015/08/13/0930
  - https://apps.topcoder.com/wiki/display/tc/SRM+665
 
 res = (u,v,4/7) where |cnt(u,v,4)-cnt(u,v,7)|==1
 
 Summary:
  - quick analysis and algorithm design 👍
  - took a bit time to combine count of 4 and 7 edges and shortest distance 👎
  - don't miss bi-directional edges in undirected graph 💢
 
 */
int cnt4[100][100];
int cnt7[100][100];
int mx[100][100];
class LuckyCycle {
  public:
  const int Inf=1000;
  vector<int> getEdge(vector<int> E1, vector<int> E2, vector<int> W) {
    ZERO(cnt4); ZERO(cnt7);
    int V=SZ(W)+1;
    REP(i,V)REP(j,V) mx[i][j]=Inf;
    REP(i,V-1) {
      int u=E1[i]-1,v=E2[i]-1;
      if(W[i]==4) cnt4[u][v]=cnt4[v][u]=1;
      else cnt7[u][v]=cnt7[v][u]=1;
      mx[u][v]=mx[v][u]=1;
    }
    REP(k,V)REP(i,V)REP(j,V) {
      int d=mx[i][k]+mx[k][j];
      if(mx[i][j]>d) {
        cnt4[i][j]=cnt4[i][k]+cnt4[k][j];
        cnt7[i][j]=cnt7[i][k]+cnt7[k][j];
        mx[i][j]=d;
      }
    }
    
    REP(i,V) REP(j,V) if(i!=j&&abs(cnt4[i][j]-cnt7[i][j])==1&&mx[i][j]>1) {
      int x=cnt4[i][j]<cnt7[i][j]?4:7;
      return {i+1,j+1,x};
    }
    return {};
  }
};

// CUT begin
ifstream data("LuckyCycle.sample");

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

bool do_test(vector<int> edge1, vector<int> edge2, vector<int> weight, vector<int> __expected) {
    time_t startClock = clock();
    LuckyCycle *instance = new LuckyCycle();
    vector<int> __result = instance->getEdge(edge1, edge2, weight);
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
        vector<int> edge1;
        from_stream(edge1);
        vector<int> edge2;
        from_stream(edge2);
        vector<int> weight;
        from_stream(weight);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(edge1, edge2, weight, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503268550;
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
        cout << "LuckyCycle (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
