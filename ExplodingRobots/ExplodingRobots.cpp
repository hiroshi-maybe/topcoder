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
typedef pair<int,int> II;

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
 
 8/2/2017
 
 8:26-9:02 passed system test (252.80 pt). shit. poor implementation.
 
 Editorial:
 - https://apps.topcoder.com/wiki/display/tc/SRM+681
  - same approaches
    - https://community.topcoder.com/stat?c=problem_solution&rm=328047&rd=16651&pm=14137&cr=23331847
    - https://community.topcoder.com/stat?c=problem_solution&rm=328058&rd=16651&pm=14137&cr=40058522
 
 - rectangle overlap
  - https://community.topcoder.com/stat?c=problem_solution&rm=328059&rd=16651&pm=14137&cr=21761868
 
 23:09-23:27 read editorial and add simple solution
 
 Key:
 - goal is make both dx and dy 0.
 - robots process the same instructions. that means in each direction, we can choose optimal move in each command greedily.
  - if x1<x2, move robot1 for L command, move robot2 for R command. It's always optimal.
 */

class ExplodingRobots {
public:
  string canExplode(int x1, int y1, int x2, int y2, string S) {
    int x=0,y=0;
    FORR(c,S) {
      if(c=='U'||c=='D') ++y;
      else ++x;
    }
    
    int dx=abs(x1-x2),dy=abs(y1-y2);
    return dx<=x&&dy<=y ? "Explosion" : "Safe";
  }
};

unordered_map<char,II> T={{'U',{0,1}},{'D',{0,-1}},{'L',{-1,0}},{'R',{1,0}}};
int offset = 100;
int A[200][200];
int B[200][200];
class ExplodingRobots_org {
  public:
  void fill(int xl, int xr, int yb, int yt, int C[200][200]) {
//    dump4(xl,xr,yt,yb);
    for(int x=xl; x<=xr; ++x) for(int y=yb; y<=yt; ++y) C[x][y]=true;
  }
  string canExplode(int x1, int y1, int x2, int y2, string S) {
    memset(A,0,sizeof A); memset(B,0,sizeof B);
    x1+=offset, y1+=offset, x2+=offset, y2+=offset;
    int py = count(S.begin(),S.end(),'U');
    int ny = count(S.begin(),S.end(),'D');
    int px = count(S.begin(),S.end(),'R');
    int nx = count(S.begin(),S.end(),'L');

    int x1l=x1-nx,x1r=x1+px,y1b=y1-ny,y1t=y1+py;
    int x2l=x2-nx,x2r=x2+px,y2b=y2-ny,y2t=y2+py;
    
    /*
    dump4(x1l,x1r,y1b,y1t);
    dump4(x2l,x2r,y2b,y2t);
    
    bool xok=false,yok=false;
    if(x1r>=x2l||x2l<=x1r||x2r>=x1l||x1l<=x2r) xok=true;
    if(y1t>=y2b||y2b<=y1t||y2t>=y1b||y1b<=y2t) yok=true;
    
    return xok&&yok ? "Explosion" : "Safe";*/
    
    fill(x1l,x1r,y1b,y1t,A);
    fill(x2l,x2r,y2b,y2t,B);
    
    REP(i,200)REP(j,200) { if(A[i][j]&&B[i][j]) return "Explosion"; }
    return "Safe";
  }
};

// CUT begin
ifstream data("ExplodingRobots.sample");

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

bool do_test(int x1, int y1, int x2, int y2, string instructions, string __expected) {
    time_t startClock = clock();
    ExplodingRobots *instance = new ExplodingRobots();
    string __result = instance->canExplode(x1, y1, x2, y2, instructions);
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
        int x1;
        from_stream(x1);
        int y1;
        from_stream(y1);
        int x2;
        from_stream(x2);
        int y2;
        from_stream(y2);
        string instructions;
        from_stream(instructions);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x1, y1, x2, y2, instructions, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501687552;
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
        cout << "ExplodingRobots (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
