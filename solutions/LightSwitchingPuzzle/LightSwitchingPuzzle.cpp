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
 
 9/13/2017
 
 8:29-9:25 pause
 18:25-18:45 system test passed
 
 editorial:
  - http://torus711.hatenablog.com/entry/20141217/1418830607
    - detailed proof
  - https://apps.topcoder.com/wiki/display/tc/SRM+642
  - http://kmjp.hatenablog.jp/entry/2014/12/19/0900
  - http://roiti46.hatenablog.com/entry/2014/12/18/TopCoder_SRM_642_Div2
  - https://ik-fib.com/2014/12/srm642-div2/
 
 we need to keep fixing smaller numbers because they affect state of larger numbers.
 
 key:
  - analysis is key that what light affects what light
 
 summary:
  - in the morning, I had no idea to solve it though, in the evening I found a solution quickly
 
 24:00-24:04 add simpler iterative solution
 
 */

class LightSwitchingPuzzle {
public:
  int minFlips(string S) {
    int N=SZ(S);
    VI X(N); REP(i,N) X[i]=S[i]=='Y';
    
    int res=0;
    REP(i,N) if(X[i]) {
      ++res;
      for(int j=i; j<N; j+=i+1) X[j]^=1;
    }
    return res;
  }
};

class LightSwitchingPuzzle_original {
public:
  int N;
  int dfs(VI X) {
    int st=-1;
    REP(i,N) if(!X[i]) {
      st=i;
      break;
    }
    if(st==-1) return 0;
    
    int cycle=st+1;
    for(; st<N; st+=cycle) {
      X[st]^=1;
    }
    return dfs(X)+1;
  }
  
  int minFlips(string state) {
    this->N=SZ(state);
    VI on(N,0),off(N,0);
    REP(i,N) {
      on[i]=state[i]=='Y';
      off[i]=state[i]!='Y';
    }
    
    // original answer. actually no need to try `dfs(on)+1`
    //return min(dfs(on)+1, dfs(off));
    return dfs(off);
  }
};

class LightSwitchingPuzzle_wrong {
  public:
  int N;
  int dfs(SETI S) {
    SETI mins=S;
//    dumpAR(S);
    FORR(n,S) {
      SETI T=S;
      for(int k=1; n*k<=N; ++k) {
        if(S.count(n*k)) T.erase(n*k);
        else T.insert(n*k);
      }
      if(SZ(T)<SZ(mins)) mins=T;
    }
    dumpAR(mins);
//    dump2(SZ(mins),SZ(S));
    return SZ(mins)<SZ(S)?dfs(mins)+1:SZ(S);
  }
  
  int minFlips(string state) {
    SETI on,off;
    this->N=SZ(state);
    REP(i,N) {
      (state[i]=='Y'?on:off).emplace(i+1);
    }
    dump(N);
    dumpAR(on);
    //return min(dfs(on), dfs(off)+1);
    return dfs(on);
  }
};

// CUT begin
ifstream data("LightSwitchingPuzzle.sample");

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

bool do_test(string state, int __expected) {
    time_t startClock = clock();
    LightSwitchingPuzzle *instance = new LightSwitchingPuzzle();
    int __result = instance->minFlips(state);
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
        string state;
        from_stream(state);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(state, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505316570;
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
        cout << "LightSwitchingPuzzle (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
