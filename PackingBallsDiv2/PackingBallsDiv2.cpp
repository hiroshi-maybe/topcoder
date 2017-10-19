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
 
 10/18/2017
 
 8:31-8:46 system test passed (389.07 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+609
  - http://emkcsharp.hatenablog.com/entry/SRM609/PackingBallsDiv2
 
 18:35-18:49 add two more solutions
 
 summary:
  - I wondered if there is greedy solution though, did DP for safety
 
 submit solutions:
  - O(1) greedy:
   - https://community.topcoder.com/stat?c=problem_solution&rm=320698&rd=15842&pm=12995&cr=22718397
   - https://community.topcoder.com/stat?c=problem_solution&rm=320683&rd=15842&pm=12995&cr=22910860
  - O(N) geedy
   - https://community.topcoder.com/stat?c=problem_solution&rm=320688&rd=15842&pm=12995&cr=23281422
  - DP
   - https://community.topcoder.com/stat?c=problem_solution&rm=320721&rd=15842&pm=12995&cr=23027795
 
 */

// same as official editorial
// try possible number of variety sets, O(max(R,G,B)) time
class PackingBallsDiv2 {
public:
  const int Inf=1000;
  int minPacks(int r, int g, int b) {
    // number of variety sets is in range [0,max(r,g,b)]
    int res=Inf;
    for(int x=0; x<=max({r,g,b}); ++x) {
      int pr=(max(r-x,0)+2)/3;
      int pg=(max(g-x,0)+2)/3;
      int pb=(max(b-x,0)+2)/3;
      res=min(res,x+pr+pg+pb);
    }
    
    return res;
  }
};

// greedy (no proof)
class PackingBallsDiv2_greedy {
public:
  const int Inf=1000;
  int minPacks(int r, int g, int b) {
    int res=min({r,g,b});
    r-=res,g-=res,b-=res;
    
    if(g<b) swap(g,b);
    if(r<g) swap(r,g);
    if(g<b) swap(g,b);

    int xx=Inf;
    for(int x=0; x<=g; ++x) {
      int d=x+(r-x+2)/3+(g-x+2)/3;
      xx=min(xx,d);
    }
    
    return res+xx;
  }
};

// O(N^3) time
int memo[101][101][101];
class PackingBallsDiv2_dp {
  public:
  const int Inf=1000;
  int f(int r, int g, int b) {
    
    // minor optimization. system test passes without this.
    if(g<b) swap(g,b);
    if(r<g) swap(r,g);
    if(g<b) swap(g,b);
    assert(r>=g&&g>=b);

    if(r<=0&&g<=0&&b<=0) return 0;
    if(memo[r][g][b]>=0) return memo[r][g][b];
    
    int res=Inf;
    res=min(res,1+f(max(r-1,0),max(g-1,0),max(b-1,0)));
    if(r>3)res=min(res,1+f(r-3,g,b));
    if(g>3)res=min(res,1+f(r,g-3,b));
    if(b>3)res=min(res,1+f(r,g,b-3));
    
    return memo[r][g][b]=res;
  }
  int minPacks(int R, int G, int B) {
    MINUS(memo);
    return f(R,G,B);
  }
};

// CUT begin
ifstream data("PackingBallsDiv2.sample");

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

bool do_test(int R, int G, int B, int __expected) {
    time_t startClock = clock();
    PackingBallsDiv2 *instance = new PackingBallsDiv2();
    int __result = instance->minPacks(R, G, B);
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
        int R;
        from_stream(R);
        int G;
        from_stream(G);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(R, G, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508340688;
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
        cout << "PackingBallsDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
