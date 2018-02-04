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
 
 2/4/2018
 
 17:18-17:49 It took 31 mins to understand problem correctly (NOT x<=maxR but x<maxR)
 17:50 submit and ACC (135.14 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+540
  - http://d.hatena.ne.jp/kusano_prog/20120411/1334157309
    - O(1) solution
  - http://lepton.hatenablog.jp/?page=1334230879
  - http://kg86.hatenablog.com/entry/20130627/1372343721
  - http://rkx1209.hatenablog.com/entry/2012/11/01/205619
 
 O(1) solution is cool.
 If we represent upper bound conditions by R2,G2,B2 and lower bound conditions R1,G1,B1,
 
   expected condition
 = (R2&G2&B2)&(R1|G1|B1)
 = (R2&G2&B2)&!(!R1&!G1&!B1)
 
 res = (R max range)*(G max range)*(B max range) - (R min range)*(G min range)*(B min range)
 
 Summary:
  - Do not use name "max**" for exclusive range 👎
 
 */

class RandomColoringDiv2 {
public:
  int getCount(int maxR, int maxG, int maxB, int startR, int startG, int startB, int d1, int d2) {
    int S[3]={startR,startG,startB};
    int U[3]={maxR-1,maxG-1,maxB-1};
    
    int a=1;
    REP(i,3) a*=min(S[i]+d2,U[i])-max(S[i]-d2,0)+1;
    int b=1;
    REP(i,3) b*=max(min(S[i]+d1-1,U[i])-max(S[i]-d1+1,0)+1,0);
    return a-b;
  }
};

class RandomColoringDiv2_org {
  public:
  int getCount(int maxR, int maxG, int maxB, int startR, int startG, int startB, int d1, int d2) {
    int res=0;
    REPE(a,200) REPE(b,200) REPE(c,200) {
      if(a>=maxR||b>=maxG||c>=maxB) continue;
      int aa=abs(a-startR),bb=abs(b-startG),cc=abs(c-startB);
      bool ok=true;
      ok&=((aa<=d2)&&(bb<=d2)&&(cc<=d2));
      ok&=((d1<=aa)||(d1<=bb)||(d1<=cc));
//      if(ok) dump3(a,b,c);
      res+=ok;
    }
    return res;
  }
};

// CUT begin
ifstream data("RandomColoringDiv2.sample");

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

bool do_test(int maxR, int maxG, int maxB, int startR, int startG, int startB, int d1, int d2, int __expected) {
    time_t startClock = clock();
    RandomColoringDiv2 *instance = new RandomColoringDiv2();
    int __result = instance->getCount(maxR, maxG, maxB, startR, startG, startB, d1, d2);
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
        int maxR;
        from_stream(maxR);
        int maxG;
        from_stream(maxG);
        int maxB;
        from_stream(maxB);
        int startR;
        from_stream(startR);
        int startG;
        from_stream(startG);
        int startB;
        from_stream(startB);
        int d1;
        from_stream(d1);
        int d2;
        from_stream(d2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(maxR, maxG, maxB, startR, startG, startB, d1, d2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517707061;
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
        cout << "RandomColoringDiv2 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
