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

//constexpr int MOD = 1e9+9;

/*
 
 9/4/2017
 
 10:55-11:30 give up

 16:00-16:55 read editorials:
  - http://kmjp.hatenablog.jp/entry/2015/03/02/1100
  - http://mayokoex.hatenablog.com/entry/2015/03/20/103241
 
 16:55-17:20 add solution
 
 Key:
  - create unique K tiles first by set<set<II>> S[K];
  - create shapes by adjusting their coordinate so that negative x or negative y does not happen
   - s1={(-1,0),(0,0)} and s2={(0,0),(1,0)} form the same shape
   - by adjusting origin of s1 by (0,0), we get the same set {(0,0),(1,0)}
   - thus duplicated shape never happens
  - we can just go through positions in board and ++res if shape is not disturbed by obstacle '#'
   - now shapes are unique and positions are sorted in consistent order by ordered set
   - no need to worry about duplicated count due to this unique order of positions
  - mod 1e9+9 is unnecessary
 
 Summary:
  - I tried to build k tiles by starting from (i,j) though, I couldn't find out how to count up without duplication
  - adjusting coordinate work. it may not be elegant though, it suffices.
 
 17:21-17:39 add visualized shapes for fun :D
 
 generated shapes:
  - K=8: 2725 shapes https://github.com/k-ori/topcoder/blob/master/FoxConnection4/8-shape.txt
  - K=7:  760 shapes https://github.com/k-ori/topcoder/blob/master/FoxConnection4/7-shape.txt
  - K=6:  216 shapes https://github.com/k-ori/topcoder/blob/master/FoxConnection4/6-shape.txt
  - K=5:   63 shapes https://github.com/k-ori/topcoder/blob/master/FoxConnection4/5-shape.txt
  - K=4:   19 shapes https://github.com/k-ori/topcoder/blob/master/FoxConnection4/4-shape.txt
  - K=3:    6 shapes https://github.com/k-ori/topcoder/blob/master/FoxConnection4/3-shape.txt
  - K=2:    2 shapes https://github.com/k-ori/topcoder/blob/master/FoxConnection4/2-shape.txt
  - K=1:    1 shape  https://github.com/k-ori/topcoder/blob/master/FoxConnection4/1-shape.txt
 
 */

vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };
set<set<II>> S[9]; // shapes
class FoxConnection4 {
  public:
  int howManyWays(vector<string> B, int K) {
    REP(i,K) S[i].clear();
    set<II> so={make_pair(0,0)};
    S[1].emplace(so);
    FOR(i,1,K) {
      for(set<II> s1 : S[i]) {
        for(auto p : s1) {
          FORR(m,moves) {
            int x2=p.first+m.first,y2=p.second+m.second;
            if(s1.count({x2,y2})) continue;
            int adjx=x2<0,adjy=y2<0;
            set<II> s2={make_pair(x2+adjx,y2+adjy)};
            for(auto q : s1) s2.emplace(q.first+adjx,q.second+adjy);
            S[i+1].emplace(s2);
          }
        }
      }
    }
    
    /*
    if(K==8) {
      int i=0;
      FORR(s,S[8]) {
        cout << "------------" << i++ << endl;
        visualize(s);
      }
    }*/
    
    int res=0;
    int M=SZ(B),N=SZ(B[0]);
    REP(i,M) REP(j,N) {
      FORR(s,S[K]) {
        bool ok=true;
        FORR(o,s) {
          int r=i+o.first,c=j+o.second;
          if(r<0||r>=M||c<0||c>=N) {
            ok=false;
            break;
          }
          if(B[r][c]=='#') ok=false;
        }
        res+=ok;
      }
    }
    
    return res;
  }
  
  void visualize(set<II> s) {
    int maxx=0,maxy=0;
    FORR(p,s) maxx=max(maxx,p.first),maxy=max(maxy,p.second);
    REP(y,maxy+1) {
      REP(x,maxx+1) {
        if(s.count({x,y})) cout << "#";
        else cout << " ";
      }
      cout << endl;
    }
  }
};

// CUT begin
ifstream data("FoxConnection4.sample");

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

bool do_test(vector<string> board, int k, int __expected) {
    time_t startClock = clock();
    FoxConnection4 *instance = new FoxConnection4();
    int __result = instance->howManyWays(board, k);
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
        vector<string> board;
        from_stream(board);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504547693;
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
        cout << "FoxConnection4 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
