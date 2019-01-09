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
 
 7/14/2017
 
 8:59 start
 9:11 try dijkstra
 9:27 design on-demand edge detection in dijkstra
 9:36 still TLE in sample 5 :(
 9:51 unit distance -> BFS?
 9:56 passed samples (404.97 pt)
 
 21:40-22:23 read editorials
 - https://apps.topcoder.com/wiki/display/tc/SRM+699
 - http://kmjp.hatenablog.jp/entry/2016/09/27/0930
 - http://kenkoooo.hatenablog.com/entry/2016/09/27/022827
 - It took some time to understand that each (a[i],b[i]) pair is taken only once.
   If (a[i],b[i]) is taken twice, some loop should be happening. Thus it cannot be shortest path.
 
 23:00-23:18 add more efficient LCM solution
 
 */

int dist[501];

LL gcd(LL a, LL b) { return b==0 ? a : gcd(b,a%b); }
LL lcm(LL a, LL b) { return a*b/gcd(a,b); }

class FromToDivisibleDiv2 {
public:
  int shortest(int N, int S, int T, vector<int> a, vector<int> b) {
    memset(dist, 0, sizeof dist);
    int M=SZ(a);
    queue<int> Q;
    REP(i,M) if(S%a[i]==0) {
      dist[i]=1;
      Q.emplace(i); // b[i] can be queued instead of i
    }
    
    while(SZ(Q)) {
      int i=Q.front(); Q.pop();
      if(T%b[i]==0) return dist[i];
      
      REP(j,M) {
        if(dist[j]==0&&lcm(b[i],a[j])<=N) {
          dist[j]=dist[i]+1;
          Q.emplace(j);
        }
      }
    }
    
    return -1;
  }
};

// O(M*N) time
class FromToDivisibleDiv2_org {
public:
  int shortest(int V, int S, int T, vector<int> a, vector<int> b) {
    int M=SZ(a);
    vector<int> visited(V+1, false);
    vector<int> res(V+1, INT_MAX);
    queue<int> Q;
    
    res[S] = 0;
    Q.emplace(S);
    visited[S]=true;
    
    while(Q.size()) {
      auto u = Q.front(); Q.pop();
      REP(i,M) {
        if(u%a[i]!=0) continue;
        for(int k=1; k*b[i]<=V; ++k) {
          int v=k*b[i];
          
          if (visited[v]) continue;
          if (res[u]==INT_MAX) continue;
          
          if (v==T) return res[u]+1;
          
          res[v] = res[u]+1;
          Q.emplace(v);
          visited[v]=true;
        }
      }
    }
    
    return res[T]==INT_MAX ? -1 : res[T];
  }
};

/*
class FromToDivisibleDiv2_dijkstra {
  public:
  int shortest(int V, int S, int T, vector<int> a, vector<int> b) {
    int M=SZ(a);
    vector<int> visited(V+1, false);
    vector<int> res(V+1, INT_MAX);
    set<pair<int,int>> Q;
    
    res[S] = 0;
    Q.emplace(0, S);
    
    int x=0;
    while(Q.size()) {
      auto it = *(Q.begin()); Q.erase(it);
      int u = it.second;
      visited[u] = true;
      //dump2(Q.size(),u);
      if (u==T) {
        dump(x);
        return it.first;
      }
      
      REP(i,M) {
        if(u%a[i]!=0) continue;
        for(int k=1; k*b[i]<=V; ++k) {
          int v=k*b[i];
          
          if (visited[v]) continue;
          if (res[u]==INT_MAX) continue;
          ++x;
          
          auto vi=Q.find({res[v], v});
          if (vi!=Q.end()) Q.erase(vi);
          
          res[v] = min(res[v], res[u] + 1);
          Q.emplace(res[v], v);
        }
      }
    }
    
    return res[T]==INT_MAX ? -1 : res[T];
  }
};*/

// CUT begin
ifstream data("FromToDivisibleDiv2.sample");

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

bool do_test(int N, int S, int T, vector<int> a, vector<int> b, int __expected) {
    time_t startClock = clock();
    FromToDivisibleDiv2 *instance = new FromToDivisibleDiv2();
    int __result = instance->shortest(N, S, T, a, b);
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
        int N;
        from_stream(N);
        int S;
        from_stream(S);
        int T;
        from_stream(T);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, S, T, a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500047974;
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
        cout << "FromToDivisibleDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
