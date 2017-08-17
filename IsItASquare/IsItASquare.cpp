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

/**
 
 8/16/2017
 
 9:14-9:36 passed system test (396.98 pt)
 
 23:12-23:30 read editorials
  - https://apps.topcoder.com/wiki/display/tc/SRM+668
    - same as my solution. compare four sides and two diagonals
  - http://kmjp.hatenablog.jp/entry/2015/09/17/1000
    - vector rotation by 90 degrees
    - ∃ p1,p2 s.t. p1==A+C, p2==B+C, C=rotate(A-B, 90 degrees)
      - rotate(A=(a,b), 90 degrees) = (-b,a)
  - https://topcoder.g.hatena.ne.jp/yambe2002/20150916/1442373452
    - number of distinct distances is at most 2 <=> square
    - most simple and beautiful solution ✨
 
 23:30-23:37 add @kmjp solution
 23:40-23:47 add solution which simplified original one
 23:55-
 
 Key:
  - ab==bc==cd==da && ac==bd <=> (a,b,c,d) forms square
    - compare diagonals to differentiate from rhombus
    - sort points or brute-foce (4!)
  - vector rotation
 
 Summary:
  - analyze point positions to avoid permutation 👍
  - slow implementation 👎
    - Euclidean distance should have been exported to a helper
 
 */
class IsItASquare_org {
  public:
  string isSquare(vector<int> X, vector<int> Y) {
    vector<II> ps(4);
    REP(i,4) ps[i]={X[i],Y[i]};
    sort(ps.begin(),ps.end());
    
    VI ord = {0,1,3,2};
    VI ds(4);
    REP(i,4) {
      int dx=ps[ord[i]].first-ps[ord[(i+1)%4]].first;
      int dy=ps[ord[i]].second-ps[ord[(i+1)%4]].second;
      ds[i]=dx*dx+dy*dy;
    }
    
    int mind=*min_element(ds.begin(),ds.end());
    int maxd=*max_element(ds.begin(),ds.end());
    
    if(mind!=maxd||mind==0||maxd==0) return "Not a square";
    
    int dx5=ps[0].first-ps[3].first,dy5=ps[0].second-ps[3].second,
        dx6=ps[1].first-ps[2].first,dy6=ps[1].second-ps[2].second;

    int d1=dx5*dx5+dy5*dy5,d2=dx6*dx6+dy6*dy6;
    
    if(d1!=d2||d1==0||d2==0) return "Not a square";
    
    return "It's a square";
  }
};

class IsItASquare_vector {
public:
  string ok="It's a square",ng="Not a square";
  string isSquare(vector<int> X, vector<int> Y) {
    set<II> S;
    REP(i,4) S.emplace(X[i],Y[i]);
    
    FOR(i,1,4) {
      int dx=X[i]-X[0],dy=Y[i]-Y[0];
      int cx=-dy,cy=dx;
      if(!S.count({X[0]+cx, Y[0]+cy})) continue;
      if(!S.count({X[i]+cx, Y[i]+cy})) continue;
      return ok;
    }
    return ng;
  }
};

class IsItASquare_side_diagonals {
public:
  int dist(II p1, II p2) {
    int dx=p1.first-p2.first,dy=p1.second-p2.second;
    return dx*dx+dy*dy;
  }
  
  string isSquare(vector<int> X, vector<int> Y) {
    vector<II> ps(4);
    REP(i,4) ps[i]={X[i],Y[i]};
    sort(ps.begin(),ps.end());
    
    VI ord = {0,1,3,2};
    VI ds(4);
    REP(i,4) ds[i]=dist(ps[ord[i]],ps[ord[(i+1)%4]]);
    
    int mind=*min_element(ds.begin(),ds.end());
    int maxd=*max_element(ds.begin(),ds.end());
    if(mind!=maxd||mind==0||maxd==0) return "Not a square";
    
    int d1=dist(ps[0],ps[3]),d2=dist(ps[1],ps[2]);
    if(d1!=d2||d1==0||d2==0) return "Not a square";
    
    return "It's a square";
  }
};

class IsItASquare {
public:
  string ok="It's a square",ng="Not a square";
  int dist(II p1, II p2) {
    int dx=p1.first-p2.first,dy=p1.second-p2.second;
    return dx*dx+dy*dy;
  }
  
  string isSquare(vector<int> X, vector<int> Y) {
    SETI ds;
    REP(i,4)FOR(j,i+1,4) {
      ds.insert(dist({X[i],Y[i]},{X[j],Y[j]}));
    }
    return SZ(ds)<=2 ? ok : ng;
  }
};

// CUT begin
ifstream data("IsItASquare.sample");

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

bool do_test(vector<int> x, vector<int> y, string __expected) {
    time_t startClock = clock();
    IsItASquare *instance = new IsItASquare();
    string __result = instance->isSquare(x, y);
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
        string __answer;
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
        int T = time(NULL) - 1502900066;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "IsItASquare (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
