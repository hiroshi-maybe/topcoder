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
 
 2/25/2018
 
 17:59-19:29 1WA (345.63 pt) and give up
 22:20-22:43 read editorial
 22:44-23:10 add solution
 
 Problem statement is asking to give "abc...def (g digits)" if length>=9.
 So I've imagined that this has some special meaning.
 
 "abc...def (g digits)" = abc*10^(g-3)+?*10^3+def
 
   (abc*10^(g-3)+?*10^3+def)%N
 = abc%N*10^(g-3)%N+?%N*10^3%N+def%N
 
 There are at most 10^6 (`abc`%N, `def`%N) pairs.
 However I had no idea how to resolve middle part `?*10^3` 👎👎👎👎👎👎👎👎👎
 
 I wanted to upper-bound total length `g`. However I had no idea about this.
 I should have assumed that length `g` could be huge.
 If so, I may have had an idea to handle number in string format and limited state upper-bounded by N.
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+524
  - http://d.hatena.ne.jp/kusano_prog/20111223/1324667961
  - http://topcoder.g.hatena.ne.jp/firewood/20111119/1321703233
 
 After reading editorial, this was graph problem rather than numeric theorem.
 We want min number x s.t. x%N==0.
 If next digit is `d`, 10*x%N gives us new state.
 The point is that there are only at most 10000 states because N<=10000.
 If we try digits in ascendent order, f((10*x+d)%N)=f(x)+"d".
 Thus we just want first value which reaches f(0) state.
 BFS finds such value with O(N) state.
 
 # Proof why f(10*x+d) obtained by BFS is minimal:
 
 f(y) = 10*s+d, s.t. `d` and `s` are smallest possible values.
 
 Hypothesis: 10*s+d is minimal s.t. y = (10*s+d)%N
 
 Assume there exists 10*s'+d' s.t. f(x') = 10*s'+d' AND 10*s'+d'<10*s+d
 
 We found s before s' in BFS queue. That means s<s'. Otherwise s' is founds before s.
 
 s<s' <=> 10*s<10*s' ... 1
 
 Also 10*s'+d'<10*s+d ...2 from our assumption.
 
 #1 <=> s'-s>0 <=> s'-s>=1
 
     #2
 <=> 10*s'-10*s<d-d'
 <=> d-d'>10*(s'-s)
 <=> d-d'>=10 from #1
 
 However 0<=d,d'<10 => 0<=d-d'<10, which contradicts that d-d'>=10.
 
 Thus 10*s+d is minimal which satisfies y=(10*s+d)%N
 
 # Possible scenario to solve this problem:
 
 1. There is no idea about how large the length `g` is. We may need to handle number in string format. There is constraint about possible digits. String representation helps us handle this as well.
 2. Multiple of N means S%N==0. This is typical approach to solve multiple of something. Also N is not very large
 3. We are interested in S s.t. S%N=0. Even if S is very large (like |S|>=9), we can digest S with x=S%N. It's easy to find x' s.t. x' = 10*S+d (mod N) = (10*x+d)%N
 4. Modular arithmetic forms state loop. However we can find minimal S s.t. S%N=0 by finding a shortest path from S=0
 
 Key:
  - Compress states in N because we are interested if S%N==0. Modular arithmetic forms only N states
  - We are handling very large number with possible digits. Process number in string representation
  - If add smaller digits, BFS finds minimal number S s.t. S ≡ x (mod N)
  - Again S could be very large. However problem is asking part of them. Encode number with length and partial numbers to save memory.
 
 Summary:
  - I sticked to "abc...def" format and numeric theorem. However it was not right approach 👎👎
  - I should have evaluated upper-bound of states x (mod N)
  - BFS to search minimal value may be a common technique
   - If there are small states like (x%N), BFS is applicable to search minimal value.
  - If interested in number in decimal format, handle numbers in string
  - State loop in modular arithmetic
   - Modular arithmetic forms ring which has essentially state loop
   - In

 */

int L[10001];
string S[10001];
class MultiplesWithLimit {
public:
  string no="IMPOSSIBLE";
  string minMultiples(int N, vector<int> FB) {
    set<int> OK;
    REP(d,10) if(count(FB.begin(),FB.end(),d)==0) OK.emplace(d);
    ZERO(L);
    REP(i,10000) S[i]="";
    queue<int> Q;
    Q.emplace(0);
    while(SZ(Q)) {
      int x=Q.front(); Q.pop();
      int l=L[x];
      string s=S[x];
//      dump3(x,l,s);
      FORR(d,OK) {
        if(x==0&&d==0) continue;
        int x2=(10*x+d)%N;
        if(L[x2]!=0) continue;
        int ll=l+1;
        L[x2]=ll;
        if(ll<8) {
          S[x2]=s;
          S[x2]+=('0'+d);
        } else {
          string s1=s.substr(0,4),s2=s.substr(5,3);
          s2+=('0'+d);
          S[x2]=s1+s2;
        }
        Q.push(x2);
      }
    }
//    REP(i,N) cout << L[i] <<",";
//    cout << endl;
    if(L[0]==0) return no;
    string s=S[0];
    if(L[0]<9) return s;
    return s.substr(0,3)+"..."+s.substr(4,3)+"("+to_string(L[0])+" digits)";
  }
};

// this doesn't work for length>9
class MultiplesWithLimit_wrong {
  public:
  string no="IMPOSSIBLE";
  SETI OK;
  void gen(int i, int cur, VI &X) {
    if(i==3) {
      X.push_back(cur);
      return;
    }
    FORR(d,OK) {
      gen(i+1,cur*10+d, X);
    }
  }
  
  string minMultiples(int N, vector<int> FB) {
    REP(d,10) if(count(FB.begin(),FB.end(),d)==0) OK.emplace(d);
//    dumpAR(OK);
    vector<int> X;
    gen(0,0,X);
    sort(X.begin(),X.end());
//    dumpAR(X);
    FORR(x,X) if(x%N==0&&x>=N) return to_string(x);
    int offset=1000%N;
    unordered_map<int,LL> Z;
    FORR(x,X) if(x>0) {
      LL xx=x*1000000LL;
      LL r=xx%N;
      if(r!=0&&!Z.count(r)) Z[r]=xx;
    }
    set<LL> Y;
    FORR(x,X) if(x>0) FORR(y,X) {
      int r=((x*offset)%N+y%N)%N;
      int xy=x*1000+y;
      if(r==0&&xy>=N) Y.emplace(xy);
      if(r!=0) {
        int rr=N-r;
        if(Z.count(rr)==0) continue;
        LL z=Z[rr];
        LL xyz=z+xy;
        if(xyz%N!=0) {
//          dump2(r,rr);
//          dump4(z,x,y,xyz);
        }
        assert(xyz%N==0);
        Y.emplace(xyz);
      }
    }
    if(SZ(Y)) {
      LL a=*(Y.begin());
      string s=to_string(a);
      int L=SZ(s);
      if(L<9) return s;
      return s.substr(0,3)+"..."+s.substr(L-3,3)+"("+to_string(L)+" digits)";
    }
    
    return no;
  }
};

// CUT begin
ifstream data("MultiplesWithLimit.sample");

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

bool do_test(int N, vector<int> forbiddenDigits, string __expected) {
    time_t startClock = clock();
    MultiplesWithLimit *instance = new MultiplesWithLimit();
    string __result = instance->minMultiples(N, forbiddenDigits);
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
        int N;
        from_stream(N);
        vector<int> forbiddenDigits;
        from_stream(forbiddenDigits);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, forbiddenDigits, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519610357;
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
        cout << "MultiplesWithLimit (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
