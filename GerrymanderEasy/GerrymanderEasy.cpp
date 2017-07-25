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
 
 7/24/2017
 
 8:34-8:46 passed system test (420.20 pt)
 
 Interesting, O(N^3) does not hit TLE (N^3=10^9)
 - https://apps.topcoder.com/wiki/display/tc/SRM+690

 22:15-22:18 add brute-force O(N^3) solution
 
 Yet another O(N^2) solution
 - https://apps.topcoder.com/wiki/display/tc/SRM+690
 - https://community.topcoder.com/stat?c=problem_solution&rm=328683&rd=16729&pm=14235&cr=40336744
 
 Binary search solution
 - https://community.topcoder.com/stat?c=problem_solution&rm=328695&rd=16729&pm=14235&cr=40037036
 
 22:35-22:49 add binary search solution
 
 */

// binary search O(N^2*lg 10^9) time
class GerrymanderEasy {
public:
  int N;
  vector<double> cumA,cumB;
  bool ok(double x, int K) {
    REP(i,N+1) for(int j=i+K;j<N+1;++j) {
      if(cumB[j]-cumB[i]>=x*(cumA[j]-cumA[i])) return true;
    }
    return false;
  }
  double getmax(vector<int> A, vector<int> B, int K) {
    N=SZ(A);
    cumA=vector<double>(N+1,0.0), cumB=vector<double>(N+1,0.0);
    REP(i,N) cumA[i+1]=cumA[i]+A[i], cumB[i+1]=cumB[i]+B[i];
    
    double good=0.0,bad=1.1;
    while(abs(good-bad)>=1e-9) {
      double mid = (good+bad)/2.0;
      if(ok(mid, K)) good=mid;
      else bad=mid;
    }
    
    return good;
  }
};

// Brute force, O(N^3) time
class GerrymanderEasy_bruteForce {
public:
  double getmax(vector<int> A, vector<int> B, int K) {
    int N=SZ(A);
    double res=0.0;
    REP(i,N) REP(j,N) if(j-i+1>=K) {
      double a=0.0,b=0.0;
      FOR(k,i,j+1) a+=A[k],b+=B[k];
      res = max(res, b/a);
    }
    
    return res;
  }
};

// cumulative sum, O(N^2) time, original solution
class GerrymanderEasy_cumulative {
  public:
  double getmax(vector<int> A, vector<int> B, int K) {
    int N=SZ(A);
    vector<double> cumA(N+1,0),cumB(N+1,0);
    REP(i,N) cumA[i+1]=cumA[i]+A[i],cumB[i+1]=cumB[i]+B[i];
    
    double res = 0.0;
    FOR(j,K,N+1) {
      for(int i=0;j-i>=K; ++i) {
        res = max(res, (cumB[j]-cumB[i])/(cumA[j]-cumA[i]));
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("GerrymanderEasy.sample");

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

bool do_test(vector<int> A, vector<int> B, int K, double __expected) {
    time_t startClock = clock();
    GerrymanderEasy *instance = new GerrymanderEasy();
    double __result = instance->getmax(A, B, K);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        int K;
        from_stream(K);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500910438;
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
        cout << "GerrymanderEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
