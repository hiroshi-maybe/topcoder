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
 
 8/10/2017
 
 9:04-10:00 pause
 17:45-18:35 design
 18:40-18:47 impl idea and pased half of tests
 18:47-19:21 tried to redesign though, give up
 
 19:21-20:37 read editorials
 - http://mayokoex.hatenablog.com/entry/2015/11/28/105835
 - http://kmjp.hatenablog.jp/entry/2015/11/20/0930
 - https://apps.topcoder.com/wiki/display/tc/SRM+673
 
 f(n) = ∑ { f(i)*(n-i-1)!+f(n-i-1)*i!+∑∑ {(k-j)*(i-1)!*(n-i-2)! : j=0..i-1, k=i+1..n-1 } : i=0..n-1 }
 f(0) = f(1) = f(2) = 0
 
 22:20-23:00 add solution
 
 Key:
 - use recursive property of tree
  - two subtrees are also cartesian trees in a cartesian tree
  - topdown approach
 - value itself does NOT affect result in size-n array
  - calculate result for sub-array and multiply by all the patterns
 - once smallest number is pinned to calculate score, order of other numbers don't matter
  - calculate score and multiply by possible orders of other numbers
  - once i numbers are chosen from n-1, smallest number is determined because nubmers are distinct.
 - sum of two factors of score
  1. sum of left tree score * right permutation + sum of right tre score * left permutation
  2. abs(position of root of left subtree - position of root of right subtree) * combination of positions and groups
 
 Summary:
  - observe what is independent? what is dependent? carefully
  - too weak to count problem
 
 */

LL memo[101];

class BearPermutations2 {
public:
  LL MOD;
  LL CH[101][101];
  LL FACT[101];
  
  // Populate n chooses k (n={1..N},k={1..N}) (accumulate by DP)
  // C(n,k) = C(n-1,k)+C(n-1,k-1)
  // O(N^2) time
  void choose(LL N) {
    // i chooses j
    for(int i=0; i<=N; ++i) {
      CH[i][0]=1;
      for(int j=1; j<=i; ++j) {
        CH[i][j] = CH[i-1][j]+CH[i-1][j-1], CH[i][j]%=MOD;
      }
    }
  }
  
  void fact(LL n) {
    FACT[0]=1;
    for(LL i=1; i<=n; ++i) FACT[i]=FACT[i-1]*i, FACT[i]%=MOD;
  }
  
  LL f(int n) {
    if(n<=2) return 0;
    if(memo[n]>=0) return memo[n];
    
    LL res=0;
    REP(i,n) {
      LL a=f(i)*FACT[n-i-1]; a%=MOD;
      a+=f(n-i-1)*FACT[i], a%=MOD;
      REP(j,i) FOR(k,i+1,n) {
        LL x=(k-j)*FACT[i-1]; x%=MOD;
        x*=FACT[n-i-2], x%=MOD;
        a+=x, a%=MOD;
      }
      a*=CH[n-1][i], a%=MOD;
      res+=a, res%=MOD;
    }
    
    return memo[n]=res;
  }
  
  int getSum(int N, int _MOD) {
    MOD=_MOD;
    MINUS(memo);
    ZERO(CH); ZERO(FACT);
    choose(N); fact(N);
    
    return f(N);
  }
};

LL F[101][101][2];
LL G[101][101];
class BearPermutations2_wrong {
public:
  LL MOD;
  LL f(int k, int l, int gt) {
    dump4("f",k,l,gt);
    if(l==0) return 0;
    if(F[k][l][gt]>=0) return F[k][l][gt];
    
    LL res=0;
    REP(p,l) {
      res+=f(p,l-p-1,0), res%=MOD;
      if(gt) { res+=2+k+p+f(k,p,1);
        dump4(k,l,p,2+k+p);
      } else res+=f(k,p,0);
      res%=MOD;
    }
    
    return F[k][l][gt]=res;
  }
  LL g(int k, int l) {
    dump3("g",k,l);
    if(k==0) {
      if(l==0) return 0;
      else return g(l,0);
    }
    if(G[k][l]>=0) return G[k][l];
    
    LL res=0;
    REP(p,k) {
      res+=g(p,k-p-1), res%=MOD;
      res+=f(k-p-1,l,1), res%=MOD;
    }
    
    return G[k][l]=res;
  }
  
  int getSum(int N, int _MOD) {
    MOD=_MOD;
    MINUS(F); MINUS(G);
    
    return g(N,0);
  }
};

// CUT begin
ifstream data("BearPermutations2.sample");

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

bool do_test(int N, int MOD, int __expected) {
    time_t startClock = clock();
    BearPermutations2 *instance = new BearPermutations2();
    int __result = instance->getSum(N, MOD);
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
        int MOD;
        from_stream(MOD);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, MOD, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502430392;
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
        cout << "BearPermutations2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
