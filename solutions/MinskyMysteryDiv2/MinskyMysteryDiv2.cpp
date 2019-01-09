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
 
 2/20/2018
 
 16:53-18:08 Submit. However wrong answer.
 18:09-18:53 Reanalyze, implement and ACC
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+529
  - http://kmjp.hatenablog.jp/entry/2014/01/09/0900
  - http://topcoder.g.hatena.ne.jp/kojingharang/20120115/1326594296
  - http://topcoder.g.hatena.ne.jp/firewood/20120116/1326726454
  - http://wabelog.blogspot.com/2012/01/topcoder-529.html
  - http://kujira16.hateblo.jp/entry/20120115/1326609669
 
 Keys:
  - for x = 2....
   - If N%x=0, result is N/x+x
   - If N%x!=0, continue
   - If N is prime, N+1 is the result
 
 Summary:
  - Very poor math sense 👎
  - I used 6 pages of papers to try things. However I couldn't find keys until getting WA in first system test. 👎👎
  - I simulated with variable N. I stopped simulation before {bag1} is incremented. I lost chance to notice increasing {bag1} property here 👎👎👎👎
  - Simulate numbers which is not too large and is not too small. Compound number may be helpful as well.
  - In this kind of math problem, use of OEIS may be a good start as well...
   - https://oeis.org/search?q=3%2C4%2C4%2C6%2C5%2C8%2C6%2C6%2C7%2C12%2C8&language=english&go=Search
 
 */
class MinskyMysteryDiv2 {
public:
  long long computeAnswer(long long N) {
    if(N==0||N==1) return -1;
//    if(N==2) return 3;
//    if(N==3) return 4;
    for(LL y=2; y*y<=N; ++y) if(N%y==0) {
      LL x=N/y;
      return x+y;
    }
    return N+1;
  }
};

class MinskyMysteryDiv2_org {
  public:
  long long computeAnswer(long long N) {
    if(N==0) return -1;
    LL b0=N,b1=1,b2=0,b3=0,b4=0;
    int c=0;
    if(b0>100) {
      LL x=(N-100LL)/2LL;
      dump(x);
      b0=N-2*x;
      b1=2;
      b2=2*x;
      b3=0;
      b4=x;
      dump4(b0,b1,b2,b4);
      goto AAA;
    }
    while(c++<1000) {
      b1+=1; b4=0;
      while(b0>0) {
      AAA:
        if(c==0) {
          dump2(b0,b1);
          dump3(b2,b3,b4);
        }
//        dump3(b2,b3,b4);
        LL p=min(b0,b1);
        b0-=p,b1-=p,b2+=p,b3+=p;
        b4+=1;
        if(b0==0&&b1==0) return b3+b4;
        b1+=b3; b3=0;
      }
      b0+=b2; b2=0;
    }
    return -1;
  }
};

// CUT begin
ifstream data("MinskyMysteryDiv2.sample");

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

bool do_test(long long N, long long __expected) {
    time_t startClock = clock();
    MinskyMysteryDiv2 *instance = new MinskyMysteryDiv2();
    long long __result = instance->computeAnswer(N);
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
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519087973;
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
        cout << "MinskyMysteryDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
