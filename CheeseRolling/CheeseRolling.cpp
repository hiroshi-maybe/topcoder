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
 
 8/22/2017
 
 8:19-9:12 try TLE solution and TLE in sample 3 as expected
 18:50-19:32 tried ztransform and gave up
 
 my TLE recurrence relation:
  - dp[W[x][y]?x:y][k][smask1|smask2] = dp[x][k-1][smask1] * dp[y][k-1][smask2]
      where smask1&smask2=0, popcount(smask1)=popcount(smask2), smask1,smask2 = 0...2^N
 
 19:33-19:56 read editorial and passed system test
  - http://kmjp.hatenablog.jp/entry/2015/08/01/1000
  - https://apps.topcoder.com/wiki/display/tc/SRM+663

 let mask = smask1|smask2. then mask ⊃ smask1, mask ⊃ smask1, smask2 = mask ^ smask1
 smask1 = { mask : mask ⊂ mask, popcount(mask)*2 = popcount(mask) }
 We can get smask1 by O(3^N) time. Then smask2 = mask^mask1 (complement of mask1 in superset mask)
 
 Now DP formula is...
 dp[W[x][y]?x:y][mask] += dp[x][smask1] * dp[y][smask2]
  for mask = 0..2^N, x=0..N-1, y=0..N-1
 dp[x][1<<x]=1LL
 
 res[x] = dp[x][(1<<N)-1]
 
 Key:
  - DP state transition between supermask and subamask => submask enumeration by O(3^N)
   - https://e-maxx-eng.appspot.com/algebra/all-submasks.html
   - http://codeforces.com/blog/entry/18169
 
 Summary:
  - recurrence relation was close though, completely forgot submask enumeration
  - should have taken care of superset/subset relation
 
 23:20-23:35 add more efficient editorial solution
 
 */

// O(N^2*3^N) time < 1*10^10, this fits 4 second time limit
LL dp[17][1<<16];
class CheeseRolling {
public:
  vector<long long> waysToWin(vector<string> W) {
    int N=SZ(W);
    ZERO(dp);
    REP(mask, 1<<N) {
      int pc=__builtin_popcount(mask);
      if(pc&(pc-1)) continue;
      if(pc==1) {
        int x=__builtin_ctz(mask);
        dp[x][1<<x]=1LL;
        continue;
      }
      for(int smask1=mask; smask1>0; smask1=(smask1-1)&mask) if(__builtin_popcount(smask1)*2==pc) {
        int smask2=mask^smask1;
        REP(x,N) REP(y,N) if(x!=y) {
          dp[W[x][y]=='Y'?x:y][mask]+=dp[x][smask1]*dp[y][smask2];
        }
      }
    }
    
    vector<LL> res(N,0);
    REP(i,N) res[i]=dp[i][(1<<N)-1];
    return res;
  }
};

class CheeseRolling_org {
public:
  LL dp[17][5][1<<16];
  vector<long long> waysToWin(vector<string> W) {
    int N=SZ(W);
    int K=log2((double)N+0.1);
    ZERO(dp);
    REP(i,N) dp[i][0][1<<i]=1LL;
    
    FOR(k,1,K+1) REP(mask,1<<N) {
      int pc=__builtin_popcount(mask);
      if(pc&(pc-1)) continue; // technique: 2^k bit ON check
      
      // technique: submask enumeration
      for(int sub1=mask; sub1>0; sub1=(sub1-1)&mask) {
        int pc1=__builtin_popcount(sub1);
        if(pc1*2!=pc) continue; // half of bit ON check
        int sub2=sub1^mask;
        REP(x,N) REP(y,N) if(x!=y&&dp[x][k-1][sub1]&&dp[y][k-1][sub2]) {
          dp[W[x][y]=='Y'?x:y][k][sub1|sub2] += dp[x][k-1][sub1]*dp[y][k-1][sub2];
        }
      }
    }
    
    vector<LL> res(N);
    REP(i,N) res[i]=dp[i][K][(1<<N)-1];
    return res;
  }
};

/*
LL dp[17][5][1<<16];
LL z[17][5][1<<16];
class CheeseRolling {
public:
  vector<long long> waysToWin(vector<string> W) {
    int N=SZ(W);
    int K=log2((double)N+0.1);
    ZERO(dp);
    REP(i,N) dp[i][0][1<<i]=1LL;
    dump2(K,N);
    dump2(dp[0][0][1],dp[1][0][2]);
    
    FOR(k,1,K+1) {
      REP(x,N) {
        REP(mask,1<<N) z[x][k-1][mask]=dp[x][k-1][mask];
        // ztransform
        REP(i,N) REP(T,1<<N) {
          if ((T&(1<<i))==0) z[x][k-1][T]+=z[x][k-1][T|(1<<i)];
        }
      }
      
      REP(mask, 1<<N) {
        REP(x,N) REP(y,N) if(x!=y&&W[x][y]=='Y'&&dp[x][k-1][mask]) {
          dump3(x,y,mask);
          int mask2 = (~mask)&((1<<N)-1);
          dp[x][k][mask|(1<<y)] += 2*dp[x][k-1][mask]*z[y][k-1][mask2];
          dump4(mask2,dp[x][k-1][mask],z[y][k-1][mask2],dp[x][k][mask|(1<<y)]);
        }
      }
    }
    
    vector<LL> res(N);
    REP(i,N) REP(mask,1<<N) res[i]+=dp[i][K][mask];
    return res;
  }
};*/

class CheeseRolling_TLE {
  public:
  unordered_map<int,LL> dp[17][5];
  vector<long long> waysToWin(vector<string> W) {
    int N=SZ(W);
    int K=log2((double)N+0.1);
    ZERO(dp);
    REP(i,N) dp[i][0][1<<i]=1LL;

    FOR(k,1,K+1) REP(x,N) REP(y,N) if(x<y) {
      FORR(xp, dp[x][k-1]) FORR(yp, dp[y][k-1]) {
        int mask1=xp.first,mask2=yp.first;
        if((mask1&mask2)==0) {
//          dump4(k,x,y,2*xp.second*yp.second);
          dp[W[x][y]=='Y'?x:y][k][mask1|mask2] += 2*xp.second*yp.second;
        }
      }
    }
    
    vector<LL> res(N);
    REP(i,N) res[i]=dp[i][K][(1<<N)-1];
    return res;
  }
};

// CUT begin
ifstream data("CheeseRolling.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<string> wins, vector<long long> __expected) {
    time_t startClock = clock();
    CheeseRolling *instance = new CheeseRolling();
    vector<long long> __result = instance->waysToWin(wins);
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
        vector<string> wins;
        from_stream(wins);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(wins, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503415131;
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
        cout << "CheeseRolling (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
