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

int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}
LL lcm(LL a, LL b) {
  return (a*b) / (LL)gcd(a,b);
}

/**
 
 7/9/2017

 16:01 start
 16:41 go lcm solution not sure TLE though
 17:00 give up
 17:25 union-find tree, huh
 17:35 passed samples and system test

 vertices are connected in graph? -> union-find tree is a good option
 Actually I came up with it though, I was not sure how to figure out edge combination can be obtained in time...
 I should have been back to union-find idea when I figured out linear edge detection.
 Also without visited check, still runtime complexity is o(n^2)
 because...
 T(n) = ∑{n/i,i=1..n} = n*∑{1/i,i=1..n} = n*Θ(log n) = Θ(n*log n)
 https://en.wikipedia.org/wiki/Summation
 https://en.wikipedia.org/wiki/Harmonic_number
 
 */

int uf[1000001];
class GCDGraph {
public:
  int find(int n) {
    if (uf[n]==n) return n;
    else return uf[n]=find(uf[n]);
  }
  void unite(int n1, int n2) {
    int p1=find(n1), p2=find(n2);
    uf[p1]=p2;
  }
  
  string possible(int N, int K, int x, int y) {
    memset(uf,0,sizeof uf);
    REP(i,N+1) uf[i]=i;
    
    VI visited(N+1,0);
    for(int n=K+1; n<=N; ++n) {
      if(visited[n]) continue;
      for(int p=1; p*n<=N; ++p) {
        unite(n,p*n);
        visited[p*n]=1;
      }
    }
    
    return find(x)==find(y) ? "Possible" : "Impossible";
  }
};

class GCDGraph_wrong {
  public:
  string possible(int N, int k, int x, int y) {
    SETI X,Y;
    VI visited(N+1,0);
    for(int n=k+1; n<=x; ++n) {
      if (visited[n]||x%n!=0) continue;
      X.insert(n);
      for(int k=1; n*k<=x; ++k) visited[n*k]=1;
    }
    visited = VI(N+1,0);
    for(int n=k+1; n<=y; ++n) {
      if (visited[n]||y%n!=0) continue;
      Y.insert(n);
      for(int k=1; n*k<=y; ++k) visited[n*k]=1;
    }
    
    FORR(n,X) {
      FORR(m,Y) {
        dump3(n,m,lcm(n,m));
        if(lcm(n,m)<=(LL)N) return "Possible";
      }
    }
    return "Impossible";
  }
};

// CUT begin
ifstream data("GCDGraph.sample");

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

bool do_test(int n, int k, int x, int y, string __expected) {
    time_t startClock = clock();
    GCDGraph *instance = new GCDGraph();
    string __result = instance->possible(n, k, x, y);
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
        int k;
        from_stream(k);
        int x;
        from_stream(x);
        int y;
        from_stream(y);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, k, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499641293;
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
        cout << "GCDGraph (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
