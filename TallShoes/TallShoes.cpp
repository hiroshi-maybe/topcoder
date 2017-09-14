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
 
 9/13/2017
 
 9:31-9:54 hmmm flow?
 18:51-19:02 rough design
 19:03-19:22 start writing code and wondered how to design tie breaker. ok binary search.
 19:23-19:34 only sample 3 failed. ok overflow between int and LL
 19:46 system test passed
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2014/12/19/0930
  - http://torus711.hatenablog.com/entry/20141217/1418830606
  - https://apps.topcoder.com/wiki/display/tc/SRM+642
 
 editorial:
  - more costs enables taller shoes. thus binary search works
  - in every trial of binary search, we can validate it by solving shortest distance problem
 
 summary:
  - I solved by floyd-warshall + binary search though, Dijkstra's algorithm like editorials is more efficient
 
 22:42-23:10 add solution with Dijkstra's algorithm
 
 */

VI mx[51][51];
// O(V^4*lg B) time
class TallShoes_floydwarshall {
public:
  LL B;
  
  int ok(VI hs, int T) {
    LL b=B;
    FORR(h,hs) if(h<T) {
      b-=((LL)T-(LL)h)*((LL)T-(LL)h);
    }
    return b>=0;
  }
  
  int possibleHeight(VI hs) {
    int bad=1e8,good=*min_element(hs.begin(),hs.end());
    while(abs(good-bad)>1) {
      int mid=good+(bad-good)/2;
      if(ok(hs,mid)) good=mid;
      else bad=mid;
    }
    return good;
  }
  
  int maxHeight(int V, vector<int> X, vector<int> Y, vector<int> H, long long B) {
    this->B=B;
    REP(i,V)REP(j,V) mx[i][j].clear();
    
    REP(i,SZ(X)) {
      int u=X[i],v=Y[i],h=H[i];
      mx[u][v].push_back(h),mx[v][u].push_back(h);
    }
    
    REP(k,V)REP(i,V) REP(j,V) if(SZ(mx[i][k])&&SZ(mx[k][j])) {
      VI hs;
      FORR(a,mx[i][k]) hs.push_back(a);
      FORR(a,mx[k][j]) hs.push_back(a);
      
      if(mx[i][j].empty()) {
        mx[i][j] = hs;
      } else if(possibleHeight(mx[i][j])<possibleHeight(hs)) {
        mx[i][j] = hs;
      }
    }
    
    //    dumpAR(mx[0][V-1]);
    return possibleHeight(mx[0][V-1]);
  }
};

vector<II> E[51];
LL cost[51];
// Dijkstra's algorithm, O((V+E)*lg V*lg B) time
class TallShoes {
  public:
  LL B;
  int V;
  const LL Inf=1e16;
  
  bool ok(int H) {
    REP(i,V) cost[i]=Inf;

    set<pair<LL,int>> Q;
    Q.emplace(0,0); cost[0]=0;
    while(SZ(Q)) {
      auto it=Q.begin();
      LL cost1=(*it).first;
      int u=(*it).second;

      Q.erase(it);
      FORR(p,E[u]) {
        int v=p.first, h=p.second;
        LL cost2=h>=H?0:((LL)H-(LL)h)*((LL)H-(LL)h);

        cost2+=cost1;
        if(cost2>=cost[v]) continue;
        auto it2=Q.find(make_pair(cost[v],v));
        if(it2!=Q.end()) Q.erase(it2);
        Q.emplace(cost2,v); cost[v]=cost2;
      }
    }
    return cost[V-1]<=B;
  }
  
  int maxHeight(int V, vector<int> X, vector<int> Y, vector<int> H, long long B) {
    this->V=V;
    this->B=B;
    REP(i,V) E[i].clear();
    REP(i,SZ(X)) {
      int u=X[i],v=Y[i],h=H[i];
      E[u].emplace_back(v,h), E[v].emplace_back(u,h);
    }
    
    int bad=1e8,good=0;
    while(abs(good-bad)>1) {
      int mid=good+(bad-good)/2;
      if(ok(mid)) good=mid;
      else bad=mid;
    }
    
    return good;
  }
};

// CUT begin
ifstream data("TallShoes.sample");

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

bool do_test(int N, vector<int> X, vector<int> Y, vector<int> height, long long B, int __expected) {
    time_t startClock = clock();
    TallShoes *instance = new TallShoes();
    int __result = instance->maxHeight(N, X, Y, height, B);
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
        vector<int> X;
        from_stream(X);
        vector<int> Y;
        from_stream(Y);
        vector<int> height;
        from_stream(height);
        long long B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, X, Y, height, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505320248;
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
        cout << "TallShoes (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
