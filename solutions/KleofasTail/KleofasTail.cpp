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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('\n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

/*
 
 11/8/2018
 
 14:40-16:20 give up
 16:40, 17:38-19:21 read editorials and got AC
 
 http://apps.topcoder.com/wiki/display/tc/SRM+546
 
 I figured out binary representation matters early.
 However I completely missed analysis of parity of K.
 Also tons of bugs to count based on prefix.

 I associated digit dp to count keeping <=A.
 Digit dp like solution is over-kill and way too complicated.
 There are some reasons why digit dp is UNNECESSARY
  - The number is at most 1e18. It's possible to do simple integer comparison
  - Condition to be satisfied is only <=A and prefix match. No need to manage complicated condition.
 
 Summary:
  - Look for as simple plan as possible before applying algorithm for more complex problem
  - If number is in range of long long, compare integers directly without using decimal represenataion
 
 */

class KleofasTail_editorial {
public:
  LL K;
  LL f(LL X) {
    LL res=0;
    LL l=K,r=K;
    if(K%2==0) ++r;
    while(l<=X) {
      res+=min(X,r)-l+1;
      l*=2;
      r*=2,r+=1;
    }
    return res;
  }
  
  long long countGoodSequences(long long K, long long A, long long B) {
    this->K=K;
    if(K==0) return B-A+1;
    LL a=f(A-1),b=f(B);
    return b-a;
  }
};

// This solution is wrong because numbers which cover both K and K+1 (K is even) is duplicated
class KleofasTail {
  public:
  VI K;
  LL f(LL AA) {
    if(K.empty()) return AA;
    VI A;
    while(AA>0) A.push_back(AA%2),AA/=2;
    reverse(ALL(A));
    if(SZ(K)>SZ(A)) return 0;
    int c=1;
    REP(i,SZ(K)) {
      if(A[i]<K[i]) {
        c=0;
        break;
      } else if(A[i]>K[i]) {
        c=2;
        break;
      }
    }
    int L=SZ(A)-SZ(K);
    LL res=(1LL<<L)-1;
    LL a=0;
    if(c==1) FOR(i,SZ(K),SZ(A)) {
      a=2LL*a+A[i];
    }
    if(c==1) ++a;
    if(c==2) {
      a=(1LL<<L);
    }
    return res+a;
  }
  
  long long solve(long long KK, long long A, long long B) {
    K={};
    while(KK>0) K.push_back(KK%2),KK/=2;
    reverse(ALL(K));
    LL b=f(B),a=f(A-1);
    dump4(KK,a,b,b-a);
    return b-a;
  }
  
  long long countGoodSequences(long long K, long long A, long long B) {
    if(K==0) return B-A+1;
    LL res=solve(K,A,B);
    if(K%2==0) res+=solve(K+1,A,B);
    return res;
  }
};

// CUT begin
ifstream data("KleofasTail.sample");

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

bool do_test(long long K, long long A, long long B, long long __expected) {
    time_t startClock = clock();
    KleofasTail *instance = new KleofasTail();
    long long __result = instance->countGoodSequences(K, A, B);
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
        long long K;
        from_stream(K);
        long long A;
        from_stream(A);
        long long B;
        from_stream(B);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(K, A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541716780;
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
        cout << "KleofasTail (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
