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
 
 8/13/2017
 
 9:24-9:52 passed system test (265.40 pt)
 
 15:20-15:30 read editorials
  - http://kmjp.hatenablog.jp/entry/2015/10/11/0930
  - https://apps.topcoder.com/wiki/display/tc/SRM+670
 
 15:34 add O(N^2) time greedy solution
 
 O(N) time solution:
  - https://pastebin.com/ApzH4XUz
 
 16:05 add linear time solution
 
 greedy solution:
  - https://community.topcoder.com/stat?c=problem_solution&rm=327281&rd=16550&pm=14060&cr=40283096
  - https://community.topcoder.com/stat?c=problem_solution&rm=327264&rd=16550&pm=14060&cr=23331178
  - https://community.topcoder.com/stat?c=problem_solution&rm=327283&rd=16550&pm=14060&cr=23181786
 DP solution
  - https://community.topcoder.com/stat?c=problem_solution&rm=327259&rd=16550&pm=14060&cr=40264966
 
 */

int memo[51][110][51];
int offset=55;

class Drbalance {
public:
  int lesscng(string S, int K) {
    int res=0,N=SZ(S);
    VI ns(N+1,0);
    int b=0,tot=0;
    REP(i,SZ(S)) {
      if(S[i]=='+') ++b;
      else --b;
      if(b<0) ++ns[-b],++tot;
    }
    
    for(int i=1; i<=N&&tot>K; i+=2) {
      tot-=ns[i]+ns[i+1];
      ++res;
    }
    
    return res;
  }
};

// O(N^2) time
class Drbalance_greedy {
public:
  int cnt(string s) {
    int b=0,res=0;
    REP(i,SZ(s)) {
      if(s[i]=='+') ++b;
      else --b;
      if(b<0) ++res;
    }
    
    return res;
  }
  int lesscng(string S, int K) {
    int res=0;
    while(cnt(S)>K) {
      REP(i,SZ(S)) if(S[i]=='-') {
        S[i]='+';
        ++res;
        break;
      }
    }
    return res;
  }
};

// DP, O(N^3) time
class Drbalance_dp {
  public:
  int K,N;
  string S;
  int Inf=100;
  
  int f(int i, int bal, int prefs) {
    if(i==N) {
      return prefs<=K ? 0 : Inf;
    }
    if(memo[i][bal+offset][prefs]>=0) return memo[i][bal+offset][prefs];
    
    int res=Inf;
    if(S[i]=='+') {
      // no change
      int bal1=bal+1;
      int prefs1=prefs+(bal1<0);
      res = min(res, f(i+1,bal1,prefs1));
      
      // change
      int bal2=bal-1;
      int prefs2=prefs+(bal2<0);
      res = min(res, f(i+1,bal2,prefs2)+1);
    } else {
      // no change
      int bal1=bal-1;
      int prefs1=prefs+(bal1<0);
      res = min(res, f(i+1,bal1,prefs1));
      
      // change
      int bal2=bal+1;
      int prefs2=prefs+(bal2<0);
      res = min(res, f(i+1,bal2,prefs2)+1);
    }
    
    return memo[i][bal+offset][prefs]=res;
  }
  
  int lesscng(string s, int k) {
    K=k; S=s;
    N=SZ(S);
    MINUS(memo);
    return f(0,0,0);
  }
};

// CUT begin
ifstream data("Drbalance.sample");

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

bool do_test(string s, int k, int __expected) {
    time_t startClock = clock();
    Drbalance *instance = new Drbalance();
    int __result = instance->lesscng(s, k);
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
        string s;
        from_stream(s);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502641435;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Drbalance (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
