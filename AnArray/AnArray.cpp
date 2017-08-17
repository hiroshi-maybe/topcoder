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

void test() {
  map<int,int> test;
  FOR(n,1,1000000) {
    int x=0;
    for(int p=1; p*p<=n; ++p) {
      if(n%p==0) x+=2;
      if(p*p==n) --x;
    }
    ++test[x];
    if(x==240) dump(n);
  }
  FORR(kvp,test) dump2(kvp.first,kvp.second);
}

/**
 
 8/16/2017
 
 9:38-9:45 pause
 17:26-18:20 design done
 18:24 passed samples and systemt test
 
 suppose q is at `j` index.
  res += miss[x] if x|A[j]
  miss[y]++ if y=K/GCD(A[i]*A[j], K) i=0..<j
 
 iterate `j` from 1 to N
 
 18:36-19:00,22:00-30 read editorials
  - http://kmjp.hatenablog.jp/entry/2015/09/17/1030
  - http://apps.topcoder.com/wiki/display/tc/SRM+668
 
 22:30-22:41 add memoized DP solution of official editorial
  f(i,p,t) = f(i+1,p,t)+f(i+1,p/gcd(A[i],p),t-1)
  f(_,_,0) = p==1
  f(N,_,_) = 0
 
 Key:
  - find max number of divisors of K to estimate complexity
    - highly composite number
      - https://en.wikipedia.org/wiki/Highly_composite_number
  - missing number can be found by K/GCD(K,X*Y)
 
 Submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=327047&rd=16548&pm=13994&cr=23287458
    - same recurrence relation with official editorial
    - bottom-up dp
  - https://community.topcoder.com/stat?c=problem_solution&rm=327037&rd=16548&pm=13994&cr=23332137
    - pre-compute
 
 Summary:
  - solved 👍
    - great to analyze that divisor of K is maximum 240
    - nice to find missing number by K/GCD(K,X*Y)
    - nice to count up missing number and combination at the same time in single iteration
  - analysis progressed after looking at samples
    - should look at samples earlier
  - wish noticed keys earlier
 
 */

// O(D*N^2*lg X) time, D: number of divisor of K, X: greatest number of multiple of two numbers
class AnArray_org {
  public:
  int solveProblem(vector<int> A, int K) {
    int N=SZ(A);
    MAPII miss;
    int res=0;
    FOR(j,1,N) {
      int n=A[j];
      FORR(kvp,miss) if(n%kvp.first==0) res+=kvp.second;
      REP(i,j) {
        LL y=(LL)K/__gcd(1LL*A[i]*A[j],1LL*K);
        ++miss[(int)y];
      }
    }
    return res;
  }
};

// O(4*D*N*lg X) time
MAPII memo[2001][4];
class AnArray {
public:
  int N;
  VI A;
  int f(int i, int p, int t) {
    if(t==0) return p==1;
    if(i==N) return 0;
    if(memo[i][t].find(p)!=memo[i][t].end()) return memo[i][t][p];
    
    int res=0;
    res += f(i+1,p,t);
    res += f(i+1,p/__gcd(A[i],p),t-1);
    
    return memo[i][t][p]=res;
  }
  int solveProblem(vector<int> _A, int K) {
    A=_A; N=SZ(A);
    REP(i,N) REP(j,4) memo[i][j].clear();
    return f(0,K,3);
  }
};

// CUT begin
ifstream data("AnArray.sample");

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

bool do_test(vector<int> A, int K, int __expected) {
    time_t startClock = clock();
    AnArray *instance = new AnArray();
    int __result = instance->solveProblem(A, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502901513;
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
        cout << "AnArray (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
