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
 
 10/30/2017
 
 9:05-9:16 understood problem
 9:17-9:55 pause
 18:00-18:30 give up
 
 18:30-19:32 read editorials and add solution:
  - DP
   - https://apps.topcoder.com/wiki/display/tc/SRM+602
   - http://torus711.hatenablog.com/entry/20140105/p1
  - inclusion exclusion principle
   - http://kmjp.hatenablog.jp/entry/2013/12/29/1030
   - http://snuke.hatenablog.com/entry/2013/12/29/040056
     - writer's comment
  - both
   - http://emkcsharp.hatenablog.com/entry/SRM602/BlackBoxDiv2
 
 21:30-24:30 add solution with inclusion-exclusion principle
 
 1. DP
 
 Firstly just ignore empty cells and rebuild grid without them following coordinate compression idea.
 Problem is reduced to count cases to paint each grid without making empty row or column.
 What specific row or column paints doesn't matter by symmetric property.
 
 So we can build below recurrence relation as described in official editorial:
 
 Suppose we have H*W grid.
  f(x,y) = ∑ { yCs * f(x-1,y-s) * (2^(H-y) - (s==0)) : s=0..y }
  f(0,y) = y==0
  res = f(W,H)
 
 2. Inclusion exclusion principle
 
     res
   = U - | { r[i] is empty : i=0..R-1 } ∪ { c[j] is empty : j=0..C-1 } |
   = U - | ∪ { X[i] : i=0..R+C-1 } | // set of empty row and set of empty col are merged
   = U - ∑ { |X[i]| : i=0..R+C-1 } - ∑ { |X[i] ∩ X[j]| : 0<=i<j<=R+C-1 } + ∑ { |X[i] ∩ X[j] ∩ X[k]| : 0<=i<j<k<=R+C-1 }
   ...
 
   Thus res = ∑ { -1^(i+j) * 2^(R-i)*(C-j) * C(R,i) * C(C,j) : i=0..R-1, j=0..C-1 }
   This is counting number of grid with i empty rows and j empty cols and arbitrary assignment to others.
   Naiive computation is O(2^(R+C)) time due to assignment of empty/non-empty to each row and col though,
   this formula is merging different assignments by symmetry property.
 
 Key:
  - Ignore empty cells. This idea comes from coordinate compression.
  - Painting has symmetric property. Where to paint does not matter.
    - We can count by binomial coefficient without knowing which specific row was actually painted.
  - Inclusion exclusion principle
    - Ant book 4-1 more complex math problems
 
 Summary:
  - Both DP and inclusion-exclusion principle came up though, I couldn't solve
  - This problem was far away from my skill.
  - Great problem to learn some new techniques
   - ignore unrelated grid cells
   - dp with binomical coefficient leveraging symmetric property
   - inclusion exclusion principle
  - I should pay more attention to what should be remembered and what should NOT be remembered?
   - like ignorable empty cell in this problem..
 
 Submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=319986&rd=15820&pm=12929&cr=23288971
   - DP
   - f(i,j) = 2^(i*j) - ∑ { iCk * jCh * f(i-k,j-h) : k=0..i, h=0..j }
    - f(i,j) shows count of grids with no empty rows or no empty cols
    - res = f(R,C)
    - k rows are all '.' and h cols aer all '.'. Others f(i-k,j-h) are not empty
  - https://community.topcoder.com/stat?c=problem_solution&rm=319966&rd=15820&pm=12929&cr=23137498
   - DP
   - f(i,j) = ∑ { f(i-1,k)*2^k*(n-k)C(j-k) : k=0..j-1 }
   - res = f(R,C)
 
 */

constexpr int MOD = 1e9+7;
LL memo[51][51];
LL C[51][51];

LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}

class BlackBoxDiv2 {
public:
  int H,W;
  int count(string front, string side) {
    this->H=std::count(side.begin(),side.end(),'B');
    this->W=std::count(front.begin(),front.end(),'B');
    ZERO(C);
    REP(i,51) {
      C[i][0]=1;
      FOR(j,1,i+1) C[i][j]=(C[i-1][j-1]+  C[i-1][j])%MOD;
    }
    
    LL res=0;
    REP(i,H+1) REP(j,W+1) {
      LL a=powmod(2LL,(H-i)*(W-j));
      a*=C[H][i],a%=MOD;
      a*=C[W][j],a%=MOD;
      if((i+j)%2==0) {
        res+=a,res%=MOD;
      } else {
        res+=MOD-a,res%=MOD;
      }
    }
    return res;
  }
};

class BlackBoxDiv2_dp {
  public:
  int H,W;
  LL f(int x, int y) {
    if(x==0) return y==0;
//    if(y==0) return 1;
    if(memo[x][y]>=0) return memo[x][y];
//    dump3(x,y,memo[x][y]);
    LL res=0;
    REP(s,y+1) {
      LL a=C[y][s]*f(x-1,y-s); a%=MOD;
      LL b=(1LL<<(H-y))-(s==0); b%=MOD;
      a*=b,a%=MOD;
      res+=a,res%=MOD;
    }
    return memo[x][y]=res;
  }
  
  int count(string front, string side) {
    this->H=std::count(side.begin(),side.end(),'B');
    this->W=std::count(front.begin(),front.end(),'B');
    ZERO(C);
    REP(i,51) {
      C[i][0]=1;
      FOR(j,1,i+1) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
    }
    
    MINUS(memo);
    return f(W,H);
  }
};

// CUT begin
ifstream data("BlackBoxDiv2.sample");

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

bool do_test(string front, string side, int __expected) {
    time_t startClock = clock();
    BlackBoxDiv2 *instance = new BlackBoxDiv2();
    int __result = instance->count(front, side);
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
        string front;
        from_stream(front);
        string side;
        from_stream(side);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(front, side, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509379538;
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
        cout << "BlackBoxDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
