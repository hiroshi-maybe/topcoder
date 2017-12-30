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
 
 12/29/2017
 
 14:02-14:52 time up

 I tried to enumerate edges. However, I couldn't resolve following problems:
  - Count without duplication
  - How to differentiate cases when L>1? Seems to be edgea need to be consecutive.
  - How to differentiate cases below cases
   - Families are all one side
   - Families are in both sides
 
 17:40-18:25 read editorials
 18:26-18:40 add solution
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+561
  - http://kmjp.hatenablog.jp/entry/2012/12/23/0930
   - floyd-warshall instead of dfs
 
 21:30-23:00 look back linearity of expectation and add analysis:
 
 We can define random variable X = ∑ { I{e[i]} : i=0..N-1 }
 I{e[i]} is an indicator random variable as defined below:
 
 I{e[i]} = 1 if edge[i] is full road
         = 0 otherwise
 
 We find that X shows random variable which maps sample spaces (city selection of families) to total number of full roads.
 
   E[X]
 = E[∑{ I{e[i]} }]   // definition
 = ∑{ E[I{e[i]}] }   // linearity of expectation
 = ∑{ 1*Pr{e[i]} }   // definition
 = ∑{ Pr{e[i]} }
 
 Pr(e[i]) = (a2/(V-1))^b1 * (a1/(V-1))^b2
  a1: number of nodes in one side from edge[i]
  b1: number of families in one side from edge[i]
  a2: number of nodes in the other side
  b2: number of families in the other side
 
 (a1,b1) and (a2,b2) can be computed by DFS
 
 Total runtime is O(V^2) time
 
 Linearity of expected value:
  - CLRS 5.2 Indicator Random Variables Lemma 5.1
  - CLRS C.3 Discrete random variables
  - https://en.wikipedia.org/wiki/Expected_value#Linearity
  - http://garnacha.techblog.jp/archives/38524130.html
 
 Key:
  - Iterate edges instead of vertices to satisfy full path condition
    - To achieve full path, all the families need to go through an edge
    - Enumerate all the edges and compute probability that all the families visisit opposite side of cities
  - Linearity of expected value
 
 Summary:
  - Poor understanding of expected value 👎
  - Linearity of expected value is very typical trick 👎
 
 */
class FoxAndTouristFamilies {
  public:
  int V;
  VI es[51];
  int fs[51]; // v -> number of families
  II dfs(int u, int pre) {
    int a=1,b=fs[u];
    FORR(v,es[u]) if(v!=pre) {
      auto p=dfs(v,u);
      a+=p.first,b+=p.second;
    }
    return {a,b};
  }
  double expectedLength(vector<int> A, vector<int> B, vector<int> F) {
    this->V=SZ(A)+1;
    REP(i,SZ(A)) {
      int u=A[i],v=B[i];
      es[u].push_back(v);
      es[v].push_back(u);
    }
    REP(i,SZ(F)) fs[F[i]]++;
    
    double res=0;
    REP(i,SZ(A)) {
      int u=A[i],v=B[i];
      auto p1=dfs(u,v),p2=dfs(v,u);
      
//      dump2(u,v);
//      dump4(p1.first,p2.first,p1.second,p2.second);
      
      double P1=pow(1.0*p1.first/(V-1), p2.second);
      double P2=pow(1.0*p2.first/(V-1), p1.second);
      
//      dump2(P1,P2);
      
      res += P1*P2;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("FoxAndTouristFamilies.sample");

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

bool do_test(vector<int> A, vector<int> B, vector<int> f, double __expected) {
    time_t startClock = clock();
    FoxAndTouristFamilies *instance = new FoxAndTouristFamilies();
    double __result = instance->expectedLength(A, B, f);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        vector<int> f;
        from_stream(f);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, f, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514584940;
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
        cout << "FoxAndTouristFamilies (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
