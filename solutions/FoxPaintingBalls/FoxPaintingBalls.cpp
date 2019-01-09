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
 
 1/12/2018
 
 8:54-9:51 1WA due to 0-division (202.01 pt)
 9:55 2WA logic bug
 9:58 3WA due to overflow
 9:58-10:04 pause
 10:50-11:05 4WA
 11:07 5WA
 13:15-13:30 sorted out analysis and system test passed.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+552
   - binary search
  - http://topcoder.g.hatena.ne.jp/agw/comment?date=20120904
   - math
  - http://topcoder.g.hatena.ne.jp/firewood/20120818/1345309354
   - math
  - http://topcoder.g.hatena.ne.jp/kojingharang/20120817/1345219583
   - binary search
  - http://mayokoex.hatenablog.com/entry/2016/06/11/110624
   - binary search
  - http://n-knuu.hatenablog.jp/entry/2016/06/11/023348
   - binary search
  - http://rsujskf.blog32.fc2.com/blog-entry-2276.html
   - math and binary search
  - https://chaingng.github.io/post/srm-552-div1-easy---foxpaintingballs/
   - binary search
 
 My analysis
 
 Without losing generality, we have A,B,C balls (A<=B<=C).
 
 If N=1, obviously res=A+B+C
 If N>1, S(N)=N*(N+1)/2 is needed to build N-triangle.
 
 Difference of number of painted colors is at most one.
 If number of painted colro is defined by P1,P2,P3, there are three possibilities:
 1) P1=P,P2=P,P3=P
 2) P1=P,P2=P,P3=P+1
 3) P1=P,P2=P+1,P3=P+1
 
 However 3) cannot happen. It can be proved by induction.
 We can observe it from below example too:
 S(1)%3 = 1 (case #2)
 S(2)%3 = (1+2)%3 = 0 (case #1)
 S(3)%3 = (0+3)%3 = 0 (case #1)
 S(4)%3 = (0+4)%3 = 1 (case #2)
 ...

 If S(N)%3=0, we need to use total exactly 3*P balls, where P=S(N)/3
 Therefore res=A/P=A/(S(N)/3)
 
 We show S(N)%3=1 case in following.
 
 Suppose e = (B-A)+(C-A). This is extra ball we want to use to fill +1 part out of P3=P+1.
 
 A: **|**|**|
 B: **|**|**|*
 C: **|**|**|****
             ^ e = 5 in this example
    ^ P=2 in this example

 Ideally we can use entire `e` to build A/P triangles. It's possible if A/P<=e.
 If it's impossible, we try to build x triangles. Then following equation will be satisfied:
 
 (A-P*x) + (B-P*x) + (C-P*x) = x
 <=> x = (A+B+C)/(3*P+1)
 
 This is showing that we need `x` extra balls addition to 3*P*x.
 `e` is not enough to fill it. We try to pull it from A, B and C.
 
 In summary:
 
 res = A/P             if A/P <= e
       (A+B+C)/(3*P+1) Otherwise
 
 Or we can simply use binary search in S(N)%3=1 case.
 
 Key:
  - Figure out trick of (mod 3) in S(N)=N*(N+1)/2
  - Analyze mathematically or notice binary search
 
 Summary:
  - Tons of bugs in my analysis and implementation
   - mistake in formula building
   - overflow
  - I should use more paper to sort out idea when solving this kind of analysis intensive problem
  - Strategy to start from ideal case and reduce to general case worked in this case too
 
 */

class FoxPaintingBalls {
public:
  long long theMax(long long A, long long B, long long C, int N) {
    LL M=1LL*N*(N+1)/2;
    if(A>B) swap(A,B);
    if(B>C) swap(B,C);
    if(A>B) swap(A,B);
    assert(A<=B&&B<=C);
    if(M%3==0) return A/(M/3LL);
    
    int MM=(int)(M%3LL);
    LL P=M/3;
    if(P==0) return A+B+C;
    dump3(M,MM,P);

    LL good=0,bad=A+B+C;
    while(abs(good-bad)>1) {
      LL mid=good+(bad-good)/2LL;
      if(mid<=A/P&&A+B+C-3*P*mid>=mid) good=mid;
      else bad=mid;
    }
    return good;
  }
};

class FoxPaintingBalls_org {
  public:
  long long theMax(long long A, long long B, long long C, int N) {
    LL M=1LL*N*(N+1)/2;
    if(A>B) swap(A,B);
    if(B>C) swap(B,C);
    if(A>B) swap(A,B);
    assert(A<=B&&B<=C);
    if(M%3==0) return A/(M/3LL);
    
    int MM=(int)(M%3LL);
    LL P=M/3;
    if(P==0) return A+B+C;
    dump3(M,MM,P);
    
    assert(MM==1);
    
    LL e=B-A+C-A;
    dump4(A,B,C,e);
    if(e==0) return (A+B+C)/(3*P+1);
    
    dump3(e,A/P,P>=A/P);
    if(e>=A/P) return A/P;
    
    return (A+B+C)/(3*P+1);
  }
};

// CUT begin
ifstream data("FoxPaintingBalls.sample");

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

bool do_test(long long R, long long G, long long B, int N, long long __expected) {
    time_t startClock = clock();
    FoxPaintingBalls *instance = new FoxPaintingBalls();
    long long __result = instance->theMax(R, G, B, N);
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
        long long R;
        from_stream(R);
        long long G;
        from_stream(G);
        long long B;
        from_stream(B);
        int N;
        from_stream(N);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(R, G, B, N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515776073;
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
        cout << "FoxPaintingBalls (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
