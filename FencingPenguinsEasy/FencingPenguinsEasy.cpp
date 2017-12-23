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
 
 12/21/2017
 
 23:13-24:20 It took 50 mins to understand sample 5
 
 12/22/2017
 
 9:30-10:00 time up
 
 I tried two approaches
  1. Find segments which wraps all the penguins greedily like GRAHAM-SCAN (convex hull)
   => I was willing to solve by greedy algorithm. I didn't have an idea of DP
  2. Find convex hull of penguins by graham-scan algorithm and try to find points which surrounds them
   => I couldn't find an algorithm which finds polygon which wraps polygon internally
 
 Approach #1 was closer to expected solution.
 Assume posts `ps` are indexed in counter-clock wise order from (r,0).
 Difficult part is cycle. However, segment from ps[b] to ps[a] (a<b) happens only once.
 So we can brute-force them.
 
 Suppose segment ps[b]->ps[a] are given.
 If all the penguins are located in left side from ps[b]->ps[a], this is valid.
 It's possible to compute it in O(|X|). This information is independent.
 In order to avoid computing it repeatedly, let's pre-compute it and store the result in ok[i][j] in (|X|*N^2) time
 Now we want to search minimum area by picking up points in [a..b]
 If we pick up next point `x`, it reduces sub-problem to find a new point in [x..b].
 Now we found optimal substructure. We can build recurrence relation and solve by DP.
 
 f(i,j) = min { area(ps[i],ps[x],ps[j])+f(x,j) : x=i+1..j, ok[i][x]=1 }
 f(i,i) = 0
 f(i,i+1) = ok[i][i+1]?0:Inf
 
 res = min { ok[b][a]?f(a,b):Inf : b>a }
 
 Amortized runtime of the DP is O(N^3).
 
 Note that there are N^2 pairs of (b,a).
 However that doesn't contribute to total runtime because it doesn't affect runtime of DP.
 DP state is not reset for each (b,a) pair. So total runtime is still O(N^3) time.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+566
  - http://kmjp.hatenablog.jp/entry/2013/01/13/1100
  - http://takapt0226.hatenablog.com/entry/2013/01/16/045800
  - http://topcoder.g.hatena.ne.jp/minus9d/comment?date=20130122
 
 16:45-17:50 pause (sample 6 does not pass)
 20:00-20:50 add system test (too small Inf and boundary bug)
 
 Reference:
  - Polar coordinate: https://en.wikipedia.org/wiki/Polar_coordinate_system
 
 Key:
  - Precompute valid segments first
  - keep adding triangles and compute minimal value by DP
  - Area of polygon is sum of composed triangles
  - Area of triangle is det(A,B)/2
  - Cartesian coordinate is (r*cosΘ,r*sinΘ)

 Summary:
  - This might be the first problem that DP is applicable in geometriy problem. Great chance to learn
  - How to compute area was not clear for me as well. It made this problem more difficult to approach
  - By finding next point one by one, we can compute area of polygon by summing up area of triangles
   - This viewpoint may have helped find DP approach
  - I was not familiar with some of techniques much. It prevented from reaching DP idea
   - area of polygon can be computed from triangle
   - area of triangle can be computed from cross product
 
 */

double deg2rad(double deg) {
  return deg*M_PI/180.0;
}

pair<double,double> polar2cartesianSys(double r, double deg) {
  double rad=deg2rad(deg);
  return { r*cos(rad), r*sin(rad) };
}

pair<double,double> rotate(pair<double,double> p, double deg) {
  double x=p.first,y=p.second;
  double rad=deg2rad(deg);
  double C = cos(rad);
  double S = sin(rad);
  return { x*C-y*S, x*S+y*C };
}

double area(pair<double,double> p1, pair<double,double> p2, pair<double,double> p3) {
  pair<double,double> v1={ p2.first-p1.first,p2.second-p1.second };
  pair<double,double> v2={ p3.first-p1.first,p3.second-p1.second };
  
  return abs(v1.first*v2.second-v1.second*v2.first)*0.5;
}

// O(N^3) time
double memo[223][223];
class FencingPenguinsEasy {
  public:
  int ok[223][223];
  vector<pair<double,double>> ps;
  const double Inf=100000.0*100000.0*M_PI;
  void setupPs(int N, int r) {
    ps.emplace_back(r, 0);
    double udeg=360.0/N;
    FOR(i,1,N) {
      ps.push_back(rotate(ps[i-1], udeg));
    }
  }
  
  double f(int i, int j) {
    double &res=memo[i][j];
    if(res>=0) return res;
    if(i==j) return 0;
    if(j==i+1) return ok[i][j]?0:Inf;
    assert(i<j);

    res=Inf;
    FOR(x,i+1,j+1) if(ok[i][x]) {
      res=min(res,area(ps[i],ps[x],ps[j])+f(x,j));
    }
    return res;
  }
  
  double calculateMinArea(int N, int r, vector<int> X, vector<int> Y) {
    setupPs(N,r);
    ZERO(ok); MINUS(memo);
    REP(i,N) REP(j,N) if(i!=j) {
      ok[i][j]=true;
      pair<double,double> v1={ ps[j].first-ps[i].first, ps[j].second-ps[i].second };
      REP(k,SZ(X)) {
        double x=X[k],y=Y[k];
        pair<double,double> v2={ x-ps[i].first, y-ps[i].second };
        double cp=v1.first*v2.second-v1.second*v2.first;
        if(cp<0) ok[i][j]=false;
      }
    }
    
    double res=Inf;
    REP(j,N) REP(i,j) if(ok[j][i]) res=min(res,f(i,j));

    return res==Inf?-1:res;
  }
};

// CUT begin
ifstream data("FencingPenguinsEasy.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int numPosts, int radius, vector<int> x, vector<int> y, double __expected) {
    time_t startClock = clock();
    FencingPenguinsEasy *instance = new FencingPenguinsEasy();
    double __result = instance->calculateMinArea(numPosts, radius, x, y);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int numPosts;
        from_stream(numPosts);
        int radius;
        from_stream(radius);
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numPosts, radius, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513926772;
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
        cout << "FencingPenguinsEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
