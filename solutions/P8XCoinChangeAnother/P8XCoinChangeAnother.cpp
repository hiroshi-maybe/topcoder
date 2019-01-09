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
 
 2/22/2018
 
 9:40-10:06 analysis
 10:07-10:12 Implement and ACC (523.79 pt)
 
 Firstly coin just shows binary representation of number.
 That means that theoretically any number can be represented by coins.
 
 We want to satisfy below condition:
 a) ∑ { 2^i*res[i] : i=0..N-1 } = S
 b) ∑ { res[i] : i=0..N-1 } = C
 c) res is lexicographically minimal
 
 Minimum count of coin to make S `minc` can be obtained by keep deviding S with 2^i in descendent order.
 Also this is lexicographically minimal for `minc` coins.
 
 If given `C` < `minc`, we cannot make S.
 Otherwise, we can increase use of coin `c` by 1 by following operation.
 Let's remove coin of 2^i and add coin of 2^(i-1). Coin increases by 1 because 2^(i-1)*2 = 2^i*1.
 We can proceed this operation until `c` reaches `C`.
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+527
  - http://kmjp.hatenablog.jp/entry/2014/01/10/0930
  - http://area.hateblo.jp/entry/2013/09/25/005347
  - http://d.hatena.ne.jp/kusano_prog/20111220/1324330958
   - solving system of equations

 Summary:
  - Figuring out how to make `minc` quickly was good
  - In order to make lexicographically minimal sequence, keep adjusting from least significant scale is one of the best practice.
    - https://github.com/k-ori/topcoder/blob/master/StrIIRec/StrIIRec.cpp
 
 */
class P8XCoinChangeAnother {
  public:
  vector<long long> solve(int N, long long S, long long C) {
    vector<LL> res(N,0);
    for(int i=N-1; i>=0; --i) {
      LL a=S/(1LL<<i);
      res[i]=a;
      S%=(1LL<<i);
    }
    LL minc=accumulate(res.begin(),res.end(),0LL);
    if(minc>C) return {};
    
    LL rem=C-minc;
    for(int i=N-1; i>0&&rem>0; --i) {
      LL x=min(res[i],rem);
      res[i]-=x;
      res[i-1]+=2LL*x;
      rem-=x;
    }
    return rem==0?res:vector<LL>();
  }
};

// CUT begin
ifstream data("P8XCoinChangeAnother.sample");

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

bool do_test(int N, long long coins_sum, long long coins_count, vector<long long> __expected) {
    time_t startClock = clock();
    P8XCoinChangeAnother *instance = new P8XCoinChangeAnother();
    vector<long long> __result = instance->solve(N, coins_sum, coins_count);
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
        int N;
        from_stream(N);
        long long coins_sum;
        from_stream(coins_sum);
        long long coins_count;
        from_stream(coins_count);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, coins_sum, coins_count, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519321248;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "P8XCoinChangeAnother (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
