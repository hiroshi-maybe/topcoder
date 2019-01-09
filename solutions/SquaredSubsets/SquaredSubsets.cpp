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
 
 2/28/2018
 
 8:55-9:18, 9:19-9:39 approach 1. but samples don't pass
 9:40-10:07 approach 2 doesn't work for sample #3
 10:07-10:47 Work around missing cases. Submit without proof. ACC (331.77 pt)

 To handle positions with real number position, I firstly did coordinate expansion.
 L<=10^8 doesn't allow us to try L positions around each point.
 I searched (x±1,y±) though, sample #3 didn't pass due to some missing cases.
 I didn't have proof though, I brute-forced middle between two points in x-axis and y-axis.
 System test passed though, I had no proof why this works 😵
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+521
  - http://kmjp.hatenablog.jp/entry/2014/01/14/1000
  - http://d.hatena.ne.jp/kusano_prog/20111013/1318531612
   - This idea seems to be same as my second approach. Why it passes? 🤔
   - Ok. Probably I didn't try different combinations of x and y
  - https://topcoder.g.hatena.ne.jp/firewood/20111025/1319549885
 
 Ok it turned out middle positions don't matter. I figured out it from @kusano's editorial.

 I was somehow assuming only below case. This is not sufficient 👎

 ^
 | . .   .
 | .   . .
 |
 |------------

 Points on the border does not necessarily at the corner obviously... 👎👎
 Generalize to cover below case:
 
 ^
 |    .
 | .     .
 |    .
 |------------
 
 Thus I was just missing different combination of x and y like (X[i],Y[j]) (i!=j)... 👎👎👎👎
 
 Key:
  - Find possible squares greedily based on the given N points
 
 Summary:
  - Idea to expand coordinate and try neighbored points was great though, poorly tried only corners 👎
  - Sample I tried first was not good. That
 
 */

class SquaredSubsets {
public:
  VI X,Y;
  bool ok(int ox, int oy, int L, int x, int y) {
    return ox<=x&&x<=(ox+L)&&oy>=y&&y>=(oy-L);
  }
  int N;
  LL count(int ox, int oy, int L) {
    LL mask=0;
    REP(k,N) if(ok(ox,oy,L,X[k],Y[k])) mask|=1LL<<k;
    return mask;
  }
  long long countSubsets(int L, vector<int> X_, vector<int> Y_) {
    L*=2;
    this->N=SZ(X_);
    REP(i,N) X_[i]*=2,Y_[i]*=2;
    this->X=X_,this->Y=Y_;
    
    set<LL> S;
    set<int> PX,PY;
    REP(i,N) for(int x=X[i]-L; x<=X[i]+L; x+=L) for(int d=-1;d<=1;++d) PX.emplace(x+d);
    REP(i,N)  for(int y=Y[i]-L; y<=Y[i]+L; y+=L) for(int d=-1;d<=1;++d) PY.emplace(y+d);
    
    FORR(ox,PX) FORR(oy,PY) {
      LL mask=count(ox,oy,L);
      if(mask) S.emplace(mask);
    }
    
    return SZ(S);
  }
};

// First version that passed system test.
class SquaredSubsets_org {
public:
  VI X,Y;
  bool ok(int ox, int oy, int L, int x, int y) {
    return ox<=x&&x<=(ox+L)&&oy>=y&&y>=(oy-L);
  }
  int N;
  LL count(int ox, int oy, int L) {
    LL mask=0;
    REP(k,N) if(ok(ox,oy,L,X[k],Y[k])) mask|=1LL<<k;
    return mask;
  }
  long long countSubsets(int L, vector<int> X_, vector<int> Y_) {
    L*=2;
    this->N=SZ(X_);
    REP(i,N) X_[i]*=2,Y_[i]*=2;
    this->X=X_,this->Y=Y_;
    VI SX=X_,SY=Y_;
    sort(SX.begin(),SX.end()); sort(SY.begin(),SY.end());
    
    set<LL> S;
    set<int> PX,PY;
    REP(i,N) for(int x=X[i]-L; x<=X[i]+L; x+=L) for(int dx=-1;dx<=1;++dx) PX.emplace(x+dx);
    REP(i,N)  for(int y=Y[i]-L; y<=Y[i]+L; y+=L) for(int dy=-1;dy<=1;++dy) PY.emplace(y+dy);
    
    // Below is not necessary. Trying combination of x and y of different point is the key.
    REP(i,N-1) for(int dx=-1;dx<=1;++dx) PX.emplace((SX[i]+SX[i+1])/2+dx);
    REP(i,N-1) for(int dy=-1;dy<=1;++dy) PY.emplace((SY[i]+SY[i+1])/2+dy);
    
    FORR(ox,PX) FORR(oy,PY) {
      LL mask=count(ox,oy,L);
      if(mask) S.emplace(mask);
    }

    return SZ(S);
  }
};

class SquaredSubsets_wrong2 {
public:
  bool ok(int ox, int oy, int L, int x, int y) {
    return ox<=x&&x<=(ox+L)&&oy>=y&&y>=(oy-L);
  }
  long long countSubsets(int L, vector<int> X, vector<int> Y) {
    L*=2;
    int N=SZ(X);
    REP(i,N) X[i]*=2,Y[i]*=2;
    set<LL> S;
    REP(i,N) {
      for(int x=X[i]-L; x<=X[i]; x+=L)for(int y=Y[i]+L; y>=Y[i]; y-=L)
        for(int dx=-1;dx<=1;++dx)for(int dy=-1;dy<=1;++dy) {
          int ox=x+dx,oy=y+dy;
          LL mask=0;
          REP(j,N) if(ok(ox,oy,L,X[j],Y[j])) mask|=1LL<<j;
          if(mask) S.emplace(mask);
        }
    }
    return SZ(S);
  }
};

class SquaredSubsets_wrong1 {
  public:
  bool ok(int ox, int oy, int L, int x, int y) {
    return ox<=x&&x<=(ox+L)&&oy>=y&&y>=(oy-L);
  }
  long long countSubsets(int L, vector<int> X, vector<int> Y) {
    L*=2;
    int N=SZ(X);
    REP(i,N) X[i]*=2,Y[i]*=2;
    LL res=0;
    REP(i,N) {
      int x1=X[i]-1,y1=Y[i]+1;
      int cnt1=0;
      REP(j,N) cnt1+=ok(x1,y1,L,X[j],Y[j]);
      x1=X[i],y1=Y[i];
      int cnt2=0;
      REP(j,N) cnt2+=ok(x1,y1,L,X[j],Y[j]);
      res+=cnt1==cnt2?1:2;
      dump3(i,cnt1,cnt2);
    }
    return res;
  }
};

// CUT begin
ifstream data("SquaredSubsets.sample");

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

bool do_test(int n, vector<int> x, vector<int> y, long long __expected) {
    time_t startClock = clock();
    SquaredSubsets *instance = new SquaredSubsets();
    long long __result = instance->countSubsets(n, x, y);
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
        int n;
        from_stream(n);
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519836899;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SquaredSubsets (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
