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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/5/2017
 
 8:44-8:59 (388.61 pt)
 
 read https://community.topcoder.com/stat?c=problem_solution&rd=16850&rm=329609&cr=40491362&pm=14507
 
 19:40-20:00 add simpler solution
 
 */

// O(1) time
class SellingFruits {
public:
  int maxDays(int x, int f, int d, int p) {
    /*
     res = min(f+f', (d-p*f')/x) where f' is number of fruit to be bought in addition to f
     
     In optimal situation, f+f'==(d-p*f')/x
     <=> f'=(d-f*x)/(x+p)
     
     i) f'<=0
        <=> d-f*x<=0 <=> f>=x/d
        thus res=x/d
     ii) otherwise
        res = f+f' = f+(d-f*x)/(x+p)
     
     Or....
     
     i) x*d<f
      result is upper-bounded by current $ (no extra $ to buy more fruit).
     ii) otherwise
      d-=x*f // spend $ to live `f` days
      res = f
      res += d/(x+p) // spend x+p from d every day
     */
    if (f>d/x) return d/x;
    return f+(d-f*x)/(x+p);
  }
};

// binary search, O(lg (max(f+d/p,d/x)-min(f,d/x)) time
class SellingFruits_org {
  public:
  int maxDays(int x, int f, int d, int p) {
    LL good=min(f,d/x), bad=max(f+d/p,d/x);
    while(abs(bad-good)>1) {
      LL mid=(bad+good)/2;
      if (ok(mid,x,f,d,p)) good=mid;
      else bad=mid;
    }
    
    return good;
  }
  
  bool ok(LL n, LL x, LL f, LL d, LL p) {
    LL f2 = f>=n ? 0 : n-f;
    d = d-f2*p; //fruit
    
    return d>=n*x;
  }
};

// CUT begin
ifstream data("SellingFruits.sample");

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

bool do_test(int x, int f, int d, int p, int __expected) {
    time_t startClock = clock();
    SellingFruits *instance = new SellingFruits();
    int __result = instance->maxDays(x, f, d, p);
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
        int x;
        from_stream(x);
        int f;
        from_stream(f);
        int d;
        from_stream(d);
        int p;
        from_stream(p);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, f, d, p, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499269438;
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
        cout << "SellingFruits (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
