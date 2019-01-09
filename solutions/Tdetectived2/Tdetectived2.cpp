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
 
 9:29-10:20, 11:00-11:45 tried Dijkstra's algorithm
 18:30-19:10 tried to store states of suspicious level though, hit TLE in system test
 
 19:20-19:30 read editorial
 - http://kmjp.hatenablog.jp/entry/2015/10/21/0930
 - https://apps.topcoder.com/wiki/display/tc/SRM+672
 
 19:30-19:48 add bit DP solution
 
 Key:
  - distance = number of visited
  - easy to differentiate states just by counting who's been visited
  - each person is visited only once
  - N is small. Bit DP works
 
 Summary:
  - Dijkstra's algorithm, huh?
    - In this case, no optomality property like a Dijkstra's algorithm
    - If suspicion lv is tied, need to follow up multiple search paths
  - This was easier than other div2 hard problem. Should have solved.
    - once figured out bit dp approach, it's straightforward
  - If in stuck, try different approach. Don't stick to the initial approach

 */

int ok[1<<18];
int dist[18];
class Tdetectived2 {
public:
  int dist[20];
  int Inf=1e9;
  int reveal(vector<string> S) {
    int N=SZ(S);
    ZERO(ok);
    REP(i,N) dist[i]=100;
    
    ok[1] = true;
    REP(mask,1<<N) if(ok[mask]) {
      VI X(N,0);
      REP(i,N) if(mask&(1<<i)) REP(j,N) if((mask&(1<<j))==0) {
        X[j]=max(X[j],S[i][j]-'0');
      }
      int maxn=*max_element(X.begin(),X.end());
      int d=__builtin_popcount(mask);
      REP(i,N) if((mask&(1<<i))==0&&X[i]==maxn) {
        dist[i]=min(dist[i],d);
        ok[mask|(1<<i)]=1;
      }
    }
    
    int res=0;
    REP(i,N) res+=i*dist[i];
    return res;
  }
};

class Tdetectived2_tle {
public:
  int dist[20];
  int Inf=1e9;
  int reveal(vector<string> S) {
    int V=SZ(S);
    ZERO(dist);
    queue<pair<int,VI>> Q;
    VI X(V); X[0]=-1; dist[0]=0;
    FOR(i,1,V) {
      X[i]=S[0][i]-'0';
      dist[i]=Inf;
    }
//    dumpAR(X);
    Q.emplace(1,X);
    
    while(SZ(Q)) {
      auto p=Q.front(); Q.pop();
      int d=p.first;
      VI X=p.second;
      int maxn=*max_element(X.begin(),X.end());
      if (maxn==-1) continue;
      
      dumpAR(X);
      dump3(maxn,d,SZ(Q));
      
//      dump3(u,d,cost);
      REP(u,V) if(X[u]==maxn) {
        VI Y=X;
        dist[u]=min(dist[u],d);
        Y[u]=-1;
        REP(v,V) if(Y[v]!=-1) Y[v]=max(Y[v],S[u][v]-'0');
        Q.emplace(d+1,Y);
      }
    }
    
    int res=0;
    FOR(i,1,V) res+=i*dist[i];
    
    return res;
  }
};

/*
class Tdetectived2 {
  public:
  int reveal(vector<string> S) {
    int V=SZ(S);
    ZERO(W); ZERO(viz); ZERO(dist);
    dist[0]=0; viz[0]=1;
    
    set<III> Q;
    REP(u,V) Q.emplace(S[0][u]-'0',u);
    
    int d=0;
    while(SZ(Q)) {
      int cost,u;
      tie(cost,u) = Q.top(); Q.pop();
      if(viz[u]) continue;
      if(cost<W[u]) continue;
      dump3(u,cost,W[u]);
      viz[u]=true;
      W[u]=cost;
      ++d;
      dist[u]=d;
      REP(v,V) if(u!=v&&!viz[v]) {
        int cost2=S[u][v]-'0';
//        if (cost2>W[v]) Q.emplace(cost2,mind-1,v);
        Q.emplace(cost2,v);
        dump3(u,v,cost2);
      }
    }
    
    int res=0;
    FOR(i,1,V) res+=i*dist[i];
    
    return res;
  }
};
*/

// CUT begin
ifstream data("Tdetectived2.sample");

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

bool do_test(vector<string> s, int __expected) {
    time_t startClock = clock();
    Tdetectived2 *instance = new Tdetectived2();
    int __result = instance->reveal(s);
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
        vector<string> s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502468974;
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
        cout << "Tdetectived2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
