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
 
 14:10-14:27 debug sample 3
 14:57 TLE in system test (396.18 pt)
 15:12 TLE again
 15:18 system test passed by memoization
 
 16:20-16:28 add BFS solution
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+618
  - http://torus711.hatenablog.com/entry/20140428/1398697489
  - http://kmjp.hatenablog.jp/entry/2014/04/27/1200
 
 key:
  - move of rooks still keeps permutation
  - number of possible state is at most 8! (≈4*10^4)
  - state transition forms DAG => DP or BFS
 
 summary:
  - it took a lot of time to figure out DAG and memoization 👎
  - obviously total number of state is N!. we want to avoid revisit. just manage visited state 😡
 
 solutions in contest:
  - BFS
   - https://community.topcoder.com/stat?c=problem_solution&rm=321891&rd=15851&pm=13065&cr=23139161
   - https://community.topcoder.com/stat?c=problem_solution&rm=321863&rd=15851&pm=13065&cr=22916803
   - https://community.topcoder.com/stat?c=problem_solution&rm=321859&rd=15851&pm=13065&cr=22761932
  - DFS
   - https://community.topcoder.com/stat?c=problem_solution&rm=321897&rd=15851&pm=13065&cr=22849803
 
 */

// O(N!) time, O(N!) space
class MovingRooksDiv2 {
public:
  string yes="Possible",no="Impossible";
  string move(vector<int> C1, vector<int> C2) {
    int N=SZ(C1);
    queue<VI> Q;
    set<VI> viz;
    
    Q.emplace(C1); viz.emplace(C1);
    while(SZ(Q)) {
      VI cur=Q.front(); Q.pop();
      REP(i,N) FOR(j,i+1,N) if(cur[i]>cur[j]) {
        swap(cur[i],cur[j]);
        if(!viz.count(cur)) {
          Q.emplace(cur); viz.emplace(cur);
        }
        swap(cur[i],cur[j]);
      }
    }
    return viz.count(C2)?yes:no;
  }
};

// O(N!) time, O(N!) space
map<VI,int> memo;
class MovingRooksDiv2_dfs {
  public:
  string yes="Possible",no="Impossible";
  int N;
  VI C2;
  bool dfs(VI &cur) {
    if(cur==C2) return true;
    if(memo.count(cur)) return memo[cur];
    /*
     int cnt=0;
    REP(i,N) {
      if(cur[i]==C2[i]) ++cnt;
      else if(cur[i]<C2[i]) {
        bool ok=false;
        REP(j,i) if(cur[j]>cur[i]) ok=true;
        if(!ok) return memo[cur]=false;
      } else {
        bool ok=false;
        FOR(j,i+1,N) if(cur[j]<cur[i]) ok=true;
        if(!ok) return memo[cur]=false;
      }
    }
    if(cnt==N) return true;*/
    
    bool res=false;
    REP(i,N) FOR(j,i+1,N) if(cur[i]>cur[j]) {
      swap(cur[i],cur[j]);
      res|=dfs(cur);
      swap(cur[i],cur[j]);
    }
    return memo[cur]=res;
  }
  string move(vector<int> C1, vector<int> C2) {
    this->N=SZ(C1);
    this->C2=C2;
    memo.clear();
    return dfs(C1)?yes:no;
  }
};

// CUT begin
ifstream data("MovingRooksDiv2.sample");

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

bool do_test(vector<int> Y1, vector<int> Y2, string __expected) {
    time_t startClock = clock();
    MovingRooksDiv2 *instance = new MovingRooksDiv2();
    string __result = instance->move(Y1, Y2);
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
        vector<int> Y1;
        from_stream(Y1);
        vector<int> Y2;
        from_stream(Y2);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(Y1, Y2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507410623;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MovingRooksDiv2 (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
