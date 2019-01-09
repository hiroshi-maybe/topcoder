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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/31/2017
 
 9:15-9:29 design
 9:49 OMG, we need sum of size :(
 9:57 time up
 
 18:20-20:00 read editorials
 - Inclusion-exclusion principle and formula transformation
  - http://pekempey.hatenablog.com/entry/2016/03/01/132020
 - compute dependency from set of subtree to another subtree
  - https://apps.topcoder.com/wiki/display/tc/SRM+683
  - http://kmjp.hatenablog.jp/entry/2016/03/01/1000
 
 22:00-22:10 sort out recursion relation.
 
 cnt(u,v[j]) = ∏ { 1+cnt(v[i],*) : i = 0..j }
 sum(u,v[j]) = sum(u,v[j-1]) * (1+cnt(v[j],*)) + sum(v[j],*) * cnt(u,v[j-1])
 
 cnt(u,*)=1, sum(u,*)=1 if no children
 
 res = ∑ { sum(u,*) : u∈V }
 
 22:10-22:19 implement and passed system test (official editorial and @kmjp approach)
 
 @pekempey's formula:
 
 cnt(u) = ∏ { 1+cnt(v[i] }
 sum(u) = ∑ { sum(v[i])*cnt(u)/(1+cnt(v[i]) } + cnt(u)  ....(X)
        = cnt(u) * ( 1 + ∑ { sum(v[i])/(1+cnt(v[i]) } ) ....(Y)
 
 22:20-23:13 I missed conversion from (X) to (Y) above and took some time to resolve it though, passed system test
 
 23:15-23:23 read submit solutions.
 official editorial approach
 - https://community.topcoder.com/stat?c=problem_solution&rm=328151&rd=16653&pm=14179&cr=23328790
 - https://community.topcoder.com/stat?c=problem_solution&rm=328151&rd=16653&pm=14179&cr=23295192
 @pekempey's approach
 - https://community.topcoder.com/stat?c=problem_solution&rm=328163&rd=16653&pm=14179&cr=40045834
 
 Key
 - instead of focusing on how many total sizes parent has (top-down), think about how sizes of children can contribute to total sizes (bottom-up)
 - make a recursive relation in children-wise (official editorial) or use Inclusion-exclusion principle (@pekempey)
  - in either way, basic analysis is almost same. focus on how to handle sum of each subtrees.
 - writing a simple example helps a lot in this problem too
 
 Summary
 - straightforward how to count number of distinct sub trees
 - I was wondering if another state is needed though, solution didn't come up with me
 - we cannot give states to {tree size} x {tree count}. try to solve by only iterating children.
 - instead of focusing on how many total sizes parent has (top-down), think about how sizes of children can contribute to total sizes (bottom-up)
  - which is better approach? it depends on problems. probably important thing is that if either way doesn't work, try the other for more chance to solve problems.
  - another tricky part is solving horizontal subproblem iterating each sub-trees. this is actually very popular way to solve tree problem. keep in mind
 - nice to find out how to count size of subtree sets. another hop is necessary to solve this problem.
 
 */
constexpr int MOD = 1e9+7;
VI E[100005];
LL SUM[100005];
LL CNT[100005];

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
LL modinv(LL a) {
  return powmod(a, MOD-2);
}

class SubtreesCounting {
public:
  LL ans=0;
  void dfs(int u) {
    CNT[u]=1LL;
    SUM[u]=1LL;
    FORR(v,E[u]) {
      dfs(v);
      CNT[u]*=(1+CNT[v]), CNT[u]%=MOD;
      SUM[u]+=SUM[v]*modinv(1+CNT[v]), SUM[u]%=MOD;
    }
    SUM[u]*=CNT[u], SUM[u]%=MOD;
    ans += SUM[u], ans%=MOD;
  }
  
  int sumOfSizes(int V, int a0, int B, int C, int M) {
    REP(i,V+1) E[i].clear();
    vector<LL> A(V-1,a0);
    FOR(i,1,V-1) A[i]=((LL)B*A[i-1]+(LL)C)%(LL)M;
    FOR(c,1,V) {
      int par=A[c-1]%c;
      E[par].push_back(c);
    }
    dfs(0);
    
    return ans;
  }
};

class SubtreesCounting_dp1 {
public:
  LL ans=0;
  void dfs(int u) {
    LL cnt=1LL;
    LL sum=1LL;
    
    FORR(v,E[u]) {
      dfs(v);
      sum *= 1LL+CNT[v], sum%=MOD;
      sum += SUM[v]*cnt, sum%=MOD;
      cnt *= (1+CNT[v]), cnt%=MOD;
    }
    
    SUM[u]=sum, CNT[u]=cnt;
    ans += SUM[u], ans%=MOD;
  }
  
  int sumOfSizes(int V, int a0, int B, int C, int M) {
    REP(i,V+1) E[i].clear();
    vector<LL> A(V-1,a0);
    FOR(i,1,V-1) A[i]=((LL)B*A[i-1]+(LL)C)%(LL)M;
    FOR(c,1,V) {
      int par=A[c-1]%c;
      E[par].push_back(c);
    }
    dfs(0);
    
    return ans;
  }
};

class SubtreesCounting_cnt {
  public:
  LL ans=0;
  LL dfs(int u) {
    LL res=1LL;
    FORR(v,E[u]) (res*=dfs(v)+1)%=MOD;
    (ans+=res)%=MOD;
    return res;
  }
  
  int sumOfSizes(int V, int a0, int B, int C, int M) {
    REP(i,V+1) E[i].clear();
    vector<LL> A(V-1,a0);
    FOR(i,1,V-1) A[i]=((LL)B*A[i-1]+(LL)C)%(LL)M;
    FOR(c,1,V) {
      int par=A[c-1]%c;
      E[par].push_back(c);
    }
    dfs(0);
    return ans;
  }
};

// CUT begin
ifstream data("SubtreesCounting.sample");

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

bool do_test(int n, int a0, int b, int c, int m, int __expected) {
    time_t startClock = clock();
    SubtreesCounting *instance = new SubtreesCounting();
    int __result = instance->sumOfSizes(n, a0, b, c, m);
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
        int n;
        from_stream(n);
        int a0;
        from_stream(a0);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        int m;
        from_stream(m);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, a0, b, c, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501517694;
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
        cout << "SubtreesCounting (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
