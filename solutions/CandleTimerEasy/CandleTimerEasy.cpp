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
 
 9/17/2017
 
 12:07-13:51 system test passed
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+638
  - http://kmjp.hatenablog.jp/entry/2014/11/03/1000
   - div1 hard V<=200
 
 brute-force combinations of fired leaves.
 duration time is furthest point from fired end points (leaves)
 
 In my solution, computed each potential inner point.
 In editorial's solution, tracking parent node which visited before current vertex.
 
 key:
  - *2 to avoid .5 distance
  - Dijkstra's algorithm to find shortest paths to each vertex
  - compute inner point from pair of shortest distances of vertices
 
 summary:
  - figured out bitmask from small size of |V|
  - figured out BFS like approach and selected Dijkstra's algorithm
  - it took a lot of time to analyze how to resolve bi-directional trace of an edge
 
 submit solution:
  - only two solutions passed in the contest
  - https://community.topcoder.com/stat?c=problem_solution&rm=324214&rd=16081&pm=13519&cr=23327007
    - this solution is taking diameter*2 to avoid complex computation of inner point. very smart.
  - https://community.topcoder.com/stat?c=problem_solution&rm=324207&rd=16081&pm=13519&cr=23127234
    - using double instead len[i]*2
 
 */
vector<II> E[21];
int dist[21];
// O(2^V*V*lg V) time
class CandleTimerEasy {
  public:
  const int Inf=1e6;
  int differentTime(vector<int> A, vector<int> B, vector<int> len) {
    int V=SZ(A)+1;
    REP(i,V) E[i].clear();
    VI ls;
    REP(i,SZ(A)) {
      int u=A[i],v=B[i],l=len[i]*2;
      E[u].emplace_back(v,l),E[v].emplace_back(u,l);
    }
    REP(u,V) if(SZ(E[u])==1) ls.push_back(u);
    
    SETI ts;
    REP(mask,1<<SZ(ls)) if(__builtin_popcount(mask)>0) {
      REP(i,V) dist[i]=Inf;
      int dd=0;
      
      set<II> Q;
      REP(i,SZ(ls)) if(mask&(1<<i)) {
        dist[ls[i]]=0;
        Q.emplace(0,ls[i]);
      }
      
      while(SZ(Q)) {
        int d,u;
        auto it=Q.begin();
        tie(d,u)=*it; Q.erase(it);
        dd=max(dd,d);
        FORR(p,E[u]) {
          auto v=p.first,w=p.second;
          if(dist[v]>d+w) {
            // unidirectional
            auto it2=Q.find(make_pair(dist[v],v));
            if(it2!=Q.end()) Q.erase(it2);
            dist[v]=d+w;
            Q.emplace(dist[v],v);
          } else {
            // bidirectional
            int remd=w-abs(d-dist[v]);
            assert(remd%2==0);
            dd=max(dd,max(d,dist[v])+remd/2);
          }
        }
      }
      ts.emplace(dd);
    }
    
    return SZ(ts);
  }
};

// CUT begin
ifstream data("CandleTimerEasy.sample");

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

bool do_test(vector<int> A, vector<int> B, vector<int> len, int __expected) {
    time_t startClock = clock();
    CandleTimerEasy *instance = new CandleTimerEasy();
    int __result = instance->differentTime(A, B, len);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        vector<int> len;
        from_stream(len);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, len, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505675220;
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
        cout << "CandleTimerEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
