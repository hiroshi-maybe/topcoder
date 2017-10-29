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
 
 10/27/2017
 
 16:17-16:33 analysis
 16:34-16:57 implemented, debug and passed system test (240.94 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+604
  - http://torus711.hatenablog.com/entry/20140111/p3
 
 1. Simple brute force
  log3(10^9)<20. There are at most 2^19 choices which is enough to brute-force.
 
 2. Deterministic choice or ternary number
        X=    3^1+3^2    +3^4            +3^8+..
        Y=3^0        +3^3    +3^5+3^6+3^7    +..
 --------------------------------------------
      X/3=    3^0+3^1    +3^3            +3^7+..
  (Y-1)/3=           +3^2    +3^4+3^5+3^6    +..
 
 This shows that X%3==1 or Y%3==1 shows up every time they are divided by 3.
 
 key:
  - 1e9<3^20
  - Process x and y as ternary number
 
 summary:
  - time loss due to mistake to compute summation of 3^i
  - I analyzed that 1e9<3^20. I should have tried brute force at that time
 
 Submit solutions:
  - brute force
   - https://community.topcoder.com/stat?c=problem_solution&rm=320218&rd=15837&pm=12952&cr=22891945
   - https://community.topcoder.com/stat?c=problem_solution&rm=320185&rd=15837&pm=12952&cr=23138918
  - ternary number
   - https://community.topcoder.com/stat?c=problem_solution&rm=320230&rd=15837&pm=12952&cr=23184436
   - https://community.topcoder.com/stat?c=problem_solution&rm=320187&rd=15837&pm=12952&cr=23264406
 
 */

// O(log3(max(X,Y)) time
class PowerOfThreeEasy {
public:
  string ok="Possible",ng= "Impossible";
  string ableToGet(int X, int Y) {
    return f(X,Y)?ok:ng;
  }
  bool f(int X, int Y) {
    if(X==0&&Y==0) return true;
    if(X%3+Y%3!=1) return false;
    return f(X/3,Y/3);
  }
};

// O(2^log3(max(X,Y))) time
class PowerOfThreeEasy_bruteforce {
public:
  string ok="Possible",ng= "Impossible";
  string ableToGet(int X, int Y) {
    return f(X,Y,1)?ok:ng;
  }
  bool f(int X, int Y, LL d) {
    if(X<0||Y<0) return false;
    if(X==0&&Y==0) return true;
    return f(X-d,Y,d*3)||f(X,Y-d,d*3);
  }
};

class PowerOfThreeEasy_org {
  public:
  string ok="Possible",ng= "Impossible";
  string ableToGet(int X, int Y) {
    LL pow3[22]={0};
    pow3[0]=1;
    REP(i,21) pow3[i+1]=pow3[i]*3LL;
//    dumpAR(pow3);
    LL N=2*(X+Y)+1;
    int k=0;
    for(; k<22; ++k) if(pow3[k]==N) {
      break;
    }
//    dump(k);
    if(k==22) return ng;
    
    for(LL mask=0; mask<(1<<k); ++mask) {
      LL x=0,y=0;
      REP(i,k) {
        if(mask&(1LL<<i)) {
          x+=pow3[i];
        } else {
          y+=pow3[i];
        }
      }
      if(x==X&&y==Y) return ok;
    }
    
    return ng;
  }
};

// CUT begin
ifstream data("PowerOfThreeEasy.sample");

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

bool do_test(int x, int y, string __expected) {
    time_t startClock = clock();
    PowerOfThreeEasy *instance = new PowerOfThreeEasy();
    string __result = instance->ableToGet(x, y);
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
        int y;
        from_stream(y);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509232652;
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
        cout << "PowerOfThreeEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
