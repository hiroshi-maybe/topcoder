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
 
 7/23/2017
 
 8:58 start
 9:44 designed
 9:49 oops. xxx case was missing in analysis
 10:10 give up
 
 13:26-14:30 read editorials
 - https://apps.topcoder.com/wiki/display/tc/SRM+692
 - http://kmjp.hatenablog.jp/entry/2016/09/05/0930
 - https://docs.google.com/document/d/1uDF4p6TUQG3QftYT3lRhKqd9fH2R_GgK9fap_QVeajw/edit
 
 14:30-15:19 add solution
 
 Aho-cracking algorithm
 - https://en.wikipedia.org/wiki/Aho–Corasick_algorithm
 
 Key
 - keep appending N chatacters
 - implement string matching to figure out which character can be appended
 - keep decreasing K or N in recurrence relation
  - f(p,K,N) = f(0,K-1,N)+f(p',K,N-1)
 - prefix match is part of state
 
 Summary
 - insertion DP didn't work in this case
 - it was hard to find out prefix match is a key
 
 */

constexpr int MOD = 1e9+9;

class LinenCenterEasy {
public:
  int L;
  int PRE[50][26]={};
  int OK[50]={};
  int memo[51][51][51]={};
  int countStrings(string S, int N, int K) {
    L=SZ(S);
    REP(i,L) {
      // prefix + S = S?
      string pre=(S.substr(0,i)+S).substr(0,L);
      OK[i]=(i==0)||(pre!=S);
      REP(j,26) {
        char c='a'+j;
        PRE[i][j]=0; // by default go to head
        // prefix + ch
        string t = S.substr(0,i) + c;
        
        for(int l=SZ(t); l>=0; --l) {
          assert(S.substr(0,l).length() == t.substr(t.size()-l).length());
          // prefix of S == suffix of t (t=prefix of S + x)
          if(S.substr(0,l)==t.substr(SZ(t)-l)) {
            PRE[i][j] = l;
            break;
          }
        }
      }
    }
    memset(memo, -1, sizeof memo);
    return f(0, K, N);
  }
  
  LL f(int p, int k, int n) {
    if(memo[p][k][n]>=0) return memo[p][k][n];
    LL res=0;
    
    if(p==L) return memo[p][k][n]=0;
    if(k==0) ++res;
    if(n>0) {
      REP(i,26) res+=f(PRE[p][i],k,n-1), res%=MOD;
    }
    if(k>0&&OK[p]) res += f(0,k-1,n), res%=MOD; // insert S
    
    return memo[p][k][n]=res;
  }
};

/*
class LinenCenterEasy {
  public:
  int L;
  LL f(LL l, LL r) {
    if(l==0&&r==0) return 1;
    if(memo[l][r]>=0) return memo[l][r];
    
    LL res=0;
    if(l>0) {
      if(l%L)
    }
      
  }
  int countStrings(string S, int N, int K) {
    memset(memo, -1, sizeof memo);
    LL res=0;
    REP(lr,N) {
      REP(l,lr) {
        res += f(l,lr-l); res%=MOD;
      }
    }
    return res;
  }
};*/

// CUT begin
ifstream data("LinenCenterEasy.sample");

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

bool do_test(string S, int N, int K, int __expected) {
    time_t startClock = clock();
    LinenCenterEasy *instance = new LinenCenterEasy();
    int __result = instance->countStrings(S, N, K);
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
        string S;
        from_stream(S);
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500825523;
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
        cout << "LinenCenterEasy (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
