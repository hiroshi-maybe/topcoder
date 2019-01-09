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
typedef pair < int,int > II;
typedef tuple < int,int,int > III;

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
 
 7/28/2017
 
 8:44-9:18 passed system test (263.26 pt)
 23:23-23:39 add simplified solution
 
 23:40- read editorials
 - http://pekempey.hatenablog.com/entry/2016/03/29/174017
 - neat implementation using pair to compare right end-point and keep index
 - https://apps.topcoder.com/wiki/display/tc/SRM+686
 
 Key
 - sweep line and greedy
 
 Summary
 - figured out sweep line approach early though, moved line by one rather than per points. It's unnecessarily complex.
 - Don't be in rush. Solve the problem first. Ensure no counter examples. After that, write code.
 - I've not advanced enough to solve medium level problem in rush.
 
 */

class SegmentsAndPoints {
public:
  string isPossible(vector<int> P, vector<int> L, vector<int> R) {
    int N=SZ(P);
    VI used(N,false);
    sort(P.begin(),P.end());
    
    FORR(p,P) {
      II x={1001, -1};
      REP(i,N) if(!used[i]) if(L[i]<=p&&p<=R[i]) {
        x = min(x, {R[i],i});
      }
      if(x.second==-1) return "Impossible";
      used[x.second]=true;
    }
    return "Possible";
  }
};

VI bal[1010];
class SegmentsAndPoints_org {
  public:
  string isPossible(vector<int> p, vector<int> l, vector<int> r) {
    REP(i,1010) bal[i].clear();
    int O=505;
    
    int N=SZ(p);
    vector<III> ivs;
    REP(i,N) ivs.emplace_back(r[i],l[i],i);
    sort(ivs.begin(),ivs.end());
    REP(i,N) {
      for(int k=get<1>(ivs[i]); k<=get<0>(ivs[i]); ++k) bal[k+O].push_back(get<2>(ivs[i]));
    }
    
    MAPII PS;
    FORR(n,p) ++PS[n];
    SETI used;
    for(int n=-500; n<=500; ++n) {
      while(PS[n]>0) {
        int id=-1;
        FORR(x, bal[n+O]) if(used.count(x)==0) {
          id=x;
          break;
        }
        if(id==-1) return "Impossible";
        used.insert(id);
        --PS[n];
      }
    }
      
    return "Possible";
  }
};

// CUT begin
ifstream data("SegmentsAndPoints.sample");

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

bool do_test(vector<int> p, vector<int> l, vector<int> r, string __expected) {
    time_t startClock = clock();
    SegmentsAndPoints *instance = new SegmentsAndPoints();
    string __result = instance->isPossible(p, l, r);
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
        vector<int> p;
        from_stream(p);
        vector<int> l;
        from_stream(l);
        vector<int> r;
        from_stream(r);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(p, l, r, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501256643;
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
        cout << "SegmentsAndPoints (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
