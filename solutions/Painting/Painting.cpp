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
 
 10/8/2018
 
 13:22-13:28 analysis
 13:32 1WA
 14:05 AC
 
 http://mayokoex.hatenablog.com/entry/2015/11/29/194918
 http://rsujskf.blog32.fc2.com/blog-entry-1878.html
 http://www.vexorian.com/2011/01/member-srm-494-commentary-and.html
 http://topcoder.g.hatena.ne.jp/namakemono_srm/20110616/1308203084
 https://topcoder.g.hatena.ne.jp/shnya_m/20110123
 
 */
class Painting {
public:
  int largestBrush(vector<string> B) {
    int N=SZ(B),M=SZ(B[0]);
    vector<vector<int>> cum(N+1,VI(M+1,0));
    vector<vector<int>> X(N,VI(M,0));
    REP(i,N)REP(j,M) {
      cum[i+1][j+1]=cum[i+1][j]+cum[i][j+1]-cum[i][j]+(B[i][j]=='B');
    }
    REP(i,N)REP(j,M) if(B[i][j]=='B') {
      int x=1;
      FORE(l,1,min(N,M)) if(i+l<=N&&j+l<=M) {
        int ii=i+l,jj=j+l;
        int a=cum[ii][jj]-cum[i][jj]-cum[ii][j]+cum[i][j];
        if(a!=l*l) break;
        x=l;
      }
//      dump3(i,j,x);
      FOR(ii,i,i+x)FOR(jj,j,j+x) {
        SMAX(X[ii][jj],x);
      }
    }
    int res=1000;
    REP(i,N)REP(j,M) if(B[i][j]=='B') SMIN(res,X[i][j]);
    return res;
  }
};

class Painting_wrong {
  public:
  int largestBrush(vector<string> B) {
    int N=SZ(B),M=SZ(B[0]);
    const int Inf=100;
    int res=Inf;
    REP(i,N) {
      int cnt=0;
      REP(j,M) {
        if(B[i][j]=='B') {
          ++cnt;
          if(j==M-1||B[i][j+1]=='W') SMIN(res,cnt);
        } else {
          cnt=0;
        }
      }
    }
    REP(j,M) {
      int cnt=0;
      REP(i,N) {
        if(B[i][j]=='B') {
          ++cnt;
          if(i==N-1||B[i+1][j]=='W') SMIN(res,cnt);
        } else {
          cnt=0;
        }
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("Painting.sample");

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

bool do_test(vector<string> picture, int __expected) {
    time_t startClock = clock();
    Painting *instance = new Painting();
    int __result = instance->largestBrush(picture);
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
        vector<string> picture;
        from_stream(picture);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(picture, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539030149;
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
        cout << "Painting (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
