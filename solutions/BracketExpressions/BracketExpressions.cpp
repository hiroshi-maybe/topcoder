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
 
 9/27/2017
 
 8:47-10:00 tried to solve by DP and in stuck to detect invalid seq like "([)]"
 18:05-18:12 ok, just brute force X by backtracking and validate by stack. system test passed.
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2014/07/23/1030
  - https://apps.topcoder.com/wiki/display/tc/SRM+628
 
 key:
  - X is at most 5 -> X can be out of 6 characters. We can brute-force it.
  - validate parenthesis sequence by stack.
 
 summary:
  - bracket -> DP without deep analysis. I wasted a lot of time.
 
 */

// O(5^6*N) time
class BracketExpressions {
public:
  const string yes="possible",no="impossible";
  const string bs="(){}[]";
  
  bool solve(string S) {
    unordered_map<char, char> bb={{')','('},{'}','{'},{']','['}};
    stack<char> st;
    FORR(c,S) {
      if(bb.count(c)) {
        if(SZ(st)==0) return false;
        char c2=st.top(); st.pop();
        assert(bb.count(c));
        if(c2!=bb[c]) return false;
      } else {
        st.push(c);
      }
    }
    
    return st.empty();
  }
  
  vector<string> SS;
  void dfs(int i, string &cur) {
    if(i>=SZ(cur)) {
      SS.push_back(cur);
      return;
    }
    if(cur[i]!='X') dfs(i+1,cur);
    else {
      REP(j,SZ(bs)) {
        cur[i]=bs[j];
        dfs(i+1,cur);
        cur[i]='X';
      }
    }
  }

  string ifPossible(string S) {
    dfs(0,S);
    FORR(s,SS) if(solve(s)) return yes;
    return no;
  }
};

// this doesn't work for "([)]"
int b[51][51][3];
int ds[2]={1,-1};
class BracketExpressions_wrong2 {
public:
  const string yes="possible",no="impossible";
  const string bs="(){}[]";
  bool solve(string S) {
    ZERO(b);
    int N=SZ(S);
    
    b[0][0][0]=b[0][0][1]=b[0][0][2]=1;
    REP(i,N) {
      
      int c=bs.find(S[i]);
      assert(c!=string::npos);
      
      int br=c/2;
      bool open=c%2;
      int d=ds[open];
      REP(j,N+1) REP(bi,3) {
        if(br==bi) {
          if(0<=j+d&&j+d<=N&&b[i][j][bi]) b[i+1][j+d][bi]=1;
        } else {
          b[i+1][j][bi]|=b[i][j][bi];
        }
      }
    }
    //    dump3(b[16][0][0],b[16][0][1],b[16][0][2]);
    dump3(b[N][0][0],b[N][0][1],b[N][0][2]);
    return b[N][0][0]==1&&b[N][0][1]==1&&b[N][0][2]==1;
  }
  
  vector<string> SS;
  void dfs(int i, string &cur) {
    if(i>=SZ(cur)) {
      SS.push_back(cur);
      return;
    }
    if(cur[i]!='X') dfs(i+1,cur);
    else {
      REP(j,SZ(bs)) {
        cur[i]=bs[j];
        dfs(i+1,cur);
        cur[i]='X';
      }
    }
  }
  // ([]{()[()]()}[])[{{}}]
  string ifPossible(string S) {
    dfs(0,S);
    //    dumpAR(SS);
    FORR(s,SS) if(solve(s)) return yes;
    return no;
  }
};

class BracketExpressions_wrong1 {
  public:
  const string yes="possible",no="impossible";
  string ifPossible(string S) {
    string bs="(){}[]X";
    ZERO(b);
    int N=SZ(S);
    
    b[0][0][0]=b[0][0][1]=b[0][0][2]=1;
    REP(i,N) {
      
      int c=bs.find(S[i]);
      assert(c!=string::npos);
      
      int br=c/2;
      if(br<3) {
        bool open=c%2;
        int d=ds[open];
        REP(j,N+1) REP(bi,3) {
          if(br==bi) {
            if(0<=j+d&&j+d<=N&&b[i][j][bi]) b[i+1][j+d][bi]=1;
          } else {
            b[i+1][j][bi]|=b[i][j][bi];
          }
        }
      } else {
        // X
        dump(i);
        REP(j,N+1) REP(bi,3) {
          REP(di,2) {
            int d=ds[di];
            if(0<=j+d&&j+d<=N&&b[i][j][bi]) b[i+1][j+d][bi]=1;
          }
          b[i+1][j][bi]=1;
        }
      }
    }
    dump3(b[16][0][0],b[16][0][1],b[16][0][2]);
    dump3(b[N][0][0],b[N][0][1],b[N][0][2]);
    return b[N][0][0]==1&&b[N][0][1]==1&&b[N][0][2]==1?yes:no;
  }
};

// CUT begin
ifstream data("BracketExpressions.sample");

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

bool do_test(string expression, string __expected) {
    time_t startClock = clock();
    BracketExpressions *instance = new BracketExpressions();
    string __result = instance->ifPossible(expression);
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
        string expression;
        from_stream(expression);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(expression, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506527239;
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
        cout << "BracketExpressions (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
