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
 
 1/2/2017
 
 10:36-10:42 analysis
 10:43-10:52 (389.45 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+560
  - http://purple-jwl.hatenablog.com/entry/20121111/1352595324
  - http://topcoder.g.hatena.ne.jp/firewood/20121127/1354038424
 
 My original solution is iterating keys though, it can be simplified.
 We can create buckets with costs and put larger frequency in the bucket of smaller cost.
 
 S = {1,2,3}
 => S' = {1,1,1,2,2,3}
 
 F = {5,4,3,2,1}
 => {(5,1),(4,1),(3,1),(2,2),(1,2)}
 
 res=5*1+4*1+3*1+2*2+1*2=18
 
 Proof of greedy choice:

 We can assign costs to larger frequency first without losing generality.
 We want to compute f(n,S): min cost of frequency<=n and cost set S.
 
 If we take x = min { S }..
 
 f1(n,S) = n*x + f(n', S-{x})
 f(n',S-{x}) = n'*x' + f(n'',S-{x,x'})
 => f1(n,S) = n*x+n'*x'+f(n'',S-{x,x'})
 
 Note that x'∈S, x'>=x, n'<=n, n''<=n'
 
 On the other hand, if we take x' for n..
 
 f2(n,S) = n*x' + f(n', S-{x'})
 f(n',S-{x'}) = n'*x + f(n'',S-{x,x'})
 => f2(n,S) = n*x' + n'*x + f(n'',S-{x,x'})
 
 If f1(n,S)<=f2(n,S), we can prove that `x` is optimal choice.
 
   f1(n,S) - f2(n,S)
 = n*x+n'*x'+f(n'',S-{x,x'}) - (n*x' + n'*x + f(n'',S-{x,x'}))
 = n*x+n'*x' - (n*x' + n'*x)
 = n(x-x')+n'(x'-x)
 = (n'-n)*(x'-x)
 <= 0 (x'>=x, n'<=n => x'-x >= 0, n' - n <= 0)
 
 f1(n,S) - f2(n,S) <= 0
 <=> f1(n,S) <= f2(n,S)
 
 Thus choosing minimal `x` is optimal choice.
 
 Summary:
  - Typical greedy
  - Prepare buckets first is cool
 
 */

class TomekPhone {
public:
  int minKeystrokes(vector<int> F, vector<int> S) {
    VI S2;
    FORR(s,S) REP(x,s) S2.push_back(x+1);
    sort(S2.begin(),S2.end());
    sort(F.rbegin(),F.rend());
    int res=0;
    if(SZ(S2)<SZ(F)) return -1;
    REP(i,SZ(F)) res+=F[i]*S2[i];
    return res;
  }
};

class TomekPhone_org {
  public:
  int minKeystrokes(vector<int> F, vector<int> S) {
    int cap=accumulate(S.begin(),S.end(),0);
    if(SZ(F)>cap) return -1;
    
    sort(F.rbegin(),F.rend());
    
    int N=SZ(S);
    VI cnt(N,0);
    int i=0,res=0;
    FORR(x,F) {
      int j=i;
      while(j<i+N&&cnt[j%N]>=S[j%N]) ++j;
      assert(j!=i+N);
      assert(cnt[j%N]<S[j%N]);
      i=j%N;
      cnt[i]++;
//      dump3(_,i,cnt[i]);
      res+=cnt[i]*x;
      i=(i+1)%N;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("TomekPhone.sample");

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

bool do_test(vector<int> frequencies, vector<int> keySizes, int __expected) {
    time_t startClock = clock();
    TomekPhone *instance = new TomekPhone();
    int __result = instance->minKeystrokes(frequencies, keySizes);
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
        vector<int> frequencies;
        from_stream(frequencies);
        vector<int> keySizes;
        from_stream(keySizes);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(frequencies, keySizes, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514918185;
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
        cout << "TomekPhone (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
