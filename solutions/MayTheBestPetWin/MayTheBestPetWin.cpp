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
 
 11/8/2017
 
 9:03-10:13 analysis (dp) https://en.wikipedia.org/wiki/Partition_problem
 10:14-10:32 1WA due to MLE (364.23 pt)
 10:33-11:19 translate to interative DP and system test passed
 
 Define lower range and upper range of time in team S and T as (s0,s1) and (t0,t1).
 
 s0=∑ { A[i] : i∈S }, s1=∑ { B[i] : i∈S }
 t0=∑ { A[i] : i∈T }, t1=∑ { B[i] : i∈T }
 
 Since S ∪ T = U, s0+t0=sumA, s1+t1=sumB.
 
 We want to compute lower bound of f(S)=max(abs(s0-t1), abs(t0-s1))

   f(S)
 = max(abs(s0-t1), abs(t0-s1))
 = max(abs(s0-(sumB-s1)), abs(sumA-s0-s1))
 = max(abs(s0+s1-sumB), abs(sumA-s0-s1))
 
 s0+s1 = ∑ { A[i]+B[i] : i∈S }
 
 Now we want to find S s.t. f(S) is smallest.
 f(x)=max(abs(x-A), abs(x-B)) is unimodal function. It's minimum when x-A=B-x.
 Thus x=(A+B)/2
 So it's minimal when s0+s1 is as close as (sumA+sumB)/2.
 This is almost equal to partition problem which is NP-hard.
 It can be solved by pseudo polynomial time by DP. So we can compute such x by DP.
 
 My original solution computed closest minimum difference between S and T though,
 Actually we can simply compute all possible value of s0+s1 and iterate it later as shown in editorials.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+593
  - http://topcoder.g.hatena.ne.jp/agw/20131011/1381524986
  - http://mayokoex.hatenablog.com/entry/2016/02/04/112516
  - http://d.hatena.ne.jp/simezi_tan/20131008/1381210308
  - http://topcoder.g.hatena.ne.jp/kojingharang/20131006#1381050540
  - https://topcoder.g.hatena.ne.jp/nitoyon/20131006/1381070268
 
 Key:
  - Analysis by formula transformation
  - Reduced to subset sum or partition problem
 
 Summary:
  - It took a lot of time though, impressive work to solve by myself 👍
   - also this problem is div1 medium
  - My original solution of memoized recursion hits MLE. It's my first time
    - good chance to review my process to pay more attention to memory space
  - Great to learn how to convert recurrence relation to iterative DP
    - we eventually calculate max(sumB-x, x-sumA) after each x state
    - that means we can do it in base case!
  - Solving by reducing to subset sum is brilliant!
 
 */

// solution by subset sum
const int Inf=1000001;
int dp[Inf];
class MayTheBestPetWin {
public:
  int calc(vector<int> A, vector<int> B) {
    int N=SZ(A);
    int tota=accumulate(A.begin(),A.end(),0);
    int totb=accumulate(B.begin(),B.end(),0);
    ZERO(dp);
    dp[0]=1;
    REP(i,N) for(int x=Inf; x>=0; --x) if(x+A[i]+B[i]<Inf&&dp[x]) {
      dp[x+A[i]+B[i]]=1;
    }
    int res=Inf;
    REP(x,Inf) if(dp[x]) {
      res=min(res,max(totb-x,x-tota));
    }
    
    return res;
  }
};

// DP by official editorial
int dp1[1000001],dp2[1000001];
class MayTheBestPetWin_cleandp {
public:
  int N;
  int calc(vector<int> A, vector<int> B) {
    this->N=SZ(A);
    int tota=accumulate(A.begin(),A.end(),0);
    int totb=accumulate(B.begin(),B.end(),0);
    REP(x,1000001) dp1[x]=max(totb-x,x-tota);
    REP(i,N) {
      REP(x,1000001) {
        int a=x+A[i]+B[i]<=1000000?dp1[x+A[i]+B[i]]:1000001;
        dp2[x]=min(dp1[x], a);
      }
      swap(dp1,dp2);
    }
    
    return dp1[0];
  }
};

class MayTheBestPetWin_org {
public:
  int N;
  int tot;
  VI C;
  int dp[500010][2];
  int calc(vector<int> A, vector<int> B) {
    this->N=SZ(A);
    this->C=VI(N,0);
    REP(i,N) C[i]=A[i]+B[i];
    tot=accumulate(C.begin(),C.end(),0);
    MINUS(dp);
    dp[0][0]=C[0];
    dp[C[0]][0]=C[0];
    int sum=C[0];
    FOR(i,1,N) {
      int o1=(2+i-1)%2,o2=o1^1;
//      assert(o1==1||o1==0);
      for(int n=500000; n>=0; --n) if(dp[n][o1]>=0) {
        int m=sum-n;
//        dump3(i,n,m);

        // add to m
        int m1=m+C[i];
        int x1=abs(m1-n);
        if(n<=500000&&(dp[n][o2]==-1||dp[n][o2]>x1)) {
          dp[n][o2]=x1;
//          dump3(n,o2,x1);
        }
//        dp[n][o2]=min(dp[n][o1],x1);
//        assert(dp[n]!=2);

        // add to n
        int n1=n+C[i];
        int x2=abs(n1-m);
        if(n1<=500000&&(dp[n1][o2]==-1||dp[n1][o2]>x2)) {
          dp[n1][o2]=x2;
//          dump3(n1,o2,x2);
//          assert(dp[n1]!=2);
        }
      }
      for(int n=500000; n>=0; --n) dp[n][o1]=-1;
      sum+=C[i];
    }
    
    int d=500000;
    int o=(2+N-1-1)%2; o^=1;
    REP(i,500001) if(dp[i][o]!=-1) d=min(d,dp[i][o]);
    dump(d);
    int n1=(tot-d)/2,n2=tot-n1;
    int suma=accumulate(A.begin(),A.end(),0);
    int sumb=accumulate(B.begin(),B.end(),0);
    int res1=max(abs(suma-n1),abs(sumb-n1));
    int res2=max(abs(suma-n2),abs(sumb-n2));
    return min(res1,res2);
  }
};

// MLE due to 64MB memory limit :(
class MayTheBestPetWin_MLE {
  public:
  int memo[51][500010];
  int N;
  int tot;
  VI C;
  int f(int i, int cur) {
    dump2(cur,i);
    int &res=memo[i][cur];
    if(res>=0) return res;
//    dump2(cur,i);
    if(i==N) {
      int n2=tot-cur;
      return res=abs(n2-cur);
    }
    return res=min(f(i+1,cur+C[i]),f(i+1,cur));
  }
  int calc(vector<int> A, vector<int> B) {
    this->N=SZ(A);
    this->C=VI(N,0);
    dumpAR(C);
    REP(i,N) C[i]=A[i]+B[i];
    tot=accumulate(C.begin(),C.end(),0);
    dump(tot);
    MINUS(memo);
    int d=f(0,0);
    dump(d);
    int n1=(tot-d)/2,n2=tot-n1;
    int suma=accumulate(A.begin(),A.end(),0);
    int sumb=accumulate(B.begin(),B.end(),0);
    int res1=max(abs(suma-n1),abs(sumb-n1));
    int res2=max(abs(suma-n2),abs(sumb-n2));
    return min(res1,res2);
  }
};

// CUT begin
ifstream data("MayTheBestPetWin.sample");

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

bool do_test(vector<int> A, vector<int> B, int __expected) {
    time_t startClock = clock();
    MayTheBestPetWin *instance = new MayTheBestPetWin();
    int __result = instance->calc(A, B);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510160614;
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
        cout << "MayTheBestPetWin (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
