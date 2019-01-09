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
 
 8/15/2018 SRM 736
 
 8:00-8:31 AC (140.56 pt)
 
 Editorials:
  - http://kmjp.hatenablog.jp/entry/2018/08/16/0900
  - https://www.hamayanhamayan.com/entry/2018/08/16/103133
  - http://hamko.hatenadiary.jp/entry/2018/08/17/002600
 
 Tweets:
  - https://togetter.com/li/1257026
  - https://twitter.com/beet_aizu/status/1029768470102126592
  - https://twitter.com/torus711/status/1029769020466028545
  - https://twitter.com/natsugir/status/1029769715839684608
 
 Summary:
  - I haven't imagined that brute-force does not TLE. I should have been able to submit earlier..
 
 */

// 8:31
const LL MOD=998244353;
LL P10[510];
class DigitRotation {
  public:
  int sumRotations(string X) {
    
    int N=SZ(X);
    vector<LL> Y(N); REP(i,N)Y[i]=X[i]-'0';
    reverse(Y.begin(),Y.end());
    P10[0]=1;
    REP(i,500)P10[i+1]=P10[i]*10LL%MOD;
    LL tot=0;
    REP(i,N)tot+=P10[i]*Y[i]%MOD,tot%=MOD;
    
    LL res=0;
    REP(i,N)REP(j,i)REP(k,j) {
      if(i==N-1&&Y[k]==0)continue;
      LL x=tot;
      
      x=x+MOD-Y[i]*P10[i]%MOD,x%=MOD;
      x=x+MOD-Y[j]*P10[j]%MOD,x%=MOD;
      x=x+MOD-Y[k]*P10[k]%MOD,x%=MOD;
      
      x=x+P10[k]*Y[j]%MOD,x%=MOD;
      x=x+P10[j]*Y[i]%MOD,x%=MOD;
      x=x+P10[i]*Y[k]%MOD,x%=MOD;

//      dump4(i,j,k,x);
      
      res+=x,res%=MOD;
    }
    return res;
  }
};

// CUT begin
ifstream data("DigitRotation.sample");

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

bool do_test(string X, int __expected) {
    time_t startClock = clock();
    DigitRotation *instance = new DigitRotation();
    int __result = instance->sumRotations(X);
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
        string X;
        from_stream(X);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1534345273;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DigitRotation (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
