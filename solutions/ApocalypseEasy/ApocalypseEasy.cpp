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
 
 10/2/2017
 
 18:00-18:44 analysis
 18:45-18:53 submit, but 1 WA
 18:54-19:23 find reachable token greedily and system test passed
 
 editorial:
  - min-cut/max-flow
    - http://kmjp.hatenablog.jp/entry/2017/09/27/1000
    - http://codeforces.com/blog/entry/54768
 
 submit solutions:
  - flow
   - https://community.topcoder.com/stat?c=problem_solution&rm=330602&rd=16983&pm=14710&cr=40640673
   - https://community.topcoder.com/stat?c=problem_solution&rm=330607&rd=16983&pm=14710&cr=40610429
   - https://community.topcoder.com/stat?c=problem_solution&rm=330592&rd=16983&pm=14710&cr=40640194
   - https://community.topcoder.com/stat?c=problem_solution&rm=330592&rd=16983&pm=14710&cr=40640606
  - greedy
   - https://community.topcoder.com/stat?c=problem_solution&rm=330597&rd=16983&pm=14710&cr=22853104
 
 */
LL X[51];
int mx[51][51];
class ApocalypseEasy {
  public:
  const int Inf=1e4;
  int maximalSurvival(vector<int> P, vector<int> position, int T) {
    int V=SZ(P)+1;
    ZERO(X);
    SETI ts,es;
    REP(i,SZ(position)) ts.emplace(position[i]);
    REP(i,V) if(!ts.count(i)) es.emplace(i);
    
    REP(i,V)REP(j,V) mx[i][j]=i==j?0:Inf;
    REP(i,SZ(P)) {
      int u=i+1,v=P[i];
      mx[u][v]=mx[v][u]=1;
    }
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]=min(mx[i][j],mx[i][k]+mx[k][j]);
    
    set<tuple<int,LL,int>> Q;
    FORR(u,es) {
//      cout << u << ":";
      FORR(v,ts) if(mx[u][v]<=T) { /*cout<<v<<",";*/ X[u]|=(1LL<<v); }
//      cout << endl;
      Q.emplace(__builtin_popcountll(X[u]),X[u],u);
    }
    
    LL viz=0;
    while(SZ(Q)) {
      auto it=Q.begin();
      int cnt,u; LL mask;
      tie(cnt,mask,u)=*it;
//      dump2(cnt,mask);
      Q.erase(it);
      if(cnt==0) continue;
      REP(i,V) if((viz&(1LL<<i))==0 && (mask&(1LL<<i))) {
//        dump(i);
        viz|=(1LL<<i);
        break;
      }
    }
    
    return __builtin_popcountll(viz);
  }
};

// CUT begin
ifstream data("ApocalypseEasy.sample");

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

bool do_test(vector<int> p, vector<int> position, int t, int __expected) {
    time_t startClock = clock();
    ApocalypseEasy *instance = new ApocalypseEasy();
    int __result = instance->maximalSurvival(p, position, t);
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
        vector<int> position;
        from_stream(position);
        int t;
        from_stream(t);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(p, position, t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506934285;
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
        cout << "ApocalypseEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
