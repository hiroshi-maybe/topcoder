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
#include <iomanip>
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
#define dump(x) if(TRACE) { cout <<setprecision(12)<<fixed<< #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout <<setprecision(12)<<fixed<< #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout <<setprecision(12)<<fixed<< #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout <<setprecision(12)<<fixed<< #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 8/30/2018
 
 18:39-18:47 analysis
 19:03 WA (161.91 pt), WA 3,{2,2}, WA {-10, {-8, -7}}
 19:31 give up
 19:57 passed system test after tons of precision errors
 
 Editorials:
  - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm413
   - trying to find rational number
  - http://topcoder.g.hatena.ne.jp/peryaudo/20130926/1380169633
  - https://chngng.blogspot.com/2015/05/srm-413-div1-easy-arithmeticprogression.html
   - precision error
  - http://topcoder.g.hatena.ne.jp/n4_t/20081222/1230196120
 
 Summary:
  - Tons of annoying precision errors
  - Official editorial is trying to find optimal rational number to avoid precision error....
 
 */

// 18:39-18:47 analysis
// 19:03 (161.91 pt)
// 1WA 1,{1}
// 2WA 3,{2,2}
// 3WA {-10, {-8, -7}}
// 19:31 give up
// 19:57 passed system test after tons of precision errors

/*
class ArithmeticProgression {
public:
  int a0,N;
  VI S;
  bool test(double d) {
    double x=a0;
    bool ok=true;
    REP(i,N) {
      x+=d;
      if(floor(x)>S[i]) ok=false;
    }
    return ok;
  }
  
  double minCommonDifference(int a0, vector<int> S) {
    this->N=SZ(S),this->a0=a0,this->S=S;
    if(N==0) return 0.0;
    if(a0>S[0]) return -1.0;
    double bad=S[0]-a0+1,good=S[0]-a0;
    REP(_,1000) {
      double mid=(good+bad)/2.0;
      (test(mid)?good:bad)=mid;
    }
        dump(good);
    //    if(good<0) return -1.0;
    bool ok=true;
    double x=a0;
    REP(i,N) {
      x+=good;
      ok&=floor(x)==S[i];
      //      dump3(i,x,S[i]);
    }
    return ok?good:-1.0;
  }
};*/

const long double eps=1e-10;
class ArithmeticProgression_okorg {
  public:
  int fl(double x) {
    return int(floor(x));
  }
  double minCommonDifference(int a0, vector<int> S) {
    int N=SZ(S);
    if(N==0) return 0.0;
    if(a0>S[0]) return -1.0;
//    long double bad=-1.0,good=1e7;
//    long double good=S[0]-a0,bad=good+1;
    long double bad=S[0]-a0,good=bad+1.0;
//    dump(S[0]-a0+1);
//    REP(_,good) {
    REP(_,128) {
      long double mid=(good+bad)/2.0;
      long double x=a0;
      bool ok=true;
      REP(i,N) {
//        x+=mid;
        double x2=a0+mid*(i+1);
//        dump4(x,x2,fl(x),fl(x2));
//        assert(fl(x)==fl(x2));
        if(fl(x2)<S[i]) ok=false;
      }
      (ok?good:bad)=mid;
    }
//    dump(good);
//    if(good<0) return -1.0;
    bool ok=true;
    long double x=a0;
    REP(i,N) {
//      x+=good;
      double x=a0+(i+1)*good;
      ok&=fl(x)==S[i];
//      dump4(i,x,fl(x),S[i]);
    }
    return ok?good:-1.0;
  }
};

/*
#define MAX 128
#define FOR(i, a, b) for(i = (a); i < (b); ++i)
class ArithmeticProgression_ok3 {
public:
  double minCommonDifference(int a0, vector <int> a)
  {
    int N = SZ(a);
    if(N == 0)
      return 0.0;
    
    if(a[0] < a0)
      return -1.0;
    
    double Min = a[0] - a0;
    double Max = Min + 1.0;
    
    int i, j;
    FOR(i, 0, MAX)
    {
      double Mid = (Min + Max)/2;
      
      FOR(j, 0, N)
      if(floor(a0 + (j + 1)*Mid) < a[j])
        break;
      
      if(j < N)
        Min = Mid;
      else
        Max = Mid;
    }
    
    FOR(i, 0, N)
    if(int(floor(a0 + (i + 1)*Max)) != a[i])
      break;
    
    if(i < N)
      return -1.0;
    
    return Max;
  }
  
  
  
};*/

// system test passes
class ArithmeticProgression_ok {
public:
  double minCommonDifference(int a0, vector<int> seq) {
    double top = 1e20;
    double bottom = 0.0;
    for (int i = 0; i < seq.size(); ++i) {
      double curTop = (double)(seq[i] + 1 - a0) / (i + 1);
      double curBottom = (double)(seq[i] - a0) / (i + 1);
      if (curTop < top) top = curTop;
      if (bottom < curBottom) bottom = curBottom;
      if (top <= bottom) return -1.0;
    }
    return bottom;
  }
};

// by @anta
class ArithmeticProgression_ok2 {
public:
  double minCommonDifference(int a0, vector<int> seq) {
    double l=0,u=1e7;
    int s,none=1;
    REP(_,100) {
//      double m=u/2+l/2;
      double m=(u+l)/2;
      // this is necessary
      //m=floor(m*1e10)/1e10;
//      dump2(m,floor(m*1e10)/1e10);
      s=0;
      REP(i,SZ(seq)) {
        double x=a0+m*(i+1);
        int y=floor(x);
        if(y<seq[i]) {
          s=-1;
        } else if(y>seq[i]) {
          s=1;
        }
      }
      if(s<0) {
        l=m;
      } else if(s>=0) {
        if(s==0)none=0;
        u=m;
      }
    }
    if(none)return -1;
    return l;
  }
};

class ArithmeticProgression {
public:
  double minCommonDifference(int a0, vector <int> seq) {
    // fraction representing 0/1 (minimum permissible value)
    pair <long long, long long> res(0, 1);
    // find d
    for(int i = 0; i < seq.size(); ++i)
      if(res.first * (i + 1) < (seq[i] - a0) * res.second) {
        res.first = seq[i] - a0;
        res.second = i + 1;
      }
    // check whether a solution is possible
    for(int i = 0; i < seq.size(); ++i)
      if(seq[i] != a0 + (i + 1) * res.first / res.second)
        return -1;
    dump2(res.first,res.second);
    return res.first / double(res.second);
  }
};

// CUT begin
ifstream data("ArithmeticProgression.sample");

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

bool do_test(int a0, vector<int> seq, double __expected) {
    time_t startClock = clock();
    ArithmeticProgression *instance = new ArithmeticProgression();
    double __result = instance->minCommonDifference(a0, seq);
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
        int a0;
        from_stream(a0);
        vector<int> seq;
        from_stream(seq);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a0, seq, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535679560;
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
        cout << "ArithmeticProgression (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
