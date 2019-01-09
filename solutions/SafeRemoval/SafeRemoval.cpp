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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/9/2018
 
 22:15-22:30 analysis
 22:36-22:42 debug and find design bug. reanalyze..
 23:06 pause
 23:20-23:29 we eventually need order by DP, maybe greedy?
 23:39-23:42 greedy designed and submit. 1WA. design mistake
 23:43-23:54 give up
 
 1. Order matters -> Knapsack DP doesn't work
 2. I tried to keep state of (mod 4)
 
 However I could not figure out how to design state transition.
 It turned out semi-greedy strategy was needed.
 
 3. I also tried simple greedy solution though, I got WA and figured out that still order matters.
 I gave up.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+553
  - http://tccommunity.wpengine.com/tco12/happened-in-srm-553/
  - http://kmjp.hatenablog.jp/entry/2013/11/09/1000
  - http://area.hateblo.jp/entry/2013/12/29/063400
 
 1/10/2018
 
 17:00-17:31 Take a look at editorial, implement and submit. System test passed.
 
 Summary:
  - Needs search. That means dp should be a good option.
  - Looking at modulo was a good point though, it turned out that it's combination of greedy and DP
 
 */

// O(K^4) time
int dp[50][50][50][50];
VI X[4];
class SafeRemoval {
public:
  int removeThem(vector<int> S, int K) {
    REP(i,4) X[i].clear();
    sort(S.begin(),S.end());
    REP(i,SZ(S)) X[S[i]%4].push_back(S[i]);
    int tot=accumulate(S.begin(),S.end(),0);
//    dumpAR(S);
//    dump(tot);
    
    MINUS(dp);
    dp[0][0][0][0]=tot;
    int A=SZ(X[0]),B=SZ(X[1]),C=SZ(X[2]),D=SZ(X[3]);
//    dump4(A,B,C,D);
    REPE(a,A) REPE(b,B) REPE(c,C) REP(k,K) if(dp[a][b][c][k]>0) {
      int d=k-a-b-c;
      assert(d>=0);
//      dump4(a,b,c,d);
      int x=dp[a][b][c][k];
//      dump2(k,x);
      if(a<A&&(x-X[0][a])%4) MAXS(dp[a+1][b][c][k+1],x-X[0][a]);
      if(b<B&&(x-X[1][b])%4) MAXS(dp[a][b+1][c][k+1],x-X[1][b]);
      if(c<C&&(x-X[2][c])%4) MAXS(dp[a][b][c+1][k+1],x-X[2][c]);
      if(d<D&&(x-X[3][d])%4) MAXS(dp[a][b][c][k+1],x-X[3][d]);
    }
    
    int res=-1;
    REPE(a,A)REPE(b,B)REPE(c,C) MAXS(res,dp[a][b][c][K]);
    return res;
  }
};

int viz[50];
class SafeRemoval_wronggreedy {
public:
  int removeThem(vector<int> S, int K) {
    int N=SZ(S);
    sort(S.begin(),S.end());
    int tot=accumulate(S.begin(),S.end(),0);
    dumpAR(S);
    dump2(N,tot);

    ZERO(viz);
    int res=tot;
    while(K-->0) {
      bool ok=false;
      REP(i,N) if(!viz[i]&&(res-S[i])%4) {
        viz[i]=true;
        res-=S[i];
        ok=true;
        dump2(i,res);
        break;
      }
      if(!ok) return -1;
    }

    return res;
  }
};

class SafeRemoval_org {
  public:
  int dp[50001][50];
  int removeThem(vector<int> S, int K) {
    int N=SZ(S);
    int tot=accumulate(S.begin(),S.end(),0);
    dump2(N,tot);
    ZERO(dp);
    dp[tot][0]=1;
    REP(i,N) REPE(sum,tot) FORE(k,1,K) if(dp[sum][k-1]&&sum-S[i]>=0) {
      if((sum-S[i])%4!=0) {
//        dump4(i,sum,k,sum-S[i]);
        dp[sum-S[i]][k]|=dp[sum][k-1];
      }
    }
    
    int res=-1;
    REP(sum,tot) {
      dump2(sum,dp[sum][K]);
      if(dp[sum][K]) res=sum;
    }
    return res;
  }
};

// CUT begin
ifstream data("SafeRemoval.sample");

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

bool do_test(vector<int> seq, int k, int __expected) {
    time_t startClock = clock();
    SafeRemoval *instance = new SafeRemoval();
    int __result = instance->removeThem(seq, k);
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
        vector<int> seq;
        from_stream(seq);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(seq, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515564937;
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
        cout << "SafeRemoval (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
