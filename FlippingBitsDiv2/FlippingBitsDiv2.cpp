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
 
 11/13/2017
 
 8:55-9:42 analysis
 9:42-9:54 implementation
 9:55-10:16 debug, submit and 1WA (356.12 pt)
 10:17-10:23 found a mistake in analysis. my design was wrong greedy.
 
 17:30-18:58 redesigned and system test passed
 
 Editorials:
  - http://snuke.hatenablog.com/entry/2013/08/27/214629
  - http://kmjp.hatenablog.jp/entry/2013/08/28/1030
  - http://emkcsharp.hatenablog.com/entry/SRM589/FlippingBitsDiv2
  - https://apps.topcoder.com/wiki/display/tc/SRM+589

 Problem can be divided into left part and right part.
 At most |S|/M+1 different problems.

 P=P(left)+P(right)
 
 Left and right are independent same problem.
 We can solve them separatedly and sum up.
 
 In each M group, we can make a decision to make 1) all 0, or 2) all 1.
 
 1) 000000|10 -> 00000000 -> 11111111
           ^
 2) 111111|10 -> 11111111
            ^
 
 We can choose optimal one out of them.
 f(i,1) = min(
   f(i-1,0)+cnt(1 in group[i])+1, // case 1
   f(i+1,1)+cnt(0 in group[i])    // case 2
 )
 f(N,_)=0
 
 res=min { f_left(i,1)+f_right(|S|/M-i,1) : i=0..|S|/M }
 
 Key:
  - Divide into left and right part in |S|/M ways <2500
  - There is an optimal substructure after decision in each group
 
 Summary:
  - Approach was smooth and straightforward 👍
    - Head and tail are independent and same subproblems
    - Tried to compute them in linear to achieve O(N^2) runtime
  - My first analysis was completely missing transformation 11110000 => 00000000 => 11111111 👎
    - I went easy way just taking care of samples without proof
    - I should have analyzed keeping generality
  - After getting 1WA, I figured out what was wrong and expected some DP is needed though, it took much time to classify transformation cases.
    - I was afraid that state transition loop f(1111) => f(0000) => f(1111)
      - We know that we eventually want to make 1111. We can calculate like f(1111)+2
    - It took some time to fix bug of index boundary in cumulative sum
      - It came from first implementation.
      - I should have reviewed code when applying different design
 
 Clean iterative DP
  - https://community.topcoder.com/stat?c=problem_solution&rm=318565&rd=15701&pm=12731&cr=23183974
 
 */

// dp, O(N^2) time
// This solution is not efficient because ther is no need to try all possible `x` in each state.
int cum1[2501];
int cum2[2501];
int memo[2501];
class FlippingBitsDiv2 {
public:
  int K,M;
  int cumm(int l, int r, int cum[2501]) {
    return cum[r]-cum[l];
  }
  int f(int l, int cum[2501]) {
    int &res=memo[l];
    if(res>=0) return res;
    if(l==0) return 0;
    res=min(l*M-cumm(0,l,cum),cumm(0,l,cum)+1);
    FOR(x,1,l) {
      int to0l=min(cumm(0,x,cum), f(x,cum)+1),to1l=min(x*M-cumm(0,x,cum),f(x,cum));
      int to0r=cumm(x,l,cum),to1r=(l-x)*M-cumm(x,l,cum);
      res=min({res,to0l+to0r+1,to0l+to1r+1,to1l+to1r,to1l+to0r+2});
    }
    return res;
  }
  int getmin(vector<string> SS, int M) {
    this->M=M;
    string S=""; FORR(s,SS) S+=s;
    ZERO(cum1); ZERO(cum2);
    this->K=SZ(S)/M;
    
    VI cnt1(K,0);
    REP(i,K) FOR(j,i*M,(i+1)*M) cnt1[i]+=(S[j]=='1');
    REP(i,K) cum1[i+1]=cum1[i]+cnt1[i];
    
    string T=S; reverse(T.begin(),T.end());
    VI cnt2(K,0);
    REP(i,K) FOR(j,i*M,(i+1)*M) cnt2[i]+=(T[j]=='1');
    REP(i,K) cum2[i+1]=cum2[i]+cnt2[i];
    
    VI f1(K+1,0),f2(K+1,0);
    MINUS(memo);
//    dump(f(7,cum1));
    REP(l,K+1) f1[l]=f(l,cum1);
    MINUS(memo);
    REP(r,K+1) f2[K-r]=f(r,cum2);
    
    int res=1e5;
    REP(l,K+1) {
//      dump3(l,f1[l],f2[l]);
      res=min(res,f1[l]+f2[l]);
    }
    return res;
  }
};

class FlippingBitsDiv2_wrong {
  public:
  int K,M;
  int cumm(int l, int r, int cum[2501]) {
    return cum[r]-cum[l];
  }
  int f(int l, int cum[2501]) {
    int res=l*M-cumm(0,l,cum);
//    if(l==2) dump3(l,cumm(0,l,cum),res);
    REP(x,l) {
      int a=cumm(0,x+1,cum)+1;
      int b=(l-x-1)*M-cumm(x+1,l,cum);
//      if(l==2) dump4(x,l-x-1,(l-x-1)*M,cumm(x+1,l,cum));
//      if(l==2) dump4(x,a,b,a+b);
      res=min(res,a+b);
    }
    return res;
  }
  int getmin(vector<string> SS, int M) {
    this->M=M;
    string S=""; FORR(s,SS) S+=s;
    ZERO(cum1); ZERO(cum2);
    this->K=SZ(S)/M;
    
    VI cnt1(K,0);
    REP(i,K) FOR(j,i*M,(i+1)*M) cnt1[i]+=(S[j]=='1');
    REP(i,K) cum1[i+1]=cum1[i]+cnt1[i];
//    dumpAR(cnt1);

    string T=S; reverse(T.begin(),T.end());
    VI cnt2(K,0);
    REP(i,K) FOR(j,i*M,(i+1)*M) cnt2[i]+=(T[j]=='1');
    REP(i,K) cum2[i+1]=cum2[i]+cnt2[i];
//    dumpAR(cnt2);

    VI f1(K+1,0),f2(K+1,0);
    REP(l,K+1) f1[l]=f(l,cum1);
    REP(r,K+1) f2[K-r]=f(r,cum2);

    int res=1e5;
    REP(l,K+1) {
      dump3(l,f1[l],f2[l]);
      res=min(res,f1[l]+f2[l]);
    }
    return res;
  }
};

// CUT begin
ifstream data("FlippingBitsDiv2.sample");

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

bool do_test(vector<string> S, int M, int __expected) {
    time_t startClock = clock();
    FlippingBitsDiv2 *instance = new FlippingBitsDiv2();
    int __result = instance->getmin(S, M);
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
        vector<string> S;
        from_stream(S);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510592142;
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
        cout << "FlippingBitsDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
