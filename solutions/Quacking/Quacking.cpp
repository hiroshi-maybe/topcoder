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
 
 7/27/2017
 
 8:19-8:37 (366.38 pt)
 18:15-18:20 failed system test. found a bug immediately and re-submitted and passed.
 
 19:54- read editorials
 
 Count number of states instead of my queue solution
 - https://apps.topcoder.com/wiki/display/tc/SRM+687
 - http://pekempey.hatenablog.com/entry/2016/04/08/185137

 21:58-22:06 add solution with array
 
 Key
 - manage finite state transitions and count up
 
 Summary
 - similar to "how many meeting rooms?" problem
 - kind of max flow of linear graph?
 - use of deque in original solution is not scalable for large numbers. It's too many states to remember
  - always think to minimize states. otherwise it's hard to solve DP solutions.
  - think about what you want. In this case we are interested in number of intermittent items. It's straightforward to keep only count in this problem.
 - Even if it's not hard question, solve problem in efficient and more scalable way. Then it works for harder problems too.
 
 */

class Quacking {
public:
  int quack(string s) {
    int a[5]={0};
    
    int res=0;
    FORR(c,s) {
      if(c=='q') ++a[0];
      if(c=='u') --a[0], ++a[1];
      if(c=='a') --a[1], ++a[2];
      if(c=='c') --a[2], ++a[3];
      if(c=='k') --a[3];
      
      res=max(res, accumulate(a,a+5,0));
      int minn = *min_element(a,a+5);
      if (minn<0) return -1;
    }
    
    int maxn = *max_element(a,a+5);
    if(maxn>0) return -1;
    else return res;
  }
};

class Quacking_org {
  public:
  int quack(string s) {
    int res=0;
    deque<char> Q;
    FORR(c,s) {
      if(c=='q') {
        Q.push_back(c);
      } else {
        bool ok=false;
        REP(i,SZ(Q)) {
          char& x=Q[i];
          if(c=='u'&&x=='q') {
            x='u';
            ok=true;
            break;
          } else if(c=='a'&&x=='u') {
            x='a';
            ok=true;
            break;
          } else if(c=='c'&&x=='a') {
            x='c';
            ok=true;
            break;
          } else if(c=='k'&&x=='c'&&i==0) {
            Q.pop_front();
            ok=true;
          }
        }
        if(!ok) return -1;
      }
      res = max(res, SZ(Q));
    }
    return Q.empty() ? res : -1;
  }
};

// CUT begin
ifstream data("Quacking.sample");

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

bool do_test(string s, int __expected) {
    time_t startClock = clock();
    Quacking *instance = new Quacking();
    int __result = instance->quack(s);
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
        string s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501168731;
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
        cout << "Quacking (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
