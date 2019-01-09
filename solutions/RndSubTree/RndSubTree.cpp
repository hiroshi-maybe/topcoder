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
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/17/2018 SRM 731
 
 9:33-10:00 give up
 
 I tried to leverage linearity of expectation.
 E[X] = 2^d * ∑ { ∑ { l*r*Pr[l,r|d] } : d=1..K-1 }
 
 Edge at depth `d` shows up l*r times, where l = number of red vertices under the edge, r = number of red vertices upon the edge.
 
 However, I couldn't figure out how to compute `Pr[l,r|d]` during the contest
 
 Editorials:
  - http://kmjp.hatenablog.jp/entry/2018/03/19/0930
  - https://kimiyuki.net/blog/2018/03/18/srm-731-med/
  - https://twitter.com/n_vip/status/975065459023233024
  - https://togetter.com/li/1209650
 
 Those solutions are simple though, I cannot understand 😞
  - https://community.topcoder.com/stat?c=problem_solution&rm=331066&rd=17095&pm=14837&cr=22931891
  - https://community.topcoder.com/stat?c=problem_solution&rm=331069&rd=17095&pm=14837&cr=23177873
  - https://community.topcoder.com/stat?c=problem_solution&rm=331064&rd=17095&pm=14837&cr=251074
 
 20:30-22:30 read editorials
 22:30-23:30 describe @kmjp's editorial, copy and paste kmjp's solution.
 Suppose we are marking with red color the leftmost node `u` at depth `x` in i-th attempt.
 Probability is shown as P(i,x). We are going to iterate i=1..K, x=1..K in O(K^2).
 
 We are firstly computing probability of two cases:
 a) node above `u` is marked
 b) node below `u` (subtree of `u`) is marked
 
 Probability of case #b is easier to compute. It's 1/2^x because it needs to come exactly child of `u` at depth `x`.
 
 P(i+1,x+1) += P(i,x) * 1/2^x
 
 Probability of case #a is actually complement of #b. It's 1-1/2^x. Note that depth does not increase in this case.
 
 P(i+1,x) += P(i,x) * (1-1/2^x)
 
 Based on those probabilities, we can compute expectation which is contributed by (K-i) remaining attempt.
 We are looking at node `u` which was marked in i-th attempt.
 Note that `i` nodes already stays above node `u`.
 
 If all the `k-i` attempts goes into below `u`, expectation is...
 
 p1 = P(i,x) * i * (k-i) * 1/2^x
 
 As mentioned earlier, this edge is used i * (k-i) times (I don't fully understand this part. This may be wrong)

 If some of nodes do not come below `u`, somehow below expectation is added:
 
 p2 = P(i,x) * C(k-i,2) * 1/2^x * (1-1/2^x)
 
 Summary:
  - My approach was good. However I couldn't go forward to recurrence relation.
  - I still actually don't understand some part of @kmjp's explanation 😞
   - Why is probability not (1/2^x)^(k-i) if k-i attempts go below `u`?
   - If some of nodes below `u` is marked, why don't we need to consider existing `i` nodes above `u`?
  - Level of this problem is far far far far away from my level 🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔
 
 */
const LL MOD=1e9+7;
LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}
LL P[2020][2020];
LL pow2[2020],pow2inv[2020];
class RndSubTree {
  public:
  int count(int K) {
    pow2[0]=pow2inv[0]=1;
    FORE(i,1,2010) {
      pow2[i]=pow2[i-1]*2%MOD;
      pow2inv[i]=modinv(pow2[i],MOD);
    }
    
    ZERO(P);
    P[0][0]=1;
    LL res=0;
    FORE(i,1,K) REPE(x,i) {
      (P[i][x]+=P[i-1][x]*(MOD+1LL-pow2inv[x]))%=MOD;
      (P[i][x+1]+=P[i-1][x]*pow2inv[x])%=MOD;
      
      LL p1=P[i-1][x]*pow2inv[x]%MOD*(K-i)%MOD*pow2inv[x+1]%MOD*i%MOD;
      LL p2=P[i-1][x]*pow2inv[x]%MOD*(K-i)%MOD*(K-i-1)%MOD*pow2inv[x+1]%MOD*(MOD+1-pow2inv[x+1])%MOD;
      LL y=(p1+p2)%MOD*pow2[x+1]%MOD;
      res+=y,res%=MOD;
    }
    return res;
  }
};

// CUT begin
ifstream data("RndSubTree.sample");

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

bool do_test(int k, int __expected) {
    time_t startClock = clock();
    RndSubTree *instance = new RndSubTree();
    int __result = instance->count(k);
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
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521304392;
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
        cout << "RndSubTree (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
