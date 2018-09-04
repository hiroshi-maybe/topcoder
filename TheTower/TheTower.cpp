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
 
 9/3/2018
 
 19:04-19:15 analysis
 19:21 1WA. Figured out misunderstanding of the problem
 19:40 give up
 19:47 add solution after looking at @anta's solution
 
 Editorials:
  - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm423
  - https://topcoder.g.hatena.ne.jp/nitoyon/20081029/1225294551
  - https://chngng.blogspot.com/2015/05/srm-423-div1-easy-thetower.html
  - http://kagamiz.hatenablog.com/entry/2014/12/21/213931
 
 We can choose optimal position in median to minimize ∑ abs(X[i]-x).
 
 Suppose X[i] is sorted...
 If |X| is even, it's any position between [X[N/2],X[N/2+1]].
 If |X| is odd, optimal position is X[N/2].
 In one dimension, we can always choose X[N/2] for either even or odd points.
 
 In this problem, we need to resolve two problems
 1. We need to choose `cnt` points out of N points
 2. Points are located in two dimension
 
 #2 seems to make problem complex. However that's not the case.
 We need to choose (x,y) to minimize sum of manhattan distances.
 However we don't have any constraint to choose (x,y).
 So we can choose x and y independently.
 Suppose we already have `cnt` points.
 Obviously we can choose median of `x` and `y` independently from `cnt` points.
 
 Now we can remember back the first discussion.
 Median of fixed points can be X[N/2] and Y[N/2], which are one of given `x`s and `y`s.
 We can just brute-force them. If (x,y) is fixed, we can find `cnt` closest points by sorting with manhattan distance to fixed (x,y).
 
 Analysis key is fixing subset of points to narrow down possible values for `x` and `y`.
 If the theory of median is known, we can clarify that possible points are just all pairs of x and y.
 It's typical process to fix some conditions to prove something.
 
 I brute-forced all the points. However that's not optmal obviously.
 For fixed points, project x and y values to x-axis and y-axis.
 Clearly we should choose median of them independently, which means selecting points is not always optimal.
 
 y
 
 ^
 |
 *    .(x2,y2)
>* .(x1,y1)
 |
 *       .(x3,y3)
 |
 --*--*--*-> x
      ^
 
 Obviously (x2,y1) is optimal. (x1,y1),(x2,y2) or (x3,y3) is not optimal.
 
 Key:
  - (X[i], Y[j]) gives optimal position
  - Sort by manhattan distance to select closest `cnt` points
 
 Summary:
  - Read problem statement carefully
  - Optimal solution stays in edges is typical property.
 
 */

class TheTower {
public:
  vector<int> count(vector<int> X, vector<int> Y) {
    int N=SZ(X);
    VI res(N,1e9);
    FORE(cnt,1,N) {
      REP(i,N)REP(j,N) {
        vector<int> A;
        REP(k,N) {
          int d=abs(X[k]-X[i])+abs(Y[k]-Y[j]);
          A.emplace_back(d);
        }
        sort(A.begin(),A.end());
        SMIN(res[cnt-1],accumulate(A.begin(),A.begin()+cnt,0));
      }
    }
    return res;
  }
};

class TheTower_wrong {
  public:
  vector<int> count(vector<int> X, vector<int> Y) {
    int N=SZ(X);
    VI res(N,1e9);
    FORE(cnt,1,N) {
      REP(i,N) {
        vector<pair<int,int>> A;
        REP(j,N) {
          int d=abs(X[j]-X[i])+abs(Y[j]-Y[i]);
          A.emplace_back(d,j);
        }
        sort(A.begin(),A.end());
        VI XX,YY;
        REP(j,cnt) XX.emplace_back(X[A[j].second]),YY.push_back(Y[A[j].second]);
        sort(XX.begin(),XX.end()),sort(YY.begin(),YY.end());
        int mid=(cnt)/2;
        int tot=0;
        REP(j,cnt) tot+=abs(XX[j]-XX[mid])+abs(YY[j]-YY[mid]);
        SMIN(res[cnt-1],tot);
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("TheTower.sample");

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

bool do_test(vector<int> x, vector<int> y, vector<int> __expected) {
    time_t startClock = clock();
    TheTower *instance = new TheTower();
    vector<int> __result = instance->count(x, y);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536026594;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheTower (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
