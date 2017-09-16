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
 
 9/16/2017
 
 8:58-9:55 give up
 
 14:30-14:54 read editorials and add solution
  - http://kmjp.hatenablog.jp/entry/2014/11/29/0900
  - https://chaingng.github.io/post/srm-639-div2-middle---alicegameeasy-/
  - https://ik-fib.com/2014/11/srm639-div2/
  - https://apps.topcoder.com/wiki/display/tc/SRM+639
    - proof of greedy
 
 If X+Y==n*(n*1)/2, there always exists an assignment of X and Y.
 To minimize turn of Alice, we can greedily give larger number to Alice in n,n-1,..,1 order
 
 summary:
  - I figured out X+Y==n*(n*1)/2 condition though, somehow I couldn't figure out how to assign them 👎👎👎👎👎👎👎👎👎👎👎👎👎👎
  - I should have played around examples more
 
 */

class AliceGameEasy {
public:
  long long findMinimumValue(long long X, long long Y) {
    LL n=0;
    for(; ; ++n) {
      LL sum=n*(n+1)/2;
      if(sum>X+Y){
        n=-1;
        break;
      } else if(sum==X+Y) break;
    }
    if(n==-1) return -1;
    int res=0;
    while(X>0) {
      ++res;
      X-=min(X,n);
      --n;
    }
    
    return res;
  }
};

map<pair<LL,LL>,LL> memo;
class AliceGameEasy_tle {
  public:
  const LL Inf = 1e13;
  LL X,Y;
  LL f(LL i, LL x) {
    if(memo.count(make_pair(i,x))) return memo[make_pair(i,x)];
    LL res=Inf;
    LL n1=i%2==0?i/2:i, n2=(i-1)%2==0?(i-1)/2:i-1;
    LL sum=n1*n2;
    LL y=sum-x;
    if(x==X&&y==Y) return 0;
    if(x>X||y>Y) return memo[make_pair(i,x)]=res;
//    dump4(i,sum,x,y);
    return memo[make_pair(i,x)]=min(f(i+1,x),1+f(i+1,x+i));
  }
  long long findMinimumValue(long long x, long long y) {
    memo.clear();
    this->X=x,this->Y=y;
    LL res = f(1,0)>=Inf?-1:f(1,0);
    dump(SZ(memo));
    return res;
  }
};

// CUT begin
ifstream data("AliceGameEasy.sample");

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

bool do_test(long long x, long long y, long long __expected) {
    time_t startClock = clock();
    AliceGameEasy *instance = new AliceGameEasy();
    long long __result = instance->findMinimumValue(x, y);
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
        long long x;
        from_stream(x);
        long long y;
        from_stream(y);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505577505;
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
        cout << "AliceGameEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
