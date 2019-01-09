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
 
 9/30/2017
 
 17:42-17:57 1WA (398.43 pt)
 18:06 resubmit (unordered_set -> set) and system test passed. (277.31 pt)
 
 10/1/2017
 
 12:54-13:05 add solution without ordered set
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+625
  - http://kmjp.hatenablog.jp/entry/2014/06/22/1030
  - http://torus711.hatenablog.com/entry/20140622/1403446850
  - http://topcoder.g.hatena.ne.jp/capythm/20140624/1403617845
 
 summary:
  - greedily we need to fill smaller one first
   - my first submit solution did not work due to unordered set
 
 */

class IncrementingSequence {
public:
  const string ok="POSSIBLE",ng="IMPOSSIBLE";
  string canItBeDone(int K, vector<int> A) {
    int N=SZ(A);
    int cnt[51];
    ZERO(cnt);
    FORR(n,A) ++cnt[n];
    for(int x=1; x<=N; ++x) {
      bool ok=false;
      for(int y=1; y<=x; ++y) if(cnt[y]&&(x-y)%K==0) {
        --cnt[y];
        ok=true;
        break;
      }
      if(!ok) return ng;
    }
    return ok;
  }
};

class IncrementingSequence_org {
  public:
  const string ok="POSSIBLE",ng="IMPOSSIBLE";
  string canItBeDone(int K, vector<int> A) {
    int N=SZ(A);
    sort(A.begin(),A.end());
    SETI S(A.begin(),A.end());
    set<int> miss;
    for(int i=1; i<=N; ++i) if(S.count(i)==0) miss.emplace(i);
    REP(i,N) {
      int a=A[i];
      if(a>N) return ng;
      if(i>0&&A[i]==A[i-1]) {
        FORR(x,miss) if(x>a&&(x-a)%K==0) {
          miss.erase(x);
          break;
        }
      }
    }
//    dump(SZ(miss));
    return SZ(miss)>0?ng:ok;
  }
};

// CUT begin
ifstream data("IncrementingSequence.sample");

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

bool do_test(int k, vector<int> A, string __expected) {
    time_t startClock = clock();
    IncrementingSequence *instance = new IncrementingSequence();
    string __result = instance->canItBeDone(k, A);
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
        int k;
        from_stream(k);
        vector<int> A;
        from_stream(A);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, A, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506818543;
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
        cout << "IncrementingSequence (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
