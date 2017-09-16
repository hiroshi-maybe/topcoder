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
 
 9/15/2017
 
 9:26-10:05 pause
 18:15-18:26 time up
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+640
  - http://kmjp.hatenablog.jp/entry/2014/12/12/1130
 
 Suppose we have A[i] and B[j].
 If A[i] ≡ B[j] (mod M), distance(A[i], B[j]) = abs(cnt(A[i])-cnt(B[j]))
 Otherwise distance(A[i], B[j]) = cnt(A[i])+cnt(B[j])
 
 A[i] ≡ B[j] (mod M) => A[i] - B[j] ≡ 0 (mod M)
 
 We can brute-force such M.
 It reduces at least one pair. However we don't know how it affects other numbers.
 Thus we can just try them all. |A| and |B| are small. It's feasible.
 
 18:50-19:30,22:12-22:40 read editorial and add solution
 
 key:
  - modular congruence
  - analyze what kind of `M` reduces distance
  - try all dividers of A[i]-B[j]
    - number of dividers under 10^9 is at most 1344 from highly composit numbers
    - http://wwwhomes.uni-bielefeld.de/achim/highly.txt
  - once M is determined, it's easy to compute distance
 
 summary:
  - we are not sure how M affects other numbers. just brute-force in such a case
  - tried to leverage Chinese Remainder Theorem or pi number though, in stuck
 
 */
class TwoNumberGroupsEasy {
  public:
  VI A,B,NA,NB;
  int res=1e9;
  
  int dist(int M) {
    int res=0;
    MAPII mm; // size of map is upperbounded by SZ(A)+SZ(B)
    REP(i,SZ(A)) mm[A[i]%M]+=NA[i];
    REP(i,SZ(B)) mm[B[i]%M]-=NB[i];
    FORR(kvp,mm) res+=abs(kvp.second);

    return res;
  }
  
  void calc(int M) {
    if(M<=1) return;
    res=min(res,dist(M));
    for(int p=2; p*p<=M; ++p) if(M%p==0) {
      res=min(res,dist(p));
      res=min(res,dist(M/p));
    }
  }
  
  int solve(vector<int> A, vector<int> numA, vector<int> B, vector<int> numB) {
    this->A=A,this->B=B,this->NA=numA,this->NB=numB;
    res=dist(1e9);
    REP(i,SZ(A)) REP(j,SZ(B)) calc(abs(A[i]-B[j]));
    
    return res;
  }
};

// CUT begin
ifstream data("TwoNumberGroupsEasy.sample");

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

bool do_test(vector<int> A, vector<int> numA, vector<int> B, vector<int> numB, int __expected) {
    time_t startClock = clock();
    TwoNumberGroupsEasy *instance = new TwoNumberGroupsEasy();
    int __result = instance->solve(A, numA, B, numB);
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
        vector<int> A;
        from_stream(A);
        vector<int> numA;
        from_stream(numA);
        vector<int> B;
        from_stream(B);
        vector<int> numB;
        from_stream(numB);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, numA, B, numB, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505492774;
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
        cout << "TwoNumberGroupsEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
