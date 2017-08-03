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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 8/2/2017
 
 9:07-9:50 give up
 18:50-20:55,22:30-23:30 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/02/07/1030
 - https://apps.topcoder.com/wiki/display/tc/SRM+681
 
 23:30-24:11 gave up and copied @kmjp solution
 
 Key
 - X<M in bit computation => look at from more significant bit to less significant bit
  - X[..d]==M[..d] => X[d-1..0] should be M[d-1..0]
  - X[..d]< M[..d] => X[d-1..0] can be any number
 - mask2 is subset of mask? `mask2&mask==mask2`
 - precompute validity to save time
 
 Summary:
  - 👍 consider each bit separatedly
  - my approach: pin bit and tried to satisfy A[i]<=m. However it was hard.
   - closer to approach in official editorial
  - solution's approach: keep A[i]<=m. look at each bit so that S[i][j] satisfies A[i]^A[j]
   - @kmjp's approach
 
 */

constexpr int MOD = 1e9+7;

// https://apps.topcoder.com/wiki/display/tc/SRM+681
class XorLists {
public:
  int countLists(vector<int> s, int m)
  {
    
    // translate m to binary:
    vector<int> bit_m;
    for (int i = 0; i < 30; i++) {
      bit_m.push_back( m % 2 );
      m /= 2;
    }
    reverse(bit_m.begin(), bit_m.end() );
    int n = 0;
    while ( (n + 1)*(n + 1) <= s.size() ) {
      n++;
    }
    int t = bit_m.size();
    
    
    // precalculate which bit combinations are valid for each bit position:
    bool valid_mask[1<<n][t];
    for (int mask = 0; mask < (1<<n); mask++) {
      for (int i = 0; i < t; i++) {
        valid_mask[mask][i] = true;
        for (int a = 0; a < n; a++) {
          for (int b = 0; b < n; b++) {
            int x = (mask >> a) & 1;
            int y = (mask >> b) & 1;
            int z = (s[a*n + b] >> (t-i-1) ) & 1;
            if ( (x ^ y) != z ) {
              valid_mask[mask][i] = false;
            }
          }
        }
        
      }
      
    }
    
    
    // the dynamic programming
    int dp[1<<n][t+1];
    
    // the base case, all bits have been assigned, it doesn't matter if
    // the number is less or equal to m, all those cases are valid
    for (int eq_mask = 0; eq_mask < (1 << n); eq_mask++) {
      dp[eq_mask][t] = 1;
    }
    
    for (int i = t - 1; i >= 0; i--) {
      for (int eq_mask = 0; eq_mask < (1 << n); eq_mask++) {
        // Calculate each f(eq_mask, i)
        dp[eq_mask][i] = 0;
        // try all combinations:
        for (int mask = 0; mask < (1 << n); mask++) {
          int neq_mask = 0;
          bool valid = valid_mask[mask][i];
          
          for (int j = 0; (j < n) && valid; j++) {
            // verify if this bit won't make the number larger than m
            int b = (mask >> j) & 1;
            int e = (eq_mask >> j) & 1;
            int ne = e;
            if (e == 1) {
              if (b > bit_m[i]) {
                valid = false;
              } else if (b < bit_m[i]) {
                // no longer equal
                ne = 0;
              }
            }
            neq_mask = (neq_mask | (ne << j) );
          }
          
          
          if (valid) {
            dp[eq_mask][i] = (dp[eq_mask][i] + dp[neq_mask][i+1]) % MOD;
          }
        }
      }
    }
    
    return dp[ (1<<n) - 1][0];
  }
};

int S[10][10];
LL memo[31][1<<10];
int OK[31][1<<10];

class XorLists_kmjp {
  public:
  int N,M,D;
  LL f(int d, int mask) {
    if(d<0) return 1;
    if(mask==0) return 1<<(d+1);
    if(memo[d][mask]>=0) return memo[d][mask];
    LL res=0;
    REP(mask2,1<<N) if((mask2&mask)==mask2) {
      //if(!OK[d][mask2]) continue;
      
      // from @kmjp
      int ng=0;
      REP(y,N) REP(x,y) if((mask>>x)&(mask>>y)&1) if(((S[x][y]>>d)^(mask2>>x)^(mask2>>y))&1) ng++;
      if(ng>0) continue;
      
      if((M&(1<<d))==0) {
        if(mask2!=0) continue;
        res += f(d-1,mask);
      } else {
        res += f(d-1,mask2);
      }
      res %=MOD;
    }
    return memo[d][mask]=res;
  }
  
  int countLists(vector<int> s, int m) {
    N=sqrt(SZ(s)+0.1);
    M=m;
    memset(S, 0, sizeof S);
    memset(memo, -1, sizeof memo);
    memset(OK, 0, sizeof OK);
    
    REP(i,30) if((M>>i)&1) D=i;
    dump2(N,D);
    REP(i,N) REP(j,N) S[i][j]=s[i*N+j];
    
    // from @kmjp
    REP(x,N) if(S[x][x]) return 0;
    REP(y,N) REP(x,N) if(S[x][y]!=S[y][x]) return 0;
    REP(x,N) REP(y,N) REP(z,N) if(S[x][y]^S[y][z]^S[x][z]) return 0;
    
    /*
    REP(mask,1<<N) REP(d,D+1) {
      OK[d][mask]=true;
      REP(i,N) REP(j,N) {
        int x=(mask>>i)&1;
        int y=(mask>>j)&1;
        int z=(S[i][j]>>d)&1;
        if((x^y)!=z) OK[d][mask]=false;
      }
    }*/
    
    return f(D, (1<<N)-1)%MOD;
  }
};

// CUT begin
ifstream data("XorLists.sample");

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

bool do_test(vector<int> s, int m, int __expected) {
    time_t startClock = clock();
    XorLists *instance = new XorLists();
    int __result = instance->countLists(s, m);
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
        vector<int> s;
        from_stream(s);
        int m;
        from_stream(m);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501690051;
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
        cout << "XorLists (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
