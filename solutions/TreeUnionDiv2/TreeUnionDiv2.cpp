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
 
 11/30/2017
 
 9:40-10:00 analysis
 17:55-18:49 implement, bug fix (missing clear of global var) and TLE
 19:27 give up
 
 20:16-20:31 read editorial and add solution
 
 Editorial:
  - http://apps.topcoder.com/wiki/display/tc/SRM+581
  - http://kmjp.hatenablog.jp/entry/2013/06/05/0930
 
 Generic algorithm to find K-length cycle does not work.
 So we need to use some property unique to merge of two trees.
 
 Since merging two trees which has no cycle in itself, cycle needs to visit both A and B.
 Suppose we start from tree A without losing generaligy.
 If we want to visit tree B twice, K needs to be more than 7 as shown below:

   A B
 /-0-0
 |   |
 | 1-1
 | |
 | 2-2
 |   |
 \-3-3
 
 So we visit B only once.
 
 There should be exactly two vertices in cycle which are connected to B.
 We can brute force them in O(N^2).
 If dist(i_A,j_A)+dist(i_B,j_B)+2 == K, it's the path we want to count.
 
 dist(i,j) for A and B is always min distance because there is no cycle in tree.
 It can be precomputed by floyd-warshall.
 If permutation is given, i_B and j_b can be determined in O(1).
 If we brute force permutation in O(N!), total runtime is O(N!*N^2) ≈3*10^7.
 
 We checkmated.
 
 Key:
  - Generic way to count K-length cycle does not work for given size of trees
  - If we want to visit tree B twice, we need at least distance 8. So tree B is visited only once.
  - Number of vertices in A which is connected to B is at most 2. We can brute force it in O(N^2)
  - Total distance is dist(i_A,j_A)+dist(i_B,j_B)+2
 
 Summary:
  - I tried to solve by finding K-length cycle in generic way
    - I thought that it's possible by O(N^2*K) though, it was actually O(K!). Thus my code TLEed
     - O(N!*K!) ≈ 2*10^9
    - I learned that my understanding of analysis of DFS was not correct
     - It's linear only when we don't need to differentiate order of visit
     - Since my TLEed code is flipping viz flags, order matters.
     - It's visiting all the possible sequences => O(K!) time
  - I should have analyzed O(K!) before writing code
   - Then I should have tried different idea
 
 */

int A[10][10],B[10][10];
class TreeUnionDiv2 {
public:
  int maximumCycles(vector<string> AA, vector<string> BB, int K) {
    int N=SZ(AA);
    
    const int Inf=100;
    REP(i,N)REP(j,N) A[i][j]=Inf,B[i][j]=Inf;
    REP(i,N) REP(j,N) {
      if(AA[i][j]=='X') A[i][j]=1;
      if(BB[i][j]=='X') B[i][j]=1;
    }
    REP(i,N) A[i][i]=0,B[i][i]=0;
    
    REP(k,N) REP(i,N) REP(j,N) {
      A[i][j]=min(A[i][j],A[i][k]+A[k][j]);
      B[i][j]=min(B[i][j],B[i][k]+B[k][j]);
    }
    
    int res=0;
    VI P(N);
    REP(i,N) P[i]=i;
    
    do {
      int cnt=0;
      REP(j,N) REP(i,j) {
        int ii=P[i],jj=P[j];
        if(A[i][j]+B[ii][jj]+2==K) ++cnt;
      }
      
      res=max(res, cnt);
      //      assert(++c<=362880);
    } while(next_permutation(P.begin(),P.end()));
    
    return res;
  }
};

int viz[21];
VI E[20];
class TreeUnionDiv2_tle {
  public:
  int N,K,V;
  int dfs(int u, int d, int pre, int st) {
    if(d==K) return u==st;
    assert(d<=K);
    if(viz[u]) return 0;
    viz[u]=1;
    
    int res=0;
    FORR(v,E[u]) if(v!=pre&&v>=st) {
      res+=dfs(v,d+1,u,st);
    }
    
    viz[u]=0;
    return res;
  }
  
  int f(VI &P) {
    REP(u,N) {
      int v=P[u];
      E[u].push_back(v);
      E[v].push_back(u);
    }
    
//    dumpAR(P);
    int res=0;
    REP(u,V) {
      ZERO(viz);
      int x=dfs(u,0,-1,u);
//      dump2(u,x);
      assert(x%2==0);
      res+=x/2;
    }
    
    REP(u,N) {
      int v=P[u];
      E[u].pop_back();
      E[v].pop_back();
    }
    
//    dump(res);
    return res;
  }
  
  int maximumCycles(vector<string> A, vector<string> B, int K) {
    this->N=SZ(A);
    this->K=K;
    this->V=2*N;
    REP(i,V) E[i].clear();
    
    REP(i,N) REP(j,N) {
      if(A[i][j]=='X') E[i].push_back(j);
      if(B[i][j]=='X') E[N+i].push_back(N+j);
    }
//    dumpAR(E[0]);
    
    int res=0;
    VI P(N);
    REP(i,N) P[i]=N+i;
    
//    int c=0;
    do {
//      dump(++c);
      res=max(res, f(P));
//      assert(++c<=362880);
    } while(next_permutation(P.begin(),P.end()));
    
    return res;
  }
};

// CUT begin
ifstream data("TreeUnionDiv2.sample");

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

bool do_test(vector<string> tree1, vector<string> tree2, int K, int __expected) {
    time_t startClock = clock();
    TreeUnionDiv2 *instance = new TreeUnionDiv2();
    int __result = instance->maximumCycles(tree1, tree2, K);
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
        vector<string> tree1;
        from_stream(tree1);
        vector<string> tree2;
        from_stream(tree2);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(tree1, tree2, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512063590;
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
        cout << "TreeUnionDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
