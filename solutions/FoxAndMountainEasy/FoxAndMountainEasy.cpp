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
 
 13:50-14:35 2WA (% operator against negative integer, unexpected `continue`)
 14:45 AC

 I solved by simulation. However it's so cumbersome.
 
 http://apps.topcoder.com/wiki/display/tc/SRM+557

 Solutions of @semiexp and @anta are easy to understand.
 It's optimal to move the known segment to left.
 
 Suppose we can put segment at `i`.
 We are going to move the segment to left.
 Up/down of left can be moved to right by this operation.
 The only loss happens when minimum depth of the segment hits ground.
 In such a case, we cannot move this segment to left.
 So as long as we initially put `abs(mind)` ups and put the segment, we never hit the ground.
 The remaining subproblem is that N-M-abs(mind) is enough to fill the remaining gap.
 
 Summary:
  - Congratulation on super complex solution by simulation. Very stupid.
  - If we can put arbitrary option, we may find special optimal case without breaking the condition
 
 */
const string yes="YES",no="NO";
class FoxAndMountainEasy {
public:
  string possible(int N, int h0, int hn, string S) {
    if(N%2!=abs(hn-h0)%2) return no;
    int d=0,mind=0,M=SZ(S);
    REP(i,M) {
      d+=S[i]=='U'?1:-1;
      SMIN(mind,d);
    }
    if(h0<abs(mind)) {
      int x=abs(mind)-h0;
      h0+=x,N-=x;
    }
    h0+=d,N-=M;
    if(abs(hn-h0)>N) return no;
    return yes;
  }
};

class FoxAndMountainEasy_wrong {
public:
  string possible(int N, int h0, int hn, string S) {
    int D=hn-h0;
    if(abs(D)%2!=N%2) return no;
    int M=SZ(S);
    int d=0,mind=0;
    REP(i,M) {
      d+=S[i]=='U'?1:-1;
      SMIN(mind,d);
    }
        dump3(D,d,mind);
    D-=d;
    if(abs(D)>N-M) return no;
    int x=(N-M-D)/2;
    if(hn>h0+d) x+=hn-(h0+d);
    int y=h0+x;
    REP(i,M) {
      if(S[i]=='U') ++y;
      else --y;
      if(y<0) return no;
    }
//    if(max(h0,hn)+x+mind<0) return no;
    return yes;
  }
};

class FoxAndMountainEasy_org {
  public:
  string possible(int N, int h0, int hn, string S) {
    int M=SZ(S);
    if(N%2!=abs(hn-h0)%2) return no;
    int d=0,mind=0;
    REP(i,M) {
      d+=(S[i]=='U')?1:-1;
      SMIN(mind,d);
    }
    dump2(mind,d);
    mind=abs(mind);
    int l=h0,r=h0;
    int p0=h0%2;
    REP(i,N) {
      int j=i+M;
      if(j>N) continue;
      int l2=l;
      if(l2<mind) l2=mind;
      dump3(i,l2,r);
      if(l2%2!=(p0+i)%2) l2++;
      int ll1=l2+d,rr1=r+d;
      if(rr1>=0&&l2<=r) {
        if(ll1<0) ll1=abs(ll1)%2;
        int dd=N-(i+M);
        assert(dd>=0);
        int ll2=hn-dd,rr2=hn+dd;
        if(ll2<0) ll2=abs(ll2)%2;
        
        int x=max(ll1,ll2),y=min(rr1,rr2);
        
                  dump3(i,ll1,rr1);
                  dump4(ll2,rr2,x,y);

        
        if(y-x>=0) {
          return yes;
        }
      }
      l-=1,r+=1;
      if(l<0)l=1;
    }
    
    return no;
  }
};

// CUT begin
ifstream data("FoxAndMountainEasy.sample");

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

bool do_test(int n, int h0, int hn, string history, string __expected) {
    time_t startClock = clock();
    FoxAndMountainEasy *instance = new FoxAndMountainEasy();
    string __result = instance->possible(n, h0, hn, history);
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
        int n;
        from_stream(n);
        int h0;
        from_stream(h0);
        int hn;
        from_stream(hn);
        string history;
        from_stream(history);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, h0, hn, history, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541800261;
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
        cout << "FoxAndMountainEasy (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
