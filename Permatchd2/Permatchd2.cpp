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
 
 7/4/2017
 
 9:24 start
 9:50 start coding
 10:18 passed samples (205 pt) and system test
 
 14:28 read https://community.topcoder.com/stat?c=problem_solution&rd=16853&rm=329755&cr=23309657&pm=14539
 15:16 add union-find tree solution
 */
class Permatchd2 {
public:
  int uf[50]; int es[50]; int vs[50];
  int find(int x) { return x==uf[x] ? x : uf[x]=find(uf[x]); }
  void unite(int x, int y) { uf[y]=x; }
  int fix(vector<string> G) {
    int N = SZ(G);
    memset(es, 0, sizeof(es));
    REP(i,N) { uf[i]=i; vs[i]=1; }
    
    REP(v,N) REP(u,v) if(G[u][v]=='Y') {
      int p = find(u), q=find(v);
      if (p!=q) {
        unite(p,q);
        es[p]+=es[q]+1;
        vs[p]+=vs[q];
      } else ++es[p];
    }
    
    vector<pair<int,int>> comps;
    REP(u,N) if(find(u)==u) comps.emplace_back(es[u], vs[u]);
    if (comps.size()==1&&(comps[0].first&1)&&comps[0].second*(comps[0].second-1)==2*comps[0].first) return -1;
    int res=0;
    FORR(c,comps) if(c.first&1) ++res;
    return res;
  }
};

int visited[51];
class Permatchd2_org {
  public:
  vector<string> G;
  int VN;
  VI vs;
  void dfs(int cur) {
    if (visited[cur]) return;
    visited[cur]=1;
    vs.push_back(cur);
    REP(i,VN) {
      if(G[cur][i]!='Y') continue;
      if(visited[i]) continue;
      dfs(i);
    }
  }
  
  int fix(vector<string> graph) {
    G = graph; VN = SZ(graph);
    memset(visited, 0, sizeof(visited));
    
    vector<pair<int,int>> comps;
    REP(i,VN) {
      if (visited[i]) continue;
      vs.clear();
      dfs(i);
      
      int es=0;
      for(auto n: vs) {
        for(auto &c : G[n]) if(c=='Y') ++es;
      }
      comps.emplace_back(vs.size(), es/2);
    }
    
//    FORR(p,comps) dump2(p.first,p.second);
    
    int es=0, os=0, res=0;
    FORR(c,comps) {
      if (c.second%2==0) { ++es; continue; }
      if (c.second<(c.first*(c.first-1)/2)) {
        ++res; ++es;
      } else {
        ++os;
      }
    }
//    dump3(es,os,res);
    if (es>0) return res+os;
    if (os==1) return -1;
    return os;
  }
};

// CUT begin
ifstream data("Permatchd2.sample");

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

bool do_test(vector<string> graph, int __expected) {
    time_t startClock = clock();
    Permatchd2 *instance = new Permatchd2();
    int __result = instance->fix(graph);
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
        vector<string> graph;
        from_stream(graph);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(graph, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499185439;
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
        cout << "Permatchd2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
