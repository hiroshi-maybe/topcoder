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
 
 9/10/2018
 
 16:45-16:58 analysis
 17:58 1WA (bug of implementation to find LCA)
 18:08 AC
 
 http://apps.topcoder.com/wiki/display/tc/SRM+443
 
 Actually building tree is overkill. We can just color circles with 4 colors.
 0: neither include P1 or P2
 1: include only P1
 2: include only P2
 3: include both P1 and P2
 
 res = count(color=1) + count(color=2)
 
 This is sufficient and necessary to number of LCA in circle tree.
 
 */

// test if circle 1 stays inside circle 2
bool insideCircle(int x1, int y1, int r1, int X2, int Y2, int R2) {
  double d=hypot(abs(x1-X2),abs(y1-Y2));
  return d+r1<=R2;
}

class CirclesCountry {
public:
  int leastBorders(vector<int> X, vector<int> Y, vector<int> R, int x1, int y1, int x2, int y2) {
    int N=SZ(X);
    VI col(N);
    REP(i,N) {
      int a=insideCircle(x1,y1,0,X[i],Y[i],R[i]),b=insideCircle(x2,y2,0,X[i],Y[i],R[i]);
      col[i]=(a<<1)|(b);
    }
    int res=0;
    REP(i,N) res+=__builtin_popcount(col[i])==1;
    return res;
  }
};


VI E[51];
class CirclesCountry_org {
  public:
  int N;
  VI X,Y,R;
  bool inside(int a, int b, int R, int x, int y, int r) {
    double d=hypot(abs(a-x),abs(b-y));
    return d<R-r;
  }
  double rend(int a, int b, int r, int y) {
//    assert(r*r-(y-b)*(y-b)>0);
    return sqrt(r*r-(y-b)*(y-b))+a;
  }
  VI dfs(int u, int x, int y, int r) {
    VI res;
    FORR(v,E[u]) if(inside(X[v],Y[v],R[v],x,y,r)) {
      res=dfs(v,x,y,r);
      res.push_back(v);
    }
    return res;
  }
  int leastBorders(vector<int> X, vector<int> Y, vector<int> R, int x1, int y1, int x2, int y2) {
    X.push_back(0),Y.push_back(0),R.push_back(1e5);
    this->X=X,this->Y=Y,this->R=R;
    N=SZ(X);
    REP(i,N-1) {
      int x=X[i],y=Y[i];
//      dump3(x,y,R[i]);
      vector<pair<double,int>> A;
      REP(j,N) if(i!=j) if(inside(X[j],Y[j],R[j],x,y,R[i])) {
        A.emplace_back(rend(X[j],Y[j],R[j],y),j);
      }
      sort(A.begin(),A.end());
      assert(SZ(A));
      int u=A.front().second;
      E[u].push_back(i);
      dump2(u,i);
    }
    VI A=dfs(N-1,x1,y1,0),B=dfs(N-1,x2,y2,0);
    reverse(A.begin(),A.end()),reverse(B.begin(),B.end());
    dumpAR(A);
    dumpAR(B);
    int i=0;
    while(i<min(SZ(A),SZ(B))&&A[i]==B[i]) {
      ++i;
    }
    int res=SZ(A)-i+SZ(B)-i;
    return res;
  }
};

// CUT begin
ifstream data("CirclesCountry.sample");

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

bool do_test(vector<int> X, vector<int> Y, vector<int> R, int x1, int y1, int x2, int y2, int __expected) {
    time_t startClock = clock();
    CirclesCountry *instance = new CirclesCountry();
    int __result = instance->leastBorders(X, Y, R, x1, y1, x2, y2);
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
        vector<int> X;
        from_stream(X);
        vector<int> Y;
        from_stream(Y);
        vector<int> R;
        from_stream(R);
        int x1;
        from_stream(x1);
        int y1;
        from_stream(y1);
        int x2;
        from_stream(x2);
        int y2;
        from_stream(y2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, Y, R, x1, y1, x2, y2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536623084;
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
        cout << "CirclesCountry (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
