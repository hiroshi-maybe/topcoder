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
 
 12/3/2017
 
 15:48-16:36 give up
 
 12/4/2017
 
 17:30-17:55 by reading editorial, I figured out that I was misunderstanding problem.
 
 I should have read sample 2 more carefully...
 goose relation is transitive...
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+578
  - http://emkcsharp.hatenablog.com/entry/SRM578/GooseInZooDivTwo
   - Union-find, O(N^2*α(n)) time
 
 Key:
  - If x is goose, any bird y within distance D is goose. If y is goose, any bird z within D is ALSO goose
   - Binary relation to be goose is transitive
  - Once we find independent groups, just 2^C-1 is the answer
 
 Summary:
  - I completely misunderstood problem 👎
    - Somehow I thought that relation of goose is NOT transitive
    - I was trying to contract cycle...
    - I should have figured out problem correctly by looking at sample 2
  - Read sample carefully if problem seems to be too hard
  - DFS implementaion in editorial is cool. I would have implemented by BFS. Union find is also nice.
 
 clean BFS: https://community.topcoder.com/stat?c=problem_solution&rm=317290&rd=15498&pm=12545&cr=23155968
 clean DFS: https://community.topcoder.com/stat?c=problem_solution&rm=317294&rd=15498&pm=12545&cr=22681902
 
 */
constexpr int MOD = 1e9+7;
int viz[50][50];
class GooseInZooDivTwo {
  public:
  vector<string> G;
  int D;
  int R,C;
  void dfs(int i, int j) {
    viz[i][j]=true;
    REP(ii,R)REP(jj,C) if(G[ii][jj]=='v'&&!viz[ii][jj]) {
      if(abs(i-ii)+abs(j-jj)<=D) {
        dfs(ii,jj);
      }
    }
  }
  
  int count(vector<string> G, int D) {
    ZERO(viz);
    this->G=G, this->D=D;
    this->R=SZ(G),this->C=SZ(G[0]);
    int cnt=0;
    REP(i,R)REP(j,C) if(G[i][j]=='v'&&!viz[i][j]) {
      dfs(i,j);
      ++cnt;
    }
//    dump(cnt);
    LL res=1;
    REP(i,cnt) res*=2LL,res%=MOD;
    
    return (res+MOD-1)%MOD;
  }
};

// CUT begin
ifstream data("GooseInZooDivTwo.sample");

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

bool do_test(vector<string> field, int dist, int __expected) {
    time_t startClock = clock();
    GooseInZooDivTwo *instance = new GooseInZooDivTwo();
    int __result = instance->count(field, dist);
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
        vector<string> field;
        from_stream(field);
        int dist;
        from_stream(dist);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, dist, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512344923;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "GooseInZooDivTwo (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
