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
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/9/2018
 
 21:55-22:03 analysis
 22:04-22:15 implement and sybmit. System test passed (358.33 pt)
 
 1/10/2018
 
 Editorials:
  - http://mayokoex.hatenablog.com/entry/2016/06/17/205322
   - observe if -1 is used by index
  - http://topcoder.g.hatena.ne.jp/agw/20120907/1346974377
   - binary search
  - http://rkx1209.hatenablog.com/entry/2012/10/22/000135
   - simulate by two different numbers and compare result
  - http://topcoder.g.hatena.ne.jp/capythm/20120826
   - simulate by negative value
 
 Looks like binary search is not the assumed solution.
 
 23:00-23:28 add solution with O(N) time
 
 Summary:
  - Nice to solve in 20 mins
  - Linear search solution would be simpler and faster
   - When I figured out that computed value monotonically increases, I should analyze it deeply and find out `x` is easy to compute
 
 */

class Suminator {
public:
  LL calc(vector<LL> P, LL r) {
    REP(i,SZ(P)) if(P[i]==-1) P[i]=r;
    stack<LL> S;
    REP(i,SZ(P)) {
      if(P[i]>0) S.push(P[i]);
      else {
        LL a=0,b=0;
        if(SZ(S)) a=S.top(),S.pop();
        if(SZ(S)) b=S.top(),S.pop();
        S.push(1LL*a+b);
      }
    }
    //    dump2(r,S.top());
    return S.top();
  }
  
  int findMissing(vector<int> PP, int T) {
    vector<LL> P(PP.begin(),PP.end());
    LL a=calc(P,0);
    if(a==T) return 0;
    const LL Inf=1e12;
    LL AA=calc(P,Inf);
    if(AA<Inf) return AA==T?0:-1;
    LL A=AA-Inf;
    LL x=T-A;
    dump3(AA,A,x);
    return x>0?x:-1;
  }
};

// O(N*lg 1e11) time
class Suminator_org {
  public:
  LL calc(VI P, LL r) {
    REP(i,SZ(P)) if(P[i]==-1) P[i]=r;
    stack<LL> S;
    REP(i,SZ(P)) {
      if(P[i]>0) S.push(P[i]);
      else {
        LL a=0,b=0;
        if(SZ(S)) a=S.top(),S.pop();
        if(SZ(S)) b=S.top(),S.pop();
        S.push(1LL*a+b);
      }
    }
//    dump2(r,S.top());
    return S.top();
  }
  
  int findMissing(vector<int> P, int T) {
    LL a=calc(P,0);
    if(a==T) return 0;
    
    const LL Inf=1e11;
    LL ok=1LL,ng=Inf;
    while(llabs(ok-ng)>1) {
      LL mid=(ok+ng)/2LL;
      LL x=calc(P,mid);
      (x>T?ng:ok)=mid;
    }
    if(calc(P,ok)==T) return ok;
    return -1;
  }
};

// CUT begin
ifstream data("Suminator.sample");

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

bool do_test(vector<int> program, int wantedResult, int __expected) {
    time_t startClock = clock();
    Suminator *instance = new Suminator();
    int __result = instance->findMissing(program, wantedResult);
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
        vector<int> program;
        from_stream(program);
        int wantedResult;
        from_stream(wantedResult);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(program, wantedResult, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515563741;
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
        cout << "Suminator (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
