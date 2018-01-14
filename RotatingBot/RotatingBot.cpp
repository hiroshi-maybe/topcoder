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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/14/2018
 
 12:36-12:45 analysis
 13:00 I cannot understand sample 5 👎
 "The robot may not leave the grid." I hate this question.
 13:34 submit and ACC (219.75 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+550
  - http://topcoder.g.hatena.ne.jp/minus9d/20120723/1343050522
   - explaining about very cool implementation by @Petr
  - http://mayokoex.hatenablog.com/entry/2016/05/28/001548
 
 Add @Petr's smart solution
 
 */
vector< pair < int, int > >  moves = { {0,1}/*R*/,{-1,0}/*U*/,{0,-1}/*L*/,{1,0}/*D*/ };

class RotatingBot {
public:
  int minArea(vector<int> xs) {
    int mi=0;
    int r=0,c=0;
    set<II> viz,out;
    viz.emplace(r,c);
    REP(i,SZ(xs)) {
      int steps=xs[i];
      REP(_,steps) {
        r+=moves[mi].first,c+=moves[mi].second;
        if(viz.count({r,c})) { dump4(i,mi,r,c); return -1; }
        viz.emplace(r,c);
      }
      //      dump4(i,mi,r,c);
      int rr=r+moves[mi].first,cc=c+moves[mi].second;
      if(i!=SZ(xs)-1&&!viz.count({rr,cc})) out.emplace(rr,cc);
      
      mi=(mi+1)%4;
    }
    int minr=1e4,maxr=-1e4,minc=1e4,maxc=-1e4;
    FORR(p,viz) {
      MINS(minr,p.first),MAXS(maxr,p.first);
      MINS(minc,p.second),MAXS(maxc,p.second);
    }
    dump4(minr,maxr,minc,maxc);
    dump(SZ(out));
    FORR(p,out) if((minr<=p.first&&p.first<=maxr)&&(minc<=p.second&&p.second<=maxc)) {
      dump2(p.first,p.second);
      return -1;
    }
    int R=maxr-minr+1,C=maxc-minc+1;
    return R*C;
  }
};

class RotatingBot_org {
  public:
  int minArea(vector<int> xs) {
    int mi=0;
    int r=0,c=0;
    set<II> viz;
    viz.emplace(r,c);
    REP(i,SZ(xs)) {
      int steps=xs[i];
      REP(_,steps) {
        r+=moves[mi].first,c+=moves[mi].second;
        if(viz.count({r,c})) { dump4(i,mi,r,c); return -1; }
        viz.emplace(r,c);
      }
//      dump4(i,mi,r,c);
      mi=(mi+1)%4;
    }
    int minr=1e4,maxr=-1e4,minc=1e4,maxc=-1e4;
    FORR(p,viz) {
      MINS(minr,p.first),MAXS(maxr,p.first);
      MINS(minc,p.second),MAXS(maxc,p.second);
    }
    dump4(minr,maxr,minc,maxc);

    int R=maxr-minr+1,C=maxc-minc+1;
    
    /*
    vector<VI> B(maxr-minr+1,VI(maxc-minc+1,0));
    FORR(p,viz) {
      int r=p.first-minr,c=p.second-minc;
      B[r][c]=1;
    }
    REP(i,SZ(B)){
      REP(j,SZ(B[0])) {
        cout << B[i][j];
      }
      cout<<endl;
    }*/
    
    r=-minr,c=-minc;
    mi=0;
    dump2(r,c);
    viz.clear();
    viz.emplace(r,c);
    REP(i,SZ(xs)) {
      int steps=xs[i];
      REP(_,steps) {
        r+=moves[mi].first,c+=moves[mi].second;
        if(viz.count({r,c})) { dump4(i,mi,r,c); return -1; }
        viz.emplace(r,c);
      }
      dump4(i,mi,r,c);
      int rr=r+moves[mi].first,cc=c+moves[mi].second;
      if(rr<0||rr>=R||cc<0||cc>=C||viz.count({rr,cc})) {
        mi=(mi+1)%4;
        continue;
      }
      dump2(rr,cc);
      if(i!=SZ(xs)-1) return -1;
    }
    
    return R*C;
  }
};

// CUT begin
ifstream data("RotatingBot.sample");

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

bool do_test(vector<int> moves, int __expected) {
    time_t startClock = clock();
    RotatingBot *instance = new RotatingBot();
    int __result = instance->minArea(moves);
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
        vector<int> moves;
        from_stream(moves);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(moves, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515962160;
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
        cout << "RotatingBot (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
