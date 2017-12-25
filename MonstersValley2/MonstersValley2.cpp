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
 
 12/23/2017
 
 16:39-16:57 system test passed (370.22 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+565
  - http://torus711.hatenablog.com/entry/20121220/p1
  - http://d.hatena.ne.jp/kusano_prog/20121220/1356031599
  - http://www.amazing-create.com/topcoder/srm-div2/srm-565-div2-medium/2/
  - http://kmjp.hatenablog.jp/entry/2012/12/22/0930
   - div1 easy
 
 19:00-19:10 add dp solution
 
 Key:
  - brute-force
  - knapsack-problem-like dp (div1 easy constraint)
 
 Summary:
  - N<=20. It's straighforward to try 2^20 cases
 
 */

// O(N^2) time
LL dp[21][2*21];
class MonstersValley2 {
public:
  int minimumPrice(vector<int> A, vector<int> B) {
    int N=SZ(A);
    const LL Inf=21*1e9;
    REP(i,N+1) REP(j,41) dp[i][j]=-Inf;
    dp[0][0]=0;
    REP(i,N) REP(j,41) if(dp[i][j]>=0) {
      if(dp[i][j]>=A[i]) dp[i+1][j]=max(dp[i+1][j],dp[i][j]);
      dp[i+1][j+B[i]]=max(dp[i+1][j+B[i]], dp[i][j]+A[i]);
    }
    
    int res=100;
    REP(j,41) if(dp[N][j]>0) res=min(res,j);
    return res==100?-1:res;
  }
};

// O(N*2^N) time
class MonstersValley2_bruteforce {
  public:
  int minimumPrice(vector<int> A, vector<int> B) {
    int N=SZ(A);
    const int Inf=100;
    int res=Inf;
    REP(mask,1<<N) {
      LL d=0;
      int c=0;
      REP(i,N) {
        if(mask&(1<<i)) d+=1LL*A[i],c+=B[i];
        else {
          if(d<(LL)A[i]) c=Inf;
        }
//        dump4(i,mask&(1<<i),d,c);
      }
//      if(c==1) dump(mask);
      res=min(res,c);
    }
    return res;
  }
};

// CUT begin
ifstream data("MonstersValley2.sample");

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

bool do_test(vector<int> dread, vector<int> price, int __expected) {
    time_t startClock = clock();
    MonstersValley2 *instance = new MonstersValley2();
    int __result = instance->minimumPrice(dread, price);
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
        vector<int> dread;
        from_stream(dread);
        vector<int> price;
        from_stream(price);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(dread, price, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514075930;
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
        cout << "MonstersValley2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
