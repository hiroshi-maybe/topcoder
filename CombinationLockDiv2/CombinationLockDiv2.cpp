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
 
 10/20/2017
 
 9:20-10:24 time up
 
 17:37-21:00 read editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+607
  - https://apps.topcoder.com/forums/?module=Thread&threadID=810022&start=0
   - interesting analysis of similarity with bracket DP
  - http://ekaing.hatenablog.com/entry/2014/02/23/232805
  - editorial of div1 medium
   - https://gyazo.com/748b9196b0e4c230200edb1f164abda9 for div1 medium
   - http://kmjp.hatenablog.jp/entry/2014/02/06/0930
   - http://torus711.hatenablog.com/entry/20140212/p1
 
 key:
  - actual numbers in S and T don't matter. abs(S[i]-T[i]) matters.
  - we can ignore overlap of add and subtract in the same index as described in editorial
  - solve from left to right without losing generality
  - maximum rotation is not 9. why?
 
 summary:
  - I've not solved interval DP problem 😡
  - too difficult for me
 
 submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=320463&rd=15840&pm=12969&cr=23285916
  - https://community.topcoder.com/stat?c=problem_solution&rm=320476&rd=15840&pm=12969&cr=23177326
  - https://community.topcoder.com/stat?c=problem_solution&rm=320474&rd=15840&pm=12969&cr=23127720
  - https://community.topcoder.com/stat?c=problem_solution&rm=320463&rd=15840&pm=12969&cr=22682720
 
 
 
 */

int memo[51][501][2];
class CombinationLockDiv2 {
  public:
  int N;
  VI X;
  const int Inf=500;
  int f(int i, int bal, int up) {
    if(i==N) return 0;
    if(memo[i][bal][up]>=0) return memo[i][bal][up];
    
    int res=Inf;
//    dump3(i,bal,up);
    REP(up2,2) REP(bal2,Inf) {
      if(up2==1) {
        if((X[i]+bal2)%10!=0) continue;
      } else {
        if((10+X[i]-bal2)%10!=0) continue;
      }
      
      int step;
      if(up==up2) step=max(bal2-bal,0);
      else step=bal2;

      res=min(res,f(i+1,bal2,up2)+step);
    }
    
    /*
    // wrong
    if(up) {
      int d0=10-X[i];
      res=min(res, max(d0-bal,0)+f(i+1,d0,up)); // no-reset
      res=min(res, d0+f(i+1,d0,1^up)); // reset up->down
    } else {
      int d1=X[i];
      res=min(res, max(d1-bal,0)+f(i+1,d1,up)); // no-reset
      res=min(res, 10-d1+f(i+1,10-d1,1^up)); // reset down->up
    }*/
    
    return memo[i][bal][up]=res;
  }
  int minimumMoves(string S, string T) {
    this->N=SZ(S);
    MINUS(memo);
    REP(i,N) this->X.push_back((S[i]-T[i]+10)%10);
//    dumpAR(X);
    return f(0,0,0);
  }
};

// http://kmjp.hatenablog.jp/entry/2014/02/06/0930
class CombinationLockDiv2_div1 {
public:
  int N;
  VI X;
  const int Inf=500;

  int minimumMoves(string S, string T) {
    this->N=SZ(S);

    int L=S.size();
    vector<int> D;
    REP(i,L) S[i]=(10+S[i]-T[i])%10;
    D.push_back(S[0]);
    REP(i,L-1) D.push_back((10+S[i+1]-S[i])%10);
    sort(D.begin(),D.end());
    
    int mi=1000000;
    REP(i,D.size()+1) {
      int down=0,up=0;
      REP(j,D.size()) {
        if(j<i) down+=D[j];
        else up+=10-D[j];
      }
      mi=min(mi,max(down,up));
    }
    
    return mi;
  }
};

// CUT begin
ifstream data("CombinationLockDiv2.sample");

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

bool do_test(string S, string T, int __expected) {
    time_t startClock = clock();
    CombinationLockDiv2 *instance = new CombinationLockDiv2();
    int __result = instance->minimumMoves(S, T);
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
        string S;
        from_stream(S);
        string T;
        from_stream(T);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, T, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508516415;
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
        cout << "CombinationLockDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
