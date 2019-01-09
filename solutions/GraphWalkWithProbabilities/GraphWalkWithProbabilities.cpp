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
 
 10/29/2017
 
 14:56-16:11 passed samples though 1WA (346.77 pt)
 16:30-16:52 time up
 
 16:53-18:00, 22:00-23:10 read editorial and add solution:
  - https://apps.topcoder.com/wiki/display/tc/SRM+603#GraphWalkWithProbabilities
   - https://apps.topcoder.com/forums/?module=Thread&threadID=808190&start=0
  - http://kmjp.hatenablog.jp/entry/2014/01/08/0900
  - http://emkcsharp.hatenablog.com/entry/SRM603/GraphWalkWithProbabilities

 The point was "Plays the game optimally".
 If we simply try to figure out optimal solution, we need to know probability to win at vertices which we've yet to visit.
 So state dependency is cyclic. In order to resolve it, we need to compute probability when we did sifnificantly many moves.
 
 There are two ways to compute it:
  1. Compute convergent probability by math first
   - http://emkcsharp.hatenablog.com/entry/SRM603/GraphWalkWithProbabilities
   - https://community.topcoder.com/stat?c=problem_solution&rm=320096&rd=15836&pm=12908&cr=23290909
  2. Compute optimal choice by DP until diff of probability is supposed to go under EPS (official editorial)
   - https://apps.topcoder.com/forums/?module=Thread&threadID=808190&start=0

 1. Compute convergent probability by math
 
  Firstly at each vertices compute convergent probability which determines optimal probability
   ∑ { w_p*(1-w_p-l_p)^i : i->∞ } = w_p/(w_p+l_p) because ∑ { a*r^i : i->∞ } = a/(1-r)
 
  Compute maximal probability choosing best choice by convergent value.
  When going through an edge, original probability is reduced by multiplying probability. So optimality in shortest path problem is satisfied. We can use Floyd-warshall, Dijkstra's algorithm or Bellman-ford.
 
 2. Compute optimal choice by DP
 
  State transition seems to be cyclic due to cycle in graph.
  However probability decreases monotonically as moves are repeated.
  So we can repeat moves significantly many moves until reduced probability is under EPS 1e-9.

  This gives us recurrence relation of DP.
  Suppose we compute P[i,k] = winning probability at vertex `i` in at most `k` step.
  Then..
  P[i,k] = max { W[j]+(1-W[j]-L[j])*P[j,k-1] : G[i][j] = '1' }
  P[_,0] = 0.0
 
  res = P[S,10000]
 
 Key:
  - Kind of typical problem to compute until value converges.
  - "Play optimally" means better probability afer significantly many number of moves
    - Without this idea, we cannot resolve state cycle
  - Due to the optimality, we cannot reduce problem to system of linear equations like SRM 614 TorusSailingEasy
  - Two solutions
   - Compute optimal choice by DP until diff of probability is supposed to go under EPS
   - Firstly compute convergent probability which determines optimal probability and compute maximal probability choosing best optimal probability by solving shortest path problem

 Summary:
  - By simulating samples, I thought "play optimally" means taking better probability in convergence of inifinite moves. It was correct. 👍
  - I did simple DFS without understanding the problem deeply. My code didn't pass graph with loop. 👎
  - I needed to compute convergent probability first and solve max value from each to start position.
  - Official editorial is showing solution by repeating moves until dif goes under EPS. I had the idea though, I couldn't reduce it to design.
  - Make cyclic graph DAG by introducing steps is typical pattern. It's worth to remember.
 
 Submit solutions:
  - solution by approach 1
   - https://community.topcoder.com/stat?c=problem_solution&rm=320096&rd=15836&pm=12908&cr=23290909
     - solving shoftest path by Bellman-ford
   - https://community.topcoder.com/stat?c=problem_solution&rm=320068&rd=15836&pm=12908&cr=23290922
   - https://community.topcoder.com/stat?c=problem_solution&rm=320095&rd=15836&pm=12908&cr=23127079
  - solution by approach 2
   - https://community.topcoder.com/stat?c=problem_solution&rm=320069&rd=15836&pm=12908&cr=23290923
 
 */

double memo[50][10001];
class GraphWalkWithProbabilities {
public:
  int V;
  vector<string> G;
  vector<double> W;
  vector<double> L;
  double f(int u, int k) {
    if(k==0) return 0;
    if(k==1) return W[u];
    if(memo[u][k]>=0) return memo[u][k];
    
    double res=0;
    REP(v,V) if(G[u][v]=='1') res=max(res,W[v]+(1.0-W[v]-L[v])*f(v,k-1));
    return memo[u][k]=res;
  }
  
  double findprob(vector<string> G, vector<int> WW, vector<int> LL, int S) {
    this->G=G;
    this->V=SZ(G);
    this->W=vector<double>(V);
    this->L=vector<double>(V);
    REP(i,V) W[i]=WW[i]*0.01,L[i]=LL[i]*0.01;
    
    MINUS(memo);
    return f(S,10000);
  }
};

double P[51][10001];
class GraphWalkWithProbabilities_iterativeDP {
public:
  double findprob(vector<string> G, vector<int> WW, vector<int> LL, int S) {
    int V=SZ(G);
    vector<double> W(V);
    vector<double> L(V);
    REP(i,V) W[i]=WW[i]*0.01,L[i]=LL[i]*0.01;
    
    ZERO(P);
    FOR(k,1,10001) REP(i,V) REP(j,V) if(G[i][j]=='1') {
      P[i][k]=max(P[i][k], W[j]+(1.0-W[j]-L[j])*P[j][k-1]);
    }
    
    return P[S][10000];
  }
};

// Solution by convergent probability
class GraphWalkWithProbabilities_convergence {
public:
  double P[51];
  double findprob(vector<string> G, vector<int> WW, vector<int> LL, int S) {
    int V=SZ(G);
    vector<double> W(V);
    vector<double> L(V);
    REP(i,V) W[i]=WW[i]*0.01,L[i]=LL[i]*0.01;
    ZERO(P);
    
    REP(i,V) P[i]=W[i]/(W[i]+L[i]);
    // bellman-ford
    REP(_,V)REP(i,V)REP(j,V) if(G[i][j]=='1') {
      P[i]=max(P[i], W[i]+(1.0-W[i]-L[i])*P[j]);
    }
    
    double res=0;
    // we can select first move for free from S
    REP(i,V) if(G[S][i]=='1') res=max(res,P[i]);
    return res;
  }
};

class GraphWalkWithProbabilities_wrong {
  public:
  const double EPS=1e-9;
  int V;
  vector<string> G;
  vector<double> W;
  vector<double> L;
  vector<double> P;
  double f(int u, double p) {
    double contP=1.0-W[u]-L[u];
    P[u]=p*W[u]/(1.0-contP);
//    dump2(u,P[u]);
    int next=-1;
    double maxp=P[u];
    REP(v,V) if(v!=u&&G[u][v]=='1') {
      double pp=P[v]>=0?P[v]:f(v,p*contP);
      if(maxp<pp) next=v,maxp=pp;
    }
    if(next==-1) return P[u];
    else return p*W[u]+maxp;
  }
  double findprob(vector<string> G, vector<int> winprob, vector<int> looseprob, int s) {
    this->G=G;
    this->V=SZ(G);
    REP(i,V) W.push_back(winprob[i]/100.0),L.push_back(looseprob[i]/100.0);
    this->P=vector<double>(V,-0.1);
    
    double contP=1.0-W[s]-L[s];
    if(contP<EPS) return W[s];

    P[s]=W[s]/(1.0-contP);
//    dump2(s,P[s]);
    int next=-1; double maxp=P[s];
    REP(v,V) if(v!=s&&G[s][v]=='1') {
      double pp=f(v,1.0);
      if(maxp<pp) next=v,maxp=pp;
    }
    return next==-1?P[s]:maxp;
  }
};

// CUT begin
ifstream data("GraphWalkWithProbabilities.sample");

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

bool do_test(vector<string> graph, vector<int> winprob, vector<int> looseprob, int Start, double __expected) {
    time_t startClock = clock();
    GraphWalkWithProbabilities *instance = new GraphWalkWithProbabilities();
    double __result = instance->findprob(graph, winprob, looseprob, Start);
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
        vector<string> graph;
        from_stream(graph);
        vector<int> winprob;
        from_stream(winprob);
        vector<int> looseprob;
        from_stream(looseprob);
        int Start;
        from_stream(Start);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(graph, winprob, looseprob, Start, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509314204;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "GraphWalkWithProbabilities (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
