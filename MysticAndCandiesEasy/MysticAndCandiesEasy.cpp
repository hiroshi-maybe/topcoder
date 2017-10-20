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
 
 10/19/2017
 
 8:51-9:50 understood problem statement and meaning of sample 3
 9:51-9:52 implement, submit and system test passed (195.65 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+608
  - http://torus711.hatenablog.com/entry/20140207/p2
 
 Suppose...
 U = {0,..,N-1}
 we select boxes S = { i : box i is selected }. Also S'=U-S.
 Selected box has `a` candies, unselected box has `b` candies.
 
 Then a+b=C
 <=> b=C-a <= H, where H = ∑ {h[i] : i ∈ S' }
 <=> C-a <= H
 <=> a >= C - H >= X
 <=> H <= C - X
 
 We want to know minimum |S| which always satisfies H <= C - X.
 The smaller h[i] is, the larger |S'| is. Then |S| is smaller.
 Thus we can find max k s.t. hh = ∑ { h[i] : i=0..k }, hh<=C-X. Note that h is sorted.
 res = N-k-1
 
 key:
  - selecting boxes with higher limit is always better choice
  - in worst case, unchosen boxes have maximum candies
 
 summary:
  - below problem statement was so confusing for me. I couldn't understand sample 3
   "he will always choose a subset of boxes for which he is sure that they must contain at least X candies"
  - Greedy only by intuition cannot solve harder problems.
  - I should be more familiar with analysis by math and formula.
 
 */

class MysticAndCandiesEasy {
public:
  int minBoxes(int C, int X, vector<int> h) {
    int N=SZ(h);
    sort(h.begin(),h.end());
    int res=N,sum=0;
    REP(i,N) {
      sum+=h[i];
//      dump4(i,sum,X-C,N-i-1);
      if(sum<=C-X) res=min(res,N-i-1);
    }
    return res;
  }
};

class MysticAndCandiesEasy_org {
public:
  int minBoxes(int C, int X, vector<int> H) {
    int N=SZ(H);
    dump(N);
    
    sort(H.begin(),H.end());
//    dumpAR(H);
    
    VI S(N,0);
    REP(i,N) {
      S[i]=min(H[i],C);
      C-=S[i];
      assert(C>=0);
      if(C==0) break;
    }
    assert(C==0);
//        dumpAR(S);
    int res=0,x=0;
    for(int i=N-1; i>=0; --i) {
      x+=S[i]; res++;
      if(x>=X) break;
    }
    
    return res;
  }
};

class MysticAndCandiesEasy_wrong2 {
public:
  int minBoxes(int C, int X, vector<int> H) {
    int N=SZ(H);
    dump(N);
    
    sort(H.rbegin(),H.rend());
    dumpAR(H);
    
    VI S(N,0);
    REP(i,N) {
      S[i]=min(H[i],C);
      C-=S[i];
      assert(C>=0);
      if(C==0) break;
    }
    assert(C==0);
    sort(S.begin(),S.end());
    dumpAR(S);
    int res=0,x=0;
    REP(i,N) {
      x+=S[i]; res++;
      if(x>=X) break;
    }
    
    return res;
  }
};

class MysticAndCandiesEasy_wrong {
  public:
  int minBoxes(int C, int X, vector<int> H) {
    int N=SZ(H);
    dump(N);
    
    sort(H.begin(),H.end());
    dumpAR(H);

    VI S(N,0);
    REP(i,N) {
      S[i]=min(H[i],C/(N-i));
      C-=S[i];
      assert(C>=0);
      if(C==0) break;
    }
    assert(C==0);
    sort(S.rbegin(),S.rend());
    dumpAR(S);
    int res=0,x=0;
    REP(i,N) {
      x+=S[i]; res++;
      if(x>=X) break;
    }

    return res;
  }
};

// CUT begin
ifstream data("MysticAndCandiesEasy.sample");

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

bool do_test(int C, int X, vector<int> high, int __expected) {
    time_t startClock = clock();
    MysticAndCandiesEasy *instance = new MysticAndCandiesEasy();
    int __result = instance->minBoxes(C, X, high);
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
        int C;
        from_stream(C);
        int X;
        from_stream(X);
        vector<int> high;
        from_stream(high);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(C, X, high, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508428266;
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
        cout << "MysticAndCandiesEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
