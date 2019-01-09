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
 
 3/7/2018
 
 8:54-9:48 ACC (206.41 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+515
  - http://d.hatena.ne.jp/kusano_prog/20110820/1313867955
  - http://kg86.hatenablog.com/entry/20130708/1373302780
  - http://d.hatena.ne.jp/nise_nabe/20110822/1313968941
  - http://programming-tatuyan.blogspot.com/2011/08/topcoder-srm-515div2.html

 23:20-23:35 add more efficient solution
 
 Summary:
 - Meaning of 30 degree mark was not clear for me. I wasted a lot of time.
 
 */

class RotatedClock {
public:
  string getEarliest(int hh, int mh) {
    for(int x=0; x<360; x+=30) {
      int d=(360+hh-x)%360;
      int t=2*d;
      int mhmh=(x+(t%60)*6)%360;
      if(mhmh==mh) {
        int h=t/60,m=t%60;
        string hs=to_string(t/60);
        if(h<10) hs="0"+hs;
        string ms=to_string(m);
        if(m<10) ms="0"+ms;
        return hs+":"+ms;
      }
    }
    return "";
  }
};

class RotatedClock_org {
  public:
  string getEarliest(int hh, int mh) {
    REPE(t,720) REP(x,360) if(t%2==0&&x%30==0) {
      int a=(t/2+x)%360,b=(6*(t%60)+x)%360;
      if(a==hh&&b==mh) {
        dump4(t,x,a,b);
        
        int h=t/60,m=t%60;
        string hs=to_string(t/60);
        if(h<10) hs="0"+hs;
        string ms=to_string(m);
        if(m<10) ms="0"+ms;
        return hs+":"+ms;
      }
    }
    return "";
  }
};

// CUT begin
ifstream data("RotatedClock.sample");

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

bool do_test(int hourHand, int minuteHand, string __expected) {
    time_t startClock = clock();
    RotatedClock *instance = new RotatedClock();
    string __result = instance->getEarliest(hourHand, minuteHand);
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
        int hourHand;
        from_stream(hourHand);
        int minuteHand;
        from_stream(minuteHand);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(hourHand, minuteHand, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520441675;
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
        cout << "RotatedClock (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
