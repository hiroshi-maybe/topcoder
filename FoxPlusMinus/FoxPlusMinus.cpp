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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/12/2018
 
 17:21-18:15 analysis
 18:16-19:40 Values of matrix is too large. Give up.
 
 My analysis:
 
 There is recurrence relation for A[x]. That can be represented by K*K matrix transformation:
 
 f(x)     (1,-1,1,-1,..,(-1)^(K-1))   f(x-1)
 f(x-1)   (1, 0,0, 0,..,         0)   f(x-2)
 .      = (0, 1,0, 0,..,         0) x .
 .        ...                         .
 f(x-K)   (0, 0,0, 0,.,1,        0)   f(x-K-1)

 f(x)     (1,-1,1,-1,..,(-1)^(K-1))^(x-K+1)   f(K-1)
 f(x-1)   (1, 0,0, 0,..,         0)           f(K-2)
 .      = (0, 1,0, 0,..,         0)         x .
 .        ...                                 .
 f(x-K)   (0, 0,0, 0,.,1,        0)           f(0)

 1/13/2018
 
 16:00-17:19 read editorial and add solution.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+552
  - http://kmjp.hatenablog.jp/entry/2013/12/28/0930
 
 Rearrangement inequality
  - https://en.wikipedia.org/wiki/Rearrangement_inequality
 
 Summary:
  - I represented recurrence relation and computed A[N] by matrix power in O(N^3*lg N) though, value is too large 😵
  - Value keeps increasing like fibonacci. It's very large number. We should not try to compute it without MOD.
  - We want to know order of K elements in A[N]. Computing real value is not necessary.
  - In such a case, we can try to find cycle or math property.
  - I figured out rearrangement inequality by myself 👍
  - My biggest fault is that I didn't analyze the case K is even 👎
 
 */
const int MX=51;
LL A[MX][MX], B[MX][MX];
//constexpr int MOD = 1e9+7;

// matrix multiplication
// X = XxY, X: NxN matrix, Y: NxN matrix, N<MX
void timeMat(LL X[MX][MX], LL Y[MX][MX], int N) {
  LL tmp[MX][MX]; memset(tmp,0,sizeof(tmp));
  
  for(int i=0; i<N; ++i) {
    for(int j=0; j<N; ++j) {
      for(int k=0; k<N; ++k) tmp[i][j] += (X[i][k]*Y[k][j]);
    }
  }
  
  for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) X[i][j]=tmp[i][j];
}
// B = A^n, B: NxN matrix, A: NxN matrix, N<MX
void powerMat(LL n, int N) {
  assert(N<=MX);
  assert(n>=0);
  
  // B = I (identity matrix)
  memset(B,0,sizeof B);
  for(int i=0; i<N; ++i) B[i][i]=1;
  
  LL X[MX][MX];
  for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) X[i][j]=A[i][j];
  
  while(n) {
    // invariant: X = A^(2^i)
    if (n&1) timeMat(B,X,N); // B=B*X
    timeMat(X,X,N); // X=X^2
    n>>=1;
  }
}

int P[51];
class FoxPlusMinus_wrong {
  public:
  int K;
  VI solve(VI ns, vector<LL> X) {
    sort(ns.begin(),ns.end());
    MINUS(P);
    dumpAR(ns);
    dumpAR(X);
    
    VI res(K);
    set<pair<LL,int>> S;
    REP(i,K) S.emplace(X[i],i);
    
    int i=0;
    FORR(p,S) res[p.second]=ns[i++];
    
    /*
    const LL Inf=1e18;
    REP(i,SZ(X)) {
      LL k=-1, x=-Inf;
      REP(j,SZ(ns)) if(P[j]==-1&&ns[j]*X[i]>x) k=j,x=ns[j]*X[i];
      
    }*/
    
    return res;
  }
  
  vector<int> maximize(vector<int> ff, int N) {
    this->K=SZ(ff);
    ZERO(A);
    REP(i,K) A[0][i]=(K-i-1)%2==0?1:-1;
    FOR(i,1,K) A[i][i-1]=1;

    if(N<K) {
      vector<LL> X(K,0);
      X[N]=1;
      return solve(ff,X);
    }
    
    LL base[MX][MX]={};
    ZERO(base);
    REP(i,K) base[i][K-i-1]=1;
    
    powerMat(N-K+1,K);
    
    // B=P^(N-K+1), base=A0
    timeMat(B,base,K);
    
    vector<LL> X(K,0);
    REP(i,K) {
      X[i]=B[0][i];
//      if(i%2&&(N-K+1)%2) X[i]*=-1;
//      if(i%2==0&&(N-K+1)%2==0) X[i]*=-1;
    }
    
    return solve(ff, X);
  }
};

class FoxPlusMinus {
public:
  int K;
  VI solve(VI ns, VI X) {
    sort(ns.begin(),ns.end());
    MINUS(P);
    dumpAR(ns);
    dumpAR(X);
    
    VI res(K);
    set<II> S;
    REP(i,K) S.emplace(X[i],i);
    
    int i=0;
    FORR(p,S) res[p.second]=ns[i++];
    
    return res;
  }
  
  vector<int> maximize(vector<int> ff, int N) {
    this->K=SZ(ff);
    VI X(K,0);
    if(N<K) {
      X[N]=1;
      return solve(ff,X);
    }
    // K is odd
    if(K%2==1) {
      if(N%(K+1)==K) {
        REP(i,K) X[i]=i%2==1?-1:1;
        return solve(ff,X);
      } else {
        X[N%(K+1)]=1;
        return solve(ff,X);
      }
    }
    
    // K is even
    if(N<2*K) {
      REP(i,N-K) X[i]=i+1;
      FOR(i,N-K,K) X[i]=N-K+1;
    } else {
      REP(i,K) X[i]=i+1;
    }
    REP(i,K) {
      if(i%2&&(N-K+1)%2) X[i]*=-1;
      if(i%2==0&&(N-K+1)%2==0) X[i]*=-1;
    }
    
    return solve(ff, X);
  }
};

// CUT begin
ifstream data("FoxPlusMinus.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> first, int N, vector<int> __expected) {
    time_t startClock = clock();
    FoxPlusMinus *instance = new FoxPlusMinus();
    vector<int> __result = instance->maximize(first, N);
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
        vector<int> first;
        from_stream(first);
        int N;
        from_stream(N);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(first, N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515806445;
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
        cout << "FoxPlusMinus (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
