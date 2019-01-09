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
 
 10/10/2018 SRM 739
 
 9:05-9:15 time is up
 
 10/17/2018
 
 21:20-22:40 tried to solve by myself. However gave up.
 
 res = min( max(f(p[0],S[0]),f(p[1],S[1]),..,f(p[M-1],S[M-1]) )
 
 f(p[i],S[i]) = p[i]+∑{A[j]:j∈S[i]} if S[i]!=𝜙
 
 minimal of maximum => binary search?
 
 I want to make auxiliary problem if applying binary search
 
 Try induction to discover new knowledge or hypothesis
 
 I built binary search by greedily assigning larger A[i] to further P[i].
 However sample #2 doesn't pass on the algorithm because some cow may eat and move and eat.
 Problem condition allows it.
 
 Sample 2
 
 c0: 2+1(0 wait, 1 eat at p0)+1+3(0 wait 3 eat at p1) = 7
 c1: 2+3(1 wait, 2 eat at p0)+2(0 wait 2 eat at p1) = 7
 c2: 2+7(3 wait, 4 eat at p0) = 9
 
 res = 9
 
 22:40-23:00 read editorial
 
 10/18/2018
 
 17:30-19:10 read editorial
 19:10-19:22 implement and got AC
 
 https://www.topcoder.com/blog/single-round-match-739-editorials/
 http://kmjp.hatenablog.jp/entry/2018/10/13/1000
 https://twitter.com/uwitenpen/status/1050064048824307712
 https://twitter.com/osrehun/status/1050065016219557888
 
 Based on monotinicity of consuming time, we solve by binary search.
 
 Let's focus on how to solve decision problem to figure out if we can achieve time `t` to feed all the cows.
 If `t` is fixed, we know that each barn can supply t-P[i] unit of food.
 However we have not dropped move time completely yet because cows may have food at `x` and move to `y` and have more food.
 
 Suppose cow has appetite `A`. The cow has food at both barns position `x` and position `y`.
 Possible supply of `x` and `y` are `t-x` and `t-y`.
 Note that `x` does not have enough barn to feed the cow. Thus t-x<A.
 Total time that cow spends can be computed as below:
 
   x + e + (y-x) + A-e, e=t-x which is food that cow had at `x`.
   ^move    ^move
 = y+A
 
 Then `y+A`<=t should hold so that cow can be fed within `t` time.
 That means there should exist `y` s.t. A<=t-y to achieve `t` time.
 This is the same even if cow eats in more than two places.
 If cow finished eating at P[i], A<=t-P[i] must hold.
 
 For following cows, we can reduce already consumed unit of food from supply.
 Now we can keep solving new subproblem repeatedly.
 
 From this observation, we can assign cow with more appetite first to satisfy A<=t-P[i].
 If more cows consumes supply, we have less chance to satisfy A<=t-P[i], because t-P[i] is larger for closer barns.
 
 Key:
  - More time we have, more likely cows appetite can be satisfied. There is monotinicity => binary search works
   - Problem can be reduced to decision problem (auxiliary problem 1)
   - by putting upper-bound of time in decision problem, upper-bound of served feed is determined at each barn which could serve unlimited amount of food
  - In decision problem (upper-bound of time `t`), moving time can be dropped by reducing to another problem by formula transformation (auxiliary problem 2)
   - If `t` is fixed, possible amount of feeding service is determined at P[i] by `t-P[i]`
   - If a cow has enough time to satisfy its appetite, there should exist `i` s.t. A<=t-P[i]
    - Solve a part of problem, where one cow can finish appetite `A` withint `t` and research condition
    - greedy strategy is derived from this lemma
 
 Summary:
  - Two phase problem reduction (two auxiliary problems) needs to be made, which is pretty creative.
  - My guess to assign cows with more appetite to closer barn was correct. However I couldn't extend it to partial feed
  - How to solve it?
   - Try to remove complication one by one. Fix something and see if problem can be simplified
   - Do you know similar problem with similar unknown (minimize maxmized values)? => binary search
   - Can you solve part of the problem? Can you solve a special problem? Isn't it actually auxiliary problem?
    => Solve a problem with single cow and figure out reduced simplified condition
 
 */
class HungryCowsMedium {
public:
  VI A,P;
  LL ok(LL T) {
    vector<LL> PP;
    REP(i,SZ(P)) if(T-P[i]>0) PP.push_back(T-P[i]);
    int M=SZ(PP);
    FORR(aa,A) {
      LL a=aa;
      bool okok=false;
      REP(i,M) if(PP[i]>=a) okok=true;
      if(!okok) return false;
      REP(i,M) {
        LL x=min(PP[i],a);
        PP[i]-=x,a-=x;
        if(a==0) break;
      }
    }
    return true;
  }
  long long getWellFedTime(vector<int> A, vector<int> P) {
    sort(A.rbegin(),A.rend());
    sort(P.begin(),P.end());
    this->A=A,this->P=P;
    LL good=5e11, bad=0;
    while(abs(good-bad)>1) {
      LL mid=(good+bad)/2LL;
      (ok(mid)?good:bad)=mid;
    }
    return good;
  }
};

// sample #2 doesn't pass
class HungryCowsMedium_wrong {
  public:
  VI A,P;
  LL ok(LL T) {
    int M=SZ(P),N=SZ(A);
    int j=0;
    REP(i,M) {
      LL cur=P[i];
      while(j<N&&cur+A[j]<=T) cur+=A[j++];
    }
    return j>=N;
  }
  long long getWellFedTime(vector<int> A, vector<int> P) {
    sort(A.begin(),A.end());
    sort(P.rbegin(),P.rend());
    this->A=A,this->P=P;
    LL good=5e11, bad=0;
    while(abs(good-bad)>1) {
      LL mid=(good+bad)/2LL;
      (ok(mid)?good:bad)=mid;
    }
    return good;
  }
};

// CUT begin
ifstream data("HungryCowsMedium.sample");

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

bool do_test(vector<int> cowAppetites, vector<int> barnPositions, long long __expected) {
    time_t startClock = clock();
    HungryCowsMedium *instance = new HungryCowsMedium();
    long long __result = instance->getWellFedTime(cowAppetites, barnPositions);
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
        vector<int> cowAppetites;
        from_stream(cowAppetites);
        vector<int> barnPositions;
        from_stream(barnPositions);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cowAppetites, barnPositions, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539187973;
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
        cout << "HungryCowsMedium (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
