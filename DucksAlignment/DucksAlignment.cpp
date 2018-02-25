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
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/24/2018
 
 10:57-11:01 analysis
 11:02-11:20 1WA
 12:00-12:50 brute-force all the grids and ACC
 
 In one dimension, if we want to find shortest total distance to move, median is optimal.
 I actually tried to brute-force all the positions of duck's original positions to skip complication to find median.
 However system test doesn't pass by this poor algorithm because this is ignoring median of another dimension.
 Look at below test case:
 
 0.................o.....
 1...............o.......
 2..........o............
 3.......................
 4.......................
 5.......................
 6.....................o.
 7.......................
 8.............o.........
 9......................o <- median
 10.......................
 11.......................
 12.......o...............
 13................o......
 14.......................
 15............o..........
 16.......................
 17.......................
 18..................o....
 19.......................
 20...................o...
 21.......................
                   ^ median
 
 I was trying to do something like this:
 
  0.................o.....
  1...............o.......
  2..........o............
  3.......................
  4.......................
  5.......................
  6................*....o.
  7................*......
  8.............o..*......
  9................*.....o <- median
 10................*......
 11................*......
 12.......o........*......
 13................o......
 14................*......
 15............o...*......
 16................*......
 17.......................
 18..................o....
 19.......................
 20...................o...
 21.......................
                   ^ median
 
 Yes this is column-wise median. It's respecting row-wise original order.
 However it's not median in row-wise. Thus this cannot be optimal solution.
 Optimal solution is below. Note that this is row-wise median and column-wise median as well.
 
  0.................o.....
  1...............o.......
  2.........o............
  3.......................
  4................*......
  5................*......
  6................*....o.
  7................*......
  8.............o..*......
  9................*.....o <- median
 10................*......
 11................*......
 12.......o........*......
 13................o......
 14................*......
 15............o..........
 16.......................
 17.......................
 18..................o....
 19.......................
 20...................o...
 21.......................
                   ^ median
 
 23:20-23:36 Add greedy solution with algorithm to gather at (median of row, median of column).
 
 This algorithm passes system test. However total runtime is still O(N^2) to find duck's original position.
 It turns out that brute-forcing all the possible positions shown in editorials is suffient because runtime is still O(N^2).
 This is more handy because it doesn't need knowledge about median property.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+526
  - http://d.hatena.ne.jp/kusano_prog/20111207/1323246959
  - http://mayokoex.hatenablog.com/entry/2015/11/28/100804
  - https://topcoder.g.hatena.ne.jp/jackpersel/20111211/1323581251
  - https://chngng.blogspot.com/2013/10/srm-526-div1-easy-ducksalignment.html
  - http://kg86.hatenablog.com/entry/20130316/1363456333
  - http://web-officer.hateblo.jp/entry/TopCoder_SRM_526_%E9%81%8E%E5%8E%BB%E5%95%8F
 
 Summary:
  - I shot myself in the foot 😡🔫🔫🔫🔫🔫
  - Knowledge lead me wrong algorithm. Just simple brute-force solves this problem.
  - Be sure that knowledge is really really applicable to the problem. Otherwise I'll shoot myself again 😡🔫🔫🔫🔫🔫🔫🔫🔫🔫🔫
 
 */

class DucksAlignment {
public:
  int minimumTime(vector<string> B) {
    int R=SZ(B),C=SZ(B[0]);
    VI X,Y;
    REP(i,R) REP(j,C) if(B[i][j]=='o') {
      X.push_back(i),Y.push_back(j);
    }
    int N=SZ(X);
    sort(X.begin(),X.end());
    sort(Y.begin(),Y.end());
    
    int ci=X[N/2],cj=Y[N/2];
    int si=ci-N/2;
    int res=0;
    REP(i,N) res+=abs(si+i-X[i])+abs(cj-Y[i]);
    return res;
  }
};

class DucksAlignment_bruteforce {
public:
  int minimumTime(vector<string> B) {
    int R=SZ(B),C=SZ(B[0]);
    int res=1e5;
    VI X,Y;
    REP(i,R) REP(j,C) if(B[i][j]=='o') {
      X.push_back(i);
      Y.push_back(j);
    }
    int N=SZ(X);
    sort(X.begin(),X.end());
    sort(Y.begin(),Y.end());
    REP(r,R) REP(c,C) if(r<=R-N) {
      int a=0;
      REP(i,N) a+=abs(Y[i]-c)+abs(r+i-X[i]);
      SMIN(res,a);
    }
    REP(r,R) REP(c,C) if(c<=C-N) {
      int a=0;
      REP(i,N) a+=abs(r-X[i])+abs(c+i-Y[i]);
      SMIN(res,a);
    }
    
    return res;
  }
};

/*
// wrong algorithm
class DucksAlignment_org {
  public:
  int minimumTime(vector<string> B) {
    int R=SZ(B),C=SZ(B[0]);
    int res=1e5;
    vector<II> R1,C1,P;
    int N=0;
    
    int x=0;
    REP(i,R) REP(j,C) if(B[i][j]=='o') {
      dump3(i,j,abs(10-i)); x+=abs(10-i);
      R1.emplace_back(i,N);
      C1.emplace_back(j,N);
      P.emplace_back(i,j);
      ++N;
    }
    dump(x);
    
    sort(R1.begin(),R1.end());
    sort(C1.begin(),C1.end());
    VI rrank(N),crank(N);
    REP(i,N) rrank[R1[i].second]=i;
    REP(i,N) crank[C1[i].second]=i;

    REP(i,N) {
      int r=P[i].first,c=P[i].second;
      // r, oooo
      int x=0,y=0;
      REP(j,N) if(i!=j) {
        x+=abs(P[j].first-r);
        int d=crank[i]-crank[j];
        x+=abs(P[j].second-c)-abs(d);
      }
      // c
      REP(j,N) if(i!=j) {
        y+=abs(P[j].second-c);
        int d=rrank[i]-rrank[j];
        y+=abs(P[j].first-r)-abs(d);
        
        if(i==7) {
          dump3(j,P[j].first,P[j].second);
          dump3(abs(P[j].second-c),d,abs(P[j].first-r)-abs(d));
        }
      }
      dump3(i,r,c);
      dump3(res,x,y);
      res=min({res,x,y});
    }
    
    return res;
  }
};*/

// CUT begin
ifstream data("DucksAlignment.sample");

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

bool do_test(vector<string> grid, int __expected) {
    time_t startClock = clock();
    DucksAlignment *instance = new DucksAlignment();
    int __result = instance->minimumTime(grid);
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
        vector<string> grid;
        from_stream(grid);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519498604;
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
        cout << "DucksAlignment (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
