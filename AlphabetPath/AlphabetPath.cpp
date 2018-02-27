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
 
 2/26/2018
 
 9:06-9:17 ACC (219.20 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+523
  - http://topcoder.g.hatena.ne.jp/firewood/20111114/1321295768
  - http://peryaudo.hatenablog.com/entry/20111112/1321126594
  - http://programming-tatuyan.blogspot.com/2011/11/topcoder-srm-523div2.html
 
 18:20-18:24 add simpler implementation from editorals
 
 */
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
class AlphabetPath {
public:
  vector<string> B;
  int R,C;
  string yes="YES",no="NO";
  string doesItExist(vector<string> BB) {
    this->R=SZ(BB),this->C=SZ(BB[0]),this->B=BB;
    int pi=-1,pj=-1;
    REP(i,R)REP(j,C) if(B[i][j]=='A') pi=i,pj=j;
    REP(c,25) REP(i,R) REP(j,C) if(B[i][j]==('B'+c)) {
      if(abs(pi-i)+abs((pj-j))!=1) return no;
      pi=i,pj=j;
    }
    return yes;
  }
};

class AlphabetPath_org {
  public:
  vector<string> B;
  int R,C;
  string yes="YES",no="NO";
  bool dfs(int i, int j, int d) {
    if(d==26) return true;
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=R||jj<0||jj>=C) continue;
      if(B[ii][jj]==char('A'+d)) return dfs(ii,jj,d+1);
    }
    return false;
  }
  string doesItExist(vector<string> BB) {
    this->R=SZ(BB),this->C=SZ(BB[0]),this->B=BB;
    int /*T=-1,*/S=-1;
    REP(i,R)REP(j,C) {
      if(B[i][j]=='A') S=i*C+j;
//      if(B[i][j]=='Z') T=i*C+j;
    }
    return dfs(S/C,S%C,1)?yes:no;
  }
};

// CUT begin
ifstream data("AlphabetPath.sample");

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

bool do_test(vector<string> letterMaze, string __expected) {
    time_t startClock = clock();
    AlphabetPath *instance = new AlphabetPath();
    string __result = instance->doesItExist(letterMaze);
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
        vector<string> letterMaze;
        from_stream(letterMaze);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(letterMaze, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519664786;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "AlphabetPath (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
