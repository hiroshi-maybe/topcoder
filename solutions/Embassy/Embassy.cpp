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
 
 8/31/2018
 
 16:20-17:25 time is up
 
 17:40-18:15, 20:15-20:31 read editorials and add solution
 
 Editorials:
  - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm414
  - https://chngng.blogspot.com/2015/05/srm-414-div1-easy-embassy.html
  - http://topcoder.g.hatena.ne.jp/n4_t/20081222/1230196119
  - http://logfiles.hatenablog.com/entry/20140827/1409108123
 
 Leverage modular arithmetic. There is a cycle of a day.
 Looking at "time" on each day is a point.
 
 Key:
  - One day is a unit of cycles. Look at "time". If cycle is relevant, analyze based on modular arithmetic.
   - Form time MUST contribute to duration time. Additional penalty happens when end time goes beyond open time.
  - Brute force possible start time
 
 Summary:
  - Poor analysis. This problem needs brute-force with start time because we measure time from first submit
  - Even sample is encouraging to brute-force start time 😡
  - Thus I couldn't implement brute-force in time
  - Poor math taste. It took sooooooooooooooooooooooo long time to make formula 😡😡
  - Don't go rush into code. Analyze relation enough to make simple and efficient logic.
  - Simplifying model of computation without greedy trick is very weak point. I should train it too. Don't start coding without simple and clear model.
 
 */

// 16:20-17:25 time is up

class Embassy {
public:
  int visaApplication(vector<int> A, int D, int O) {
    int res=1e9;
    REP(s,D) {
      int sum=0;
      int t=s;
      FORR(a,A) {
        sum+=a;
        t=(t+a)%D;
        if(t>O) sum+=D-t,t=0;
      }
      SMIN(res,sum);
    }
    return res;
  }
};

class Embassy_wrong {
  public:
  int D,O,C;
  int f(VI A,int delta) {
    if(delta>0&&delta+A[0]>O) return 1e9;
    int res=0;
    if(delta<=0) {
      res+=abs(delta);
      A[0]+=delta;
    }
    int i=0,N=SZ(A);
    while(i<N) {
      int o=delta>0&&i==0?O-=delta:O;
      while(i<N&&A[i]<=o&&o>0) res+=A[i],o-=A[i],++i;
      if(i<N) A[i]-=o,res+=o;
      else break;
//      dump4(o,i,A[i],res);
      int d=A[i]/D;
      res+=D*d;
      A[i]-=D*d;
      if(A[i]<=C) {
        res+=C;
        ++i;
      } else {
        A[i]-=C;
      }
    }
    return res;
  }
  int visaApplication(vector<int> A, int D, int O) {
    this->D=D,this->O=O;
    this->C=D-O;
    int res=1e9;
    FORE(x,-A[0],O) {
      SMIN(res,f(A,x));
    }
    return res;
  }
};

// CUT begin
ifstream data("Embassy.sample");

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

bool do_test(vector<int> forms, int dayLength, int openTime, int __expected) {
    time_t startClock = clock();
    Embassy *instance = new Embassy();
    int __result = instance->visaApplication(forms, dayLength, openTime);
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
        vector<int> forms;
        from_stream(forms);
        int dayLength;
        from_stream(dayLength);
        int openTime;
        from_stream(openTime);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(forms, dayLength, openTime, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535757570;
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
        cout << "Embassy (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
