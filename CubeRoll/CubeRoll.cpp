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
 
 3/21/2018
 
 9:25-10:20 give up
 
 abs(G-S) should be represented as below:
 
 a^2
 a^2+b^2, a^2-b^2
 a^2+b^2+c^2, a^2+b^2-c^2
 a^2+b^2+c^2+d^2, a^2+b^2+c^2-d^2, a^2+b^2-c^2-d^2
 
 How many squares do we need? It's the pain point to solve this problem.
 I tried to show it's at most 2 first. However looks like 6 needs 3 squares.
 I tried to show it's at most 3. However I couldn't prove it...
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+507
  - http://topcoder.g.hatena.ne.jp/ir5/20110529
  - http://kmjp.hatenablog.jp/entry/2014/02/17/0930
  - http://d.hatena.ne.jp/kusano_prog/20110528/1306615359
  - http://topcoder.g.hatena.ne.jp/firewood/20110529/1306687970
  - http://area.hateblo.jp/entry/2013/08/19/011852
 
 Lagrange's four-square theorem
  - https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem
 
 3/22/2018
 
 18:00-19:00, 21:30-22:40 describe proof of this solution.
 
 Let's try to solve simple problem. Ignore hole condition and try to solve steps to reach from S to G.
 
 # Analysis of square numbers
 
 Define ∆ = abs(G-S)
 
 1) a^2
  check if sqrt(G-S) is integer, O(√N)
 
 2) a^2+b^2
  check if ∆-a^2=b^2, O(√N)
  test int(sqrt(∆-a^2))*int(sqrt(∆-a^2))==∆-a^2
 
 3) a^2-b^2
 
  a^2-b^2 = (a+b)*(a-b)
  This does not seem to be easy to find something useful.
  Another form of difference of squares is (x+k)^2 - x^2
  This is the most important key to solve this problem 🗝

  (x+k)^2 - x^2 = k*(2x+k)
 
  We can select arbitrary pair of (x, k)
  If k is negative, it's same as swapping (x+k) and x.
  If k=0, ∆=0. So no need to discuss about two steps.
  Thus without losing generality, we can say k>=1.
 
  Let's look at from small numbers.
 
  i) k=1
 
  If we use steps like (x+1)^2-x^2, ∆ = 2*x+1
  This means that *any* ∆ of odd number is achievable by two steps as shown below:

  5 = 9-4 = 3^2-2^2
  7 = 16-9 = 4^2-3^2
 
  ii) k=2
 
  If we use steps like (x+2)^2-x^2, ∆ = 4*(x+1)
  This means *any* ∆ which is multiple of 4 can be reached by two steps.
 
  8 = 9-1 = 3^2-1^2
 
  From analysis of i) and ii), we showed that ∆ of odd numbers (4*p+1, 4*p+3), multiple of 4 (4*p) is reachable in at most two steps.
  Missing case is 4*p+2. Is it possible to represent 4*p+2 with k*(2x+k)?
 
  Since 4*p+2 = 2*(2*p+1), both can be represented by compound of at least two numbers.
  We can compare those pairs.
 
  a) what if 2=k and 2*p+1=2*x+k?
 
  Since k=2, 2*x+k = 2*x+2 = 2*(x+1) != 2*p+1
  Thus this case does not happen.
 
  b) 2*p+1=k, 2*x+k=2
 
  2*x+k=2 => 2*x+2*p+1=2 => 2*(x+p) = 1
  x and p should be natural number. It turns out this case does not happen either.
 
  From analysis of a) and b), 4*k+2 cannot be represented by difference of square numbers.
  However, we know that any odd number can be shown by two steps.
  even number + 1 = odd. So we are sure that other even number can be represented by three squares.
 
 4) a^2-b^2+c^2
 
  Any even number which is not multiple of 4 can be represented by a^2-b^2+1^2.
  Now our analysis is sufficient.
 
 # Analysis of holes
 
 Now we can finally look into holes.
 
 1) There is a hole between S and G
 
 Obviously res = -1
 
 2) Both S and G are surrounded by holes
 
 Distance between holes is upper-bounded by 10^5.
 We can do BFS from S to G. V<=10^5. E<=10^5*√10^5≈3*10^7
 
 3) Either left or right of S and G is infinitely open (no holes)
 
 We can apply analysis of square numbers in previous section.
 
 22:41-23:11 add solution
 
 # Other comment
 
 Analysis of (x+k)^2 - x^2 is the most creative part of this problem.
 
 I feel like (x+k)^2 - x^2 is hard to come up with me.
 Another approach is transforming a^2-b^2.
 
 a^b-b^2 = (a+b)*(a-b)
 
 This formula is not easy to figure out what multiple is possible.
 Let's put a-b = x and represent a+b with x.
 
 a^b-b^2 = (a+b)*(a-b) = x*(2*b+x)

 This formula is same as the one reduced from (x+k)^2 - x^2.
 We can do the same analysis by putting x=1,2,..
 
 Official editorial is showing it based on modular arithmetic.
 
 a^2-b^2 ≡ d (mod 4)
 
 `a` and `b` are "congruent modulo 4". Then a^2 (mod 4) ∈ {0,1}, -b^2 (mod 4) ∈ {0,3}.
 a^2 - b^2 (mod 4) ∈ {0,1,3}
 Thus difference of squares can take only 4*k, 4*k+1, 4*k+3
 
 Key:
  - It's possible to brute-force one step and two steps of addition of squares
  - Analyze difference of squares in form of (x+k)^2 - x^2
   - I've seen (a+b)*(a-b) pattern though, this is a new pattern
  - Suffiency can be analyzed by looking at modular arithmetic of 4
  - We know property of odd number. Even number can be shown as odd number + 1. It turns out that any even number can be represented by three squares.
 
 Summary:
  - Approach to show at most how many squares are needed was good. It's exactly pain point of this problem 👍
  - However I didn't have an idea to look at parity or multiple of 4 😞
  - This was tough but impressive problem. I always miss an idea to look at math property in terms of parity of multiple of some small number
  - Analyzing Difference of square numbers was hard. Math analysis is always tough for me
   - Analysis of squares
   - Analysis based on parity or multiple of some numbers
  - I guess missing approach for me is representing formula by multiple of something. I need to train this more.
 
 */

class CubeRoll {
  public:
  int f(int d) {
    if(d==0) return 0;
    int sqr=(int)sqrt(d);
//    dump4(d,sqr,sqr*sqr,sqr*sqr==d);
    if(sqr*sqr==d) return 1;
    for(int a=1; a*a<d; ++a) {
      int bb=d-a*a;
      int b=(int)sqrt(bb);
      if(b*b==bb) return 2;
    }
    if(d%2==1) return 2;
    if(d%4==0) return 2;
    return 3;
  }
  int dist[100005];
  int g(int S, int G, int L, int R) {
//    dump4(S,G,L,R);
    const int Inf=1e6;
    FORE(x,L,R) dist[x]=Inf;
    queue<II> Q; Q.emplace(0,S);
    while(SZ(Q)) {
      auto p=Q.front(); Q.pop();
      int d=p.first,x=p.second;
//      dump2(d,x);
      for(int sign=-1; sign<=1; sign+=2) {
        for(int a=1; L<x+sign*a*a&&x+sign*a*a<R; ++a) {
          int xx=x+sign*a*a;
          int dd=d+1;
          if(dd<dist[xx]) {
            dist[xx]=dd;
            Q.emplace(dd,xx);
          }
        }
      }
    }
    return dist[G];
  }
  int getMinimumSteps(int S, int G, vector<int> X) {
    if(G<S) swap(S,G);
    int si=-1,gi=-1;
    sort(X.begin(),X.end());
    int N=SZ(X);
    REP(i,N) {
      if(X[i]<S) si=i;
      if(X[i]<G) gi=i;
    }
//    dump2(si,gi);
    if(si!=gi) return -1;
    if(si==-1||si==N-1) return f(G-S);
    return g(S,G,X[si],X[si+1]);
  }
};

// CUT begin
ifstream data("CubeRoll.sample");

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

bool do_test(int initPos, int goalPos, vector<int> holePos, int __expected) {
    time_t startClock = clock();
    CubeRoll *instance = new CubeRoll();
    int __result = instance->getMinimumSteps(initPos, goalPos, holePos);
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
        int initPos;
        from_stream(initPos);
        int goalPos;
        from_stream(goalPos);
        vector<int> holePos;
        from_stream(holePos);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(initPos, goalPos, holePos, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521649541;
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
        cout << "CubeRoll (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
