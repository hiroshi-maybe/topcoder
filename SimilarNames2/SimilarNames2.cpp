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
 
 11/2/2017
 
 19:46-20:00 understand problem
 20:00-20:46 1WA TLE
 20:47-20:55 1WA overflow
 21:00 system test passed
 
 I tried to solve by writer's original solution though, I could not.
 I was trying build a tree a this moment.
 I found that I can build tree and do DFS from all the vertices as root.
 However Somehow code TLEed 😱. It turns out I was building graph as below:
 a->aa->aaa
 a->aaa
 
 Also I missed to take MOD. Thus 2WA.
 
 Editorial:
  - writer's eidtorial:
   - http://topcoder.g.hatena.ne.jp/evima/20131210/1386698305
   - writer's comment: https://twitter.com/evima0/status/408294675947077633
   - build tree and use binomial coeffient (my original idea)
  - official editorial
   - https://apps.topcoder.com/wiki/display/tc/SRM+599
   - both DP and tree solutions
  - same as my DP solution
   - http://kmjp.hatenablog.jp/entry/2013/12/05/1200
    - iterative DP
   - http://torus711.hatenablog.com/entry/20131213/p2
   - http://emkcsharp.hatenablog.com/entry/SRM599/SimilarNames2

 25:00-25:24 add solution by problem writer
 
 Key:
  - build tree or graph from prefix and do DFS or DP
 
 Summary:
  - It was nice to switch to another approach
  - I was thinking that I built tree though, it was graph (DAG)
   - Pay more attention when switching approach
  - If I figure out DAG property first, it took less time.
 
 */

VI E[51];
//int viz[51];
int memo[51][51];
constexpr int MOD = 1e9+7;
class SimilarNames2_org {
  public:
  LL dfs(int u, int L) {
    if(memo[u][L]>=0) return memo[u][L];
    if(L==0) return 1;
    int res=0;
    FORR(v,E[u]) res+=dfs(v,L-1),res%=MOD;
    return memo[u][L]=res;
  }
  int count(vector<string> S, int L) {
    int N=SZ(S);
    REP(i,N) E[i].clear();
    LL F=1;
    FOR(x,1,N-L+1) F*=x,F%=MOD;
    
    sort(S.begin(),S.end());
    
    REP(j,N) REP(i,j) {
      if(S[j].find(S[i])==0) E[i].push_back(j);
    }
    
    LL pp=0;
    MINUS(memo);
    REP(i,N) pp+=dfs(i,L-1),pp%=MOD;
    return (pp*F)%MOD;
  }
};

LL C[52][52];
class SimilarNames2 {
public:
  int L;
  LL dfs(int u, int d) {
    LL res=0;
    if(d>0&&L>0&&d-1>=L-1) res+=C[d-1][L-1];
    FORR(v,E[u]) res+=dfs(v,d+1),res%=MOD;

    return res;
  }
  int count(vector<string> S, int L) {
    this->L=L;
    int N=SZ(S);
    REP(i,N+1) E[i].clear();
    ZERO(C);
    REP(i,N+2) {
      C[i][0]=1;
      FOR(j,1,i+1) C[i][j]=C[i-1][j]+C[i-1][j-1],C[i][j]%=MOD;
    }
    LL F=1;
    FOR(x,1,N-L+1) F*=x,F%=MOD;
//    sort(S.begin(),S.end());
    
    // add S[i] to longest prefix S[par]
    REP(i,N) {
      int par=N;
      REP(j,N) if(i!=j&&S[i].find(S[j])==0&&(par==N||SZ(S[j])>SZ(S[par]))) {
        par=j;
      }
      E[par].push_back(i);
    }
    LL pp=dfs(N,0);
    return (pp*F)%MOD;
  }
};

// CUT begin
ifstream data("SimilarNames2.sample");

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

bool do_test(vector<string> names, int L, int __expected) {
    time_t startClock = clock();
    SimilarNames2 *instance = new SimilarNames2();
    int __result = instance->count(names, L);
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
        vector<string> names;
        from_stream(names);
        int L;
        from_stream(L);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(names, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509677205;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SimilarNames2 (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
