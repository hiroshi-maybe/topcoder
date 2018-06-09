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
 
 6/9/2018
 
 15:25-17:10 give up
 17:25-19:00,22:00-23:30 read editorials and add solution
 
 Editorials:
  - http://fluffyowl.hatenablog.com/entry/2017/09/27/191648
  - http://kmjp.hatenablog.jp/entry/2017/09/27/0900
 
 Summary:
  - I couldn't figure out lower-bound and upper-bound correctly..
 
 */
const string yes="Possible",no="Impossible";
const int Inf=1e9+10;

int high(int D, int W) {
  int good=0,bad=Inf;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    LL n=min(1LL*D,mid);
    LL a=1LL*n*(2*mid-(n-1))/2;//(1LL*D*(2*mid-D+1)/2,1LL*D*(D+1)/2);
    if(a<=W) good=mid;
    else bad=mid;
  }
  return good;
}
int low(int D, int W) {
  int good=Inf,bad=-1;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    LL a=1LL*D*(1LL*2*mid+D-1)/2;
    if(a>=W) good=mid;
    else bad=mid;
//    dump2(good,bad);
  }
  return good;
}

class RememberWords {
public:
  string isPossible(int D1, int D2, int W1, int W2) {
    int L1=low(D1,W1),H1=high(D1,W1);
    dump2(L1,H1);
    int L2=low(D2,W2),H2=high(D2,W2);
    dump2(L2,H2);
    int l=max(L1,L2),r=min(H1,H2);
    dump2(l,r);
    if(r-l>=-1) return yes;
    return no;
  }
};

/*
typedef long long ll;

class RememberWords  {
public:
  string isPossible(int d1, int d2, int w1, int w2) {
    ll d1min = binsearch_min(d1, w1);
    ll d1max = binsearch_max(d1, w1);
    ll d2min = binsearch_min(d2, w2);
    ll d2max = binsearch_max(d2, w2);
    
    cout << d1min << " " << d1max << " " << d2min << " " << d2max << endl;
    return (d1min - 1 > d2max || d1max + 1 < d2min) ? "Impossible" : "Possible";
  }
  
  ll sm(ll a, ll n, ll d) {
    return n * (2 * a + (n - 1) * d) / 2;
  }
  
  ll binsearch_min(ll d, ll w) {
    ll hi = 1000000000;
    ll lo = -1;
    while (hi - lo > 1) {
      ll mid = (hi + lo) / 2;
      ll s = sm(mid, d, 1);
      if (s >= w) hi = mid;
      else lo = mid;
    }
    return hi;
  }
  
  ll binsearch_max(ll d, ll w) {
    ll hi = 1000000001;
    ll lo = 0;
    while (hi - lo > 1) {
      ll mid = (hi + lo) / 2;
      ll s = sm(mid, min(d, mid), -1);
      if (s <= w) lo = mid;
      else hi = mid;
    }
    return lo;
  }
  
};*/

/*
int high(int D, int W) {
  LL x=D*(D+1)/2;
  if(x>W) {
    int good=Inf,bad=-1;
    while(abs(good-bad)>2) {
      LL mid=(good+bad)/2;
      LL a=mid*(mid+1)/2;
      if(a>=W) good=mid;
      else bad=mid;
    }
    return good;
  } else {
    int good=Inf,bad=-1;
    while(abs(good-bad)>2) {
      LL mid=(good+bad)/2;
      LL a=D*(D+1)/2+mid*D;
      if(a>=W) good=mid;
      else bad=mid;
    }
    dump3(good,D,good+D);
    return good+D;
  }
}
int low(int D, int W) {
  LL x=D*(D+1)/2;
  if(x>W) return Inf;
  int good=Inf,bad=-1;
  while(abs(good-bad)>2) {
    LL mid=(good+bad)/2;
    LL a=mid*(mid+1)/2+mid*(D-mid);
    if(a>=W) good=mid;
    else bad=mid;
  }
  return good<=D?good:Inf;
}*/

class RememberWords_wrong {
  public:
  string isPossible(int D1, int D2, int W1, int W2) {
    int L1=low(D1,W1),H1=high(D1,W1);
    if(L1==Inf) L1=H1;
    dump2(L1,H1);
    int L2=low(D2,W2),H2=high(D2,W2);
    if(L2==Inf) L2=H2;
    dump2(L2,H2);
//    if(L2>H2) return no;
    int l=max(L1,L2),r=min(H1,H2);
    dump2(l,r);
    if(r-l>=-1) return yes;
    return no;
  }
};

// CUT begin
ifstream data("RememberWords.sample");

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
    RememberWords *instance = new RememberWords();
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
        int T = time(NULL) - 1528525532;
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
        cout << "RememberWords (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
