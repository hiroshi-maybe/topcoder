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
typedef pair<int,int> II;

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
 
 8/3/2017
 
 15:42-16:31 (215.93 pt)

 Editorial
 - https://apps.topcoder.com/wiki/display/tc/SRM+680
 - http://pekempey.hatenablog.com/entry/2016/01/29/164457
 - http://ddrer.exblog.jp/25196731/

 21:17-22:38 add editorial solution
 
 two conditions to satisify
 - |x-B[j]|>=d
 - x>=A[i]
 
 Start x by A[i]. If B is sorted, we can iterate A[i] from head to tail.
 If ∀j,abs(x-B[j])>=d is true, x=A[i]. If it's violated, what is next candidate?
 If abs(x-B[j])<d, next candidate is B[j]+d greedily.
 
 Smart solution by ordered set
 - https://community.topcoder.com/stat?c=problem_solution&rm=327976&rd=16650&pm=14131&cr=23330519
 
 Key:
  - N is small. O(N^2) works too
  - if N is not large, append + sort is easier than insert
  - look at B[i] rather than interval by B[i] and B[i+1]
  - if current candidate was caugut in (B[i]-d,B[i]+d), B[i]+d is next candidate
 
 Summary:
  - 👎 it took a lot of time to find how to binary search
  - 👍 implemented without any bugs
 
 */

class BearChairs {
public:
  vector<int> findPositions(vector<int> A, int d) {
    VI res;
    VI B;
    FORR(n,A) {
      int x=n;
      FORR(m,B) {
        if(abs(m-x)>d) continue;
        else if (abs(m-x)<d) x=m+d;
      }
      res.push_back(x);
      B.push_back(x);
      sort(B.begin(),B.end());
    }
    
    return res;
  }
};

class BearChairs_org {
  public:
  vector<int> findPositions(vector<int> A, int d) {
    vector<II> X;
    X.emplace_back(INT_MAX,1);
    
    int N=SZ(A);
    VI res;
    REP(i,N) {
      II tmp = {A[i],0};
      int j=lower_bound(X.begin(),X.end(),tmp) - X.begin();
      int l=X[j].second,r=X[j].first;
      int x=max(A[i],l);
      res.push_back(x);
      
      int lin=x-d+1,rin=x+d-1;
      if(lin<=l&&rin>=r) X.erase(X.begin()+j);
      else if (l<lin&&rin<r) {
        II p1={lin-1,l}, p2={r,rin+1};
        X.insert(X.begin()+j, p1);
        X[j+1] = p2;
      } else if (lin<=l) {
        X[j].second = rin+1;
      } else {
        X[j].first = lin-1;
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("BearChairs.sample");

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

bool do_test(vector<int> atLeast, int d, vector<int> __expected) {
    time_t startClock = clock();
    BearChairs *instance = new BearChairs();
    vector<int> __result = instance->findPositions(atLeast, d);
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
        vector<int> atLeast;
        from_stream(atLeast);
        int d;
        from_stream(d);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(atLeast, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501800147;
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
        cout << "BearChairs (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
