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

vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };

/*
 
 8/28/2017
 
 8:56-9:19 in 10*10 case, naiive floyd-warshall 8.76(sec) -> 4.23(sec) by skipping distinct pair
 9:26 submit (281.74 pt). however found out that it takes 5.962(sec) at topcoder server in custom sample test :(
 9:40 figured out O(1) computation and resubmit (177.10 pt). However (1,1) failed in system test :(
 9:43 fixed bug in corner case and resubmit (150 pt)
 
 editorials:
 - Manhattan distance
  - https://apps.topcoder.com/wiki/display/tc/SRM+659
  - http://kmjp.hatenablog.jp/entry/2015/05/13/0900
 - it turned out floyd-warshall works if we brute-force half by half leveraging symmetric property 😇
  - http://roiti46.hatenablog.com/entry/2015/05/19/015803
 
 Key:
  - floyd-warshall or Dijkstra's algorithm may hit TLE
  - distance between cells can be computed in O(1) by Manhattan distance
  - brute force position of transportation
  - dist(p1,p2) = min(dist(p1,p2), dist(p1,t1)+dist(t2,p2), dist(p1,t2)+dist(t1,p2))
 
 Summary:
  - It took 35(mins) to find out Manhattan distance by O(1) 👎
  - one wrong answer for (1,1) 👎

 25:02-25:10 add simpler manhattan distance solution
 
 O(1) math solution 🏆
  - https://community.topcoder.com/stat?c=problem_solution&rm=326297&rd=16462&pm=13793&cr=22874050
    - res = min(R,c)-1 + (max(R,C)-1)/2
 
 */

const int Inf=1000;

class PublicTransit {
public:
  int C;
  int minimumLongestDistance(int R, int C) {
    this->C=C;
    int res=Inf;
    int V=R*C;

    REP(t1,V)REP(t2,V) {
      int D=0;
      REP(p1,V)REP(p2,V) {
        // faster than *min_element()
        D=max(D,min({dist(p1,p2),dist(p1,t1)+dist(t2,p2),dist(p1,t2)+dist(t1,p2)}));
      }
      
      res=min(res,D);
    }
    
    return res;
  }
  int dist(int p1, int p2) {
    int p1r=p1/C,p1c=p1%C,p2r=p2/C,p2c=p2%C;
    
    return abs(p1r-p2r)+abs(p1c-p2c);
  }
};

int base[101][101];
int mx[101][101];

class PublicTransit_manhattan {
public:
  int minimumLongestDistance(int R, int C) {
    ZERO(base);
    int res=Inf;
    int V=R*C;
 
    REP(y1,R)REP(x1,C) REP(y2,R)REP(x2,C) {
      base[C*y1+x1][C*y2+x2]=abs(x1-x2)+abs(y1-y2);
    }
 
    REP(p1,V) REP(p2,V) if(p1<=p2) {
      REP(i,V)REP(j,V) mx[i][j]=base[i][j];
      
      mx[p1][p2]=mx[p2][p1]=0;
      
      REP(i,V)REP(j,V) {
        VI ds = {mx[i][j], mx[i][p1]+mx[p2][j], mx[i][p2]+mx[p1][j]};
        mx[i][j]=*min_element(ds.begin(),ds.end());
      }
      int D=0;
      REP(i,V)REP(j,V) {
        //        dump3(i,j,mx[i][j]);
        D=max(D,mx[i][j]);
      }
      res=min(res,D);
    }
    return res;
  }
};

// floyd-warshall
class PublicTransit_floydwarhsall {
  public:
  int minimumLongestDistance(int R, int C) {
    ZERO(base);
    int res=Inf;
    int V=R*C;
    
    REP(y1,R)REP(x1,C) REP(y2,R)REP(x2,C) base[C*y1+x1][C*y2+x2]=Inf;
    
    REP(i,R)REP(j,C) {
      int p=C*i+j;
      base[p][p]=0;
      FORR(m,moves) {
        int i2=i+m.first,j2=j+m.second;
        if(i2<0||i2>=R||j2<0||j2>=C) continue;
        base[p][C*i2+j2]=1;
      }
    }
    
    // if brute force all distinct pairs, it hits TLE
    // REP(p1,V) REP(p2,V) if(p1<p2) {
    // p1 and p2 are symmetric. if brute force half by half, system test passes.
    REP(p1,V/2+1) FOR(p2,V/2,V) {
      REP(i,V)REP(j,V) mx[i][j]=base[i][j];
      mx[p1][p2]=mx[p2][p1]=0;
      
      REP(k,V) REP(i,V) REP(j,V) {
        mx[i][j]=min(mx[i][j],mx[i][k]+mx[k][j]);
      }
      int D=0;
      REP(i,V)REP(j,V) {
//        dump3(i,j,mx[i][j]);
        D=max(D,mx[i][j]);
      }
      res=min(res,D);
    }
    return res;
  }
};

// CUT begin
ifstream data("PublicTransit.sample");

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

bool do_test(int R, int C, int __expected) {
    time_t startClock = clock();
    PublicTransit *instance = new PublicTransit();
    int __result = instance->minimumLongestDistance(R, C);
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
        int C;
        from_stream(C);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(R, C, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503935759;
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
        cout << "PublicTransit (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
