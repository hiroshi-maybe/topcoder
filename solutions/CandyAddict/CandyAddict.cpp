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
 
 9/25/2017
 
 9:51-10:25 analysis
 10:36-10:50 pause
 10:51-11:17 implemented. but 15 secs in sample 2
 18:00-18:30 give up
 
 19:26-19:50,21:50-24:15 read editorials and copied @vexorian's editorial solution.
  - http://kmjp.hatenablog.jp/entry/2014/08/20/1030
  - http://apps.topcoder.com/wiki/display/tc/SRM+629
  - http://codeforces.com/blog/entry/13361#comment-182664
 
 this explains about x<2*y case.
 the same code works for x>=2*y case though, I couldn't understand why it works.

 suppose Alice has m money and c (=(m+x)/y) candy.
 money increases (x-y) every day.
 when it reaches y-1, Alice can buy c+1 candy. if it takes p days, then...
 p*(x-y) = y-1
 => p = (y-1)/(x-y)
 
 Alice buys candy when she eats all. It takes c days for it.
 Now we want to know how many cycles of c equals to p days.
 t*c = p = (y-1)/(x-y)
 t = (y-1)/c*(x-y)
 
 d -= c*steps
 m += c*(x-y) * t
 
 This is the step that we can skip computation.
 We continue this process until z<=c becomes true
 
 key:
  - analysis of when bought candy increases
 
 summary:
  - I figured out solution when x >> y though, I couldn't solve x ≈ y case like sample 2
  - this problem is too difficult for my current level
 
 */

class CandyAddict {
public:
  
  LL f(LL x, LL y, LL d) {
    if (x == y) { //special case, always the same
      return 0;
    }
    
    LL m = 0;
    while(d>0) {
      LL c = (m+x)/y; //number of candy bought
      if (d<=c) { // d reaches 0 before current candies are consumed
        m = (m+x)%y+x*(d-1);
        break;
      }
      
      // the maximum bound before t changes:
      LL m_inc = c*(x-y); // the increment every c steps
      // the number of groups of t steps to skip:
      LL steps = min((y-1)/m_inc, (d-c+1)/c);
      steps = max(1LL,steps);
      d -= c*steps;
      m += m_inc * steps;
    }
    return m;
  }
  
  vector<long long> solve(vector<int> X, vector<int> Y, vector<int> Z) {
    int N=SZ(X);
    vector<LL> res;
    REP(i,N) res.push_back(f(X[i],Y[i],Z[i]));
    return res;
  }
};


class CandyAddict_org {
  public:
  
  LL f(LL X, LL Y, LL D) {
    LL m=X%Y;
    LL c=X/Y-1;
    LL d=1;
    dump3(X,Y,D);
    while(d+c+1<=D) {
      dump4(m,d,c,d+c+1);
      assert(d>0&&m>=0&&c>=0);
      LL days=c+1;
      m=m+days*X;
      c=m/Y-1;
      m%=Y;
      d+=days;
//      dump(days);
    }
    
    // D<d+c
    return m+(D-d)*X;
  }
  
  vector<long long> solve(vector<int> X, vector<int> Y, vector<int> Z) {
    int N=SZ(X);
    vector<LL> res;
    REP(i,N) res.push_back(f(X[i],Y[i],Z[i]));
    return res;
  }
};

// CUT begin
ifstream data("CandyAddict.sample");

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

bool do_test(vector<int> X, vector<int> Y, vector<int> Z, vector<long long> __expected) {
    time_t startClock = clock();
    CandyAddict *instance = new CandyAddict();
    vector<long long> __result = instance->solve(X, Y, Z);
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
        vector<int> X;
        from_stream(X);
        vector<int> Y;
        from_stream(Y);
        vector<int> Z;
        from_stream(Z);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, Y, Z, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506358307;
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
        cout << "CandyAddict (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
