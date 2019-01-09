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
 
 10/21/2017
 
 14:00-14:19 system test passed after 1WA (361.53 pt)
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2014/01/31/0900
  - http://torus711.hatenablog.com/entry/20140130/p1
  - https://apps.topcoder.com/wiki/display/tc/SRM+606
 
 submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=320336&rd=15839&pm=12975&cr=22777893
  - https://community.topcoder.com/stat?c=problem_solution&rm=320395&rd=15839&pm=12975&cr=23295835
  - https://community.topcoder.com/stat?c=problem_solution&rm=320394&rd=15839&pm=12975&cr=23027999
 
 */
class EllysNumberGuessing {
  public:
  int getNumber(vector<int> Q, vector<int> A) {
    int N=SZ(Q);
//    dump(N);
    vector<vector<int>> X(N);
    REP(i,N) {
//      dump3(i,Q[i],A[i]);
      int x1=Q[i]-A[i],x2=Q[i]+A[i];
//      dump3(i,x1,x2);
      VI xx={x1,x2};
      FORR(x,xx) if(1<=x&&x<=1e9) X[i].push_back(x);
//      dumpAR(X[i]);
      if(X[i].empty()) return -2;
      assert(X[i].size());
    }
//    dumpAR(X[0]);
    SETI S;
    FORR(x, X[0]) {
      bool ok=true;
      FOR(i,1,N) {
        ok&=count(X[i].begin(),X[i].end(),x)!=0;
      }
//      dump2(x,ok);
      if(ok) S.emplace(x);
    }
    
    if(SZ(S)==2) return -1;
    if(SZ(S)==1) return *S.begin();
    return -2;
  }
};

// CUT begin
ifstream data("EllysNumberGuessing.sample");

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

bool do_test(vector<int> guesses, vector<int> answers, int __expected) {
    time_t startClock = clock();
    EllysNumberGuessing *instance = new EllysNumberGuessing();
    int __result = instance->getNumber(guesses, answers);
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
        vector<int> guesses;
        from_stream(guesses);
        vector<int> answers;
        from_stream(answers);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(guesses, answers, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508619618;
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
        cout << "EllysNumberGuessing (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
