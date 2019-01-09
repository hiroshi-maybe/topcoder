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
 
 7/16/2017
 
 16:15-16:40 time up
 
 19:10-19:57 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/09/04/0930
 - https://apps.topcoder.com/wiki/display/tc/SRM+697#XorOrderDiv2
 
 22:37-24:48
 - https://community.topcoder.com/stat?c=problem_solution&rm=329148&rd=16776&pm=14370&cr=40159546
 - https://community.topcoder.com/stat?c=problem_solution&rm=329160&rd=16776&pm=14370&cr=40208780
 
 Keys
 - a[i] is represented by {0,1}xM
 - j=0..2^M-1 => 0 and 1 shows up 2^(M-1) times in 2^m-1 days
 - Since time is a[i]^j, a[i] is togged 2^(M-1) times
 - longer common prefix, more lost
 
 24:48 replicated code
 - to be honest, I could not understand the meaning of recursive relation.
 
 */

// O(N^2*M) time
class XorOrderDiv2 {
  public:
  vector<long long> getExpectation(int m, vector<int> a) {
    int N=SZ(a);
    vector<LL> res(N,0LL);
    REP(i,N) {
      int prefix[33][2]={};
      REP(j,N) if(i!=j) {
        int mask=a[i]^a[j];
        for(int bi=m-1; bi>=0; --bi) {
          if((mask>>bi)&1) {
            // first different bit (bi-1 prefix is common)
            bool weak = (a[i]&(1<<bi))==0;
            prefix[bi][weak]++;
            break;
          }
        }
      }
      
      LL dp[33][1005]={};
      dp[0][0]=1;
      REP(bi,m) {
        REP(k,N) {
          dp[bi+1][k+prefix[bi][0]]+=dp[bi][k];
          dp[bi+1][k+prefix[bi][1]]+=dp[bi][k];
        }
      }
      
      REP(k,N) res[i]+=dp[m][k]*(LL)k*(LL)k;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("XorOrderDiv2.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(int m, vector<int> a, vector<long long> __expected) {
    time_t startClock = clock();
    XorOrderDiv2 *instance = new XorOrderDiv2();
    vector<long long> __result = instance->getExpectation(m, a);
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
        int m;
        from_stream(m);
        vector<int> a;
        from_stream(a);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(m, a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500246926;
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
        cout << "XorOrderDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
