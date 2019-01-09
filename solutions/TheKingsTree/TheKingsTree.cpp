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
 
 9/12/2017
 
 8:51-9:03, 17:57-18:25 design
 18:26-18:37 implementation
 18:37-18:49 bug fix and system test passed
  - missing call of count()
  - out of range index access of dp array
  - missing initialization of global array
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+643
  - http://kmjp.hatenablog.jp/entry/2014/12/28/0930
 
 f(u,r) = min { ∑{f(v,r')+g : v∈u's children,r'>=0,∑g'=g-1} } color by green
            ∪ { ∑{f(v,r')+r : v∈u's children,r'>=0,∑r'=r-1} } color by red
 
 key:
  - typical tree DP
  - needs one main DP state f(u,r) and one helper DP state f'(u,t,r)
 
 summary:
  - maybe first time to solve tree dp problem by myself? 👍
  - I still need more training of tree DP problem
 
 submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=324657&rd=16086&pm=12857&cr=23054352
  - https://community.topcoder.com/stat?c=problem_solution&rm=324657&rd=16086&pm=12857&cr=22869652
  - https://community.topcoder.com/stat?c=problem_solution&rm=324648&rd=16086&pm=12857&cr=22888586
    - short solutions without brute-forcing assigning red and blue
    - giving used number of red and green in top-down. very smart.
 
 */
int cnt[51];
int memo[51][51];
VI E[51];
class TheKingsTree {
public:
  const int Inf=1e5;
  int V;
  int f(int u, int r) {
    if(r>cnt[u]) return Inf;
    if(cnt[u]==1) return 1;
    if(memo[u][r]>=0) return memo[u][r];
    int &res=memo[u][r];
    res=Inf;
    int g=cnt[u]-r;
    
    int vnum=SZ(E[u]);
    int dp[vnum+1][r+1];
    REP(i,vnum+1)REP(j,r+1) dp[i][j]=Inf;
    dp[0][0]=0;
    REP(i,vnum) REP(cur,r+1) if(dp[i][cur]<Inf) {
      REP(rr,r+1) if(cur+rr<=r) {
        dp[i+1][cur+rr]=min(dp[i+1][cur+rr],dp[i][cur]+f(E[u][i],rr));
      }
    }
    int rg=cnt[u]-g>=0?dp[vnum][cnt[u]-g]+g:Inf;
    int rr=r-1>=0?dp[vnum][r-1]+r:Inf;
    //    dump3(u,r,g);
    //    dump2(dp[vnum][cnt[u]-g],dp[vnum][r-1]);
    return res=min(rr,rg);
  }
  int count(int u) {
    int res=1;
    FORR(v,E[u]) res+=count(v);
    return cnt[u]=res;
  }
  int getNumber(vector<int> parent) {
    this->V=SZ(parent)+1;
    REP(i,V) E[i].clear();
    ZERO(cnt);
    MINUS(memo);
    REP(i,SZ(parent)) {
      E[parent[i]].push_back(i+1);
    }
    count(0);
    int res=Inf;
    REP(i,V) res=min(res,f(0,i));
    return res;
  }
};

// CUT begin
ifstream data("TheKingsTree.sample");

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

bool do_test(vector<int> parent, int __expected) {
    time_t startClock = clock();
    TheKingsTree *instance = new TheKingsTree();
    int __result = instance->getNumber(parent);
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
        vector<int> parent;
        from_stream(parent);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(parent, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505231502;
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
        cout << "TheKingsTree (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
