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
 
 10/3/2017
 
 8:42-8:57 I found out that I misunderstood problem
 9:13-9:30 pause
 
 17:50-17:55 design
 18:25-18:30 implement and submit. system test passed
 
 anyway we need to merge N-1 times.
 merging smaller ones is always more likely to fit in smaller box.
 greedily pick up merge two smallest boxes works.
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+622
  - http://kmjp.hatenablog.jp/entry/2014/05/31/1100
  - http://torus711.hatenablog.com/entry/20140529/1401377559
 
 summary:
  - I'm wondering why greedy idea didn't come up with me in the morning 🤔
 
 */
class BoxesDiv2 {
public:
  int box(int N) {
    int res=1<<30;
    
    for(int b=30; b>=0; --b) {
      int n=1<<b;
      if(n>=N) res=min(res,n);
    }
    return res;
  }
  
  int findSize(vector<int> C) {
    multiset<int> Q;
    REP(i,SZ(C)) Q.emplace(box(C[i]));

    while(SZ(Q)>1) {
      auto it1=Q.begin(),it2=next(it1);
      int x1=*it1,x2=*it2;
      Q.erase(it1); Q.erase(it2);

      Q.emplace(box(x1+x2));
    }
    return *(Q.begin());
  }
};

class BoxesDiv2_wrong {
  public:
  int box(int N) {
    int res=1<<30;
    
    for(int b=30; b>=0; --b) {
      int n=1<<b;
//      dump2(b,n);
//      xs.push_back(n);
      if(n>=N) res=min(res,n);
//      if(res==60) dump3(res,b,n);
    }
//    if(res==60) dumpAR(xs);
    return res;
  }
  
  int findSize(vector<int> C) {
    int N=SZ(C);
    sort(C.begin(),C.end());
    int cur=box(C[0]);
    FOR(i,1,N) {
      int b2=box(C[i]);
      dump4(C[i],cur,b2,box(cur+b2));
      cur=box(cur+b2);
    }
    return cur;
  }
};

// CUT begin
ifstream data("BoxesDiv2.sample");

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

bool do_test(vector<int> candyCounts, int __expected) {
    time_t startClock = clock();
    BoxesDiv2 *instance = new BoxesDiv2();
    int __result = instance->findSize(candyCounts);
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
        vector<int> candyCounts;
        from_stream(candyCounts);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(candyCounts, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507045351;
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
        cout << "BoxesDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
