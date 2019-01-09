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
 
 10/21/2017
 
 14:19-14:50 analysis
 14:50-14:57 implement but found mistake in design (Kris's move was not optimal)
 15:03-15:55 samples passed though, it TLEed.
 15:55-16:40 figured out that I don't need to keep order in state
 16:43 debug and fixed two bugs (S->X, mask update)
 16:48 system test passed (317.40 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+606
  - http://torus711.hatenablog.com/entry/20140130/p3
   - clean minimax algorithm
  - http://kmjp.hatenablog.jp/entry/2014/01/31/1000
   - DP
 
 18:10-18:26 add solution by naiive minimax algorithm
 
 key:
  - candies in box can be restored from bitmask
  - Number of state is small. Naiive implementation works too.
 
 summary:
  - It took a lot of time to figure out that candies in box can be restored from bitmask
   - no need to keep selected order to do DP
  - many bugs in implementation
 
 Submit solutions:
  - Naiive minimax
    - https://community.topcoder.com/stat?c=problem_solution&rm=320395&rd=15839&pm=12394&cr=23295835
  - dp with mask
    - https://community.topcoder.com/stat?c=problem_solution&rm=320394&rd=15839&pm=12394&cr=23027999
    - https://community.topcoder.com/stat?c=problem_solution&rm=320366&rd=15839&pm=12394&cr=23040021
  - dp with permutation
    - https://community.topcoder.com/stat?c=problem_solution&rm=320392&rd=15839&pm=12394&cr=22704094
 
 */

// O(N!) time
class EllysCandyGame {
public:
  const string P0="Elly",P1="Kris",D="Draw";
  VI S;
  const int Inf=1e7;
  int f(int p, int s0, int s1, VI &X) {
    int N=SZ(X);
    if(count(X.begin(),X.end(),0)==N) return s0-s1;
    
    int def=p%2==0?-Inf:Inf;
    int res=def;
    REP(i,N) if(X[i]>0) {
      int xx=X[i]; X[i]=0;
      if(0<i) X[i-1]*=2;
      if(i<N-1) X[i+1]*=2;
      
      if(p%2==0) {
        res=max(res,f(p+1,s0+xx,s1,X));
      } else {
        res=min(res,f(p+1,s0,s1+xx,X));
      }
      X[i]=xx;
      if(0<i) X[i-1]/=2;
      if(i<N-1) X[i+1]/=2;
    }

    return res==def?0:res;
  }
  string getWinner(vector<int> S) {
    this->S=S;
    VI X=S;
    int d=f(0,0,0,X);
    
    if(d>0) return P0;
    if(d==0) return D;
    return P1;
  }
};

// O(N*2^N) time
int memo[1<<11];
class EllysCandyGame_dp_org {
public:
  const string P0="Elly",P1="Kris",D="Draw";
  VI S;
  int K;
  int N;
  const int Inf=1e7;
  int f(int mask) {
    if(memo[mask]>=0) return memo[mask];
    if(__builtin_popcount(mask)==K) return 0;
    
    VI X(N);
    REP(i,N) {
      if(mask&(1<<i)) X[i]=0;
      else X[i]=S[i];
    }
    REP(i,N) {
      if(i>0&&X[i-1]==0&&S[i-1]!=0) X[i]*=2;
      if(i<N-1&&X[i+1]==0&&S[i+1]!=0) X[i]*=2;
    }
    int res=-Inf;
    REP(i,N) if((mask&(1<<i))==0 && S[i]>0) {
      int x=X[i];
      int d=f(mask|(1<<i));
      res=max(res, x-d);
    }
    return memo[mask]=(res==-Inf?0:res);
  }
  string getWinner(vector<int> S) {
    this->N=SZ(S);
    this->S=S;
    MINUS(memo);
    this->K=0;
    REP(i,N) K+=S[i]>0;
    
    int d=f(0);
    if(d>0) return P0;
    if(d==0) return D;
    return P1;
  }
};

class EllysCandyGame_TLE {
public:
  map<VI,int> memo;
  const string P0="Elly",P1="Kris",D="Draw";
  VI S;
  int N;
  int f(VI &cur) {
    if(memo.count(cur)) return memo[cur];
    VI X=S;
    int s0=0, s1=0;
    int used[10]={0};
    REP(i,SZ(cur)) {
      int j=cur[i];
      used[j]=1;
      (i%2==0?s0:s1)+=X[j];
      if(j>0) X[j-1]*=2;
      if(j<N-1) X[j+1]*=2;
      X[j]=0;
    }
    if(SZ(cur)%2==1) swap(s0,s1);
    if(count(X.begin(),X.end(),0)==N) {
      if(s0>s1) return 0;
      if(s0==s1) return 1;
      return 2;
    }
    
    int res[3]={0};
    REP(i,N) if(used[i]==0&&X[i]!=0) {
      cur.push_back(i);
      ++res[f(cur)];
      cur.pop_back();
    }
    
    if(res[2]>0) return memo[cur]=0;
    if(res[1]>0) return memo[cur]=1;
    return memo[cur]=2;
  }
  string getWinner(vector<int> S) {
    this->N=SZ(S);
    this->S=S;
    memo.clear();
    
    VI x={};
    int res=f(x);
    
    if(res==0) return P0;
    if(res==1) return D;
    return P1;
  }
};

class EllysCandyGame_wrong {
  public:
  const string P0="Elly",P1="Kris",D="Draw";
  VI ord;
  int f(int i, int s0, int s1, VI &X) {
    if(i==SZ(ord)) {
      if(s0>s1) return 0;
      if(s0==s1) return 1;
      return 2;
    }
    
    int j=ord[i];
    if(i%2==0) s0+=X[j];
    else s1+=X[j];
    if(j>0) X[j-1]*=2;
    if(j<SZ(X)-1) X[j+1]*=2;
    return f(i+1,s0,s1,X);
  }
  string getWinner(vector<int> S) {
    int N=SZ(S);
    REP(i,N) if(S[i]!=0) this->ord.push_back(i);
    int res[3]={0};
    do {
//      dumpAR(ord);
      VI SS=S;
      int xxx=f(0,0,0,SS);
      res[xxx]++;
//      dump(xxx);
    } while(next_permutation(ord.begin(),ord.end()));
    
    if(res[0]>0) return P0;
    if(res[1]>0) return D;
    return P1;
  }
};

// CUT begin
ifstream data("EllysCandyGame.sample");

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

bool do_test(vector<int> sweets, string __expected) {
    time_t startClock = clock();
    EllysCandyGame *instance = new EllysCandyGame();
    string __result = instance->getWinner(sweets);
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
        vector<int> sweets;
        from_stream(sweets);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(sweets, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508620785;
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
        cout << "EllysCandyGame (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
