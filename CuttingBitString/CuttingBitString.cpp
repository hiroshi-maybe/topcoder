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
 
 1/7/2018
 
 15:28-15:35 analysis
 15:35-15:45 implement and system test passed (414.78 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+555
   - dp
  - http://topcoder.g.hatena.ne.jp/agw/20120929/1348891178
   - dp
  - http://kmjp.hatenablog.jp/entry/2012/09/10/0900
   - dp
  - https://chaingng.github.io/post/srm-555-div1-easy---cuttingbitstring/
   - dp
  - http://www.amazing-create.com/topcoder/srm-div2/srm-555-div2-medium/2/
   - dfs
  - http://d.hatena.ne.jp/rintpsy/20120923/1348368544
   - bfs
  - http://topcoder.g.hatena.ne.jp/hotoku/20120908/1347067556
   - bfs
 
 This problem can be reduced to single source shortest distance with unit distance. So BFS works too.
 
 Summary:
  - At most 22 (≈log5(2^50)) strings which is power of 5
  - It was straightforward to compute min count by DP
 
 */

// O(N^2*23) time
int dp[51];
class CuttingBitString {
  public:
  string tr(LL x) {
    string res="";
    while(x>0) {
      res+=x%2?'1':'0';
      x/=2LL;
    }
    reverse(res.begin(),res.end());
//    dump2(x,res);
    assert(SZ(res));
    return res;
  }
  int getmin(string S) {
    vector<string> P;
    LL x=1;
    while(x<=(1LL<<50)) {
      P.push_back(tr(x));
      x*=5LL;
    }
    int N=SZ(S);
    
    const int Inf=100;
    REP(i,51) dp[i]=Inf;
    dp[0]=0;
    REP(i,N) if(dp[i]<Inf) {
      FORR(p,P) if(SZ(p)<=N-i) {
        if(S.substr(i,SZ(p))==p) dp[i+SZ(p)]=min(dp[i+SZ(p)],dp[i]+1);
      }
    }
    
    return dp[N]>=Inf?-1:dp[N];
  }
};

// CUT begin
ifstream data("CuttingBitString.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string S, int __expected) {
    time_t startClock = clock();
    CuttingBitString *instance = new CuttingBitString();
    int __result = instance->getmin(S);
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
        string S;
        from_stream(S);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515367676;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 555 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CuttingBitString (555 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
