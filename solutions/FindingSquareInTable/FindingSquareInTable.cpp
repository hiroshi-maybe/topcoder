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
 
 9/8/2018
 
 12:06-12:26 analysis
 13:21 WA
 13:27 AC
 
 http://apps.topcoder.com/wiki/display/tc/SRM+434
 
 */
class FindingSquareInTable {
  public:
  
  bool psqr(LL x) {
    LL a=(LL)sqrt(x);
    FORE(dt,-1,1) {
      LL b=a+dt;
      if(b*b==x) return true;
    }
    return false;
  }
  
  unordered_map<int,set<VI>> mkseqs(int N) {
    unordered_map<int,set<VI>> res;
    FORE(d,1,9)REP(c,N) {
      VI X; for(int i=c; i<N; i+=d) X.push_back(i);
      REP(i,SZ(X)) FORE(j,i+1,SZ(X)) {
        VI Y;
        FOR(k,i,j) Y.push_back(X[k]);
        if(res[SZ(Y)].count(Y)) continue;
        res[SZ(Y)].emplace(Y);
        reverse(Y.begin(),Y.end());
        res[SZ(Y)].emplace(Y);
      }
    }
    return res;
  }
  
  LL f(unordered_map<int,set<VI>> &M1, unordered_map<int,set<VI>> &M2, int l1, int l2, bool inv) {
    int p=l2/l1;
    LL res=-1;
    FORR(A,M1[l1])FORR(B,M2[l2]) {
      assert(SZ(A)==l1&&SZ(B)==l2);
      LL n=0;
      REP(j,l2) {
        int x=B[j],y=A[j/p];
        if(inv) n=10LL*n+(T[x][y]-'0');
        else n=10LL*n+(T[y][x]-'0');
      }
      if(psqr(n)) SMAX(res,n);
    }
    return res;
  }
  vector<string> T;
  int findMaximalSquare(vector<string> T) {
    this->T=T;
    int N=SZ(T),M=SZ(T[0]);
    LL res=-1;

    unordered_map<int,set<VI>> M1=mkseqs(N),M2=mkseqs(M);
    FORE(l1,1,9) FORE(l2,1,9) if((l1<=l2)&&(l2%l1==0)) {
      if(l1!=l2&&l1!=1) continue;
      SMAX(res,f(M1,M2,l1,l2,0));
      SMAX(res,f(M2,M1,l1,l2,1));
    }
    return res;
  }
};

// CUT begin
ifstream data("FindingSquareInTable.sample");

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

bool do_test(vector<string> table, int __expected) {
    time_t startClock = clock();
    FindingSquareInTable *instance = new FindingSquareInTable();
    int __result = instance->findMaximalSquare(table);
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
        vector<string> table;
        from_stream(table);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(table, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536433509;
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
        cout << "FindingSquareInTable (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
