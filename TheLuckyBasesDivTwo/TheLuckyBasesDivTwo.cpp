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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/17/2018
 
 9:43-10:17 analysis
 10:39 (404.26 pt), 1WA
 10:41 ACC
 
 If n=4 or n=7, Any B>=n is lucky bases. Thus res = -1
 Otherwise, we can look at B s.t. B<n. B!=n because 1 is not a lucky number.
 Once B is determined, we can solve decision problem if B is lucky base in O(log(B,n)).
 However there are at most 10^12 B. It doesn't work.
 Thus we need to "search" lucky base B.
 
 Digit `d` is 4 or 7. 4 or 7 should show up for B^0.
 So n-4 (=n-4*B^0) or n-7 (=n-7*B^0) should be multiple of B.
 From highly composite number, we can do trial division of n-4 or n-7.
 It's possible to compute in O(√n). Also there are at most 4096 divisors in [1..10^12].
 Once candidate of B is found, we can keep computing below:
 
 f(n,B) = B>4&&(n-4)%B==0?f((n-4)/B,B):0 + B>7&&(n-7)%B==0?f((n-7)/B,B):0
 f(4,B) = f(7,B) = 1
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+510
 - solution #3 is my original algorithm
  - http://d.hatena.ne.jp/kusano_prog/20111015/1318672219
  - http://kmjp.hatenablog.jp/entry/2014/02/14/0930
  - http://area.hateblo.jp/entry/2013/08/20/023434
  - http://purple-jwl.hatenablog.com/entry/20130325/1364185736
 
 Official editorial is searching by upper-bounding B by √n
 
 We look at number of digits from 1 in ascendent order.
 
 1) |D|=1
 
 In this case D={4} or {7}. As discussed above, res = -1
 
 2) |D|=2
 
 In this case we have only 4 options: D={4,4},{4,7},{7,4},{7,7}
 `n` is represented as below:
 
  n = a+b*B => B = (n-a)/b, (n-a)%b=0, B>max(a,b)
 
 3) |D|=3
 
 n is represented as below:
 
  n = a*B^2+b*B+c

 We want to know how `B` is upper-bounded. In the worst case, a=4,b=0,c=0. Thus..
 
  4*B^2 <= n => B <= √n/2 <= √n
 
 If |D| increases, B is getting smaller. So brute-forcing B in [1..√n] should cover |D|>3 cases as well.
 B^x is strong constraint. This solution is utilizing it.
 
 Summary:
  - Approach was good though, it's still slow. I want to complete analysis in 15 mins.
  - I analyzed based on formula. However I missed some of constraints in the code 👎
   - 4<B or 7<B, B should be consistent
   - once determined in the first step
   - Write down constraints clearly in the paper in analysis process
  - Official editorial is suggesting that search of exponential of a value is easily upper-bounded by √B
   - It's a good insight to solve other problems
 
 */

class TheLuckyBasesDivTwo {
public:
  LL ok(LL n, LL B) {
    while(n) {
      LL x=n%B;
      if(x!=4&&x!=7) return false;
      n/=B;
    }
    return true;
  }
  long long find(long long n) {
    if(n==4LL||n==7LL) return -1;
    LL res=0;
    int D[2]={4,7};
    REP(i,2)REP(j,2) {
      LL a=D[i],b=D[j];
      if((n-a)%b!=0) continue;
      LL B=(n-a)/b;
      if(B<=max(a,b)) continue;
      ++res;
    }
    
    for(LL B=2; B*B<=n; ++B) res+=ok(n,B);
    
    return res;
  }
};

class TheLuckyBasesDivTwo_org {
  public:
  LL f(LL n, LL B) {
    if((B>4&&n==4)||(B>7&&n==7)) return 1LL;
    LL res=0;
    vector<LL> ns;
    if(B>4) ns.push_back(n-4LL);
    if(B>7) ns.push_back(n-7LL);
    FORR(nn,ns) {
      if(nn%B==0) res+=f(nn/B,B);
    }
    dump3(n,B,res);
    dumpAR(ns);
//    dump4(n,B,ns[0],ns[1]);
//    dump3(n,B,res);
    return res;
  }
  long long find(long long n) {
    if(n==4LL||n==7LL) return -1;
    LL res=0;
    LL ns[2]={n-4LL,n-7LL};
    REP(i,2) {
      LL n=ns[i];
      for(LL p=2; p*p<=n; ++p) if(n%p==0) {
        LL d=n/p;
        res+=f(n/d,d);
        if(p*p!=n) res+=f(n/p,p);
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("TheLuckyBasesDivTwo.sample");

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

bool do_test(long long n, long long __expected) {
    time_t startClock = clock();
    TheLuckyBasesDivTwo *instance = new TheLuckyBasesDivTwo();
    long long __result = instance->find(n);
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
        long long n;
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
        int T = time(NULL) - 1521218594;
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
        cout << "TheLuckyBasesDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
