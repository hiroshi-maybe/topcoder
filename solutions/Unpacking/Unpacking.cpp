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
 
 12/19/2017 SRM 726
 
 8:03-9:15 Time up in contest
 
 1/4/2018
 
 23:00-23:30 retry and read editorial
 
 Editorial:
  - http://hamayanhamayan.hatenablog.jp/entry/2017/12/20/032938
  - http://kmjp.hatenablog.jp/entry/2017/12/30/0900
  - https://twitter.com/koyumeishi_/status/943176573028515840
  - http://codeforces.com/blog/entry/56434
  - https://togetter.com/li/1182951?page=8
 
 1/7/2018
 
 23:00-25:48 Read editorials, understand and add my explanation. Add solution and system test passed.
 
 Some of explanations are mentioning to Manhattan distance.
 However, reducing to formula and graph seems to be more straightforward for me.
 
 As a first step, let's pin a condition that we need to satisfy.
 Suppose we selected boxes S ⊆ U={0,..,N-1}
 In order to guarantee that number of candy of a color >=K, what needs to be satisfied?
 
 If |S|=M, a = ∑ { X[i]: i∈S }, b = ∑ { Y[i]: i∈S }, a<=b, we should satisfy...
 
 min { max(a+x,b-x) : 0<=x<=M } >= K
 
 Note that for symmetry of A and B, (X,Y) could be (A,B) or (B,A). It's determined by condition a<=b.
 
 We get below graph if max(a+x,b-x) is drawn:
 
  b|     /
   |\   /
   | \_/
   |
  a|
   |
   -------- 0<=x<=M
      p
 
 As ween in the graph, max(a+x,b-x) forms unimodal curve with downward convex.
 Also it's clearly minimal when a+p==b-p => p = floor((b-a)/2) (or ceil((b-a)/2). Either one should give same value)
 
 However `p` is not always valid in conditin 0<=x<=M
 There are two cases:
 1) M<p
 2) p<=M
 
 In case 1) a-M is minimal.
 If either of following cases holds, it's guaranteed that number of candy of a color >=K
 1-1) ∑ A[i]-|S| = ∑ (A[i]-1) >= K
 1-2) ∑ B[i]-|S| = ∑ (B[i]-1) >= K
 
 In case 2)...
 
 We use p = floor((b-a)/2)
 
   a + p
 = a + floor((b-a)/2)
 = floor(a+(b-a)/2)
 = floor((a+b)/2)
 
   b - p
 = b - floor((b-a)/2)
 = b + ceil(-(b-a)/2)
 = ceil(b-(b-a)/2)
 = ceil((a+b)/2)
 
 Look at https://en.wikipedia.org/wiki/Floor_and_ceiling_functions#Equivalences for floor/ceil arithmetic.
 
   max(a+p,b-p)
 = max(floor((a+b)/2), ceil((a+b)/2))
 = ceil((a+b)/2) >= (a+b+1)/2 >= K
 
 => a+b >= 2*K-1
 
 Now finally we figured out that we want to find minimum cost which satisfies either of following cases:
 
 1) ∑ (A[i]-1) >= K
 2) ∑ (B[i]-1) >= K
 3) ∑ (A[i]+B[i]) >= 2*K-1
 
 It's possible to find minimum cost for #1, #2, and #3 separatedly by knapsack DP.
 
 Key:
  - Analyze condition to be satisfied from formula and graph
  - Reduce to knapsack problem
  - K<=10000. No need to compute count >10000
 
 Summary:
  - I had an idea of knapsack DP during the contest though, my analysis skill was not enough to reduce to three independent cases
  - max(a+x,b-x) is popular unimodal function with downward convex. I should remember it.
  - I've not figured out some of rounding arithmetics. Be familiar with those basics.
   - a+floor(b) = floor(a+b)
   - -floor(a) = ceil(-a)
 
 */

int dp[20005];
class Unpacking {
public:
  const int Inf=1e6;
  VI A,B,AB,C;
  int N;
  int f(VI &X, int d, int K) {
    ZERO(dp);
    REP(w,20005) dp[w]=Inf;
    dp[0]=0;
    REP(i,N) for(int w=20001; w>=0; --w) {
      if(w+X[i]-d>=0) dp[min(w+X[i]-d,20000)]=min(dp[min(w+X[i]-d,20000)], dp[w]+C[i]);
    }
    int res=Inf;
    FOR(c,K,20005) res=min(res,dp[c]);
    return res;
  }
  
  int getcost(vector<int> A, vector<int> B, vector<int> C, int K) {
    this->A=A,this->B=B,this->C=C;
    this->N=SZ(A);
    
    int a=f(A,1,K),b=f(B,1,K);
    AB.resize(N);
    REP(i,N) AB[i]+=A[i]+B[i];
    int c=f(AB,0,2*K-1);
    
//    dump3(a,b,c);
    int res=min({a,b,c});
    return res==Inf?-1:res;
  }
};

class Unpacking_org {
  public:
  II dp[51][500001];
  int getcost(vector<int> A, vector<int> B, vector<int> C, int K) {
    int N=SZ(A);
    REP(i,N+1) REP(j,500001) dp[i][j]={-10,-10};
    dp[0][0]={0,0};
    REP(i,N) REP(j,500001) if(dp[i][j].first>=0&&j+C[i]<=500000) {
      int a=dp[i][j].first+A[i],b=dp[i][j].second+B[i],j2=j+C[i];
      int x=min({max(a+1,b-1),max(a,b),max(a-1,b+1)});
//      dump4(i,j,a,b);

      int a2=dp[i+1][j2].first,b2=dp[i+1][j2].second;
      int x2=min({max(a2+1,b2-1),max(a2,b2),max(a2-1,b2+1)});
      if(x>=x2) dp[i+1][j2]={a,b};
    }
    
    int res=1e9;
    REP(i,N+1) REP(c,500001) if(dp[i][c].first>=0) {
      int a=dp[i][c].first,b=dp[i][c].second;
      int x=min({max(a+1,b-1),max(a,b),max(a-1,b+1)});
//      if(x>0) dump4(c,a,b,x);
      if(x>=K) res=min(res,c);
    }
    
    return res==1e9?-1:res;
  }
};

// CUT begin
ifstream data("Unpacking.sample");

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

bool do_test(vector<int> a, vector<int> b, vector<int> cost, int K, int __expected) {
    time_t startClock = clock();
    Unpacking *instance = new Unpacking();
    int __result = instance->getcost(a, b, cost, K);
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
        vector<int> b;
        from_stream(b);
        vector<int> cost;
        from_stream(cost);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, cost, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513699383;
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
        cout << "Unpacking (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
