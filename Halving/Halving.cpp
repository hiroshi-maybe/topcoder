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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/25/2018
 
 SRM 728
 
 8:01-8:48 System test passed
 
 Editorials:
  - http://kmjp.hatenablog.jp/entry/2018/01/26/1000
  - http://hamko.hatenadiary.jp/entry/2018/01/26/024943
  - https://togetter.com/li/1193367
 
 Submit solutions:
  - Checking interval with low and high 🤔
   - https://community.topcoder.com/stat?c=problem_solution&rm=330918&rd=17064&pm=14807&cr=23288971
   - https://community.topcoder.com/stat?c=problem_solution&rm=330908&rd=17064&pm=14807&cr=10574855
   - https://community.topcoder.com/stat?c=problem_solution&rm=330908&rd=17064&pm=14807&cr=22692969
   - https://community.topcoder.com/stat?c=problem_solution&rm=330914&rd=17064&pm=14807&cr=40021276
   - https://community.topcoder.com/stat?c=problem_solution&rm=330911&rd=17064&pm=14807&cr=22777715
 
 I understood solution of top contestants.
 
 It's guaranteed that there exists a value to which all the values converge.
 Basic idea is picking up an element in given array and test if all the values converges to its divided value `y`.
 
 In each division step, there are at most two values.
 
  a) if n is even, obviously we get only n/2
  b) suppose n is odd. We define n=2*k+1
 
   In the first step, we get {k,k+1}. Difference of them is `1`.
   In second step, {k/2,k/2+1}. Difference of them is still `1`.
   Therefore we can prove by induction that at most two values whose dif is `1` are obtained in each step.
 
 So we test at most 2*lg x values.
 In each test, we can check if all the values in the array converges to the `y`.
 Obtained value from a[i] after k-step is represented by interval [f∘k(a[i]), g∘k(a[i])], f(x)=floor(x/2), g(x)=ceil(x/2), f∘k(x) = f(f(f(...f(x)...)) (f is applied `k` times)
 https://math.stackexchange.com/questions/247710/notation-for-repeated-application-of-function
 
 If `y` is in the interval (length is at most 2), a[i] can reach `y`.
 Key is iterating divided values of an element and check if all the values converges to it.
 I iterated all the elements in the array first to find optimal meeting point.
 
 Key:
  - At most two values are obtained in each step
 
 Summary:
  - System test passed in contest 👍
  - Nice to figure out TLE in largest constraint 👍
  - Notice branch pruning earlier 👎
  - Solution without remembering reaching numbers of all the elements in the array is impressive
 
 */

class Halving {
public:
  const int Inf=1e9;
  VI A;
  
  int f(int y) {
    int res=0;
    FORR(a,A) {
      int cnt=0;
      int l=a,r=a;
      while(!(l<=y&&y<=r)) {
        if(l<1) return Inf;
        l/=2,r=(r+1)/2;
        ++cnt;
      }
      res+=cnt;
    }
    return res;
  }
  
  int minSteps(vector<int> A_) {
    this->A=A_;
    int res=Inf;
    int y=A[0];
    while(y>=1) {
      res=min({res,f(y),f(y+1)});
      y/=2;
    }
    return res;
  }
};

// Cleaned up original code
class Halving_dfs {
public:
  const int Inf=1e9;
  unordered_map<int,VI> X;
  void dfs(int x, int cnt, MAPII &viz) {
    if(viz.count(x)) return;
    viz[x]=cnt;
    if(x<=1) return;
    
    if(x%2==0) {
      dfs(x/2,cnt+1,viz);
    } else {
      dfs((x-1)/2,cnt+1,viz);
      dfs((x+1)/2,cnt+1,viz);
    }
  }
  
  int minSteps(vector<int> A) {
    int N=SZ(A);
    REP(i,N) {
      MAPII viz;
      dfs(A[i],0,viz);
      FORR(kvp,viz) {
        int x=kvp.first,cnt=kvp.second;
        X[x].push_back(cnt);
      }
    }
    
    int res=Inf;
    FORR(kvp,X) if(SZ(kvp.second)==N) {
      VI ns=kvp.second;
      res=min(res,accumulate(ns.begin(),ns.end(),0));
    }
    
    return res;
  }
};

// dfs
unordered_map<int,int> X[51];
class Halving_org {
  public:
  unordered_map<int,LL> viz;
  void dfs(int x, int i, int cnt) {
    viz[x]|=1LL<<i;
    if(X[i].count(x)!=0&&X[i][x]<=cnt) return;
    X[i][x]=cnt;
    if(x<=1) return;
    
    if(x%2==0) {
      dfs(x/2,i,cnt+1);
    } else {
      dfs((x-1)/2,i,cnt+1);
      dfs((x+1)/2,i,cnt+1);
    }
  }
  
  int minSteps(vector<int> A) {
    int N=SZ(A);
    REP(i,N) X[i].clear();
    LL full=(1LL<<N)-1;
    REP(i,N) dfs(A[i],i,0);
    
    const int Inf=1e9;
    int res=Inf;
    FORR(kvp,viz) if(kvp.second==full) {
      int x=kvp.first;
      int tot=0;
      REP(i,N) tot+=X[i][x];
      res=min(res,tot);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("Halving.sample");

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

bool do_test(vector<int> a, int __expected) {
    time_t startClock = clock();
    Halving *instance = new Halving();
    int __result = instance->minSteps(a);
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
        vector<int> a;
        from_stream(a);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1516896049;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Halving (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
