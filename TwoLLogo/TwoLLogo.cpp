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
 
 10/9/2017
 
 10:05-10:54 pause
 17:30-18:10 analysis
 18:10-19:02 implementation
 19:02-20:09 give up
 
 22:30-22:52 read editorial:
  - http://apps.topcoder.com/wiki/display/tc/SRM+616
  - http://sucrose.hatenablog.com/entry/2014/04/11/021819
  - http://kmjp.hatenablog.jp/entry/2014/04/11/1030
 
 list up all possible largest Ls at each bottom-left point: O(N*M*(N+M)) time
 brute-force all the pairs of them: O(N^2*M^2) time
 
 subtract invalid pairs by classifying three forms as described in editorial.
 computation of number of invalid pairs can be done in O(1) time.
 
 22:53-24:19 add solution
 
 key:
  - identify Ls by bottom-left point
  - list up possible largest Ls and brute force pairs of them
 
 summary:
  - focused bottom-left corner to identify L shapes 👍
  - tried inclusion-exclusion though, I couldn't complete it 👎
  - TRY SIMPLE BRUTE FORCE FIRST 💢
   - asked to find pair of Ls. just list up all of them. estimate running time.
  - looking at exact two pairs => brute force two pairs is straightforward if there is no subproblem optimality between one L and two Ls

 */

typedef tuple<int,int,int,int> IIII;
vector<IIII> Ls;
class TwoLLogo {
public:
  LL f(IIII l1, IIII l2) {
    int i1,j1,h1,w1,i2,j2,h2,w2;
    tie(i1,j1,h1,w1)=l1, tie(i2,j2,h2,w2)=l2;
    LL res=1LL*w1*h1*h2*w2;
    
//    dump4(i1,j1,h1,w1);
//    dump4(i2,j2,h2,w2);
    
    if(j1<j2&&j2<=j1+w1&&i1<i2&&i2-h2<=i1) {
      res-=1LL*w2*h1*(h2-i2+i1+1)*(w1-j2+j1+1);
    } else if(i1==i2&&j1+w1>=j2) {
      res-=1LL*(j1+w1-j2+1)*(j1+w1-j2)*h1*h2;
    } else if(j1==j2&&i2-h2<=i1) {
      res-=1LL*(h2+i1-i2+1)*(h2+i1-i2)*w1*w2;
    }
//    dump2(1LL*w1*h1*h2*w2,res);
    return res;
  }
  
  long long countWays(vector<string> G) {
    Ls.clear();
    int N=SZ(G),M=SZ(G[0]);
    REP(i,N)REP(j,M) if(i>0&&j<M-1&&G[i][j]=='.'&&G[i-1][j]=='.'&&G[i][j+1]=='.') {
      int h=0,w=0;
      while(i-h-1>=0&&G[i-h-1][j]=='.') ++h;
      while(j+w+1<M&&G[i][j+w+1]=='.') ++w;
      
      Ls.emplace_back(i,j,h,w);
    }
    
//    REP(i,N)REP(j,M) dump4(i,j,H[i][j],W[i][j]);
    
    LL res=0;
    REP(j,SZ(Ls))REP(i,j) {
      res+=f(Ls[i],Ls[j]);
    }
    return res;
  }
};

LL cnt[31][31];
LL cntV[31][31];
LL cntH[31][31];
int W[31][31];
int H[31][31];
LL dp[31][31];
class TwoLLogo_wrong {
  public:
  long long countWays(vector<string> G) {
    ZERO(cnt); ZERO(cntV); ZERO(cntH); ZERO(W); ZERO(H);
    int N=SZ(G),M=SZ(G[0]);
    LL ALL=0;
    REP(i,N)REP(j,M) if(i>0&&j<M-1&&G[i][j]=='.'&&G[i-1][j]=='.'&&G[i][j+1]=='.') {
      int h=0,w=0;
      while(i-h-1>=0&&G[i-h-1][j]=='.') ++h;
      while(j+w+1<M&&G[i][j+w+1]=='.') ++w;
      W[i][j]=w,H[i][j]=h;
      for(int d=h; d>0; --d) {
        cnt[i-d][j]+=w*(h-d+1);
        cntV[i-d+1][j]+=w*(h-d+1);
      }
      for(int d=w; d>0; --d) {
        cnt[i][j+d]+=h*(w-d+1);
        cntH[i][j+d-1]+=h*(w-d+1);
      }
      cnt[i][j]+=h*w;
      ALL+=h*w;
    }

    REP(i,N)REP(j,M) dump4(i,j,H[i][j],W[i][j]);
    REP(i,N)REP(j,M) dump3(i,j,cnt[i][j]);
    REP(i,N)REP(j,M) dump3(i,j,cntV[i][j]);
    REP(i,N)REP(j,M) dump3(i,j,cntH[i][j]);

    LL res=0;
    REP(i,N)REP(j,M) if(W[i][j]>0&&H[i][j]>0) {
      dump2(i,j);
      ZERO(dp);
      dp[1][1]=ALL-cnt[i][j]-cnt[i-1][j]-cnt[i][j+1]+cntV[i][j]+cntH[i][j];
//      dump4(ALL,cnt[i][j],cnt[i-1][j],cnt[i][j-1]);
//      dump3(cntV[i][j],cntH[i][j],dp[1][1]);
      FOR(h,1,H[i][j]+1) FOR(w,1,W[i][j]+1) {
        if(h+1<N) dp[w][h+1]=max(dp[w][h]-(cnt[i-h-1][j]-cntV[i-h][j]),0LL);
        if(w+1<M) dp[w+1][h]=max(dp[w][h]-(cnt[i][j+w]-cntH[i][j+w-1]),0LL);
        
        if(i==2&&j==1&&w==2&&h+1==1) dump3(w,h+1,dp[w][h+1]);
        if(i==2&&j==1&&w+1==2&&h==1) dump3(w+1,h,dp[w+1][h]);

//        dump4(h,w,cnt[i][j+w],cntH[i][j+w-1]);
//        dump3(dp[w][h],cnt[i][j+w]-cntH[i][j+w-1],dp[w][h]-(cnt[i][j+w]-cntH[i][j+w-1]));
//        dump4(h,w,dp[w][h+1],dp[w+1][h]);
      }
      FOR(h,1,H[i][j]+1)FOR(w,1,W[i][j]+1) {
        dump3(h,w,dp[w][h]);
        res+=dp[w][h];
      }
    }
    return res/2;
  }
};

// CUT begin
ifstream data("TwoLLogo.sample");

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

bool do_test(vector<string> grid, long long __expected) {
    time_t startClock = clock();
    TwoLLogo *instance = new TwoLLogo();
    long long __result = instance->countWays(grid);
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
        vector<string> grid;
        from_stream(grid);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507568732;
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
        cout << "TwoLLogo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
