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

// mod
constexpr int MOD = 1e9+7;

/**
 
 7/19/2017
 
 9:48-10:40 puase
 12:00-13:00 cannot pass some samples. give up
 
 22:16 read editorials..
 
 Pin edge vertices
 - http://kmjp.hatenablog.jp/entry/2016/08/01/1000
 
 Pin center vertices
 - http://pekempey.hatenablog.com/entry/2016/07/21/045546
 
 23:53 any editorial solutions don't pass system test case #9 or #10. test case is wrong? :(
 
 */

class BearUniqueDiameter {
public:
  int V;
  VI E[301];
  int dist[301][301];
  int dfs(int u, int pre, int rem, int I, int J) {
    if(rem<=0) return 1;
    
    LL res=1;
    int onpath = dist[I][u]+dist[u][J]<=dist[I][J];
    FORR(v,E[u]) if(v!=pre) res *= dfs(v,u,rem-1,I,J), res%=MOD;
    return res+!onpath;
  }
  
  int countSubtrees(vector<int> a, vector<int> b) {
    V=SZ(a)+1;
    REP(u,V) REP(v,V) dist[u][v] = u==v?0:2*V;
    REP(i,SZ(a)) dist[a[i]][b[i]]=dist[b[i]][a[i]]=1;
    REP(k,V)REP(i,V)REP(j,V) dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
    REP(i,V) E[i].clear();
    REP(i,SZ(a)) E[a[i]].push_back(b[i]), E[b[i]].push_back(a[i]);
    
    LL res = V;
    REP(j,V)REP(i,j) {
      int dia = dist[i][j];
      
      int c1=-1,c2=-1;
      REP(k,V) {
        if(dia%2==0&&dist[i][k]==dia/2&&dist[k][j]==dia/2) c1=k,c2=-1;
        if(dia%2==1&&dist[i][k]==dia/2&&dist[k][j]==dia/2+1) c1=k;
        if(dia%2==1&&dist[i][k]==dia/2+1&&dist[k][j]==dia/2) c2=k;
      }
      
      if(c2==-1) res+=dfs(c1,-1,dia/2,i,j), res%=MOD;
      else res+=dfs(c1,c2,(dia-1)/2,i,j)*dfs(c2,c1,(dia-1)/2,i,j), res%=MOD;
    }
    
    return res;
  }
};

class BearUniqueDiameter_wrong {
  public:
  VI E[602];
  int cnt[602];
  LL sum1[602];
  LL sum2[602];
  int V;
  
  void dfs(int u, int pre, int d) {
    assert(d<=2*V);
//    dump3(pre,u,d);
    if(u<V) ++cnt[d];
    FORR(v,E[u]) if(v!=pre) dfs(v,u,d+1);
  }
  
  int countSubtrees(vector<int> a, vector<int> b) {
    V=SZ(a)+1;
    REP(i,2*V) E[i].clear();
    REP(i,SZ(a)) {
      E[a[i]].push_back(i+V+1); E[i+V+1].push_back(a[i]);
      E[b[i]].push_back(i+V+1); E[i+V+1].push_back(b[i]);
      dump4(i,a[i],i+V+1,b[i]);
    }

    LL res=0;
    REP(u,2*V) {
      memset(sum1, 0, sizeof sum1);
      memset(sum2, 0, sizeof sum2);
//      dump(u);
      FORR(v, E[u]) {
//        dump2(u,v);
        memset(cnt, 0, sizeof cnt);
        dfs(v,u,1);
        
        REP(d,2*V) {
          sum1[d]+=(LL)cnt[d], sum2[d]+=(LL)cnt[d]*(LL)cnt[d], sum2[d]%=MOD;
        }
      }

      REP(d,2*V) {
        dump3(u,d,sum1[d]);
        res+=(sum1[d]*sum1[d]-sum2[d])/2, res%=MOD;
        dump(res);
      }
      if(u<V) ++res;
      dump(res);
    }
    
    return res%MOD;
  }
};

// CUT begin
ifstream data("BearUniqueDiameter.sample");

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

bool do_test(vector<int> a, vector<int> b, int __expected) {
    time_t startClock = clock();
    BearUniqueDiameter *instance = new BearUniqueDiameter();
    int __result = instance->countSubtrees(a, b);
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
        if ( do_test(a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500482890;
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
        cout << "BearUniqueDiameter (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
