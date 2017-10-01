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
 
 9/30/2017
 
 18:09-18:23,22:43-22:59 analysis
 23:27-24:07 1WA
 24:12 fixed a bug and system test passed.
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+625
  - http://topcoder.g.hatena.ne.jp/capythm/20140624/1403617845
  - http://kmjp.hatenablog.jp/entry/2014/06/22/1100
   - smart DP solution
 
 10/1/2017
 
 10:25-10:33 add simpler simulation solution inspired by official editorial
 12:05-12:18 add DP solution
 
 key:
  - if A[i]!='?', by determining first person as liar/honest, assignment is detemined
  - separated sequence by '?' is independent. we can try liar and honest and take assignment of less liar
  - cycle -> we can start whatever convenient position
  - based on assignment at i affects only i+1. thus DP works too.
   - top rankers are all submitting DP solution

 summary:
  - by simulation, approach is not hard though, validation part of first person is tricky
  - tricky point is those assignment should not contradict with assignment of A[0] if A[0]!='?'
   - however editorial is showing that we can start from amy '?'. Smart idea.
 
 submit solutions:
  - DP
   - https://community.topcoder.com/stat?c=problem_solution&rm=322739&rd=15858&pm=11844&cr=40027645
   - https://community.topcoder.com/stat?c=problem_solution&rm=322717&rd=15858&pm=11844&cr=22934220
   - https://community.topcoder.com/stat?c=problem_solution&rm=322741&rd=15858&pm=11844&cr=23099298
   - https://community.topcoder.com/stat?c=problem_solution&rm=322705&rd=15858&pm=11844&cr=23162961
 
 */

// DP solution inspired by @kmjp editorial
int dp[51][2];
class ConundrumReloaded {
public:
  const int Inf=1e5;
  int minimumLiars(string A) {
    int N=SZ(A);
    int res=Inf;
    REP(l,2){
      REP(i,N+1) dp[i][0]=dp[i][1]=Inf;
      dp[0][l]=0;
      REP(i,N) {
        if(A[i]=='?'||A[i]=='L') {
          dp[i+1][1]=min(dp[i+1][1],dp[i][0]+1); // honest
          dp[i+1][0]=min(dp[i+1][0],dp[i][1]); // liar
        }
        if(A[i]=='?'||A[i]=='H') {
          dp[i+1][1]=min(dp[i+1][1],dp[i][1]+1); // liar
          dp[i+1][0]=min(dp[i+1][0],dp[i][0]); // honest
        }
      }
      // take only consistent state
      res=min(res,dp[N][l]);
    }
    if(res>=Inf) res=-1;
    return res;
  }
};

// simulation from A[x]='?'
class ConundrumReloaded_simulation {
public:
  const int Inf=1e5;
  VI simulate(bool l, string A) {
    VI res;
    REP(i,SZ(A)) {
      res.push_back(l);
      bool next=A[i]=='L';
      if(l) next^=1;
      l=next;
    }
    res.push_back(l);
    return res;
  }
  int minimumLiars(string A) {
    int N=SZ(A);
    int i=-1;
    REP(j,N) if(A[j]=='?') i=j;
    
    // no '?'
    if(i==-1) {
      VI xs0=simulate(false,A),xs1=simulate(true,A);
      int cnt1=accumulate(xs0.begin(),xs0.end(),0),cnt2=accumulate(xs1.begin(),xs1.end(),-1);
      if(xs0.back()&&!xs1.back()) return -1;
      if(xs0.back()) return cnt2;
      if(!xs1.back()) return cnt1;
      return min(cnt1,cnt2);
    }
    
    A=A+A;
    int end=i+N, res=0;
    while(i<end) {
      while(i<end&&A[i]=='?') ++i;
      if(i>=end) break;
      // A[i]!='?'
      int j=i;
      while(j<end&&A[j]!='?') ++j;
      // A[j]=? or j==end
      string A2=A.substr(i,j-i);
      //      dump3(i,j,A2);
      VI xs0=simulate(false,A2),xs1=simulate(true,A2);
      int cnt1=accumulate(xs0.begin(),xs0.end(),0);
      int cnt2=accumulate(xs1.begin(),xs1.end(),0);
      res+=min(cnt1,cnt2);
      i=j;
    }

    return res;
  }
};

// simulation from A[0]
class ConundrumReloaded_org {
  public:
  const int Inf=1e5;
  VI simulate(bool l, string A) {
    VI res;
    cout << l;
    REP(i,SZ(A)) {
      res.push_back(l);
      bool next=A[i]=='L';
      if(l) next^=1;
      l=next;
      cout << l;
    }
    res.push_back(l);
    cout << endl;
    return res;
  }
  int minimumLiars(string A) {
    int N=SZ(A);
    int i=0;
    VI ls0,ls1;
    while(i<N) {
      while(i<N&&A[i]=='?') ++i;
      if(i>=N) break;
      // A[i]!='?'
      int j=i;
      while(j<N&&A[j]!='?') ++j;
      // A[j]=? or j==N
      string A2=A.substr(i,j-i);
//      dump3(i,j,A2);
      VI xs0=simulate(false,A2),xs1=simulate(true,A2);
      
      if(i==0&&j==N) {
        bool ok0=xs0.back()==xs0.front();
        bool ok1=xs1.back()==xs1.front();
        int cnt1=ok0?accumulate(xs0.begin(),xs0.end(),0):Inf;
        int cnt2=ok1?accumulate(xs1.begin(),xs1.end(),0)-1:Inf;
        int cnt=min(cnt1,cnt2);
        return cnt<Inf?cnt:-1;
      }
      if (i==0) {
        ls0=xs0,ls1=xs1;
      } else if(j==N) {
        if(xs0.back()) swap(xs0,xs1);
        if(A[0]!='?')xs1.pop_back();
        REP(i,SZ(xs0)) ls0.push_back(xs0[i]);
        REP(i,SZ(xs1)) ls1.push_back(xs1[i]);
      } else {
        int cnt1=accumulate(xs0.begin(),xs0.end(),0);
        int cnt2=accumulate(xs1.begin(),xs1.end(),0);
        VI xs2=cnt1<cnt2?xs0:xs1;
        REP(i,SZ(xs2)) {
          ls0.push_back(xs2[i]);
          ls1.push_back(xs2[i]);
        }
      }
      i=j;
    }
    
    int cnt1=accumulate(ls0.begin(),ls0.end(),0);
    int cnt2=accumulate(ls1.begin(),ls1.end(),0);
    return min(cnt1,cnt2);
  }
};

// CUT begin
ifstream data("ConundrumReloaded.sample");

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

bool do_test(string answers, int __expected) {
    time_t startClock = clock();
    ConundrumReloaded *instance = new ConundrumReloaded();
    int __result = instance->minimumLiars(answers);
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
        string answers;
        from_stream(answers);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(answers, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506820152;
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
        cout << "ConundrumReloaded (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
