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
 
 3/2/2018
 
 8:28-8:45 analysis
 8:46-9:04 implement and ACC (460.59 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+519
    - nice observation how each column changes in entire step
  - http://kmjp.hatenablog.jp/entry/2014/01/15/0930
    - recursion
  - http://d.hatena.ne.jp/kusano_prog/20110920/1316548874
    - very beautiful implementation by iterating i>>1 operation
    - this technique may be useful for problems to check each bit
  - http://topcoder.g.hatena.ne.jp/firewood/20111021/1319213138
  - http://peryaudo.hatenablog.com/entry/20110920/1316506652
  - http://mayokoex.hatenablog.com/entry/2015/08/04/170353
  - https://topcoder.g.hatena.ne.jp/jackpersel/20110920/1316533433
  - http://area.hateblo.jp/entry/2013/09/10/001023
  - http://resemblances.click3.org/?p=1365
  - https://chngng.blogspot.com/2013/10/srm-519-div1-easy-binarycards.html
  - http://expnotes9.blog.fc2.com/blog-entry-124.html
 
 When I solved this problem, I looked from least to most significant bit.
 However sounds like it's easier to see from most to least significant bit.
 
 23:30-23:44 Add simpler solution
 
 Summary:
  - I simulated from A to B. So my analysis went
  - One more deep dive even if planning is done! 🏊
   - Simulation itself is nice as described in official editorial
   - However design may not be very simple
   - Even if it's solved in analysis perspective, put one more step to research simpler way before coding
   - In this problem, bit goes right to left when incrementing integer. However eventually checking bit from left to right is easier and SUFFICIENT.
 
 */

// inspired by @kusano's solution
class BinaryCards {
public:
  long long largestNumber(long long A, long long B) {
    for(LL mask=1LL<<62; mask>0; mask>>=1LL) {
      if((A&mask)!=(B&mask)) return A|((mask<<1)-1);
    }
    return A;
  }
};

class BinaryCards_rtl1 {
public:
  long long largestNumber(long long A, long long B) {
    for(int i=62; i>=0; --i) {
      int a=(A>>i)&1,b=(B>>i)&1;
      if((a^b)==1) {
//        dump3(i,a,b);
        assert(a==0&&b==1);
        LL C=B&((1LL<<(i+1))-1);
        return B-C+(1LL<<(i+1))-1;
      }
    }
    return A;
  }
};

class BinaryCards_org {
  public:
  long long largestNumber(long long A, long long B) {
    LL res=A;
    LL n=A;
    while(n<B) {
      dump(n);
      int i=0;
      while((n>>i)&1) ++i;
      LL a=n-((1LL<<i)-1);
      LL b=(1LL<<(i+1))-1;
      n=a+b;
      dump3(n,B,n|B);
      if((n|B)==n) res=n;
    }
    return res;
  }
};

// CUT begin
ifstream data("BinaryCards.sample");

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

bool do_test(long long A, long long B, long long __expected) {
    time_t startClock = clock();
    BinaryCards *instance = new BinaryCards();
    long long __result = instance->largestNumber(A, B);
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
        long long A;
        from_stream(A);
        long long B;
        from_stream(B);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520008102;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BinaryCards (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
