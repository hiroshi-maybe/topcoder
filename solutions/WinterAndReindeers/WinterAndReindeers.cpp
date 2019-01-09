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
 
 10/31/2017
 
 9:10-10:06 give up
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+601
   - Add additional parameter to LCS and do modified LCS DP
  - http://kmjp.hatenablog.jp/entry/2013/12/23/1000
   - 3 steps to solve
    - find possible C substrings in both A and B
    - pre-compute LCS in both L2R and R2L direction
    - find LCS from each C subsequences in O(1)
  - http://emkcsharp.hatenablog.com/entry/SRM601/WinterAndReindeers
   - for all C intervals, do LCS to left and right
 
 17:24-17:47 1WA by segmentation fault
 17:47-18:10 bug fix of LCS and system test passed
 
 Problem = LCS + Endpoint of subsequence C in A and B
   - LCS: O(M*N) time
   - Endpoint of subsequence C: O(M^2+N^2) time
 
 21:00-21:21 add solution of official editorial.
 
 key:
  - pre-calculate subsequence C in A and B
  - two approaches
   - precomputation leveraging symmetric property
   - modify LCS DP by adding another parameter
 
 summary:
  - Approach was not bad though, I didn't have idea to pre-compute LCS from right to left
    - If problem has symmetry structure, pre-computation in the other direction sometimes helps
    - Or we pin specific range and compute against in both left and right side
  - I also had idea to modify LCS DP though, I couldn't build recurrence relation by myself
  - Nice problem to reduce complex problem to combination of simpler problems
  - Probably I should pay more attention to how to divide to subproblems and merge them
   - analyze runtime of subproblem, design how to use the result of subproblem to solve original problem
   - when we merge subproblem, what is runtime?
   - Problem = ∑ problem | ∏ problem
 
 Submit solutions:
  - LCS DP to left and right
    - https://community.topcoder.com/stat?c=problem_solution&rm=319873&rd=15713&pm=12872&cr=23082290
  - Modified LCS
    - https://community.topcoder.com/stat?c=problem_solution&rm=319829&rd=15713&pm=12872&cr=23144514
  - precompute left and right LCS
    - https://community.topcoder.com/stat?c=problem_solution&rm=319866&rd=15713&pm=12872&cr=22854398
    - https://community.topcoder.com/stat?c=problem_solution&rm=319877&rd=15713&pm=12872&cr=23055693
 */

int memo[2501][2501][2];
class WinterAndReindeers {
public:
  const int Inf=1e5;
  int N,M;
  string A,B,C;
  MAPII CA,CB;
  MAPII ranges(string A, string C) {
    MAPII res;
    int N=SZ(A),M=SZ(C);
    REP(i,N) if(A[i]==C[0]) {
      int s=i;
      int k=0;
      FOR(j,i,N) if(A[j]==C[k]) {
        ++k;
        if(k==M) {
          res[s]=j+1;
          break;
        }
      }
    }
    return res;
  }
  
  int f(int i, int j, int k) {
    if(i==N&&j==M) return k==0?0:Inf;
    if(memo[i][j][k]>=0) return memo[i][j][k];
    if(i==N) return memo[i][j][k]=f(i,j+1,k);
    if(j==M) return memo[i][j][k]=f(i+1,j,k);
    
    int res=0;
    if(A[i]==B[j]) {
      if(k==0&&CA.count(i)&&CB.count(j)) res=max(res,f(CA[i],CB[j],1)+SZ(C));
      res=max(res,f(i+1,j+1,k)+1);
    }
    res=max(res,f(i+1,j,k));
    res=max(res,f(i,j+1,k));

//    dump4(i,j,k,res);
    
    return memo[i][j][k]=res;
  }
  
  int getNumber(vector<string> allA, vector<string> allB, vector<string> allC) {
    string A="",B="",C="";
    FORR(s,allA) A+=s; FORR(s,allB) B+=s; FORR(s,allC) C+=s;
//    dump3(A,B,C);
    this->CA=ranges(A,C), this->CB=ranges(B,C);
    this->N=SZ(A), this->M=SZ(B);
    this->A=A, this->B=B, this->C=C;
    MINUS(memo);
    return max(f(0,0,0)-Inf,0);
  }
};

int LCS1[2501][2501],LCS2[2501][2501];
class WinterAndReindeers_dp1 {
  public:
  vector<II> ranges(string A, string C) {
    vector<II> res;
    int N=SZ(A),M=SZ(C);
    REP(i,N) if(A[i]==C[0]) {
      int s=i;
      int k=0;
      FOR(j,i,N) if(A[j]==C[k]) {
        ++k;
        if(k==M) {
          res.emplace_back(s,j);
          break;
        }
      }
    }
    return res;
  }
  
  int getNumber(vector<string> allA, vector<string> allB, vector<string> allC) {
    string A="",B="",C="";
    FORR(s,allA) A+=s; FORR(s,allB) B+=s; FORR(s,allC) C+=s;
//    dump3(A,B,C);
    ZERO(LCS1),ZERO(LCS2);
    vector<II> CA=ranges(A,C), CB=ranges(B,C);
    int N=SZ(A),M=SZ(B);
    // L to R
    FOR(i,1,N+1) FOR(j,1,M+1) {
      if(A[i-1]==B[j-1]) {
        LCS1[i][j]=max(LCS1[i][j], LCS1[i-1][j-1]+1);
      } else {
        LCS1[i][j]=max(LCS1[i-1][j], LCS1[i][j-1]);
      }
    }

    // R to L
    for(int i=N-1; i>=0; --i) for(int j=M-1; j>=0; --j) {
      if(A[i]==B[j]) {
        LCS2[i][j]=max(LCS2[i][j], LCS2[i+1][j+1]+1);
      } else {
        LCS2[i][j]=max(LCS2[i+1][j], LCS2[i][j+1]);
      }
    }

    int res=0;
    REP(i,SZ(CA)) REP(j,SZ(CB)) {
      int la=CA[i].first,lb=CB[j].first,ra=CA[i].second,rb=CB[j].second;
      res=max(res,SZ(C)+LCS1[la][lb]+LCS2[ra+1][rb+1]);
    }
    return res;
  }
};

// LCS by delivering DP
class WinterAndReindeers_dp2 {
public:
  vector<II> ranges(string A, string C) {
    vector<II> res;
    int N=SZ(A),M=SZ(C);
    REP(i,N) if(A[i]==C[0]) {
      int s=i;
      int k=0;
      FOR(j,i,N) if(A[j]==C[k]) {
        ++k;
        if(k==M) {
          res.emplace_back(s,j);
          break;
        }
      }
    }
    return res;
  }
  
  int getNumber(vector<string> allA, vector<string> allB, vector<string> allC) {
    string A="",B="",C="";
    FORR(s,allA) A+=s; FORR(s,allB) B+=s; FORR(s,allC) C+=s;
//    dump3(A,B,C);
    ZERO(LCS1),ZERO(LCS2);
    vector<II> CA=ranges(A,C), CB=ranges(B,C);
    int N=SZ(A),M=SZ(B);
    // L to R
    REP(i,N+1) REP(j,M+1) {
      if(i<N&&j<M&&A[i]==B[j]) LCS1[i+1][j+1]=max(LCS1[i+1][j+1], LCS1[i][j]+1);
      // this transition is necessary regardless of match
      if(i+1<=N) LCS1[i+1][j]=max(LCS1[i+1][j], LCS1[i][j]);
      if(j+1<=M) LCS1[i][j+1]=max(LCS1[i][j+1], LCS1[i][j]);
    }
    // R to L
    for(int i=N; i>0; --i) for(int j=M; j>0; --j) {
      if(i>0&&j>0&&A[i-1]==B[j-1]) LCS2[i-1][j-1]=max(LCS2[i-1][j-1], LCS2[i][j]+1);
      if(i>0) LCS2[i-1][j]=max(LCS2[i-1][j], LCS2[i][j]);
      if(j>0) LCS2[i][j-1]=max(LCS2[i][j-1], LCS2[i][j]);
    }
    
    int res=0;
    REP(i,SZ(CA)) REP(j,SZ(CB)) {
      int la=CA[i].first,lb=CB[j].first,ra=CA[i].second,rb=CB[j].second;
      res=max(res,SZ(C)+LCS1[la][lb]+LCS2[ra+1][rb+1]);
      //      res=max(res,SZ(C)+LCS1[la][lb]+LCS2[ra+1][rb+1]);
    }
    //    dump3(res,SZ(C),res+SZ(C));
    return res;
  }
};

// CUT begin
ifstream data("WinterAndReindeers.sample");

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

bool do_test(vector<string> allA, vector<string> allB, vector<string> allC, int __expected) {
    time_t startClock = clock();
    WinterAndReindeers *instance = new WinterAndReindeers();
    int __result = instance->getNumber(allA, allB, allC);
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
        vector<string> allA;
        from_stream(allA);
        vector<string> allB;
        from_stream(allB);
        vector<string> allC;
        from_stream(allC);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(allA, allB, allC, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509466243;
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
        cout << "WinterAndReindeers (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
