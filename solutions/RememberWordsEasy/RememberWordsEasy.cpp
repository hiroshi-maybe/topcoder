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
 
 9/26/2017 SRM721
 
 8:20-9:07 system test failed (222.20 pt)
 21:58-22:03 fix overflow bug
 22:04-22:17 fix bug of long interval
 22:18-22:52 redesigned range calculation but another WA
 22:53-24:04 give up
 
 10/1/2017
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2017/09/27/0900
 
 sum of arithmetic sequence:
  - https://en.wikipedia.org/wiki/Arithmetic_progression
 
 23:45-25:05 copied @kmjp solution and systemt test passed
 
 find `v` which can be edge of sequence in d1 or d2 days.
 
 1) search lowest `v`.
 search lowest `v` by brute force (div2) or binary search (div1).
 
 total area by low edge v can be AT MOST d*(v+(v+d-1))/2 with higher edge `v+d-1`.
 if this area >=w, we can achieve this `v`.
 even if this is larger than w, we can adjsut to w by decreasing `v+d-1`.
 however, if the area <w, v needs to increases because the area is maximum by those edges.
 
 2) search highest `v`.
 search highest `v` by brute force (div2) or binary search (div1).
 
 total area by high edge v can be AT LEAST d*( max(v-(d-1),0) + v)/2 with lower edge max(v-(d-1),0).
 note that lower edge should be non-negative value.
 if this area <=w, we can achieve this `v`.
 even if this is smaller than w, we can adjust to w by increasing lower edge.
 however, if the area >w, v needs to decrease because the area is minimum by those edges.
 
 by those search, we get [l1,r1] and [l2,r2] from (d1,w1) and (d2,w2).
 if intervals overlap or difference is just 1, return "Possible".
 
 summary:
  - the hardest div2 medium ever for me... 😵
 
 */

class RememberWordsEasy {
public:
  const string yes="Possible",no="Impossible";
  
  LL high(LL d, LL w) {
    LL res=0;
    for(int v=0; v<=w; ++v) {
      LL low=max(v-(d-1), 0LL);
      LL sum=(v+low)*(v-low+1)/2;
      if(sum<=w) res=max(res,(LL)v);
    }
    return res;
  }
  
  LL low(LL d, LL w) {
    LL res=1e9;
    for(int v=0; v<=w; ++v) {
      LL high=v+(d-1);
      LL sum=(v+high)*(d)/2;
      if(sum>=w) res=min(res,(LL)v);
    }
    return res;
  }
  
  string isPossible(int d1, int d2, int w1, int w2) {
    pair<LL,LL> r1={low(d1,w1),high(d1,w1)},r2={low(d2,w2),high(d2,w2)};
    
    dump2(r1.first,r1.second);
    dump2(r2.first,r2.second);
    
    // probably this case does not happen? 🤔
    assert(r1.first<=r1.second&&r2.first<=r2.second);
    if(r1.first>r1.second||r2.first>r2.second) return no;

    // technique to detect interval intersection
    if(r1.first<=r2.second+1&&r2.first<=r1.second+1) return yes;
    
    // or... check from my wrong solution
    // return ((r1.second+1)<r2.first||(r2.second+1)<r1.first)?no:yes;
    
    // or... from @kmjp's solution
    // if(r1.second+1==r2.first) return yes;
    // if(r2.second+1==r1.first) return yes;
    // if(max(r1.first,r2.first)<=min(r1.second,r2.second)) return yes;
    return no;
  }
};

class RememberWordsEasy_totally_wrong {
  public:
  const string yes="Possible",no="Impossible";
  II range(LL d, LL w) {
    LL x=0,base=0;
    for(; base<=1e6; ++base) {
      LL tot=base*d;
      x=0;
      while(tot+x*(x+1)/2<w) ++x;
      if(tot+x*(x+1)/2==w&&x<d) break;
    }
    dump2(base,x);
    return {base,base+x};
  }
  II range_v3_wrong(LL d, LL w) {
    LL x=1;
    while(x*(x-1)/2<=w) ++x;
    --x;
    dump2(x,d);
    if(x<=d) return {0,min(w,x)};
    
    x=0;
    while(x*d+d*(d-1)/2<=w) ++x;
    --x;
    return {x,x+d-1};
  }

  II range_v2_wrong(LL d, LL w) {
    dump(d*(d-1)/2);
    if(w<d) return {0,min(w,1LL)};
    if(w<d*(d-1)/2) return {0,d-1};
    LL x=0;
    for(;x*d+d*(d-1)/2<=w; ++x) {}
    --x;
    return {x,x+d-1};
  }
  
  II range_v1_wrong(int d, int w) {
    int lb=(1LL*w-1LL*d*(d-1)/2)/(1LL*d);
    if(lb<0) {
      LL x=0;
      for(; x*(x+1)<1LL*w; ++x) {}
      return {0,x};
    }
    int ub=lb+d-1;
    
    return {lb,ub};
  }
  string isPossible(int d1, int d2, int w1, int w2) {
    dump4(d1,d2,w1,w2);

    II r1=range(d1,w1),r2=range(d2,w2);
    
    dump2(r1.first,r1.second);
    dump2(r2.first,r2.second);
    
    return ((r1.second+1)<r2.first||(r2.second+1)<r1.first)?no:yes;
  }
};

// CUT begin
ifstream data("RememberWordsEasy.sample");

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

bool do_test(int d1, int d2, int w1, int w2, string __expected) {
    time_t startClock = clock();
    RememberWordsEasy *instance = new RememberWordsEasy();
    string __result = instance->isPossible(d1, d2, w1, w2);
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
        int d1;
        from_stream(d1);
        int d2;
        from_stream(d2);
        int w1;
        from_stream(w1);
        int w2;
        from_stream(w2);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(d1, d2, w1, w2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506439233;
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
        cout << "RememberWordsEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
