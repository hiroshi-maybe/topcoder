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
 
 11/15/2017
 
 9:50-10:47 analysis (ok, bipartite mathching, 3-coloring problem is NP-complete...)
 10:47-11:15 implement and system test passed
 
 Generally 3-coloring problem is NP-hard. So no polynomial algorithm is known.
 We can look for solution which is specific to special conditions of this problem.
 
 In N cell as below, we assign c0=R. Now what c1 and c2 should be?
 
 c0  c1
  ---
 |\  |
 | \ |
 |  \|
  ---
 c2  c3
 
 If c1=G and c2=B, then c3 cannot be colored. Thus c1 and c2 needs to be same color.
 It's same for Z cell as well because of symmetry property.
 I assigned colors from left-top to right-bottom without violating condition.
 If it's impossible, "No" is returned.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+587
  - http://kmjp.hatenablog.jp/entry/2013/08/03/1000
  - https://kano.arkoak.com/2013/08/02/topcoder/
  - http://emkcsharp.hatenablog.com/entry/SRM587/ThreeColorabilityEasy
 
 Reference:
  - Graph coloring https://en.wikipedia.org/wiki/Graph_coloring
  - 3-coloring is NP-Complete https://cgi.csc.liv.ac.uk/~igor/COMP309/3CP.pdf
 
 Summary:
  - I went back and forth to find solution for k-coloring graph problem and adhoc solution to this special problem
  - It turned out that 3-coloring problem is actually NP-hard.
  - I proved that color can be fixed one by one
  - It took some time to write code to assign colors and detect wrong coloring though, got ACC
  - I read proof in official editorial though, I thought it would be hard to notice N and Z pattern by myself
 
 */
int C[52][52];
class ThreeColorabilityEasy {
public:
  int H,W;
  string yes="Yes",no="No";
  string isColorable(vector<string> const &B) {
    this->H=SZ(B),this->W=SZ(B[0]);
    
    memset(C,-1,sizeof(C));
    C[0][0]=0;
    REP(i,H) REP(j,W) {
      int &c0=C[i][j],&c1=C[i][j+1],&c2=C[i+1][j],&c3=C[i+1][j+1];
      assert(c0>=0);
      assert((c1==-1&&c2==-1)||(c1>=0&&c2==-1)||(c1==-1&&c2>=0)||(c1>=0&&c2>=0));
      assert(c3==-1);
      if(B[i][j]=='Z') {
        // Z
        c3=c0;
        if(c1==-1&&c2==-1) {
          c1=(c0+1)%3;
          c2=3-c0-c1;
        } else if(c2==-1) {
          assert(c1>=0);
          c2=3-c0-c1;
        } else if(c1==-1) {
          assert(c2>=0);
          c1=3-c0-c2;
        }
        if(c0!=c3) return no;
        if(c0==c1||c1==c2||c1==c3||c2==c3) return no;
      } else {
        // N
        if(c1==-1&&c2==-1) {
          c1=(c0+1)%3;
          c2=c1;
        } else if(c2==-1) {
          assert(c1>=0);
          c2=c1;
        } else if(c1==-1) {
          assert(c2>=0);
          c1=c2;
        }
        c3=3-c0-c1;
        if(c1!=c2) return no;
        if(c0==c1||c0==c2||c0==c3||c1==c3||c2==c3) return no;
      }
    }
    
    return yes;
  }
};

// CUT begin
ifstream data("ThreeColorabilityEasy.sample");

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

bool do_test(vector<string> cells, string __expected) {
    time_t startClock = clock();
    ThreeColorabilityEasy *instance = new ThreeColorabilityEasy();
    string __result = instance->isColorable(cells);
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
        vector<string> cells;
        from_stream(cells);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cells, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510800396;
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
        cout << "ThreeColorabilityEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
