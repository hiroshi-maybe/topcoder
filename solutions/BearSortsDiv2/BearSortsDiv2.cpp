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

typedef long double LB;

/*
 
 8/21/2017
 
 9:25-9:45, 18:15-18:54 analysis and design
 18:55-19:10 implemented and passed system test
 
 f(S,l,r) = 0.5^p * f(S_l,l,mid) * f(S_r,mid,r)
  p=number of comparison of S_l and S_r, mid=(l+r)/2
 f(_,x,x) = 1.0
 
 21:10-22:04 read editorial:
  - simulating including merging
    - https://apps.topcoder.com/wiki/display/tc/SRM+664
  - make value -> index table, sort manually and count number of comparison
    - http://kmjp.hatenablog.jp/entry/2015/08/05/1000
    - http://mayokoex.hatenablog.com/entry/2015/09/10/205605
 
 Actually...
 
 f(S,l,r)
  = 0.5^p * f(S_l,l,mid) * f(S_r,mid,r)
  = 0.5^p * 0.5^p'*f(S_ll,l,mid')*f(S_lr,mid',mid) * 0.5^p''*f(S_rl,mid,mid'')*f(S_rr,mid'',r)
  = 0.5^(p+p'+p'') * ...
  ....
  = 0.5^m where m = ∑ { p : number of comparison }
 
 ln f(S,1,N) = ln (1/2)^m = m * ln(1/2)
 
 Editorial solutions are simulating merge sort following special order in given sequence.
 
 22:04-22:26 add editorial solution
 
 Key:
  - divided array is deterministic
  - simulate merge sort by index order
 
 Summary:
  - it was straightforward after noticing that divided array is deterministic. no search is needed 👍
  - it took a while to notice it. should have played around samples more 👎
 
 */

int idx[41]; // value -> index mapping
class BearSortsDiv2 {
public:
  int merge(int l, int r) {
    if(l>=r-1) return 0;
    int mid=(l+r)/2;
    int res=merge(l,mid)+merge(mid,r);
    VI is[2];
    // [l, r) is range of values. Make value -> index mapping to do merge sort by index
    FOR(n,l,r) is[n<mid].push_back(idx[n]);
    
    sort(is[0].begin(),is[0].end());
    sort(is[1].begin(),is[1].end());
    int p=0, q=0;
    while(p<SZ(is[0])&&q<SZ(is[1])) {
      if(is[0][p]<is[1][q]) ++p;
      else ++q;
      ++res;
    }
    
    return res;
  }
  
  double getProbability(vector<int> S) {
    REP(i,SZ(S)) idx[S[i]-1]=i;
    int m = merge(0,SZ(S));
    return (double)m*log(0.5);
  }
};

class BearSortsDiv2_org {
  public:
  double getProbability(vector<int> S) {
    LB p = f(S,1,SZ(S)+1);
    return log(p);
  }
  
  LB f(VI S, int l, int r) {
    if(l>=r-1) return 1.0;
    VI S1, S2;
    int N=SZ(S);
    int N1=N/2, N2=N-N1;
    int mid=(l+r)/2;
    LB p0=1.0;
    FORR(n,S) {
      if(SZ(S1)!=N1&&SZ(S2)!=N2) p0*=0.5;
      if(n<mid) S1.push_back(n);
      else S2.push_back(n);
    }
    
    LB p1=f(S1,l,mid);
    LB p2=f(S2,mid,r);
    
//    dump3(p0,p1,p2);
//    dumpAR(S1);
//    dumpAR(S2);
    
    return p0 * p1 * p2;
  }
};

// CUT begin
ifstream data("BearSortsDiv2.sample");

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

bool do_test(vector<int> seq, double __expected) {
    time_t startClock = clock();
    BearSortsDiv2 *instance = new BearSortsDiv2();
    double __result = instance->getProbability(seq);
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
        vector<int> seq;
        from_stream(seq);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(seq, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503332697;
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
        cout << "BearSortsDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
