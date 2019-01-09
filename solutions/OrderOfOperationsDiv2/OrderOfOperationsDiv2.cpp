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
 
 8/17/2017
 
 9:21-9:46 failed system test (314.73 pt)
 19:32-19:55 give up
 19:55-20:07 look at editorial and add DP solution O(N*2^M) time
  - http://kmjp.hatenablog.jp/entry/2015/09/12/0900
  - no need to remember what was before at s[i]. just remember cache states
  - brute force all possible states by mask. get minimum cost to reach the state.
 
 i = 0..N-1
 dp[mask'] = min(dp[mask'], dp[mask]+__builtin_popcount(mask'-mask)), mask' = mask|S[i]
 
 22:47-23:10 add solution by Dijkstra's algorighm
  - Dijkstra's algorithm works in even div1 (N=50, 10^9 runtime) though, it's not necessary.
    - as solved by DP, dependency between each state is DAG (NO loop)
    - Dijkstra is optimal only when there is a loop in state transition
 
 More editorials
  - bit DP
    - https://apps.topcoder.com/wiki/display/tc/SRM+667
      - "Note that this approach is similar to Bellman-Ford." in probably cost relaxation perspective? 🤔
  - Dijkstra
    - http://kenkoooo.hatenablog.com/entry/2015/09/12/022324
 
 Key:
  - Greedy seems working (passes all the samples) though, there is a counter example
  - M is small. save states in bit and run bit DP
  - by focusing cache state, we can figure out that order doesn't matter to know optimal solution
    - we know start state and end state. state transition forms graph. => DP
 
 Summary:
  - awesome problem. deep analysis is necessary not to be trapped by pitfall of samples
  - train proof more
    - I proved only less bit count -> more bit count case though, I've not proved same bit count -> same bit count case
  - see "11100","01011","00111" case
    - "11100"->"01011"->"00111": 9+4+0 ❌
    - "01011"->"11100"->"00111": 9+1+0 ✅
  - two hops to solve this problem
   - proof that greedy doesn't work
   - state of cahce matters. order doesn't matter. => bit DP
 
 */

int dist[1<<20];
int E[21];
// V=O(2^M), E=O(V*N)=O(N*2^M), O(N*M*2^M) time
class OrderOfOperationsDiv2 {
public:
  const int Inf=405;
  int minTime(vector<string> s) {
    int N=SZ(s),M=SZ(s[0]);
    int end=0;
    REP(i,N) {
      int mask=0;
      REP(j,M) if(s[i][j]=='1') mask|=(1<<j);
      E[i]=mask;
      end|=mask;
    }
    REP(mask,end+1) dist[mask]=Inf;
    
    set<II> Q; // cost,mask
    Q.emplace(0,0);
    dist[0]=0;
    while(SZ(Q)) {
      auto it=Q.begin();
      int cost,mask;
      tie(cost,mask)=*it; Q.erase(it);
      REP(i,N) {
        int mask2=mask|E[i];
        int d=__builtin_popcount(mask2-mask);
        int w=d*d;
        int cost2=dist[mask]+w;
        if(dist[mask2]>cost2) {
          auto it2=Q.find({dist[mask2],mask2});
          if (it2!=Q.end()) Q.erase(it2);
          Q.emplace(cost2, mask2);
          dist[mask2]=cost2;
        }
      }
    }
    
    return dist[end];
  }
};

// O(N*2^M) time
int dp[1<<20];
class OrderOfOperationsDiv2_dp {
public:
  const int Inf=405;
  int minTime(vector<string> s) {
    int N=SZ(s),M=SZ(s[0]);
    VI S(N);
    int end=0;
    REP(i,N) {
      int mask=0;
      REP(j,M) if(s[i][j]=='1') mask|=(1<<j);
      S[i]=mask;
      end |= mask;
    }
    REP(mask,end+1) dp[mask]=Inf;

    dp[0]=0;
    REP(mask,end) if(dp[mask]<Inf) REP(i,N) {
      int mask2=mask|S[i];
      int d = __builtin_popcount(mask2)-__builtin_popcount(mask);
      dp[mask2]=min(dp[mask2], dp[mask]+d*d);
    }
    
    return dp[end];
  }
};

class OrderOfOperationsDiv2_wrong_greedy {
  public:
  int minTime(vector<string> S) {
    int N=SZ(S),M=SZ(S[0]);
    vector<II> SS(N);
    REP(i,N) {
      int mask=0;
      REP(j,M) if(S[i][j]=='1') mask|=(1<<j);
      SS[i]={__builtin_popcount(mask), mask};
    }
    sort(SS.begin(),SS.end());
    int mask=0,res=0;
    REP(i,N) {
      int mask2=SS[i].second;
      int dif=__builtin_popcount(mask2)-__builtin_popcount(mask&mask2);
      res += dif*dif;
      mask |= mask2;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("OrderOfOperationsDiv2.sample");

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

bool do_test(vector<string> s, int __expected) {
    time_t startClock = clock();
    OrderOfOperationsDiv2 *instance = new OrderOfOperationsDiv2();
    int __result = instance->minTime(s);
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
        vector<string> s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502986900;
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
        cout << "OrderOfOperationsDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
