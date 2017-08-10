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

/**
 
 8/9/2017
 
 10:04-10:40 pause
 18:30-18:54 analyzed and give up
 
 22:10-24:50 read editorials:
 - http://kmjp.hatenablog.jp/entry/2015/12/04/1000
 - https://apps.topcoder.com/wiki/display/tc/SRM+674
 
 vertex cover poblem (NP-hard)
  - https://en.wikipedia.org/wiki/Vertex_cover
 
  i) child c is taken in parent-child relationship
    => must_take(c)=true
 ii) child c is NOT taken in parent-child relationship
    => must_take(parent(c))=true, never_take(c)=true
 
 S_take(u)    = never_take(u)=0 ?
                  => 1+∑ { f_size(v[i],optional) : v[i] is children of u }
                otherwise
                  => Inf
 S_notTake(u) = must_take(u)=0
                  =>   ∑ { f_size(v[i],required) : v[i] is children of u }
                otherwise
                  => Inf
 
 f_size(u,optional) = min(S_take(u), S_notTake(u))
 f_size(u,required) = S_take(u)
 
 f_cnt(u,optional) = S_take(u)==S_notTake(u)
                      => C_take(u) + C_notTake(u)
                     S_take(u)< S_notTake(u)
                      => C_take(u)
                     S_notTake(u)< S_take(u)
                      => C_notTake(u)
 f_cnt(u,required) = C_take(u)
 
 res = f_cnt(u,optional) where f_size(u,optional) for child mask x is minimum
 
 24:50-25:25 add solution
 
 Key:
  - combination of two problems 1. master-servant and 2. parents-child
    1. master-servant problem is also combination of below two problems
      - vertex cover problem of tree (DP to get minimum vertices)
      - count problem of tree
    2. parents-child
      - brute-force all the assignments of child
  - analyze master-servant and parents-child separatedly
  - {take}/{take,not take} rather than {take},{not-take} in vertex cover problem tree DP
  - Pin parents-child assignment first. do search by DP in condition of those assignments

 Summary:
  - Even DP of master-servant is wrong 👎
  - Read problem and analyze patterns CAREFULLY CAREFULLY CAREFULLY CAREFULLY 👎
    - master-servant
      - grand master (take) - servant (not take) - grand servant (take): covered
      - grand master (not take) - servant (take) - grand servant (take): covered
      - grand master (take) - servant (take) - grand servant (not take): missing this case ❌
    - parents-child (one vampire from EACH parent/child relationship
      - parent1 (not take), parent2 (not take), child (take): covered
      - parent1 (take), parent2 (not take), child (not take): WRONG ❌
      - parent1 (not take), parent2 (take), child (not take): WRONG ❌
      - parent1 (take), parent2 (take), child (not take): missing ❌
  - We need to consider two conditions. In such a case, usually pin either condition first. Search states which satisfies another condition by keeping invariant of pined first condition.
  - problem level is way too far from my skill
 
 */

constexpr int MOD = 1e9+7;
VI E[1005];
LL cnt[1005][2];
int sz[1005][2];
int mustTake[1005];
int neverTake[1005];
class VampireTreeDiv2 {
  public:
  void f(int u, int req) {
    if(sz[u][req]>0) return;
    int minsz = 1001;
    LL c=0;
    
    if(neverTake[u]==0) {
      int x=1; LL y=1;
      FORR(v,E[u]) {
        f(v,0);
        x+=sz[v][0];
        y=(y*cnt[v][0])%MOD;
      }
      minsz=x, c=y;
    }
    
    if(!req&&mustTake[u]==0) {
      int x=0; LL y=1;
      FORR(v,E[u]) {
        f(v,1);
        x+=sz[v][1];
        y=(y*cnt[v][1])%MOD;
      }
      if(x<minsz) minsz=x, c=y;
      else if(x==minsz) c=(c+y)%MOD;
    }
    
    sz[u][req]=minsz;
    cnt[u][req]=c;
  }
  
  int countMinSamples(vector<int> A, vector<int> B) {
    int V=SZ(A)+1;
    VI cs;
    REP(i,V) E[i].clear();
    REP(i,SZ(A)) {
      E[A[i]].push_back(i+1); // even if child has two parents, add only either one to avoid duplicated count
      if(B[i]!=-1) cs.push_back(i+1);
    }
    
    int minsz=1001;
    LL res=0;
    REP(mask,1<<SZ(cs)) {
      ZERO(mustTake); ZERO(neverTake);
      REP(i,SZ(cs)) {
        int c=cs[i];
        if(mask&(1<<i)) {
          mustTake[c]=1;
        } else {
          mustTake[A[c-1]]=mustTake[B[c-1]]=1;
          neverTake[c]=1;
        }
      }
      
      ZERO(sz);
      MINUS(cnt);
      f(0,0);
      if(sz[0][0]<minsz) minsz=sz[0][0], res=0;
      if(sz[0][0]==minsz) res+=cnt[0][0], res%=MOD;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("VampireTreeDiv2.sample");

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
    VampireTreeDiv2 *instance = new VampireTreeDiv2();
    int __result = instance->countMinSamples(A, B);
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
        int T = time(NULL) - 1502298254;
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
        cout << "VampireTreeDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
