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
 
 10/11/2017
 
 4:33-5:44 submit and 1WA (185.28 pt)
 7:33-7:47 give up
 
 20:32-21:04 add solution by brute forcing two removed points
 
 editorial
  - https://www.slideshare.net/EmKjp/srm614-34320184
   - problem writer's editorial
  - https://apps.topcoder.com/wiki/display/tc/SRM+614
  - http://torus711.hatenablog.com/entry/20140331/1396285930
 
 key:
   - size in problem is small. brute force pair of points in O(N^2)
   - compute square area ignoring selected pair of points in O(N)
 
 summary:
   - it turns out failure reason in system test was just implementation bug 😫
   - unnecessary greedy ignoring problem size -> complecated code -> WA 🐞
   - approach to pick up two points and compute square area was ocrrect
   - SAFE BRUTE-FORCE ALWAYS SAVES YOU A LOT 👎
 
 submit solutions:
  - remove and sort
    - https://community.topcoder.com/stat?c=problem_solution&rm=321151&rd=15847&pm=12982&cr=23161191
  -  simply iterate to get min and max
    - https://community.topcoder.com/stat?c=problem_solution&rm=321182&rd=15847&pm=12982&cr=23286857
 */

// O(N^3) time
class MinimumSquareEasy {
public:
  long long minArea(vector<int> X, vector<int> Y) {
    int N=SZ(X);
    LL res=5e18;
    REP(j,N) REP(i,j) {
      LL xl=1e9,xr=-1e9,yl=1e9,yr=-1e9;
      REP(k,N) if(k!=i&&k!=j) {
        xl=min(xl,1LL*X[k]),xr=max(xr,1LL*X[k]);
        yl=min(yl,1LL*Y[k]),yr=max(yr,1LL*Y[k]);
      }
      LL l=max(llabs(xl-xr),llabs(yl-yr));
      res=min(res,(l+2)*(l+2));
    }
    
    return res;
  }
};

// O(N^2*lg N) time
class MinimumSquareEasy_org {
  public:
  /*
  LL f(vector<pair<LL,LL>> ps) {
    sort(ps.begin(),ps.end()[](pair<LL,LL>a, pair<LL,LL>b) {
      return a.first<b.first;
    });
    
    LL res=(1e9+5LL)*(1e9+5LL);
    
    LL x0=ps[2].first-1,x1=ps.back().first+1;
    LL y0=1e9+1,y1=-1e9-1;
    FOR(i,2,N) y0=min(y0,ps[i].second-1),y1=max(y1,ps[i].second+1);
    res=llabs(x1-x0)*llabs(y1-y0);
    
    x0=ps[N-3].first+1,x1=ps[0].first-1;
    LL y0=1e9+1,y1=-1e9-1;
    REP(i,N-2) y0=min(y0,ps[i].second-1),y1=max(y1,ps[i].second+1);
    res=llabs(x1-x0)*llabs(y1-y0);
    
    return res;
  }*/
  
  LL f(int p1, int p2, vector<tuple<LL,LL,int>> ps) {
    LL x0=1e9+1,x1=-1e9-1;
    LL y0=1e9+1,y1=-1e9-1;
    
    REP(i,SZ(ps)) if(get<2>(ps[i])!=p1&&get<2>(ps[i])!=p2) {
      LL x,y; int ii;
      tie(x,y,ii)=ps[i];
      x0=min(x0,x-1),x1=max(x1,x+1);
      y0=min(y0,y-1),y1=max(y1,y+1);
    }
//    dump3(p1,p2,llabs(x1-x0)*llabs(y1-y0));
//    dump4(x0,x1,y0,y1);
    LL side=max(llabs(x1-x0),llabs(y1-y0));
//    dump2(side,side*side);
    return side*side;
  }
  
  long long minArea(vector<int> X, vector<int> Y) {
    int N=SZ(X);
    vector<tuple<LL,LL,int>> ps;
    REP(i,N)ps.emplace_back(X[i],Y[i],i);
    
    vector<pair<LL,int>> XX,YY;
    REP(i,N) XX.emplace_back(X[i],i);
    REP(i,N) YY.emplace_back(Y[i],i);
    
    sort(XX.begin(),XX.end());
    sort(YY.begin(),YY.end());
    
    LL res=f(XX[0].second,XX[1].second,ps);
    res=min(res,f(XX[N-1].second, XX[N-2].second,ps));
    res=min(res,f(XX[N-1].second, XX[0].second,ps));
    res=min(res,f(YY[0].second, YY[1].second,ps));
    res=min(res,f(YY[N-1].second, YY[N-2].second,ps));
    res=min(res,f(YY[0].second, YY[N-1].second,ps));
    
    vector<pair<int,int>> pairs={{0,0},{0,N-1},{N-1,0},{N-1,N-1}};
    FORR(p,pairs) {
      int i1=p.first,i2=p.second;
      if(XX[i1].second!=YY[i2].second) {
//        res=min(res,f(XX[i1].second, XX[i2].second,ps)); 🐞
        res=min(res,f(XX[i1].second, YY[i2].second,ps));
      } else {
        dump2(i1,i2);
        if(i1==0) {
//          res=min(res,f(XX[1].second, XX[i2].second,ps)); 🐞
          res=min(res,f(XX[1].second, YY[i2].second,ps));
        } else {
//          res=min(res,f(XX[N-2].second, XX[i2].second,ps)); 🐞
          res=min(res,f(XX[N-2].second, YY[i2].second,ps));
        }
        if(i2==0) {
//          res=min(res,f(XX[i1].second, XX[1].second,ps)); 🐞
          res=min(res,f(XX[i1].second, YY[1].second,ps));
        } else {
//          res=min(res,f(XX[i1].second, XX[N-2].second,ps)); 🐞
          res=min(res,f(XX[i1].second, YY[N-2].second,ps));
        }
      }
    }

    return res;
  }
};

// CUT begin
ifstream data("MinimumSquareEasy.sample");

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

bool do_test(vector<int> x, vector<int> y, long long __expected) {
    time_t startClock = clock();
    MinimumSquareEasy *instance = new MinimumSquareEasy();
    long long __result = instance->minArea(x, y);
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
        long long __answer;
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
        int T = time(NULL) - 1507721610;
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
        cout << "MinimumSquareEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
