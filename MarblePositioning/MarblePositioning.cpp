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
 
 12/2/2017
 
 16:59-17:31 analysis
 17:32-17:49 implement and submit (429.36 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+579#MarblePositioning
  - http://kmjp.hatenablog.jp/entry/2013/05/19/1000
  - http://emkcsharp.hatenablog.com/entry/SRM579/MarblePositioning
 
 f(l,r) = max { f(c[l],c[x])+f(c[x],c[r]) : x=l+1..r-1 }
 f(l,l+1) = √r[l]*r[l+1]
 
 Key:
  - N is small. It's possible to brute-force all the orders in N!
  - distance between adjacent circles is `2√r1*r2`
  - distance between circle[i] and circle[j] is sum of max distance with intermidiate circles.
 
 Summary;
  - Brute-forcing permutation was trivial
  - It took more time to compute distance when order is fixed
 
 */
double memo[8][8];
class MarblePositioning {
  public:
  int N;
  vector<double> X;
  double dist(int l, int r) {
    return 2.0*sqrt(X[l]*X[r]);
  }
  
  // O(N!*N^3) time
  double f_org(int l, int r) {
    double &res=memo[l][r];
    if(res>=0) return res;
    res=dist(l,r);
    if(r==l+1) return res;
    FOR(x,l+1,r) {
      res=max(res,f_org(l,x)+f_org(x,r));
    }
    return res;
  }
  
  // O(N!*N^2) time
  double f() {
    double dp[8];
    ZERO(dp);
    
    for(int j=1; j<N; ++j) {
      for(int i=0; i<j; ++i) {
        dp[j]=max(dp[j],dp[i]+dist(i,j));
      }
    }
    return dp[N-1];
  }
  
  const double Inf=1e9*55;
  double totalWidth(vector<int> XX) {
    this->N=SZ(XX);
    this->X=vector<double>(N,0.0);
    double res=Inf;
    VI ord(N);
    REP(i,N) ord[i]=i;
    do {
      MINUS(memo);
      REP(i,N) X[i]=XX[ord[i]];
      //res=min(res,f(0,N-1));
      res=min(res,f());
    } while(next_permutation(ord.begin(),ord.end()));

    return res;
  }
};

// CUT begin
ifstream data("MarblePositioning.sample");

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

bool do_test(vector<int> radius, double __expected) {
    time_t startClock = clock();
    MarblePositioning *instance = new MarblePositioning();
    double __result = instance->totalWidth(radius);
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
        vector<int> radius;
        from_stream(radius);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(radius, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512262762;
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
        cout << "MarblePositioning (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
