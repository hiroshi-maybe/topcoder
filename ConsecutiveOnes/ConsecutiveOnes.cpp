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
 
 22:08-22:50 passed samples (115.38 pt)
 23:30 failed system test
 23:35 failed again
 23:40 passed system test
 
 7/8/2017
 
 read editorials...
 https://www.topcoder.com/blog/single-round-match-711-editorials/
 http://kmjp.hatenablog.jp/entry/2017/03/26/0900
 
 13:35 add simpler solution by bit manipulation
 
 */

class ConsecutiveOnes {
public:
  long long get(long long n, int k) {
    LL res = 1LL<<61;
    
    for(int i=0; i+k<=61; ++i) {
      LL mask = (1LL<<k)-1;
      mask = mask<<i;
      // 1xk already exists in n
      if((mask&n)==mask) return n;
      
      LL x = n>>(i+k);
      x = x<<(i+k);
      x = x|mask;

      assert(x>n);
      res = min(res, x);
    }
    
    return res;
  }
};

class ConsecutiveOnes_org {
  public:
  long long get(long long n, int k) {
    VI ns;
    LL _n=n;
    while(_n>0) {
      ns.push_back(_n&1);
      _n>>=1;
    }
    if (SZ(ns)<=k) return (1LL<<(LL)k)-1LL;
    int maxc=ns[0]==1;
    FOR(i,1,SZ(ns)) {
      if(ns[i-1]==1&&ns[i]==1) {
        ++maxc;
        if (maxc>=k) return n;
      } else if (ns[i]==1) maxc=1;
      else maxc=0;
    }
    
    LL res=LLONG_MAX;
    VI ms=ns;
    REP(i,k) ms[i]=1;
    
    REP(i,SZ(ns)-k) {
      LL m=ton(ms);
      if (m>=n) res=min(res,m);
      ms[i]=0;
      ms[i+k]=1;
    }
    LL m=ton(ms);
    if (m>=n) res=min(res,m);

    return res;
  }
  
  LL ton(VI ns) {
    reverse(ns.begin(),ns.end());
    LL res=0;
    for(auto &n: ns) {
      res<<=1;
      res|=n;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ConsecutiveOnes.sample");

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

bool do_test(long long n, int k, long long __expected) {
    time_t startClock = clock();
    ConsecutiveOnes *instance = new ConsecutiveOnes();
    long long __result = instance->get(n, k);
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
        long long n;
        from_stream(n);
        int k;
        from_stream(k);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499317675;
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
        cout << "ConsecutiveOnes (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
