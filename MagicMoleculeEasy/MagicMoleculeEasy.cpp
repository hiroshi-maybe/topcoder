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
 
 12/15/2017
 
 8:34-9:50 time up
 16:30-17:06 read editorials
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+571
  - http://kmjp.hatenablog.jp/entry/2013/03/13/0900
  - http://mecha-g3.hatenablog.com/entry/20130223/1361592134

 17:30-17:55 add solution

 K is small (<=14). This is definitely a key to solve this problem.
 We want to cover ALL the edges by selecting 14 vertices.
 This is tight constraint that we need to satisfy.
 Let's iterate edges to cover all of them. There are two edge states when looking at current edge.
 1) edge is already covered (u or v is already picked up)
   => No need to cover current edge. Go to next edge. T(n)=T(n-1)
 2) edge is not covered yet
   => try picking up u or v and keep searching. T(n)=2*T(n-1)
 
 Case 2 happens at most 14 times.
 In the worst case, after branching into 2^14 states by case #2, case #1 happens |E|-K times.
 Also eventually unvisited vertices are sorted and picked up greatest `k` powers in (V-K)*lg (V-k).
 
 Thus total run time in worst case is O(2^K*(V*(V-1)/2-K + (V-K)*lg(V-k)) time (≈3*10^7 for K<=14, V<=50)
 
 Note that vertex cover problem is NP-hard. If we can find out that, we can be confident to take bruteforce approach.
  - https://en.wikipedia.org/wiki/Vertex_cover
 
 Key:
  - Sooner or later all the edges need to be covered
   - We can skip current edge ONLY when u or v is already selected in different edge
   - If current edge is not covered yet, pick it up. There is no room to make a decision of skip
   - This constraint reduces runtime drasticly!!!
  - After ensuring to have covered all the edges, we can pick up remaining k greatest vertices.
 
 Summary:
  - I estimated runtime in brute-force as C(50,14) though, that's not taking care of constraint that all the edges MUST be covered (no choice to skip)
  - It's kind of interesting that condition of coverage of all the edges upper-bounds search space
  - Nice to learn that removing choice to stick to constraint reduces complexity a lot EVEN in brute-force
  - I thought that small `K` is a key to solve though, I couldn't come up with backtracking with branch pruning proved to stop.
 
 */

int viz[51];
class MagicMoleculeEasy {
  public:
  int res=-1;
  int V;
  VI P;
  vector<II> es;
  void dfs(int p, int k) {
    if(k<0) return;
    if(p==SZ(es)) {
      int x=0;
      VI ss;
      REP(i,V) {
        if(viz[i]) x+=P[i];
        else ss.push_back(P[i]);
      }
      sort(ss.rbegin(),ss.rend());
      REP(i,k) x+=ss[i];
      res=max(res,x);
      return;
    }
    
    int u=es[p].first,v=es[p].second;
    if(viz[u]||viz[v]) {
      dfs(p+1,k);
    } else {
      viz[u]=true;
      dfs(p+1,k-1);
      viz[u]=false;
      
      viz[v]=true;
      dfs(p+1,k-1);
      viz[v]=false;
    }
  }
           
  int maxMagicPower(vector<int> P, vector<string> G, int K) {
    ZERO(viz);
    this->V=SZ(P);
    this->P=P;
    REP(v,V) REP(u,v) if(G[u][v]=='Y') es.emplace_back(u,v);
    dfs(0,K);
    return res;
  }
};

// CUT begin
ifstream data("MagicMoleculeEasy.sample");

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

bool do_test(vector<int> magicPower, vector<string> magicBond, int k, int __expected) {
    time_t startClock = clock();
    MagicMoleculeEasy *instance = new MagicMoleculeEasy();
    int __result = instance->maxMagicPower(magicPower, magicBond, k);
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
        vector<int> magicPower;
        from_stream(magicPower);
        vector<string> magicBond;
        from_stream(magicBond);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(magicPower, magicBond, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513355634;
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
        cout << "MagicMoleculeEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
