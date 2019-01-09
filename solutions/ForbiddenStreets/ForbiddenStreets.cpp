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
 
 8/4/2017
 
 18:23-18:41 design by 2*10^9 solution done
 18:41-18:53 implementation
 18:53-18:59 bugfix (missing initialization) and submit (511.83 pt)
 
 24:25-24:50, 8/5/2017 22:20-22:40 read editorials:
  - floyd-warshall solution and faster critical detection
    - https://apps.topcoder.com/wiki/display/tc/SRM+679
    - If W(i,k)+W(k,j) <  W(i,j), Critical path P(i,j) = P(i,k) ∪ P(k,j)
    - If W(i,k)+W(k,j) == W(i,j), P(i,j) = P(i,j) ∩ (P(i,k) ∪ P(k,j))
  - count paths to detect cirtical path with Dijkstra's algorithm or dfs
    - Dijkstra's algorithm
      - http://kmjp.hatenablog.jp/entry/2016/01/21/0930
      - http://shifth.hatenablog.com/entry/2016/01/24/164939
    - dfs
      - https://community.topcoder.com/stat?c=problem_solution&rm=327888&rd=16649&pm=14121&cr=40156237
    - p->q is critical path in path x->y
      => i) p->q is in one of the shortest paths => dist(x->p) + dist(p->q) + dist(q->y) = dist(x->y)
    And ii) p->q is critical => cnt(x->y) = cnt(x->p) * cnt(q->y)
 
 8/5/2017 22:40-23:25 add floyd-warshall critical path detection
  - spent time to find right parameter of set_union() and set_intersection()
 
 */

const int Inf=1e9;
int E[100][100];
int W[100][100];
int WW[100][100];
//set<int> P[100][100];

// O(V^3) time ≈10^6
class ForbiddenStreets {
public:

  vector<int> find(int V, vector<int> A, vector<int> B, vector<int> T) {
    int M=SZ(A);
    vector<vector<set<int>>> P(V, vector<set<int>>(V));
    REP(i,V) REP(j,V) W[i][j]=Inf;
    REP(i,M) {
      int u=A[i],v=B[i];
      W[u][v]=W[v][u]=T[i];
      P[u][v].emplace(i), P[v][u].emplace(i);
    }
    
    REP(k,V)REP(i,V)REP(j,V) if(W[i][k]<Inf&&W[k][j]<Inf) {
      if (W[i][k]+W[k][j] <= W[i][j]) {
        set<int> x;
        set_union(P[i][k].begin(),P[i][k].end(),P[k][j].begin(),P[k][j].end(),inserter(x, x.begin()));
        if (W[i][k]+W[k][j] < W[i][j]) P[i][j]=x;
        else if(W[i][k]+W[k][j] == W[i][j]) {
          set<int> y;
          set_intersection(P[i][j].begin(),P[i][j].end(),x.begin(),x.end(),inserter(y, y.begin()));
          P[i][j] = y;
        }
      }
      W[i][j]=min(W[i][j],W[i][k]+W[k][j]);
    }
    
    VI res(M,0);
    REP(j,V) REP(i,j) FORR(e,P[i][j]) ++res[e];

    return res;
  }
};

// O(E*V^3) time ≈2*10^9
class ForbiddenStreets_org {
  public:
  
  vector<int> find(int V, vector<int> A, vector<int> B, vector<int> T) {
    int M=SZ(A);
    REP(i,V) REP(j,V) W[i][j]=Inf,E[i][j]=Inf;
    REP(i,M) W[A[i]][B[i]]=W[B[i]][A[i]]=T[i],E[A[i]][B[i]]=E[B[i]][A[i]]=T[i];
    
    REP(k,V)REP(i,V)REP(j,V) if(W[i][k]<Inf&&W[k][j]<Inf) W[i][j]=min(W[i][j],W[i][k]+W[k][j]);
    
    VI res(M,0);
    REP(m,M) {
//      dump(m);
      REP(i,V)REP(j,V) WW[i][j]=E[i][j];
      int v1=A[m],v2=B[m];
      WW[v1][v2]=WW[v2][v1]=Inf;
      REP(k,V)REP(i,V)REP(j,V) if(WW[i][k]<Inf&&WW[k][j]<Inf) WW[i][j]=min(WW[i][j],WW[i][k]+WW[k][j]);
      
      REP(j,V)REP(i,j) if(WW[i][j]>W[i][j]) {
//        dump4(i,j,WW[i][j],W[i][j]);
        ++res[m];
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ForbiddenStreets.sample");

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

bool do_test(int N, vector<int> A, vector<int> B, vector<int> time, vector<int> __expected) {
    time_t startClock = clock();
    ForbiddenStreets *instance = new ForbiddenStreets();
    vector<int> __result = instance->find(N, A, B, time);
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
        int N;
        from_stream(N);
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        vector<int> time;
        from_stream(time);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, A, B, time, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501896199;
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
        cout << "ForbiddenStreets (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
