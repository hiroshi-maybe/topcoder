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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/23/2017
 
 17:15-17:50 give up
 
 24:05 read editorial
 - http://kmjp.hatenablog.jp/entry/2016/06/07/0930
 
 s(x)<=25 in n=0..10^9. Since s(x) is small, if we could figure out number of each s(x)∈{1..25}, we would not need to iterate from 1 to n. That reduces runtime significantly
 
 7/25/2017
 
 18:00-19:25 read editorials
 - http://pekempey.hatenablog.com/entry/2016/05/31/051622
 - https://apps.topcoder.com/wiki/display/tc/SRM+691
 
 Suppose L=LCM(1,2,..,a-1,a+1,..,b-1)
 A={n, L|n}
 B={n, a!|n} a does NOT divide n
 C={n, b!|n} b does NOT divide n
 
 f(a,b,N) = |A - (A∩B) - (A∩C) + (A∩B∩C)| *Inclusion-exclusion principle
 res = ∑ { ∑{ k2*f(k1,k2,n), k2=a+1,..,b-1 }, k1=1,..,a-1 }
 
 23:55-24:17 add solution
 
 Key
 - not divided by n1 and n2 => divisible by 1,2,..n1-1,n1+1,..,n2-1 => divisible by LCM(1,2,..n1-1,n1+1,..,n2-1)
  - Since it's a large number, s(x) is small
  - Divisibility => Count multiple => LCM
   - count up against s(x) rather than n(=1..10^9)
 
 */

LL lcm(LL a, LL b) { return a*b/__gcd(a,b); }

class Undiv2 {
  public:
  long long getsum(int n) {
    LL res=0;
    FOR(a,1,31) FOR(b,a+1,31) {
      LL L=1;
      FOR(x,1,b) if(x!=a) L=lcm(L,x);
      
      LL f = n/L - n/lcm(L,a) - n/lcm(L,b) + n/lcm(L,lcm(a,b));
      res += f*b;
    }
    return res;
  }
};

// CUT begin
ifstream data("Undiv2.sample");

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

bool do_test(int n, long long __expected) {
    time_t startClock = clock();
    Undiv2 *instance = new Undiv2();
    long long __result = instance->getsum(n);
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
        int n;
        from_stream(n);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500855341;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Undiv2 (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
