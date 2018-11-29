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
 
 11/29/2018
 
 11:41-12:17 AC
 
 https://apps.topcoder.com/wiki/display/tc/SRM+570
 
 I decomposed and reassembled contribution of each direction.
 However computing result of one cycle is simpler as shown in the editorial.
 That's possible because there is only at most 4 elements in the cycle.
 
 */
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
class RobotHerb {
public:
  long long getdist(int T, vector<int> A) {
    int N=SZ(A);
    LL d=0,dx=0,dy=0;
    REP(_,4) REP(i,N) {
      LL a=A[i];
      dx+=1LL*moves[d].first*a,dy+=1LL*moves[d].second*a;
      d=(d+A[i])%4;
    }
    
    LL x=T/4*dx,y=T/4*dy;
    assert(d==0);
    REP(_, T%4) REP(i,N) {
      LL a=A[i];
      x+=1LL*moves[d].first*a,y+=1LL*moves[d].second*a;
      d=(d+A[i])%4;
    }
    return abs(x)+abs(y);
  }
};

class RobotHerb_org {
  public:
  long long getdist(int T, vector<int> A) {
    int N=SZ(A);
    LL d=0,dx=0,dy=0;
    REP(i,N) {
      LL a=A[i];
      dx+=1LL*moves[d].first*a,dy+=1LL*moves[d].second*a;
      d=(d+A[i])%4;
    }
//    dump3(d,dx,dy);
    if(d==0) return abs(dx*T)+abs(dy*T);
    if(d==2) {
      if(T%2==0) return 0;
      else return abs(dx)+abs(dy);
    }
    
//    LL cnt[4]={T/4,T/4+(T%4<=1),T/4+(T%4<=2),T/4+(T%4<=3)};
    LL cnt[4]={};
    REP(i,4) cnt[i]=T/4+((T%4)<=i);
    if(d==1) {
      LL x=dx*cnt[0]+dy*cnt[1]-dx*cnt[2]-dy*cnt[3];
      LL y=dy*cnt[0]-dx*cnt[1]-dy*cnt[2]+dx*cnt[3];
//      dump3(d,x,y);
      return abs(x)+abs(y);
    }
    LL x=dx*cnt[0]-dy*cnt[1]-dx*cnt[2]+dy*cnt[3];
    LL y=dy*cnt[0]+dx*cnt[1]-dy*cnt[2]-dx*cnt[3];
    return abs(x)+abs(y);
  }
};

// CUT begin
ifstream data("RobotHerb.sample");

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

bool do_test(int T, vector<int> a, long long __expected) {
    time_t startClock = clock();
    RobotHerb *instance = new RobotHerb();
    long long __result = instance->getdist(T, a);
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
        int T;
        from_stream(T);
        vector<int> a;
        from_stream(a);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(T, a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1543459229;
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
        cout << "RobotHerb (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
