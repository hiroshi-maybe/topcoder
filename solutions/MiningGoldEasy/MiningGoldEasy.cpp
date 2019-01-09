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
 
 10/17/2017
 
 9:59-10:51 finally understood this problem. I was misunderstanding that goblin needs to be at the position of gold.
 10:52-11:07, 17:30-18:18 give up
 
 18:19-18:28, 18:50-19:06 read editorial:
   - https://apps.topcoder.com/wiki/display/tc/SRM+610
   - http://kmjp.hatenablog.jp/entry/2014/03/01/0930
   - http://topcoder.g.hatena.ne.jp/kagamiz/20140305
 
 We can move only in vertical or horizontal direction.
 If player's position does not match row or col of event positions,
 we'll pay more penalty in manhattan direction.
 
 Suppose player is going through event p,p+1,p+2 and event cells hold below condition.
  - ei[p]<ei[p+2]<ei[p+1]
  - ej[p]<ej[p+2]<ej[p+1]

 Player is at (x,y) s.t. ei[p]<x<ei[p+1],ej[p]<y<ej[p+1].
 Now we are going as close to (ei[p+2],ej[p+2]) as possible.
 If x≠ei[p+2] and y≠ej[p+2], we are paying extra penalty that does not happen if x=ei[p+2] or y=ej[p+2].
 Thus it's more efficient to keep (x,y) x∈ei or y∈ej
 
 19:07-19:43 add solution
 
 key:
  - no need to try {(x,y) : x∉ei or y∉ej }. We can select points greedily.
  - trying all positions relevant to ei and ej is trivial by DP
 
 summary:
  - I misunderstood this problem and wasted first 52 mins. Good job 👎
  - Possible cell is large 10^6*10^6. I tried to find optimal position in geometrical perspective though, no luck
  - I had never thought to try all positions { (x,y) : x∈ei and y∈ej }
 
 Submit solutions in contest:
  - DP
    - https://community.topcoder.com/stat?c=problem_solution&rm=320789&rd=15843&pm=12931&cr=23082290
    - https://community.topcoder.com/stat?c=problem_solution&rm=320808&rd=15843&pm=12931&cr=23099298
 
 */

// O(N^4) time
int dp[55][55][55];
class MiningGoldEasy {
public:
  int GetMaximumGold(int N, int M, vector<int> ei, vector<int> ej) {
    int D=SZ(ei);
    ZERO(dp);
    
    REP(k,D) REP(i,D) REP(j,D) {
      int X=ei[k],Y=ej[k];
      int d = N+M-abs(X-ei[i])-abs(Y-ej[j]);
      REP(ii,D) dp[k+1][ii][j]=max(dp[k+1][ii][j],dp[k][i][j]+d);
      REP(jj,D) dp[k+1][i][jj]=max(dp[k+1][i][jj],dp[k][i][j]+d);
    }
    
    int res=0;
    REP(i,D)REP(j,D) res=max(res,dp[D][i][j]);
    return res;
  }
};

// this greedy doesn't work in sample 4
class MiningGoldEasy__worngGreedy {
public:
  int GetMaximumGold(int N, int M, vector<int> ei, vector<int> ej) {
    int D=SZ(ei);
    int res=D*(N+M);
    int i=ei[0],j=ej[0];
    REP(k,D) {
      dump3(k,i,j);
      res-=abs(ei[k]-i)+abs(ej[k]-j);
      if(k<D-1) {
        if(abs(ei[k+1]-i)<abs(ei[k+1]-j)) {
          j=ej[k+1];
        } else {
          i=ei[k+1];
        }
      }
    }
    
    return res;
  }
};

// I was misunderstanding problem statement
class MiningGoldEasy_wrong {
  public:
  int GetMaximumGold(int N, int M, vector<int> ei, vector<int> ej) {
    int D=SZ(ei);
    int res=D*(N+M);
    FOR(i,1,D) res-=min(abs(ei[i]-ei[i-1]),abs(ej[i]-ej[i-1]));
    
    return res;
  }
};

// CUT begin
ifstream data("MiningGoldEasy.sample");

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

bool do_test(int N, int M, vector<int> event_i, vector<int> event_j, int __expected) {
    time_t startClock = clock();
    MiningGoldEasy *instance = new MiningGoldEasy();
    int __result = instance->GetMaximumGold(N, M, event_i, event_j);
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
        int N;
        from_stream(N);
        int M;
        from_stream(M);
        vector<int> event_i;
        from_stream(event_i);
        vector<int> event_j;
        from_stream(event_j);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, event_i, event_j, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508259571;
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
        cout << "MiningGoldEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
