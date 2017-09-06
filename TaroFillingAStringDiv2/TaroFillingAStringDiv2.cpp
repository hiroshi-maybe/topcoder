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
 
 9/5/2017
 
 8:58-9:11 solved by DP and system test passed (413.09 pt)
 
 editorial:
  - greedy
    - https://apps.topcoder.com/wiki/display/tc/SRM+650
    - http://roiti46.hatenablog.com/entry/2015/05/19/024744
    - http://kmjp.hatenablog.jp/entry/2015/02/19/0900
  - DP
    - http://torus711.hatenablog.com/entry/20150223/1424710884
 
 4 cases to process `?`
 
 1) A???A->ABABA | ( odd,     same) =>  0
 2) A???B->ABABB | ( odd,different) => +1
 3)  A??A->ABAA  | (even,     same) => +1
 4)  A??B->ABAB  | (even,different) =>  0
 
 22:45-22:56 add greedy solution
 
 Key:
  - DP or greedy

 Summary:
  - quickly solved by DP 👍
  - it would be even better if I had figured out greedy quickly
 
 submit solutions:
  - simulation
   - https://community.topcoder.com/stat?c=problem_solution&rm=325223&rd=16314&pm=13668&cr=22917402
  - dp
   - https://community.topcoder.com/stat?c=problem_solution&rm=325219&rd=16314&pm=13668&cr=40073366
  - greedy
   - https://community.topcoder.com/stat?c=problem_solution&rm=325220&rd=16314&pm=13668&cr=40132288
   - https://community.topcoder.com/stat?c=problem_solution&rm=325229&rd=16314&pm=13668&cr=40084271
 
 */

// inspired by @kmjp's solution
class TaroFillingAStringDiv2 {
public:
  int getNumber(string S) {
    vector<II> ps;
    REP(i,SZ(S)) if(S[i]!='?') ps.emplace_back(i,S[i]-'A');
    
    int res=0;
    REP(i,SZ(ps)-1) {
      auto cur=ps[i],next=ps[i+1];
      int same=cur.second==next.second,
          len=(next.first-cur.first+1)%2;
      res+=same^len;
    }
    return res;
  }
};


class TaroFillingAStringDiv2_greedy {
public:
  int getNumber(string S) {
    int res=0;
    int c=0;
    REP(i,SZ(S)) {
      if(S[i]=='?') {
        ++c;
        continue;
      }
      if(i-c-1>=0) {
        int same=S[i-c-1]==S[i];
        int odd=c%=2;
        res+=same^odd;
      }
      c=0;
    }
    return res;
  }
};

int memo[51][2];
class TaroFillingAStringDiv2_dp {
  public:
  string S;
  int f(int i, int x) {
    if(i>=SZ(S)-1) return 0;
    if(memo[i][x]>=0) return memo[i][x];
    
    if(S[i+1]!='?') {
      return (x==(S[i+1]-'A'))+f(i+1,S[i+1]-'A');
    }
    int a = (x==0) + f(i+1,0);
    int b = (x==1) + f(i+1,1);
    return memo[i][x]=min(a,b);
  }
  int getNumber(string S) {
    this->S=S;
    MINUS(memo);
    if(S[0]=='?') {
      return min(f(0,0),f(0,1));
    }
    return f(0,S[0]-'A');
  }
};

// CUT begin
ifstream data("TaroFillingAStringDiv2.sample");

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

bool do_test(string S, int __expected) {
    time_t startClock = clock();
    TaroFillingAStringDiv2 *instance = new TaroFillingAStringDiv2();
    int __result = instance->getNumber(S);
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
        string S;
        from_stream(S);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504627112;
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
        cout << "TaroFillingAStringDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
