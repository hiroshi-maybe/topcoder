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
 
 10/10/2018 SRM 739
 
 8:00-9:02 AC
 
 https://www.topcoder.com/blog/single-round-match-739-editorials/
 http://kmjp.hatenablog.jp/entry/2018/10/11/0930
 
 Summary:
  - slow submit due to two mistakes
   - 60*60 != 360 😡
   - I was underestimating <24 hours condition. I switched to brute-force to overcome it.
 
 */

class ForumPostEasy {
  public:
  int time(string s) {
    int h=(s[0]-'0')*10+s[1]-'0';
    int m=(s[3]-'0')*10+s[4]-'0';
    int ss=(s[6]-'0')*10+s[7]-'0';
//    dump3(h,m,ss);
    return 3600*h+60*m+ss;
  }
  II range(string s) {
    if(s=="few seconds ago") return {0,59};
    stringstream ss(s);
    int n; ss>>n;
    string x; ss>>x;
    if(x=="minutes") {
      return {60*n,60*n+59};
    } else {
      return {3600*n,3600*n+59*60+59};
    }
  }
  string format(int x) {
    string sh=to_string(x);
    if(x<10) sh=string(1,'0')+sh;
    return sh;
  }
  string getCurrentTime(vector<string> T, vector<string> S) {
    string res="impossible";
    int N=SZ(T);
    REP(curcur,48*3600) {
      int cur=curcur;
      bool ok=true;
      REP(i,N) {
        int t=time(T[i]);
        if(cur<t) t-=24*3600;
        if(cur-t>=24*3600) t+=24*3600;
        assert(cur-t<24*3600);
        II a=range(S[i]);
//        dump2(a.first,a.second);
        if(t+a.first<=cur&&cur<=t+a.second) continue;
        ok=false;
        break;
      }
      if(ok) {
        if(cur>=24*3600) cur-=24*3600;
        int h=cur/3600; cur%=3600;
        int m=cur/60; cur%=60;
        int s=cur;
        SMIN(res,format(h)+":"+format(m)+":"+format(s));
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("ForumPostEasy.sample");

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

bool do_test(vector<string> exactPostTime, vector<string> showPostTime, string __expected) {
    time_t startClock = clock();
    ForumPostEasy *instance = new ForumPostEasy();
    string __result = instance->getCurrentTime(exactPostTime, showPostTime);
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
        vector<string> exactPostTime;
        from_stream(exactPostTime);
        vector<string> showPostTime;
        from_stream(showPostTime);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(exactPostTime, showPostTime, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539183620;
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
        cout << "ForumPostEasy (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
