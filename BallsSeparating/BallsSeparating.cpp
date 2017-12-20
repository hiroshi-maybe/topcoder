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
 
 12/18/2017
 
 12:16-12:58 analysis
 12:58-13:34 implement and submit (179.62 pt)
 13:35 1WA due to too small Inf
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+568
  - http://kmjp.hatenablog.jp/entry/2013/01/30/0900
  - http://torus711.hatenablog.com/entry/20130130/p1
  - http://mayokoex.hatenablog.com/entry/2016/02/05/091149
  - http://tckintore.blogspot.com/2013/06/4-srm568-div1easy-balls-separating.html
 
 Key:
  - Number of balls is always positive. No need to worry about zero ball in a box
  - We make a decision which color we keep in each box separately
  - At least one box is needed to keep balls of a color. We can brute-force it.
 
 Summary:
  - Two reasons why it took a lot of time in analysis
   - I missed a constraint that number of ball is POSITIVE
    - So my original code is unnecessarily complicated
   - Poor sense of analysis of dependency
    - In my original algorithm, greedily leaving color whose ball is the most
    - However decision in each box is independent
    - It's possible to simply make a decision from left to right
 
 */

// dp, O(3*N*2^3) time
int memo[51][1<<3];
class BallsSeparating {
public:
  int N;
  const int Inf=1e6*51*3;
  vector<VI> X;
  int f(int i, int mask) {
    if(i==N) return __builtin_popcount(mask)==3?0:Inf;
    int &res=memo[i][mask];
    if(res>=0) return res;
    res=Inf;
    REP(j,3) res=min(res,X[0][i]+X[1][i]+X[2][i]-X[j][i]+f(i+1,mask|(1<<j)));
    return res;
  }
  int minOperations(vector<int> A, vector<int> B, vector<int> C) {
    this->X={A,B,C};
    this->N=SZ(A);
    if(N<3) return -1;
    MINUS(memo);
    return f(0,0);
  }
};

// brute-force and greedy, O(N^4) time
class BallsSeparating_greedy {
public:
  int minOperations(vector<int> A, vector<int> B, vector<int> C) {
    int N=SZ(A);
    if(N<3) return -1;
    int res=1e6*51*3;
    
    REP(a,N) REP(b,N) REP(c,N) if(a!=b&&b!=c&&c!=a) {
      int cnt=0;
      REP(i,N) {
        if(i==a) { cnt+=B[i]+C[i]; continue; }
        if(i==b) { cnt+=A[i]+C[i]; continue; }
        if(i==c) { cnt+=B[i]+A[i]; continue; }
        
        /*
         // my original code
         if(A[i]>=B[i]&&A[i]>=C[i]) { cnt+=B[i]+C[i]; continue; }
         if(B[i]>=A[i]&&B[i]>=C[i]) { cnt+=A[i]+C[i]; continue; }
         cnt+=B[i]+A[i];
         */
        // inspired by @kmjp's code
        cnt += A[i]+B[i]+C[i]-max({A[i],B[i],C[i]});
      }
      res=min(res,cnt);
    }
    
    return res;
  }
};

// O(N^4) time
class BallsSeparating_org {
public:
  int minOperations(vector<int> red, vector<int> green, vector<int> blue) {
    int rsum=accumulate(red.begin(),red.end(),0);
    int gsum=accumulate(green.begin(),green.end(),0);
    int bsum=accumulate(blue.begin(),blue.end(),0);
    if(rsum>gsum) swap(green,red),swap(rsum,gsum);
    if(gsum>bsum) swap(green,blue),swap(gsum,bsum);
    if(rsum>gsum) swap(green,red),swap(rsum,gsum);
    
    if(rsum==0&&gsum==0) return 0;
    int N=SZ(red);
    
    vector<II> A,B,C;
    REP(i,N) A.emplace_back(red[i],i),B.emplace_back(green[i],i),C.emplace_back(blue[i],i);
    sort(A.rbegin(),A.rend()),sort(B.rbegin(),B.rend()),sort(C.rbegin(),C.rend());
    
    const int Inf=1e6*51*3;
    int res=Inf;
    if(rsum==0) {
      /*
       // This is not necessary because r[i],g[i],b[i]>0
       REP(i,N) REP(j,N) if(i!=j) {
       int viz[50]={};
       viz[i]=2,viz[j]=3;
       int cnt=0;
       int bi=0,ci=0;
       while(bi<N||ci<N) {
       while(bi<N&&viz[B[bi].second]!=0) { if(viz[B[bi].second]!=2) {cnt+=B[bi].first;} ++bi; }
       while(ci<N&&viz[C[ci].second]!=0) { if(viz[C[ci].second]!=3) {cnt+=C[ci].first;} ++ci; }
       if(bi<N&&(ci>=N||B[bi].first>=C[ci].first)) {
       viz[B[bi++].second]=2;
       } else if(ci<N) {
       viz[C[ci++].second]=3;
       }
       }
       res=min(res,cnt);
       }*/
    } else {
      REP(i,N) REP(j,N) REP(k,N) if(i!=j&&j!=k&&k!=i) {
        //        dump3(i,j,k);
        int viz[50]={};
        viz[i]=1,viz[j]=2,viz[k]=3;
        int cnt=0;
        int ai=0,bi=0,ci=0;
        while(ai<N||bi<N||ci<N) {
          while(ai<N&&viz[A[ai].second]!=0) { if(viz[A[ai].second]!=1) {cnt+=A[ai].first;} ++ai; }
          while(bi<N&&viz[B[bi].second]!=0) { if(viz[B[bi].second]!=2) {cnt+=B[bi].first;} ++bi; }
          while(ci<N&&viz[C[ci].second]!=0) { if(viz[C[ci].second]!=3) {cnt+=C[ci].first;} ++ci; }
          if(ai<N&&((bi>=N&&ci>=N)||(bi>=N&&A[ai].first>=C[ci].first)||(ci>=N&&A[ai].first>=B[bi].first)||(A[ai].first>=B[bi].first&&A[ai].first>=C[ci].first))) {
            viz[A[ai++].second]=1;
          } else if(bi<N&&((ai>=N&&bi>=N)||(ai>=N&&B[bi].first>=C[ci].first)||(ci>=N&&B[bi].first>=A[ai].first)||(B[bi].first>=A[ai].first&&B[bi].first>=C[ci].first))) {
            viz[B[bi++].second]=2;
          } else if(ci<N) {
            viz[C[ci++].second]=3;
          }
        }
        //        dumpAR(viz);
        res=min(res,cnt);
      }
    }
    
    return res==Inf?-1:res;
  }
};

// CUT begin
ifstream data("BallsSeparating.sample");

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

bool do_test(vector<int> red, vector<int> green, vector<int> blue, int __expected) {
    time_t startClock = clock();
    BallsSeparating *instance = new BallsSeparating();
    int __result = instance->minOperations(red, green, blue);
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
        vector<int> red;
        from_stream(red);
        vector<int> green;
        from_stream(green);
        vector<int> blue;
        from_stream(blue);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(red, green, blue, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513628162;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BallsSeparating (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
