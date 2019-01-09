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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/25/2018
 
 16:40-18:05 analysis
 18:06-18:36 implement and ACC (328.01 pt) // 10 mins loss due to operator priority...
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+504
   - brute-force and polynomial-time algorithms
  - http://d.hatena.ne.jp/kusano_prog/20110430/1304181136
   - polynomial-time algorithm
  - http://kmjp.hatenablog.jp/entry/2014/04/19/1200
   - brute-force
 
 Suppose we are converting grid A to grid B.
 The most important point is that colors in previous row is already processed.
 Thus we don't need to look at A[i-1] to get B[i].
 
 B[i] = f(A[i], B[i-1])
 
 We can build inverted function f' to compute possible A[i] as below:
 
 A[i] = f'(B[i-1], B[i])
 
 Point of inversion process:
  - Process in right-to-left direction
  - If any color works, leave it wildcard
  - Don't miss verification of output
 
 The most confusing part to figure out this solution was that I was not understanding 3 states rather than 2 states.
 Color at column `i` trasitions like i_a => i_b => i_c.
 i_a is initial input, i_b is intermediate state, i_c is final output.
 
 When we are looking at column i and i+1, We are transforming i_b and (i+1)_a to i_c and (i+1)_b.
 Column `i` is already transformed in previous operation once.
 This is the first transformation for column i+1. The initial input is transfermed to intermediate one.
 This color may change in next operation. Then color is finalized.
 
 By traversing transformation from right to left, we should have i_c and (i+1)_b.
 Note that color at i+1 is given by next operation.
 We should verify i_c and (i+1)_b so that they are expected one to be produced by prev_row(i) and prev_row(i+1)
 If they are valid, we can figure out i_b and (i+1)_a.
 Now column (i+1) is fixed. We can go through previous operation.
 
 If we cannot imagine intermediate state, it's impossible to understand polynomial-time solution.
 
 Key:
  - Current row depends on previous output row
  - Brute-force and decision works
  - We can also infer original grid without search in polynomial time
 
 Summary:
  - I was totally confused what state should be referred to decide input
   - We should look at string of OUTPUT in previous row because prev row has already changed when current row is changing...
   - I was in stuck due to bit DP approach for more than one hour 👎
  - Understand the problem correctly
  - Generating string from mask was actually easier. My first wrong bit DP approach distracted it.
 
 */
class Algrid {
  public:
  const int Inf=1<<20;
  int R,C;
  vector<string> B;
  int g(int mask1, int mask2) {
    int l=(mask2>>(C-1))&1,x=0;
    for(int i=C-2; i>=0; --i) {
      // pre row
      int l1=(mask1>>(i+1))&1,r1=(mask1>>i)&1;
      // cur
      int lcur=l,rcur=(mask2>>i)&1;
      
      int ll=-1,rr=-1;
      if(l1==1&&r1==1) ll=lcur,rr=rcur;
      if(l1==0&&r1==1) ll=0,rr=0;
      if(l1==1&&r1==0) ll=1,rr=1;
      if(l1==0&&r1==0) ll=rcur,rr=lcur;
      x=2*x+ll;
      l=rr;
    }
    x=2*x+l;
    return x;
  }
  
  int f(int mask1, int T) {
    int res=Inf;
    // 0: B, 1: W
    REP(mask2,1<<C) {
      int x=g(mask1,mask2);
      if(x==T) SMIN(res,mask2);
    }
    return res;
  }
  
  vector<string> makeProgram(vector<string> B) {
    this->R=SZ(B),this->C=SZ(B[0]);
    this->B=B;
    VI res(R-1,Inf);
    
    dump2(enc(B[0]),g(enc(B[0]), 0));
    
    REP(i,R-1) res[i]=f(enc(B[i]),enc(B[i+1]));
    
    bool ok=true;
    REP(i,R-1) ok&=res[i]<Inf;
    if(!ok) return {};
    
    vector<string> ans;
    ans.push_back(B[0]);
    REP(i,R-1) ans.push_back(dec(res[i]));
    return ans;
  }
  int enc(string s) {
    int res=0;
    REP(i,C) {
      res=2*res+(s[i]=='W');
    }
    return res;
  }
  string dec(int mask) {
    string res="";
    for(int i=C-1; i>=0; --i) {
      res+=((mask>>i)&1)?'W':'B';
    }
    return res;
  }
};

// CUT begin
ifstream data("Algrid.sample");

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

bool do_test(vector<string> output, vector<string> __expected) {
    time_t startClock = clock();
    Algrid *instance = new Algrid();
    vector<string> __result = instance->makeProgram(output);
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
        vector<string> output;
        from_stream(output);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(output, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522021237;
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
        cout << "Algrid (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
