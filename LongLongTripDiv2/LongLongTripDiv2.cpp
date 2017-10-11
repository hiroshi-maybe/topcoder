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
 
 10/10/2017
 
 9:07-9:38 system test passed
 
 editorial:
  - problem writer's comment
    - http://snuke.hatenablog.com/entry/2014/04/04/213741
  - O(1) math solution
    - https://apps.topcoder.com/wiki/display/tc/SRM+615
  - binary search
    - http://torus711.hatenablog.com/entry/20140404/1396620545
    - http://kmjp.hatenablog.jp/entry/2014/04/09/1100
 
 f(x) = B*x+(T-x) = (B-1)x+T
 thus f(x) is monotonically increasing.
 we can find x s.t. f(x)=D by binary search.
 
 19:40-19:54 add more binary search solutions and O(1) math solution
 
 summary:
  - figured out binary search quickly
  - a bit confused about boundary update
 
 */

class LongLongTripDiv2 {
  public:
  string yes="Possible",no="Impossible";
  string isAble(long long D, int T, int B) {
    if(D>=T&&(D-T)%(B-1)==0&&(D-T)/(B-1)<=T) return yes;
    else return no;
  }
};

class LongLongTripDiv2_binarysearch2 {
  public:
  string yes="Possible",no="Impossible";
  int T;
  LL B,D;
  LL dd(LL x) {
    return (B-1)*x+T;
  }
  string isAble(long long D, int T, int B) {
    this->D=D,this->T=T,this->B=B;
    
    /*
    LL good=0,bad=T+1;
    while(abs(good-bad)>1) {
      LL mid=(good+bad)/2;
      if(dd(mid)<=D) good=mid;
      else bad=mid;
    }
    return good<=T&&dd(good)==D?yes:no;
     */
    
    LL l=0,r=T;
    REP(_,60) {
      LL mid=(l+r)/2;
      if(dd(mid)==D) return yes;
      if(dd(mid)<D) l=mid+1;
      else r=mid;
      dump2(l,r);
    }
    return no;
  }
};

// binary search by number of 1(mm) jump
class LongLongTripDiv2_org {
  public:
  string yes="Possible",no="Impossible";
  int T;
  LL B,D;
  LL dd(LL a) {
    return a+B*(T-a);
  }
  string isAble(long long D, int T, int B) {
    this->D=D,this->T=T,this->B=B;
    LL good=T,bad=-1;
    while(abs(good-bad)>1) {
//      dump2(good,bad);
      LL mid=(good+bad)/2;
      if(dd(mid)<=D) good=mid;
      else bad=mid;
//      dump2(good,bad);
    }
//    dump2(good,dd(good));
    return dd(good)==D?yes:no;
  }
};

// CUT begin
ifstream data("LongLongTripDiv2.sample");

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

bool do_test(long long D, int T, int B, string __expected) {
    time_t startClock = clock();
    LongLongTripDiv2 *instance = new LongLongTripDiv2();
    string __result = instance->isAble(D, T, B);
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
        long long D;
        from_stream(D);
        int T;
        from_stream(T);
        int B;
        from_stream(B);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(D, T, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507651638;
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
        cout << "LongLongTripDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
