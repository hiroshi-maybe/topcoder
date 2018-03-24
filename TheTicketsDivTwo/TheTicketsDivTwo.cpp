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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/23/2018
 
 9:15-9:25 analysis
 9:48 Sample 3 doesn't pass with small difference. EPS error...?
 9:49-9:57 Solve by dp. sample #3 still doesn't pass...
 10:04 I was missing one condition in the problem 😞. If only one friend, pick him/her up... (433.42 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+504.5
  - http://area.hateblo.jp/entry/2013/08/16/010751
  - http://kmjp.hatenablog.jp/entry/2014/02/17/1000
  - http://d.hatena.ne.jp/kusano_prog/20110519/1305837898
 
 Key:
  - Either dp or brute-force works
 
 Summary:
  - If I understood the problem correctly, I should have solved only in 30 mins 😞
 
 */
double memo[11][11][11];
class TheTicketsDivTwo_dp {
public:
  int K,M;
  double f(int i, int n, int pos) {
    double &res=memo[i][n][pos];
    if(res>-1) return res;
    if(n==1) return pos==1;
    if(i==K) return pos==1?1.0:0.0;
    double p=1.0/6.0;
    res=p*(pos==1);
    // 1,3,5 push back
    res+=3.0*p*f(i+1,n,pos==1?n:pos-1);
    // 2,6 rem first
    if(pos!=1) res+=2.0*p*f(i+1,n-1,pos-1);
    return res;
  }
  double find(int n, int m, int k) {
    this->K=k,this->M=m;
    MINUS(memo);
    return f(0,n,m);
  }
};

double P[11];
class TheTicketsDivTwo {
  public:
  int K,M;
  double res=0.0;
  void dfs(int i, deque<int> &cur) {
    if(i==K) {
//      dump(SZ(cur)&&cur.front()==M);
      if(SZ(cur)&&cur.front()==M) res+=P[i];
      return;
    }
    if(SZ(cur)==1) {
      if (cur.front()==M) res+=P[i];
      return;
    }
    FORE(d,1,6) {
      if(d==4) res+=cur.front()==M?P[i+1]:0;
      else if(d==2||d==6) {
        int x=cur.front();
        cur.pop_front();
        dfs(i+1,cur);
        cur.push_front(x);
      } else {
        int x=cur.front();
        cur.pop_front();
        cur.push_back(x);
//        if(i==0) dumpAR(cur);
        dfs(i+1,cur);
        cur.pop_back();
        cur.push_front(x);
      }
    }
  }
  double find(int n, int m, int k) {
    this->K=k,this->M=m;
    ZERO(P);
    P[0]=1.0;
    REP(i,10) P[i+1]=P[i]/6.0;
    deque<int> cur;
    REP(i,n) cur.push_back(i+1);
    dfs(0,cur);
    return res;
  }
};

// CUT begin
ifstream data("TheTicketsDivTwo.sample");

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

bool do_test(int n, int m, int k, double __expected) {
    time_t startClock = clock();
    TheTicketsDivTwo *instance = new TheTicketsDivTwo();
    double __result = instance->find(n, m, k);
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
        int n;
        from_stream(n);
        int m;
        from_stream(m);
        int k;
        from_stream(k);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521821719;
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
        cout << "TheTicketsDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
