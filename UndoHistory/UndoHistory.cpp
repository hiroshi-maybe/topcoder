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
 
 12/2/2017
 
 16:20-16:59 1WA due to analysis mistake (269.88 pt)
 17:54-18:09 1WA by implementation bug. System test passed.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+579#UndoHistory
   - simply iterate previous lines to search prefix from undo history
   - by this approach, keeping buffer is a special case of undo history
  - http://emkcsharp.hatenablog.com/entry/SRM579/UndoHistory
  - http://kmjp.hatenablog.jp/entry/2013/05/19/0900
 
 Summary:
  - 1WA for test case "absolutely","abs","absolute"
   - in line 3, restoring from undo history is optimal than keeping buffer 👎
  - Another WA due to implementation bug in above fix
 
 */

class UndoHistory {
public:
  int prematch(string p, string s) {
    int N=min(SZ(p),SZ(s));
    REP(i,N) if(p[i]!=s[i]) return i;
    return N;
  }
  int minPresses(vector<string> L) {
    int N=SZ(L);
    int res=SZ(L[0])+1;
    const int Inf=1e4;
    
    FOR(i,1,N) {
      string s=L[i];
      
      int x=Inf;
      REP(j,i) {
        int y=SZ(s)+2; // clear buffer and type all
        int match=prematch(L[j],s);
        y-=match;
        if(j==i-1&&match==SZ(L[j])) y-=2;
        x=min(x,y);
      }
      res+=x+1;
    }
    return res;
  }
};

// O(N^2) time
class UndoHistory_org {
  public:
  unordered_set<string> S={""};
  int f(string buf, string s, unordered_set<string> &S) {
    int res=0;
    FOR(i,SZ(buf),SZ(s)) {
      ++res; // type
      buf+=s[i];
      S.emplace(buf);
    }
    return res;
  }
  int minPresses(vector<string> L) {
    int N=SZ(L);
    int res=0;
    string buf="";
    REP(i,N) {
      string s=L[i];
      buf="";
      int cnt1=1000;
      unordered_set<string> S1;
      if(i>0) {
        string prev=L[i-1];
        if(SZ(prev)<=SZ(s)&&s.substr(0,SZ(prev))==prev) {
          buf=prev;
          cnt1=f(buf,s,S1);
        }
      }
      
      unordered_set<string> S2;
      int cnt2=0;
      if(i>0) {
        cnt2+=2; // click x2
        string t=s;
        while(S.count(t)==0) t.pop_back();
        buf=t;
      }
      cnt2+=f(buf,s,S2);
      if(cnt1<cnt2) {
        FORR(t,S1) S.emplace(t);
      } else {
        FORR(t,S2) S.emplace(t);
      }
      res+=min(cnt1,cnt2);
      ++res; // enter
    }
    return res;
  }
};

// CUT begin
ifstream data("UndoHistory.sample");

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

bool do_test(vector<string> lines, int __expected) {
    time_t startClock = clock();
    UndoHistory *instance = new UndoHistory();
    int __result = instance->minPresses(lines);
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
        vector<string> lines;
        from_stream(lines);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(lines, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512260410;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "UndoHistory (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
