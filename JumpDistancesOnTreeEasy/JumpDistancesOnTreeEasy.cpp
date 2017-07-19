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
using namespace std;

// type alias
typedef unsigned long UL;
typedef long long LL;

typedef vector < bool > VB;
typedef vector < int > VI;
typedef vector < string > VS;
typedef vector < vector < int > > VVI;
typedef unordered_map < int, int > MAPII;
typedef unordered_map < string, int > MAPSI;
typedef unordered_set < int > SETI;
typedef unordered_set < string > SETS;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

// vector
#define PUSH(s, e) (s).push_back(e)
#define POP(s) (s).pop_back()
#define REVERSE(c) reverse((c).begin(),(c).end())
#define SORT(c) sort((c).begin(),(c).end())
#define CONCAT(a,b) (a).insert((a).begin(), (b).begin(),(b).end())
#define ERASE(arr,i) (arr).erase((arr).begin()+i)

// pair/tuple
typedef pair< int , int > II;
typedef vector<II> VII;
#define MP make_pair
#define _1 first
#define _2 second
typedef tuple< int , int, int > III;
#define MT make_tuple

// matrix
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };

// priority queue
#define MAX_PQ(T) priority_queue<T>
#define MIN_PQ(T) priority_queue<T,vector<T>,greater<T>>

// binary search
#define LB(a,n,k) lower_bound(a,a+(n),(k))
#define UB(a,n,k) upper_bound(a,a+(n),(k))

// dp
#define DP(dp,i,j) int dp[i][j]
#define FILL(dp,x) memset(dp, x, sizeof(dp))
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

vector<vector<int>> floydWarshall(vector<vector<int>> W) {
  if (W.empty()) return W;
  int V=W.size();
  
  for(int k=0; k<V; ++k) {
    for(int i=0; i<V; ++i) {
      for(int j=0; j<V; ++j) {
        if (W[i][k]==INT_MAX || W[k][j]==INT_MAX) continue;
        W[i][j] = min(W[i][j], W[i][k]+W[k][j]);
      }
    }
  }
  
  return W;
}

/**
 
 6/26/2017 SRM 716
 
 19:05-20:05 passed system test after contest ended
 
 7/18/2017
 
 read editorials
 - http://kmjp.hatenablog.jp/entry/2017/06/29/0930
 - https://www.topcoder.com/blog/single-round-match-716-editorials/
 
 22:30-23:00 Add solution withotu floyd-warshal inspired by http://kmjp.hatenablog.jp/entry/2017/06/29/0930
 - BFS by distance in S. Iterate possible distances after search.
 
 */

VI E[52];
unordered_map<int,VI> dist[52];
int D[52][52];

// O(N^2) time
class JumpDistancesOnTreeEasy {
public:
  void dfs(int u, int pre, int from, int d) {
    dist[from][d].push_back(u);
    D[from][u]=d;
    FORR(v,E[u]) if(v!=pre) dfs(v,u,from,d+1);
  }
  string isPossible(vector<int> p, vector<int> S) {
    int N = SZ(p)+1;
    REP(i,51) E[i].clear();
    REP(i,51) dist[i].clear();
    REP(i,SZ(p)) E[i+1].push_back(p[i]), E[p[i]].push_back(i+1);
    REP(i,N) dfs(i,-1,i,0);
    
    int visited[51]={}; visited[0]=true;
    queue<int> Q; Q.push(0);
    while(SZ(Q)) {
      int u=Q.front(); Q.pop();
      
      FORR(d,S) FORR(v,dist[u][d]) if(!visited[v]) {
        Q.push(v);
        visited[v]=true;
      }
    }
    
    SETI T(S.begin(),S.end());
    REP(u,N+1) REP(v,N+1) if(visited[u]&&visited[v]) T.erase(D[u][v]);

    return T.empty() ? "Possible" : "Impossible";
  }
};

// O(N^3) time
class JumpDistancesOnTreeEasy_org {
  public:
  string isPossible(vector<int> p, vector<int> _S) {
    int N = SZ(p);
    VVI W(N+1, VI(N+1, INT_MAX));
    W[0][0] = 0;
    REP(i,N) {
      W[i+1][i+1] = 0;
      W[i+1][p[i]] = W[p[i]][i+1] = 1;
    }
    VVI ds = floydWarshall(W);
    
    SETI S(_S.begin(), _S.end());
    SETI visited; // visited "edge"
    SETI marked;
    queue<int> Q;
    Q.push(0);
    while(Q.size()) {
      int cur = Q.front(); Q.pop();
      REP(i, N+1) {
        if (S.count(ds[cur][i])&&!visited.count(cur+(N+1)*i)) {
          Q.push(i);
          visited.insert(cur+(N+1)*i);
          marked.insert(ds[cur][i]);
        }
      }
    }

    return marked.size()==S.size() ? "Possible" : "Impossible";
  }
};

// CUT begin
ifstream data("JumpDistancesOnTreeEasy.sample");

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

bool do_test(vector<int> p, vector<int> S, string __expected) {
    time_t startClock = clock();
    JumpDistancesOnTreeEasy *instance = new JumpDistancesOnTreeEasy();
    string __result = instance->isPossible(p, S);
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
        vector<int> p;
        from_stream(p);
        vector<int> S;
        from_stream(S);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(p, S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498528873;
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
        cout << "JumpDistancesOnTreeEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
