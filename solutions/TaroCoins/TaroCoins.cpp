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
 
 9/23/2017
 
 14:50-15:15 design
 15:16-15:59 tried to solve by remembering number of used coins though, it didn't work.
 16:00-16:19 remember carry over in DP. system test passed (328.60 pt)
 
 ( c[i-1], coin[i]) => (n[i],  c[i])
 (      0,       0) => (   0,     0)
 (      0,       1) => (   1,     0)
 (      0,       2) => (   0,     1)
 (      1,       0) => (   1,     0)
 (      1,       1) => (   0,     1)
 (      1,       2) => (   1,     1)
 
 f(i,1) = N[i]==1 ? f(i-1,1) : f(i-1,0)+f(i-1,1)
 f(i,0) = N[i]==0 ? f(i-1,0) : f(i-1,0)+f(i-1,1)
 f(0,0) = 1
 f(0,1) = N[0]==1
 res = f(61,0)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+631
  - http://kmjp.hatenablog.jp/entry/2014/08/31/1030
    - editorials are solving like coin exchange problem with branch pruning or semi greedy
    - proof of upper-bounded number of states is key

 (1+2+4+..+2^K) = 2^(K+1)-1
 <=> 2*(1+2+4+..+2^K) = 4*2^K-2, at most two coins can be used for each 2^i
 If N>4*2^K-2, it's impossible to pay by coins { 1,2,..,2^K }
 
 key:
  - column DP or coin exchange with branch pruning
 
 summary:
  - it's stupid to solve this problem in such a long time 😡
  - just a typical DP problem
  - original approach doesn't seem to be right
    - column i tries to pull carry though, carry is not necessarily associated with only number of coins at i-1
  - solutions in editorial is different from mine
    - they are proving that number of state is upper bounded by branch pruning
 
 submit solutions:
  - column dp
   - https://community.topcoder.com/stat?c=problem_solution&rm=323514&rd=16062&pm=12856&cr=23324636
    - simulating N-bit addition. short and clean code.
   - https://community.topcoder.com/stat?c=problem_solution&rm=323497&rd=16062&pm=12856&cr=40051994
   - https://community.topcoder.com/stat?c=problem_solution&rm=323513&rd=16062&pm=12856&cr=40049544
 
 */
LL memo[62][2];
class TaroCoins_org {
public:
  LL N;
  LL f(int i, int co) {
    if(i==0) {
      if(N&1LL) return co==0;
      else return 1;
    }
    if(memo[i][co]>=0) return memo[i][co];
    LL &res=memo[i][co];
    res=0;
    
    if(N&(1LL<<i)) {
      if(co) {
        res=f(i-1,1);
      } else {
        res=f(i-1,0)+f(i-1,1);
      }
    } else {
      if(co) {
        res=f(i-1,0)+f(i-1,1);
      } else {
        res=f(i-1,0);
      }
    }
    assert(res>=0);
    return res;
  }
  
  long long getNumber(long long N) {
    this->N=N;
    MINUS(memo);
    return f(61,0);
  }
};

map<pair<LL,int>, LL> dp;
class TaroCoins {
public:
  LL f(LL n, int i) {
    if(i==-1) return n==0;
    if(n<0||n>4*(1LL<<i)-2) return 0;
    if(dp.count({n,i})!=0) return dp[{n,i}];

    return dp[{n,i}]=f(n, i-1)+f(n-(1LL<<i), i-1)+f(n-(1LL<<i)*2, i-1);
  }
  
  long long getNumber(long long N) {
    dp.clear();
    return f(N,61);
  }
};

/*
LL dp[62][3];
class TaroCoins {
public:
  LL N;
  
  long long getNumber(long long N) {
    this->N=N;
    ZERO(dp);
    if(N&1) dp[0][1]=1;
    else dp[0][0]=dp[0][2]=1;
    
    FOR(i,1,61) {
      if(N&(1LL<<i)) {
        dp[i][1]+=dp[i-1][0]+dp[i-1][1];
        dp[i][0]+=dp[i-1][2];
      } else {
        dp[i][0]+=dp[i-1][0]+dp[i-1][1];
      }
    }
    return dp[
  }
};

LL memo[62][3];
class TaroCoins {
public:
  LL N;
  LL f(int i, int s) {
    if(i==0) {
      if(N&1LL) return s==1;
      else return s==0||s==2;
    }
    if(memo[i][s]>=0) return memo[i][s];
    LL &res=memo[i][s];
    res=0;
    
    if(N&(1LL<<i)) {
      if(s==0) res=f(i-1,2);
      else if(s==1) res=f(i-1,1)+f(i-1,0);
      else if(s==2) res=f(i-1,2);
    } else {
      if(s==0) res=f(i-1,0)+f(i-1,1);
      else if(s==1) res=0;
      else if(s==2) res=f(i-1,0)+f(i-1,1);
    }
    assert(res>=0);
    return res;
  }
  
  long long getNumber(long long N) {
    this->N=N;
    MINUS(memo);
    
    if(N&(1LL<<61)) return f(61,1)+f(60,2);
    return f(61,0);
  }
};

class TaroCoins_wrong {
  public:
  LL N;
  LL f(int i, int s) {
    if(i==0) {
      if(N&1LL) return s==1;
      else return s==0;
    }
    if(memo[i][s]>=0) return memo[i][s];
    LL &res=memo[i][s];
    res=0;
    
    int prevOn=(N&(1LL<<(i-1)))!=0;
    if(N&(1LL<<i)) {
      if(s==0) res=f(i-1,2);
      else if(s==1) res=prevOn?f(i-1,1):f(i-1,0);
      else if(s==2) res=!prevOn?f(i-1,2):0;
    } else {
      if(s==0) res=prevOn?f(i-1,1):f(i-1,0);
      else if(s==1) res=0;
      else if(s==2) res=f(i-1,0)?f(i-1,1):f(i-1,0);
    }
    assert(res>=0);
    return res;
  }
  
  long long getNumber(long long N) {
    this->N=N;
    MINUS(memo);
    
    if(N&(1LL<<61)) return f(61,1)+f(60,2);
    return f(61,0);
  }
};*/

// CUT begin
ifstream data("TaroCoins.sample");

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

bool do_test(long long N, long long __expected) {
    time_t startClock = clock();
    TaroCoins *instance = new TaroCoins();
    long long __result = instance->getNumber(N);
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
        long long N;
        from_stream(N);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506203410;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TaroCoins (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
