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
 
 3/12/2018
 
 9:34-10:30 analysis
 10:31-11:05 ACC (343.79 pt)
 
 Editorials:
  - https://topcoder.g.hatena.ne.jp/JAPLJ/20110810/1312974278
  - https://apps.topcoder.com/wiki/display/tc/SRM+514
  - http://kmjp.hatenablog.jp/entry/2014/02/13/0900
   - approach is same as mine
  - http://d.hatena.ne.jp/kusano_prog/20110810/1312992643
   - cumulative sum and iteration from low to high
   - same as official editorial
 
 Summary:
  - It was straightforward after figuring out to compute f(R+1)-f(L)
  - However it took more time to implement than expected 👎
 
 */
LL ones[1001];
LL len[1001];
class MagicalGirlLevelThreeDivTwo {
  public:
  int K;
  vector<string> F;
  int f(int i, LL R) {
    LL res=0;
    if(i<K) return count(F[i].begin(),F[i].begin()+R,'1');
    VI xs;
    int j=i-1;
    while(j>=0) {
      xs.push_back(j);
      j-=K;
    }
    for(int j=0; j<SZ(xs); ++j) {
      int ii=xs[j];
      LL l=len[ii];
      if(R<=l) {
        res+=f(ii, R);
        break;
      } else {
        res+=ones[ii];
        R-=l;
      }
    }
//    dump3(i,R,res);
    return res;
  }
  int theCount(vector<string> _F, int N, long long L, long long R) {
    this->F=_F;
    this->K=SZ(F);
    ZERO(ones); ZERO(len);
    REPE(i,N) {
      if(i<K) {
        ones[i]=count(F[i].begin(),F[i].end(),'1');
        len[i]=SZ(F[i]);
      } else {
        int j=i-1;
        while(j>=0) {
          ones[i]+=min(ones[j],(LL)1e15);
          len[i]+=min(len[j],(LL)1e15);
          j-=K;
        }
      }
//      dump3(i,len[i],ones[i]);
    }
    
    return f(N,R+1)-f(N,L);
  }
};

// CUT begin
ifstream data("MagicalGirlLevelThreeDivTwo.sample");

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

bool do_test(vector<string> first, int n, long long lo, long long hi, int __expected) {
    time_t startClock = clock();
    MagicalGirlLevelThreeDivTwo *instance = new MagicalGirlLevelThreeDivTwo();
    int __result = instance->theCount(first, n, lo, hi);
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
        vector<string> first;
        from_stream(first);
        int n;
        from_stream(n);
        long long lo;
        from_stream(lo);
        long long hi;
        from_stream(hi);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(first, n, lo, hi, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520872440;
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
        cout << "MagicalGirlLevelThreeDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
