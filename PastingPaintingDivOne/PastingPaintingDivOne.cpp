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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('\n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

/*
 
 11/9/2018
 
 17:40-18:30 AC
 
 http://apps.topcoder.com/wiki/display/tc/SRM+562
 
 */

const int MAX_N=300;
char S[MAX_N][MAX_N];
class PastingPaintingDivOne {
  public:
  int N,M;
  vector<string> C;
  void paint(int p) {
    REP(i,N)REP(j,M) {
      int ii=p+i,jj=p+j;
      if(C[i][j]!='.') S[ii][jj]=C[i][j];
    }
  }
  vector<long long> countColors(vector<string> C, int T) {
    this->N=SZ(C),this->M=SZ(C[0]),this->C=C;
    int maxn=max(N,M);
    REP(i,MAX_N)REP(j,MAX_N)S[i][j]='.';
    unordered_map<char,LL> cnt;
    if(T<4*maxn) {
      REP(p,T) paint(p);
      REP(i,MAX_N)REP(j,MAX_N)if(S[i][j]!='.') cnt[S[i][j]]++;
      return {cnt['R'],cnt['G'],cnt['B']};
    } else {
      REP(p,4*maxn) paint(p);
      REP(i,MAX_N)REP(j,MAX_N)if(S[i][j]!='.') cnt[S[i][j]]++;
//      dump3(cnt['R'],cnt['G'],cnt['B']);
      unordered_map<char,LL> cnt2;
      int p=2*maxn-1;
      FOR(i,p,MAX_N)if(S[i][p]!='.') cnt2[S[i][p]]++;
      FOR(j,p+1,MAX_N)if(S[p][j]!='.') cnt2[S[p][j]]++;
//      dump3(cnt2['R'],cnt2['G'],cnt2['B']);
      LL rem=T-4*maxn;
      assert(rem>=0);
      /*
      dump3(maxn,rem,T);
      REP(i,40){
        REP(j,40) cout<<S[i][j];
        cout<<endl;
      }*/
      
      cnt['R']+=rem*cnt2['R'],cnt['G']+=rem*cnt2['G'],cnt['B']+=rem*cnt2['B'];
      return {cnt['R'],cnt['G'],cnt['B']};
    }
  }
};

// CUT begin
ifstream data("PastingPaintingDivOne.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<string> clipboard, int T, vector<long long> __expected) {
    time_t startClock = clock();
    PastingPaintingDivOne *instance = new PastingPaintingDivOne();
    vector<long long> __result = instance->countColors(clipboard, T);
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
        vector<string> clipboard;
        from_stream(clipboard);
        int T;
        from_stream(T);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(clipboard, T, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541813956;
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
        cout << "PastingPaintingDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
