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

/**
 
 8/12/2017
 
 10:46-11:00-11:12 (310.07 pt)
 
 editorials:
  - http://kmjp.hatenablog.jp/entry/2015/10/15/1000
  - https://apps.topcoder.com/wiki/display/tc/SRM+671
 
 8/13/2017
 
 21:30-21:54 add official editorial solution.
  - O(N^3) with hash map hits 1(sec) TLE. O(N^3) with native array passes
 
 21:54-22:25 add @kmjp O(N^2) solution
 
 Key:
  - O(N^2) technique of brute force of four indices (i,j,k,l) where i<j<k<l...
    - move k and keep interesting state X of (i,j) where j<k as a loop invariant.
    - in each iteration with pinned k...
      1. brute force pairs of (k,l) l=k+1..<N with X to know the result of (x,y,k,l)
      2. brute force pairs of (i,j) i=0..<k, j=k and memoize the result in X
  - we are interested in {i,j}x{k,l}
   - for each moving j, we need to know state of pairs (i,j)
   - for each moving k, we need to know state of pairs (k,l)
    => move j and k at the same time!
 
 */

// O(N^2) time
int cnt[1000001];
class BearDartsDiv2 {
public:
  long long count(vector<int> W) {
    int N=SZ(W);
    ZERO(cnt);
    
    LL res=0;
    REP(k,N) {
      // invariant: cnt[] has number of pairs (i,j) for a*b (j<k)
      FOR(l,k+1,N) if(W[l]%W[k]==0) res+=cnt[W[l]/W[k]];
      REP(i,k) if(1LL*W[i]*W[k]<1000001LL) cnt[W[i]*W[k]]++;
    }
    return res;
  }
};

// O(N^3) time algorithm with native array
int did[1000001];
int M[501][501];
class BearDartsDiv2_official_editorial {
public:
  long long count(vector<int> W) {
    int N=SZ(W);
    MINUS(did); MINUS(M);
    REP(i,N) did[W[i]]=i;
    
    REP(i,N) {
      int n=W[i];
      if(did[n]!=i) continue;
      REP(j,N) {
        M[i][j]=0;
        FOR(k,j+1,N) if(W[k]==n) M[i][j]++;
      }
    }
    
    LL res=0;
    REP(i,N) FOR(j,i+1,N) FOR(k,j+1,N) {
      LL d=(LL)W[i]*(LL)W[j]*(LL)W[k];
      if(d<=1000000&&did[d]!=-1) res += M[did[(int)d]][k];
    }
    
    return res;
  }
};

// O(N^3) algorithm with hash map hits TLE :(
class BearDartsDiv2_tle {
public:
  long long count(vector<int> W) {
    int N=SZ(W);
    unordered_map<int,MAPII> M;
    FORR(n,W) {
      if(M.count(n)) continue;
      REP(i,N) FOR(j,i+1,N) if(W[j]==n) M[n][i]++;
    }
    
    LL res=0;
    REP(i,N) FOR(j,i+1,N) FOR(k,j+1,N) {
      LL d=(LL)W[i]*(LL)W[j]*(LL)W[k];
      if(d<=1e6) res += M[d][k];
    }
    
    return res;
  }
};

// hash table and binary search, O(N^2*lg N) time
class BearDartsDiv2_org {
  public:
  long long count(vector<int> W) {
    int N=SZ(W);
    unordered_map<LL,VI> M;
    REP(i,N)FOR(j,i+1,N) {
      LL c=W[i],d=W[j];
      if(d%c==0) M[d/c].push_back(i);
    }
    
    LL res=0;
    REP(i,N)FOR(j,i+1,N) {
      LL a=W[i],b=W[j];
      if(M.count(a*b)) {
        VI& ns=M[a*b];
        LL x=ns.end()-upper_bound(ns.begin(),ns.end(),j);
        res+=x;
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("BearDartsDiv2.sample");

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

bool do_test(vector<int> w, long long __expected) {
    time_t startClock = clock();
    BearDartsDiv2 *instance = new BearDartsDiv2();
    long long __result = instance->count(w);
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
        vector<int> w;
        from_stream(w);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(w, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502559997;
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
        cout << "BearDartsDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
