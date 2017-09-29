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
 
 9/28/2017
 
 9:22-10:05 pause
 19:00-19:20 implement wrong greedy
 19:20-19:23 debug and samples passed though 1WA in system test
 
 19:24-19:45 design dp
 19:46-19:56 implement
 19:57-20:29 debug and fixed bugs (parameter of countInv() and missing memo). system test passed.
 
 suppose we are trying to find range to reverse numbers in A[i..<N].
 we can brute force pair of indices of range [x,y) where i<=x<y<=N.
 inversion of [i,y) can be computed regardless of order in A[0..<i].
 So we can solve sub problem as below:
 
 inversion([0,l) vs [l,r) = |{ (i,j) : l<=i<j<r, A[i]>A[j] }|
 
 f(N,_) = 0
 f(i,0) = inversion([0,i) vs [i,N))
 f(i,k) = inversion([0,i) vs [i,y)) + f(y,k-1)
 res = f(0,K)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+627
    - Inversion: https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)
  - http://kmjp.hatenablog.jp/entry/2014/07/12/1030
  - http://torus711.hatenablog.com/entry/20140715/1405426075
    - Fenwick tree
 
 key:
  - problem to count inversion
  - reversed range is disjoint. inversion in intervals can be computed separatedly
 
 summary:
  - solved 👍
  - it took a long time until dp comes up 👎
  - I focused on interval and dp by left and right interval though, it's too many parameters.
  - reduced parameters by focusing on only left index and do dp from left to right
 
 */

// O(K*N^5) time
int memo[51][51];
class BubbleSortWithReversals {
public:
  int N,K;
  VI A;
  int countInvs(int l, int r, VI A) {
    int res=0;
    FOR(j,l,r) REP(i,j) {
      if(A[i]>A[j]) ++res;
    }
    return res;
  }
  
  int f(int st, int k) {
    if(k==0) return memo[st][k]=countInvs(st,N,A);
    if(st==N) return 0;
    if(memo[st][k]>=0) return memo[st][k];
    
    int res=1e9;
    FOR(x,st,N) FOR(y,x+1,N+1) {
      VI A2=A;
      reverse(A2.begin()+x,A2.begin()+y);
      res=min(res, countInvs(st,y,A2)+f(y,k-1));
    }
    return memo[st][k]=res;
  }
  
  int getMinSwaps(vector<int> A, int K) {
    this->K=K;
    this->N=SZ(A);
    this->A=A;
    MINUS(memo);
    
    return f(0,K);
  }
};

class BubbleSortWithReversals_wrong_greedy {
  public:
  int N;
  int countInvs(VI &A) {
    int res=0;
    REP(j,N) REP(i,j) {
      if(A[i]>A[j]) ++res;
    }
    return res;
  }
  
  III minRange(int l, int r, VI A) {
    int minn=countInvs(A); int resl=l,resr=r;
    FOR(i,l,r) FOR(j,i+1,r+1) {
      VI A2=A;
      reverse(A2.begin()+i, A2.begin()+j);
      int invs=countInvs(A2);
      if(invs<minn) {
        minn=invs,resl=i,resr=j;
      }
    }
    return make_tuple(minn, resl, resr);
  }
  
  int getMinSwaps(vector<int> A, int K) {
    this->N=SZ(A);
    vector<II> rs={{0,N}};
    while(K-->0) {
      int mininv=countInvs(A); int l=-1,r=-1,x=-1;
      REP(i,SZ(rs)) {
        int inv,ll,rr;
        tie(inv,ll,rr)=minRange(rs[i].first,rs[i].second,A);
        if(inv<mininv) {
          mininv=inv,l=ll,r=rr; x=i;
        }
      }
      dump4(mininv,l,r,x);
      if(l==-1||r==-1) return mininv;
      reverse(A.begin()+l,A.begin()+r);
      dumpAR(A);
      vector<II> next;
      REP(i,SZ(rs)) {
        if(i==x) {
          next.emplace_back(rs[i].first,l);
          next.emplace_back(r,rs[i].second);
        } else {
          next.push_back(rs[i]);
        }
      }
      rs=next;
    }
    return countInvs(A);
  }
};

// CUT begin
ifstream data("BubbleSortWithReversals.sample");

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

bool do_test(vector<int> A, int K, int __expected) {
    time_t startClock = clock();
    BubbleSortWithReversals *instance = new BubbleSortWithReversals();
    int __result = instance->getMinSwaps(A, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506615761;
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
        cout << "BubbleSortWithReversals (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
