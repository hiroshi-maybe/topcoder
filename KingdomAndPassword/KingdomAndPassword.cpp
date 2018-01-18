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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/16/2018
 
 9:01-9:10, 9:23-9:30 analysis
 9:45 sample 3 doesn't pass
 10:04 pause
 
 18:15-18:55 trying to prune branch in back-tracking...
 18:56-19:25 analyze greedy approach and figure out DP solution.
 20:35-21:06 implement DP and system test passed
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+548
  - http://kmjp.hatenablog.jp/entry/2013/12/28/1130
  - http://d.hatena.ne.jp/simezi_tan/20120710/1341873456
    - keep difference in DP state and restore it later
    - very smart ✅
 
 Key:
  - One problem reduction minimum absolute value => smallest larger than P or largest smaller than P
 
 Summary:
  - dp => brute-force => greedy => dp .. very long way to find a solution 😵
 
 */

// O(2N*2^N) time
string dp[1<<16][2];
class KingdomAndPassword {
public:
  int N;
  string P;
  string NG;
  string mkLarge() {
    int M=1<<N;
    REP(a,2) REP(mask,M) dp[mask][a]="~";
    dp[0][0]="";
    REP(mask,M) REP(any,2) if(dp[mask][any]!="~") {
      int k=__builtin_popcount(mask);
      REP(i,N) if((mask&(1<<i))==0) {
        if(NG[k]==(P[i])) continue;
        int mask2=mask|(1<<i);

        if(any==0) {
          if(P[k]==P[i]) MINS(dp[mask2][0],dp[mask][0]+P[i]);
          if(P[k]<P[i]) MINS(dp[mask2][1],dp[mask][0]+P[i]);
        }
        if(any==1) MINS(dp[mask2][1],dp[mask][1]+P[i]);
      }
    }
    
    if(dp[M-1][0]!="~") return dp[M-1][0];
    return dp[M-1][1];
  }
  
  string mkSmall() {
    int M=1<<N;
    REP(a,2) REP(mask,M) dp[mask][a]="#";
    dp[0][0]="";
    REP(mask,M) REP(any,2) if(dp[mask][any]!="#") {
      int k=__builtin_popcount(mask);
      REP(i,N) if((mask&(1<<i))==0) {
        if(NG[k]==(P[i])) continue;
        int mask2=mask|(1<<i);
        
        if(any==0) {
          if(P[k]==P[i]) MAXS(dp[mask2][0],dp[mask][0]+P[i]);
          if(P[k]>P[i]) MAXS(dp[mask2][1],dp[mask][0]+P[i]);
        }
        if(any==1) {
          MAXS(dp[mask2][1],dp[mask][1]+P[i]);
        }
      }
    }
    if(dp[M-1][0]!="#") return dp[M-1][0];
    return dp[M-1][1];
  }
  
  long long newPassword(long long p, vector<int> NG_) {
    this->P=to_string(p);
    this->N=SZ(P);
    REP(i,N) this->NG.push_back('0'+NG_[i]);
    
    string l=mkLarge(),s=mkSmall();
    dump2(l,s);
    if(l=="~"&&s=="#") return -1;
    if(l=="~") return stoll(s);
    if(s=="#") return stoll(l);
    LL ll=stoll(l),ss=stoll(s);
    return abs(ll-p)<abs(ss-p)?ll:ss;
  }
};

// TLE Brute-force, O(N!) time
class KingdomAndPassword_bruteforce {
public:
  int N;
  string P;
  string res="#";
  VI NG;
  string minabs(string x, string y) {
    int N=SZ(x);
//    dump3(P.substr(0,N),x,y);
    LL p=stoll(P.substr(0,N));
    LL xx=stoll(x),yy=stoll(y);
    if(abs(p-xx)<abs(p-yy)) return x;
    if(abs(p-yy)<abs(p-xx)) return y;
    return xx<yy?x:y;
  }
  
  void dfs(int p, string &cur) {
    if(p==N) {
      if(res=="#") res=cur;
      else res=minabs(cur,res);
      return;
    }
    
    // 145739817632645 (NG)
    // 241529363573463 (P)
    //  ^   ^
    
    // 239676554423331 (ex)
    // 231527363563494 (ac)
    
    FOR(i,p,N) if((cur[i]-'0')!=NG[p]) {
      swap(cur[p],cur[i]);
      dfs(p+1,cur);
      swap(cur[p],cur[i]);
    }
  }
  
  long long newPassword(long long op, vector<int> NG_) {
    this->P=to_string(op);
    this->NG=NG_;
    this->N=SZ(P);
    
    string PP=P;
    dfs(0,PP);
    return res=="#"?-1:stoll(res);
  }
};

// wrong DP
class KingdomAndPassword_dp {
  public:
  string P;
  string dp[1<<16];
  string minabs(string x, string y) {
    int N=SZ(x);
    dump3(P.substr(0,N),x,y);
    LL p=stoll(P.substr(0,N));
    LL xx=stoll(x),yy=stoll(y);
    if(abs(p-xx)<abs(p-yy)) return x;
    if(abs(p-yy)<abs(p-xx)) return y;
    return xx<yy?x:y;
  }
  long long newPassword(long long op, vector<int> NG) {
    this->P=to_string(op);
    int N=SZ(P);
    
    REP(mask,1<<N) dp[mask]="#";
    dp[0]="";
    REP(mask,1<<N) if(dp[mask]!="#") {
      REP(i,N) if((mask&(1<<i))==0) {
        int k=__builtin_popcount(mask);
        if(NG[k]==(P[i]-'0')) continue;
        int mask2=mask|(1<<i);
        string x=dp[mask]+P[i],y=dp[mask2];
        if(y=="#") dp[mask2]=x;
        else dp[mask2]=minabs(x,y);
      }
    }
    
    dump(dp[(1<<N)-1]);
    return dp[(1<<N)-1]=="#"?-1:stoll(dp[(1<<N)-1]);
  }
};

// CUT begin
ifstream data("KingdomAndPassword.sample");

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

bool do_test(long long oldPassword, vector<int> restrictedDigits, long long __expected) {
    time_t startClock = clock();
    KingdomAndPassword *instance = new KingdomAndPassword();
    long long __result = instance->newPassword(oldPassword, restrictedDigits);
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
        long long oldPassword;
        from_stream(oldPassword);
        vector<int> restrictedDigits;
        from_stream(restrictedDigits);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(oldPassword, restrictedDigits, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1516122062;
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
        cout << "KingdomAndPassword (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
