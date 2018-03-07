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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/6/2018
 
 10:42-11:07 analysis
 11:08-11:29 implement and ACC (442.81 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+516
  - http://kmjp.hatenablog.jp/entry/2014/01/16/0930
  - http://d.hatena.ne.jp/kusano_prog/20110901/1314910280
  - http://techtipshoge.blogspot.com/2011/08/
  - https://topcoder.g.hatena.ne.jp/firewood/20110928/1317217318
 
 23:30-23:45 add simpler solution inspired by @kmjp
 
 Key:
  - Constraint "character in original message is unique"
   => no loop of dependency
   => topological sort
 
 Summary:
  - It took some time to justify approach of topological sort though, solved by myself 👍
  - Slow implementation 👎
 
 */

class NetworkXMessageRecovery {
public:
  string recover(vector<string> M) {
    bool E[128][128];
    bool V[128];
    int IND[128];
    ZERO(E); ZERO(V); ZERO(IND);
    
    int N=SZ(M);
    REP(i,N)REP(j,SZ(M[i])) V[(int)M[i][j]]=1;
    REP(i,N) REP(j,SZ(M[i])-1) E[(int)M[i][j]][(int)M[i][j+1]]=1;
    REP(u,128)REP(v,128) IND[v]+=E[u][v];

    string res="";
    while(1) {
      const char Inf='{';
      char c=Inf;
      for(c='A'; c<='z'; ++c) if(V[(int)c]&&IND[(int)c]==0) break;
      if(c==Inf) break;
      V[(int)c]=0;
      res+=c;
      REP(v,128) if(E[(int)c][(int)v]) --IND[v];
    }
    
    return res;
  }
};

vector<char> M[128];
unordered_map<char,int> IND;
class NetworkXMessageRecovery_org {
  public:
  string recover(vector<string> MM) {
    REP(i,128) M[i].clear();
    IND.clear();
    REP(i,SZ(MM)) {
      if(IND.count(MM[i].front())==0) IND[MM[i].front()]=0;
      REP(j,SZ(MM[i])-1) {
        char u=MM[i][j],v=MM[i][j+1];
        M[(int)u].push_back(v);
        ++IND[v];
        dump2(u,IND[u]);
      }
    }
    set<pair<int, char>> Q;
    FORR(kvp,IND) {
//      dump2(kvp.first,kvp.second);
      Q.emplace(kvp.second,kvp.first);
    }
    dump(SZ(Q));
    string res="";
    while(SZ(Q)) {
      auto it=Q.begin();
      int cnt=it->first; char u=it->second;
      dump3(res,cnt,u);
      Q.erase(it);
      assert(cnt==0);
      res+=u;
      FORR(v,M[u]) {
        int cnt2=IND[v];
        auto it=Q.find({cnt2,v});
        Q.erase(it);
        IND[v]--;
        Q.emplace(IND[v],v);
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("NetworkXMessageRecovery.sample");

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

bool do_test(vector<string> messages, string __expected) {
    time_t startClock = clock();
    NetworkXMessageRecovery *instance = new NetworkXMessageRecovery();
    string __result = instance->recover(messages);
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
        vector<string> messages;
        from_stream(messages);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(messages, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520361734;
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
        cout << "NetworkXMessageRecovery (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
