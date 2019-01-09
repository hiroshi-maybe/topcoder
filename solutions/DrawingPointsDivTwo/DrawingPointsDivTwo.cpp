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
 
 1/2/2017
 
 10:53-11:45 analysis
 12:56 Sample 4 does NOT make sense for me 😡
 Look at https://community.topcoder.com/stat?c=problem_solution&rm=314754&rd=15182&pm=12298&cr=22920925
 13:32-13:45 fix my solution to check ONLY the initial state. System test passed.
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+560
 
 From give state, we can figure out states n-step backward.
 Now let's define board state i-step before as `S(i)`
 We can convert given points to (2*row,2*col) so that we don't need to worry about fraction like `1.5`.
 
 P = { (i*2, j*2) : (i,j) = row and col where ps[i][j]='*' }
 
 S(0) = P
 S(1) = b(S(0))
      = { b(p) : p∈S(0), b(p) = {(p.row-1,p.col-1),(p.row-1,p.col+1),(p.row+1,p.col-1),(p.row+1,p.col+1)} }
 
 T(b) = O(R*C) ≈ 40^2 (=1600)
 
 It's also possible to simulate forward step.
 
   S(0)
 = f(S(1))
 = { f(p) : p∈S(1), f(p) = (p.row+1,p.col) if (p.row+2,p.col)∈S(1) AND (p.row,p.col+2)∈S(1) AND (p.row+2,p.col+2)∈S(1) }
 
 Important point is f(b(S(i))) ≠ S(i). There is below case as seen in sample #4:
 
      S(1) =b(S(0))  -> S(2) =b(S(1)) -> S(3)=b(S(2))
    ↗︎                                    |
 S(0)                                    |
    ↖︎                                    |
      S(1)'=f(S(2)') <- S(2)'=f(S(3))   ↲
 
 This was critical missing point in my analysis.
 b(S(i)) is minimum requirement to reach S(0).
 Extra points may be contained in intermediate states though, they may disappear in f() processing.
 If so, still starting state is valid. So S(3) shown above is still valid.
 Problem writer gave us clue to figure out this fact by sample #4.
 I was not flexible enough to figure out it by additional analysis 👎
 I should have suspected my analysis.
 We eventually want to know that forward action reaches S(0).
 I should have simulated behavior when extra points are there in intermediate states 👎👎
 
 Now we need to make sure that algorithm fits in size conatraint.
 At most how many steps are possible?
 The worst case is that '*' stays at the corners in 20x20 board.
 It will take approximately 20 steps that point of one corner affects the others.
 So searching 50 steps seems to be enough.
 
 Searching 50 steps call `f()` 50^2 times.
   T
 =  T(f)*50^2
 ≤ 1600*50^2 // T(f) ≤ 1600
 =  4*10^6 << 10^8
 
 Summary:
  - By sample simulation, I tried to find some property which enables to compute max steps without simulation. However no luck 👎👎👎👎
  - I should have analyzed runtime by simulation. Then I should have saved time 👎👎👎👎👎👎👎👎
  - It was straightforward by adding extra points to avoid fraction
  - I could not understand sample 4 until looking at submit solution 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 
 */
vector< pair < int, int > >  moves = { {1,1},{1,-1},{-1,-1},{-1,1} };
vector< pair < int, int > >  ms2 = { {0,2},{2,2},{2,0} };
class DrawingPointsDivTwo {
  public:
  
  void show(set<II> P) {
    FORR(p,P) cout<<"{"<<p.first<<","<<p.second<<"}";
    cout <<endl;
  }
  
  set<II> backward(set<II> P) {
    set<II> Q;
    FORR(p,P) {
      int i=p.first,j=p.second;
      FORR(m,moves) {
        int i2=i+m.first,j2=j+m.second;
        Q.emplace(i2,j2);
      }
    }
    return Q;
  }
  
  set<II> forward(set<II> Q) {
    set<II> PP;
    FORR(q,Q) {
      int i=q.first,j=q.second;
      
      bool ok=true;
      FORR(m,ms2) {
        int i2=i+m.first,j2=j+m.second;
        ok&=Q.count({i2,j2})>0;
      }
      if(ok) PP.emplace(i+1,j+1);
    }
//    cout<<"PP:"; show(PP);
    return PP;
  }
  
  bool valid(set<II> P, set<II> Q) {
    /*
    if(P!=Q) {
      dump2(SZ(P),SZ(Q));
      cout <<"P: ";
      show(P);
      cout <<"Q: ";
      show(Q);
    }*/
    return P==Q;
  }
  int maxSteps(vector<string> ps) {
    set<II> P;
    REP(i,SZ(ps)) REP(j,SZ(ps[0])) if(ps[i][j]=='*') {
      P.emplace(2*i,2*j);
    }
//    show(P);
    
    set<II> PP=P;
    int res=0;
    while(res<50) {
      PP=backward(PP);
      set<II> Q=PP;
      REP(_,res+1) Q=forward(Q);
      if(!valid(P,Q)) return res;
      ++res;
    }
    
    return -1;
  }
};

// CUT begin
ifstream data("DrawingPointsDivTwo.sample");

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

bool do_test(vector<string> points, int __expected) {
    time_t startClock = clock();
    DrawingPointsDivTwo *instance = new DrawingPointsDivTwo();
    int __result = instance->maxSteps(points);
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
        vector<string> points;
        from_stream(points);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(points, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514919189;
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
        cout << "DrawingPointsDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
