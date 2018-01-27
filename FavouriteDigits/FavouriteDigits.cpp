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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/27/2018
 
 9:50-10:06 analysis
 10:38 438.27 pt (1WA)
 10:46 fixed a bug and system test passed.
 
 Editorials:
  - greedy and DP
   - https://apps.topcoder.com/wiki/display/tc/SRM+546
  - search and greedy
   - http://kmjp.hatenablog.jp/entry/2013/12/29/1130
   - http://kenkoooo.hatenablog.com/entry/2015/10/18/040821
   - http://hamko.hatenadiary.jp/entry/2017/02/13/131128
   - http://d.hatena.ne.jp/kusano_prog/20120616/1339875326
 
 Summary:
  - Analysis was straightforward
  - Pain of implementation to handle C1+C2>{Scale of N} and leading zeros
 
 */
LL memo[16][16][16][2][2];
LL pw10[16];
class FavouriteDigits {
  public:
  string S;
  int D1,D2;
  const LL Inf=1e17;
  LL f(int i, int c1, int c2, int any, int lz) {
    if(i<0) return c1==0&&c2==0?0:Inf;
    LL &res=memo[i][c1][c2][any][lz];
    if(res>=0) return res;
    
    res=Inf;
    REPE(d,9) {
      int x1=d==D1&&(!lz||D1!=0)?c1-1:c1; x1=max(x1,0);
      int x2=d==D2?c2-1:c2; x2=max(x2,0);
      int lz2=lz?d==0:lz;
      if(!any) {
        int dd=S[15-i]-'0';
        if(dd>d) continue;
        MINS(res,pw10[i]*d+f(i-1,x1,x2,dd<d,lz2));
      } else {
        MINS(res,pw10[i]*d+f(i-1,x1,x2,any,lz2));
      }
    }
    return res;
  }
  
  long long findNext(long long N, int D1, int C1, int D2, int C2) {
    if(D1>D2) swap(D1,D2),swap(C1,C2);
    this->D1=D1,this->D2=D2;
    MINUS(memo);
    
    pw10[0]=1LL;
    FOR(i,1,16) pw10[i]=pw10[i-1]*10LL;
    REP(i,16) S.push_back('0'+(N%10L)),N/=10L;
    reverse(S.begin(),S.end());
    
    return f(15,C1,C2,0,1);
  }
};

// CUT begin
ifstream data("FavouriteDigits.sample");

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

bool do_test(long long N, int digit1, int count1, int digit2, int count2, long long __expected) {
    time_t startClock = clock();
    FavouriteDigits *instance = new FavouriteDigits();
    long long __result = instance->findNext(N, digit1, count1, digit2, count2);
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
        long long N;
        from_stream(N);
        int digit1;
        from_stream(digit1);
        int count1;
        from_stream(count1);
        int digit2;
        from_stream(digit2);
        int count2;
        from_stream(count2);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, digit1, count1, digit2, count2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517075435;
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
        cout << "FavouriteDigits (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
