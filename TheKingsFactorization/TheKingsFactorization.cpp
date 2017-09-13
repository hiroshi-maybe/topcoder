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
 
 9/12/2017
 
 8:19-8:50 system test failed by TLE (277.33 pt)
 20:07-20:42 give up
 
 20:43-20:46,22:15-22:24 read editorial and system test passed
  - 10^6 upper bound
    - https://apps.topcoder.com/wiki/display/tc/SRM+643
    - https://ik-fib.com/2014/12/srm643-div2/
    - http://tatsyblog.sakura.ne.jp/wordpress/contests/topcoder/749/
    - http://torus711.hatenablog.com/entry/20141228/1419779429
    - http://topcoder.g.hatena.ne.jp/kuuso1/20141228/1419797270
    - http://hamko.hatenadiary.jp/entry/2017/02/13/142226
 
  - find primes between p[i] and p[i+1]
  - http://kmjp.hatenablog.jp/entry/2014/12/28/0900
  - http://kenkoooo.hatenablog.com/entry/2015/04/25/121518
 
 ////// 10^6 upper bound
 
 we have two patterns
 1. M is even
 2. M is odd
 
 1. M is even
 
 res = { P[0],?,P[1],?,..,p[N-2],x,p[N-1],y }
 
 We want to know x and y. If we found x, we would know y by dividing ∏ {p:res[i], i=0..M-2}.
 ∏ {p:p∈res} <= x*p[N-1]*y <= n <= 10^18
 
 x<=p[N-1]<=y. so x*x*x <= x*p[N-1]*y <= 10^18 => x<=3√n = 10^6
 this means that we can find x in [2..10^6]
 
 2. M is odd
 
 res = { P[0],?,P[1],?,..,p[N-2],x,p[N-1] }
 
 In similar discussion, p[N-2]*x*p[N-1] <= 10^18 => p[N-2]<=x<=10^6.
 By iterating [2..10^6], such x can be found as well.

 ////// find primes between p[i] and p[i+1]
 
 we are interested in x s.t. p[i]<=x<=p[i+1]
 x*p[i+1]<=n should always hold.
 if x*p[i+1]>n => we never have prime in current range.
 remaining n should be the largest prime.
 
 key:
  - O(√N) < 10^9 hits TLE for a case like 2*{very large prime number}
  - we know the 2nd largest prime by input
  - now we want to find 3rd largest prime which can be found in [1..10^6]
 
 summary:
  - trapped by corner case of {92233292289161182, {2LL}}
  - I tried to find primes between P[i] and P[i+1] though, in stuck
  - analysis of largest prime was a key. couldn't figure out it in analysis
  - search is bottle-necked by large range to find larger primes. I should have focused on it.
 
 */

// 10^6 upper bound solution
class TheKingsFactorization_x {
public:
  vector<long long> getVector(long long n, vector<long long> P) {
    FORR(p,P) n/=p;
    vector<LL> res=P;
    for(LL p=2LL; p<=1000000LL; ++p) {
      while(n%p==0) res.push_back(p),n/=p;
    }
    if(n>1) res.push_back(n);
    sort(res.begin(),res.end());
    return res;
  }
};

// @kmjp's solution
class TheKingsFactorization {
public:
  vector<long long> getVector(long long n, vector<long long> P) {
    FORR(p,P) n/=p;
    vector<LL> res=P;
    REP(i,SZ(P)-1) {
      for(LL p=P[i];p<=P[i+1]; ++p) {
        if(n%p==0) {
          res.push_back(p);
          n/=p;
          break;
        }
        if(n/p<P[i+1]){
          dump2(i,SZ(P));
          assert(i==SZ(P)-2);
          break;
        }
      }
    }

    if(n>1) res.push_back(n);
    sort(res.begin(),res.end());
    return res;
  }
};

// TLE for input {92233292289161182, {2LL}}
class TheKingsFactorization_TLE {
  public:
  vector<long long> getVector(long long n, vector<long long> P) {
    FORR(p,P) n/=p;
    vector<LL> res;
    for(LL p=2;p*p<=n; ++p) {
      while(n%p==0) {
        res.push_back(p);
        n/=p;
      }
    }
    if(n>1) res.push_back(n);
    FORR(p,P) res.push_back(p);
    sort(res.begin(),res.end());
    return res;
  }
};

// CUT begin
ifstream data("TheKingsFactorization.sample");

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

bool do_test(long long N, vector<long long> primes, vector<long long> __expected) {
    time_t startClock = clock();
    TheKingsFactorization *instance = new TheKingsFactorization();
    vector<long long> __result = instance->getVector(N, primes);
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
        long long N;
        from_stream(N);
        vector<long long> primes;
        from_stream(primes);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, primes, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505229558;
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
        cout << "TheKingsFactorization (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
