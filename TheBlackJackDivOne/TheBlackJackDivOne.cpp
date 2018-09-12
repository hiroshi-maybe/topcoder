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
 
 15:50-16:16 analysis
 16:29 AC (122.00 pt)
 
 16:45 add solution with recurrence relation of expectation
 
 */

class TheBlackJackDivOne {
public:
  int cnt[12]={0,0,4,4,4,4,4,4,4,4,16,4}; // 2,3,...,10,11
  
  double f(int score, int tot) {
    double res=0;
    if(score>=21) return res;
    REP(i,12) if(cnt[i]) {
      double p=1.0*cnt[i]/tot;
      cnt[i]--;
      res+=p*(1+f(score+i,tot-1));
      cnt[i]++;
    }
    return res;
  }
  
  double expected(vector<string> cards) {
    int score=0;
    REP(i,SZ(cards)) {
      char c=cards[i][0];
      if(isdigit(c)) {
        score+=c-'0';
        cnt[c-'0']--;
      } else if(c=='T'||c=='J'||c=='Q'||c=='K') {
        score+=10;
        cnt[10]--;
      } else {
        score+=11;
        cnt[11]--;
      }
    }
    int tot=0;
    REP(i,12) tot+=cnt[i];
    double res=0.0;
    res+=f(score,tot);
    return res;
  }
};

class TheBlackJackDivOne_org {
  public:
  double res=0;
  int cnt[10]={4,4,4,4,4,4,4,4,16,4}; // 2,3,...,10,11
  
  void dfs(int score, int tot, double p, int tr) {
    if(score>=21) {
      res+=tr*p;
      return;
    }
    REP(i,10) if(cnt[i]) {
      cnt[i]--;
      dfs(score+i+2,tot-1,p*(cnt[i]+1)/tot,tr+1);
      cnt[i]++;
    }
  }
  
  double expected(vector<string> cards) {
    int score=0;
    REP(i,SZ(cards)) {
      char c=cards[i][0];
      if(isdigit(c)) {
        score+=c-'0';
        cnt[c-'0'-2]--;
      } else if(c=='T'||c=='J'||c=='Q'||c=='K') {
        score+=10;
        cnt[8]--;
      } else {
        score+=11;
        cnt[9]--;
      }
    }
    int tot=0;
    REP(i,10) tot+=cnt[i];
    dfs(score,tot,1.0, 0);
    return res;
  }
};

// CUT begin
ifstream data("TheBlackJackDivOne.sample");

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

bool do_test(vector<string> cards, double __expected) {
    time_t startClock = clock();
    TheBlackJackDivOne *instance = new TheBlackJackDivOne();
    double __result = instance->expected(cards);
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
        vector<string> cards;
        from_stream(cards);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cards, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536706192;
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
        cout << "TheBlackJackDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
