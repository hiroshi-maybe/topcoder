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
 
 10/13/2017
 
 9:06-10:13 analysis
 10:14-10:24 implementation
 10:24-10:45 debug and pause
 20:15-21:25 time up
 21:26-22:40 compare with submit solution and system test passed
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+613
  - http://torus711.hatenablog.com/entry/20140322/1395477723
  - http://kmjp.hatenablog.jp/entry/2014/03/22/0930
 
 key:
  - number of possible value in S[i] is small. bit DP
  - F[i] is distinct. we should take care of only overlap with S[i]
 
 summary:
  - approach was correct though, ciritical mistake in design of recurrence relation 👎
    - don't forget mask when F[i]>10
  - That's not the only mistake. I had more
    - count of possible combination is just addition
    - unnecessary sort
  - I must be ashamed that I could not solve this problem by myself 😡
 
 clean submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=321084&rd=15846&pm=13015&cr=23069216
  - https://community.topcoder.com/stat?c=problem_solution&rm=321082&rd=15846&pm=13015&cr=40007626
 
 */
LL dp[51][101][1<<10];

// O(N*K*2^10) time
class TaroCards {
public:
  long long getNumber(vector<int> F, vector<int> S, int K) {
    int N=SZ(F);
    ZERO(dp);
    dp[0][0][0]=1;
    REP(i,N)REP(k,K+1)REP(mask,1<<10)if(dp[i][k][mask]>0) {
//      dump4(i,k,mask,dp[i][k][mask]);
      int f=F[i],s=S[i];
      
      int k2=k,mask2=mask;
      if(f>10) {
        ++k2;
      } else {
        int fm=1<<(f-1);
        k2+=(mask&fm)==0;
        mask2|=fm;
      }
      int sm=1<<(s-1);
      k2+=(mask2&sm)==0;
      mask2|=sm;
      dp[i+1][k2][mask2]+=dp[i][k][mask];
      dp[i+1][k][mask]+=dp[i][k][mask];
    }
    
    LL res=0;
    REP(x,K+1)REP(y,1<<10) {
//      if(dp[N][x][y]>0) {dump3(x,y,dp[N][x][y]);}
      res+=dp[N][x][y];
    }
    return res;
  }
};

class TaroCards_org {
public:
  long long getNumber(vector<int> F, vector<int> S, int K) {
    int N=SZ(F);
    vector<II> ps;
    SETI SS;
    REP(i,N) ps.emplace_back(F[i],S[i]), SS.emplace(F[i]), SS.emplace(S[i]);
    sort(ps.begin(),ps.end()); // this is unnecessary
    ZERO(dp);
    dp[0][0][0]=1;
    int KK=SZ(SS);
    REP(i,N)REP(k,KK+1)REP(mask,1<<10)if(dp[i][k][mask]>0) {
//      dump4(i,k,mask,dp[i][k][mask]);
      int f=ps[i].first,s=ps[i].second;

      int sm=1<<(s-1);
      if(f>10) {
        // dp[i+1][k+1][mask] += dp[i][k][mask];
        // I spent a few hours to find this bug. incredibly poor math sense.
        // I started an idea to sort by F. That brough a wrong recurrence relation to me.
        // `mask` represents state of already selected number in [1,10]
        // thus even if f>10, this may be the first time to take. then mask needs to be updated.
        dp[i+1][k+1+((mask&sm)==0)][mask|sm] += dp[i][k][mask];
      } else {
        int fm=1<<(f-1);
        
        if((mask&sm)==0&&(mask&fm)==0) {
          dp[i+1][k+1+(s!=f)][mask|sm|fm] += dp[i][k][mask];
        } else if((mask&sm)==0) {
          dp[i+1][k+1][mask|sm] += dp[i][k][mask];
        } else if((mask&fm)==0) {
          dp[i+1][k+1][mask|fm] += dp[i][k][mask];
        } else {
          dp[i+1][k][mask] += dp[i][k][mask];
        }
      }
      dp[i+1][k][mask]+=dp[i][k][mask];
    }
    
    LL res=0;
    REP(x,K+1)REP(y,1<<10) {
//      if(dp[N][x][y]>0&&x<=5) {dump3(x,y,dp[N][x][y]);}
      res+=dp[N][x][y];
    }
    return res;
  }
};

class TaroCards_wrong {
  public:
  long long getNumber(vector<int> F, vector<int> S, int K) {
    int N=SZ(F);
    vector<II> ps;
    REP(i,N)ps.emplace_back(F[i],S[i]);
    sort(ps.begin(),ps.end());
    ZERO(dp);
    dp[0][0][0]=1;
    REP(i,N)REP(k,2*N+1)REP(mask,1<<10)if(dp[i][k][mask]>0) {
      dump4(i,k,mask,dp[i][k][mask]);
      int f=ps[i].first,s=ps[i].second;
      int fm=1<<(f-1),sm=1<<(s-1);
      if(f<=10&&((mask&sm)==0)) {
        if(s!=f) {
          if(k+2<101) { dp[i+1][k+2][mask|sm|fm] += dp[i][k][mask]; /*dump4(i+1,k+2,mask|(1<<(s-1))|(1<<(f-1)),dp[i+1][k+2][mask|(1<<(s-1))|(1<<(f-1))]);*/ }
        } else {
          if(k+1<101) dp[i+1][k+1][mask|sm] += dp[i][k][mask];
        }
      }
      if((mask&sm)&&(mask&fm)==0&&s!=f) {
        int mask2=f<=10?(mask|fm):mask;
        if(k+1<101) dp[i+1][k+1][mask2] += dp[i][k][mask];
      }
      dp[i+1][k][mask]+=dp[i][k][mask];
    }
    
    LL res=0;
    REP(x,K+1)REP(y,1<<10) { if(dp[N][x][y]>0) {dump3(x,y,dp[N][x][y]);} res+=dp[N][x][y]; }
    return res;
  }
};

// CUT begin
ifstream data("TaroCards.sample");

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

bool do_test(vector<int> first, vector<int> second, int K, long long __expected) {
    time_t startClock = clock();
    TaroCards *instance = new TaroCards();
    long long __result = instance->getNumber(first, second, K);
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
        vector<int> first;
        from_stream(first);
        vector<int> second;
        from_stream(second);
        int K;
        from_stream(K);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(first, second, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507910760;
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
        cout << "TaroCards (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
