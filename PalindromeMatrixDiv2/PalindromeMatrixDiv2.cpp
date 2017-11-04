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
 
 11/1/2017
 
 9:57-10:25 analysis
 10:25-11:08 1WA (369.52 pt)
 11:08-11:13 bug fix and TLE
 11:13-11:32 pause
 18:20-18:50 time up
 
 25:30-26:30 read editorial:
  - http://topcoder.g.hatena.ne.jp/peryaudo/20160416/1460776683
   - dfs merge
  - http://emkcsharp.hatenablog.com/entry/SRM600/PalindromeMatrixDiv2
   - union-find merge
  - http://topcoder.g.hatena.ne.jp/peryaudo/20160416/1460776683
   - adhoc merge
 
 11/3/2017
 
 If we fix rows and columns which should be palindrome, there are 2^8*2^8=2^16 sub problems that we should solve.
 How do we count number of cells that we should change?
 Palindrome is strong constraint that forces A[i][x] = A[N-i-1][x] where i=0..N-1
 This constraint is transitive.
 So A[x1][y1] = A[x2][y2] and A[x2][y2] = A[x3][y3] obviously means A[x1][y1]=A[x2][y2]=A[x3][y3]
 We can create such L groups. In each group G[i], minimum number to change cell X[i] can be computed as below:
  X[i] = { min(c0,c1) : c0=|{(x,y) : x,y∈G[i], A[x][y]=0 }|, c1=|{(x,y) : x,y∈G[i], A[x][y]=1 }| }
  f(mask of row, mask of col) = ∑ { X[i] : i=0..L-1 }
 
 T(f(m1,m2)) = O(N*M). So this algorithm works in O(2^(N+M)*N*M) time or O(2^(N+M)*N*M*lg (N*M)) if union find without rank is used.
 
     *  *
   |012345
 ----------
 *0|010101
  1|110011
 *2|001100
  3|101010
 
 In this example...
 G0: A[0][0]=A[0][5]
 G1: A[0][1]=A[0][4]=A[3][4]=A[3][1]
 ...
 
 21:20-22:10 understand editorial
 22:10-22:50 implemented and system test passed. It took much time to find a bug of initilization of unioun find array 😵
 
 Key:
  - Firstly we can brute force rows and columns which should be palindrome.
  - Propagating transitive binary relation makes set of cells (graph with at most four vertices)
  - We can compute minimum number to change cells in each group in linear time O(N*M)
 
 Summary:
  - Made a mistake in running analysis. Therefore my code TLEed
  - Fixing palidrome rows by brute-force was right approach though, I couldn't figure out how to handle propagating equality constraint
  - Impressive problem to reduce to subproblem which builds small graphs
 
 */
int memo[9][9];
int A[9][9];
class PalindromeMatrixDiv2 {
public:
  const int Inf=100;
  int N,M;
  int RC,CC;
  VI uf;
  int find(int i) { return i==uf[i]?i:uf[i]=find(uf[i]); }
  void unite(int i1, int i2) {
    int p1=find(i1),p2=find(i2);
    uf[p1]=p2;
  }
  int minChange(vector<string> A, int RC, int CC) {
    this->N=SZ(A),this->M=SZ(A[0]);
    this->RC=RC, this->CC=CC;
    uf=VI(N*M,0);
    
    int res=Inf;
    REP(mask1,1<<N) if(__builtin_popcount(mask1)==RC) {
      REP(mask2,1<<M) if(__builtin_popcount(mask2)==CC) {
        REP(i,N*M) uf[i]=i;
        REP(i,N) if(mask1&(1<<i)) {
          int l=0,r=M-1;
          while(l<r) {
            unite(M*i+l,M*i+r);
            ++l,--r;
          }
        }
        REP(j,M) if(mask2&(1<<j)) {
          int l=0,r=N-1;
          while(l<r) {
            unite(M*l+j,M*r+j);
            ++l,--r;
          }
        }
        
        MAPII X0,X1;
        VI G;
        REP(i,N*M) if(find(i)==i) G.push_back(i);
        REP(i,N*M) {
          int g=find(i);
          (A[i/M][i%M]=='1'?X1[g]:X0[g])+=1;
        }
        int cnt=0;
        FORR(g,G) cnt+=min(X0[g],X1[g]);
        res=min(res,cnt);
      }
    }
    return res;
  }
};

class PalindromeMatrixDiv2_TLE {
  public:
  const int Inf=100;
  vector<string> AA;
  int N,M;
  int RC,CC;
  int f(int j, int cc, int mask) {
    if(j==M) return cc==0?0:Inf;
    if(memo[j][cc]>=0) return memo[j][cc];
    if(cc==0) return f(j+1,cc,mask);
    
    int cnt=0;
    int l=0,r=N-1;
    while(l<r) {
      cnt+=A[l][j]!=A[r][j];
      ++l,--r;
    }
    
    int res=min(f(j+1,cc,mask), cnt+f(j+1,cc-1,mask));
    
    return memo[j][cc]=res;
  }
  
  int g(vector<II> masks) {
    MINUS(memo);
    ZERO(A);
    
    REP(i,N)REP(j,M) A[i][j]=AA[i][j]=='1';
    
    int mask2=0;
    int cnt=0;
    FORR(p,masks) {
      int i=p.first,mask=p.second;
      mask2|=(1<<i);
      int l=0,r=M-1;
      while(l<r) {
        int e=(mask>>l)&1;
//        if(A[i][l]!=e&&A[i][r]!=e) return Inf;
        if(A[i][l]!=e) ++cnt,A[i][l]=e;
        if(A[i][r]!=e) ++cnt,A[i][r]=e;
        ++l,--r;
      }
    }
    
    int res=cnt+f(0,CC,mask2);
    
    return res;
  }
  
  int dfs(int i, vector<II> &cur) {
    if(i==RC) return g(cur);
    int res=Inf;
    REP(mask,1<<(M/2)) {
      cur[i].second=mask;
      res=min(res,dfs(i+1,cur));
      cur[i].second=-1;
    }
    return res;
  }
  
  int minChange(vector<string> AA, int RC, int CC) {
    this->N=SZ(AA),this->M=SZ(AA[0]);
    this->AA=AA;
    this->RC=RC, this->CC=CC;
    
    int res=Inf;
    REP(mask,1<<N) if(__builtin_popcount(mask)==RC) {
      vector<II> masks(RC);
      int j=0;
      REP(i,N) if(mask&(1<<i)) masks[j++]={i,-1};
      res=min(res,dfs(0,masks));
    }
    return res;
  }
};

// CUT begin
ifstream data("PalindromeMatrixDiv2.sample");

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

bool do_test(vector<string> A, int rowCount, int columnCount, int __expected) {
    time_t startClock = clock();
    PalindromeMatrixDiv2 *instance = new PalindromeMatrixDiv2();
    int __result = instance->minChange(A, rowCount, columnCount);
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
        vector<string> A;
        from_stream(A);
        int rowCount;
        from_stream(rowCount);
        int columnCount;
        from_stream(columnCount);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, rowCount, columnCount, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509555451;
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
        cout << "PalindromeMatrixDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
