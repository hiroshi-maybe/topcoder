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
 
 12/18/2017
 
 13:34-14:13 analysis
 14:14-15:02 time up
 
 17:30-18:30 read editorials and figured out that I was misunderstanding problem
  - http://kmjp.hatenablog.jp/entry/2013/01/30/1000
  - https://apps.topcoder.com/wiki/display/tc/SRM+568
 
 20:25-20:27 add solution
 
 1. Compute expected value until it converges (my verbose original solution):

 Number's relation matters though, actual number does not matter.
 So we can sort cards and group them by same number as `xs`.
 Ex: {1,1,2,2,3,3} => {2,2,2}
 
 Suppose expected value of n remaining i-th number is f(i,n).
 
 f(SZ(xs)-1,_) = 0
 f(i,0) = f(i+1,xs[i+1])
 
 In each state f(i,n), suppose expected value with x times shuffle is f(i,n,x).

 f(i,n) = ∑ { f(i,n,x) : x=0..∞ }
 f(i,n,x) = q^x*p(x+f(i+1,n-1)), p=n/sum, sum=n+∑ { xs[k] : k=i+1..SZ(xs)-1 }, q=1.0-p
 (pull X after x times failure and shuffle)
 
 res = 1 + f(0,xs[0])
 
 We can compute f(i,n,x). Also for very large x, f(i,n) converges.
 I ran x=10^4 so that (49/50)^x ≪ EPS=1e-9
 
 This can be solved by memoized recursion.h in O(10000*N^2) time, N=number of cards.
 
 2. Transform equation to recurrence relation (official editorial):
 
 Suppose expected value for x remaining card is f(n).
 
     f(n) = q*(1+f(n)) + p*f(n-1), p=t/n, t=number of X, q=1.0-p
 <=> f(n) = f(n-1) + p - 1
 
 base case: f(0) = 0
 res = f(N)
 
 23:00-23:28 add solution #2.
 
 Key:
  - Define state, make equation and transform to recurrence relation
  - If value decreases by more trials, we can simulate infinite series by running trials until difference converges under eps
 
 Summary:
  - I was misunderstanding problem
   - ❌ Whenever all the cards of X is pulled, shuffle happens
   - ✅ Shuffle happens when pulles card is not X (For example if card order is [1,2,3], no shuffle happens)
  - Recurrence relation mistake
   - ❌ f(i,n,x) = q^x*(x+p*f(i+1,n-1))
   - ✅ f(i,n,x) = q^x*p*(x+f(i+1,n-1))
  - After fixing above, system test passed
  - Refehresh mind and focus on new problem even though previous problem didn't go well
 
 */

class ShuffleSort {
public:
  int N;
  VI C;
  vector<double> P;
  double f(int n) {
    if(n==0) return 0;
    return f(n-1)+1.0/P[N-n]-1.0;
  }
  
  double shuffle(vector<int> C) {
    sort(C.begin(),C.end());
    this->N=SZ(C);
    this->C=C;
    this->P=vector<double>(N,0.0);
    P[N-1]=1;
    for(int i=N-2; i>=0; --i) {
      double t=C[i]==C[i+1]?P[i+1]+1:1;
      P[i]=t;
    }
    REP(i,N) P[i]/=(N-i);
//    dumpAR(P);
    return 1.0+f(N);
  }
};

// O(N^2) time
// Total number of state by `i` and `n` is upper bounded by ∑ C[i]
// Loop inside `f` is contributing to `N` too
double memo[51][51];
class ShuffleSort_org {
  public:
  VI xs;
  
  double f(int i, int n) {
    if(i==SZ(xs)-1) return 0;
    double &res=memo[i][n];
    if(res>=0) return res;
    if(n==0) return res=/*1+*/f(i+1,xs[i+1]);
    assert(n>0);
    
    int sum=n;
    FOR(j,i+1,SZ(xs)) sum+=xs[j];
    double p=1.0*n/sum,q=1.0-p;
//    assert(p>0);
    
    res=0;
    double qq=1;
    REP(x,10000) {
      res+=qq*p*(1.0*x+f(i,n-1));
      qq*=q;
    }
//    dump3(i,n,res);
    return res;
  }
  
  double shuffle(vector<int> C) {
    MINUS(memo);
    map<int,int> M;
    FORR(n,C) M[n]++;
    FORR(kvp,M) xs.push_back(kvp.second);
//    dumpAR(xs);
    return 1+f(0,xs[0]);
  }
};

// CUT begin
ifstream data("ShuffleSort.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> cards, double __expected) {
    time_t startClock = clock();
    ShuffleSort *instance = new ShuffleSort();
    double __result = instance->shuffle(cards);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> cards;
        from_stream(cards);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cards, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513632873;
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
        cout << "ShuffleSort (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
