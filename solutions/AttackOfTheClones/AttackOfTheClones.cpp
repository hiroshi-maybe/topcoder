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
 
 8/5/2017
 
 9:11-9:55 give up
 
 15:30-16:00 read editorials
 - https://apps.topcoder.com/wiki/display/tc/SRM+678
 - http://kmjp.hatenablog.jp/entry/2016/01/14/0900
 - https://topcoder.g.hatena.ne.jp/yambe2002/20160120/1453264633

 17:45-18:15 prove and add solution
 
 Proof:
 
 If at some moment shirt x is at p and it should be at q (>=p) at the last week, we need at most 1 week. So we can ignore such a shift if some shirt is behind. In next iteration, shift x can be restored to be at q.
 
 Say s[i] = x is cost which shows how behind shirt i is. In one iteration, s[i] decreases by 1. So by x iterations, s[i] eventually reaches 0. Suppose we have k shirts which are behind and sum of those costs is X. Then every iteration, X decreases by k until cost of some shirt reaches 0. That means it takes max(s[i]) weeks to make X zero.
 
 Summary:
 - proof! proof! proof!
 - figured out that shirt at x can be x-1 next week and guessed that result is at most N though, had no proof
  - find cost which monotonically decreases. If such pattern is found, we can prove that it eventually reaches zero.
 */

class AttackOfTheClones {
public:
  int count(vector<int> S, vector<int> D) {
    int N=SZ(S);
    int res=0;
    
    REP(i,N) REP(j,N) if(S[i]==D[j]) {
      res = max(res, max(i-j,0));
    }
    
    return res+1;
  }
};

/*
int X[2501][2501];
class AttackOfTheClones {
  public:
  int count(vector<int> S, vector<int> D) {
    int N=SZ(S);
    int res=1;
    while(S!=D) {
      memset(X,0,sizeof X);
      REP(i,N) X[0][i]=S[i];
      
    }
    return res;
  }
};*/

// CUT begin
ifstream data("AttackOfTheClones.sample");

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

bool do_test(vector<int> firstWeek, vector<int> lastWeek, int __expected) {
    time_t startClock = clock();
    AttackOfTheClones *instance = new AttackOfTheClones();
    int __result = instance->count(firstWeek, lastWeek);
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
        vector<int> firstWeek;
        from_stream(firstWeek);
        vector<int> lastWeek;
        from_stream(lastWeek);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(firstWeek, lastWeek, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501949456;
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
        cout << "AttackOfTheClones (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
