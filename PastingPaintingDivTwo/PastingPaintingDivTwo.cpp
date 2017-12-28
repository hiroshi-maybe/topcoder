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
 
 12/26/2017
 
 19:57-20:34 system test passed (249.23 pt)

 I was confused if contribution of the last min(R,C) sequence may be special.
 It took much time to ensure that this is not true.

 Suppose K=min(R,C) and look at delta in i-th picture (0-base index).
 
 1) i<K
 Overlap by 0..i-1 pictures are not filling RxC board.
 So delta(i) may differ in each moment.
 
 2) i>=K
 Built picture is made from recent K pictures.
 That means delta(i) is always same.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+562
  - http://kg86.hatenablog.com/entry/2014/10/07/075951
  - http://d.hatena.ne.jp/ty70/20121202/1354415334
  - http://expnotes9.blog.fc2.com/blog-entry-30.html
 
 Summary:
  - Quickly figured out that simple simulation of first 50 sequence is feasible
  - It took a lot of time to be confident that the last T-K sequence has the same deltas
 
 */
class PastingPaintingDivTwo {
  public:
  long long countColors(vector<string> B, int T) {
    int R=SZ(B),C=SZ(B[0]);
    vector<string> B2(101*R,string(101*C,'.'));
    int n=min(R,C);
    
    VI X(n+1,0);
    REP(o,n+1) {
      int cnt=0;
      REP(i,R)REP(j,C) if(B2[o+i][o+j]=='.'&&B[i][j]=='B') B2[o+i][o+j]=B[i][j],++cnt;
      X[o]=cnt;
    }
    
//    dumpAR(X);
    
    if(T<=n) {
      LL res=0;
      REP(i,T) res+=X[i];
      return res;
    }
    LL res=accumulate(X.begin(),X.end(),0LL);
    T-=n+1;
    res+=(LL)T*(LL)X.back();
    
    return res;
  }
};

// CUT begin
ifstream data("PastingPaintingDivTwo.sample");

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

bool do_test(vector<string> clipboard, int T, long long __expected) {
    time_t startClock = clock();
    PastingPaintingDivTwo *instance = new PastingPaintingDivTwo();
    long long __result = instance->countColors(clipboard, T);
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
        vector<string> clipboard;
        from_stream(clipboard);
        int T;
        from_stream(T);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(clipboard, T, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514347025;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PastingPaintingDivTwo (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
