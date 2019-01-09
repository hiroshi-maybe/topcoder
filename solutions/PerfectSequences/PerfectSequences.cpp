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
 
 3/27/2018
 
 8:34-9:19 change largest is optimal?
 9:20-9:31 implement and submit (201.47 pt). However WA. Changing largest is not optimal 👎
 10:30-10:38 bug fix and re-submit. However WA. prod>sum is not necessary condition 👎👎
 10:39-10:44 bug fix and re-submit. However WA. zeros condition is not necessary 👎👎👎👎
 10:45 ACC after 3WA 👎👎👎👎👎👎👎👎
 
 How to represent "change" one of elements is the key.
 The most straightforward procedure is replacing one element with arbitrary non-negative integer.
 Since we can change only one element. We can brute-force at most 50 times.
 Probably I am the only person who went through stupid idea to make a formula like sum+x=prod/a*(a+x)
 The crazy idea came out of SRM 507 div2 hard CubeRoll where solution was analyzing (x+h)^2-x^2 which focuses on the difference.

 Four stupid things that I did 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
  1. Formula which resolved nothing sum+x=prod/a*(a+x)
  2. Unnecessary analysis of `0`, which fell in a pitfall of corner case
  3. New value is less than original value
  4. Misunderstanding that changing the largest value is optimal

 1. formula sum+x=prod/a*(a+x)
 
 Unlike SRM 507 CubeRoll, we don't have specific benefit from this because anyway original `a` is gone.
 We can select any new value. Below formula is simple enough:
 
 sum(i) + x = prod(i) * x
 
 Note that sum(i) and prod(i) are summation and multiplication of original numbers except element at i-th index.
 Easily condition that x should hold can be reduced from this.
 Also we can try all `i` in O(N) separatedly.
 
 2. Unnecessary analysis of `0`
 
 If 0 is part of production, sum must be all zero. However that's not the case if there is only one `0` in the sequence.
 In such a case, `0` can be replaced.
 
 3. New value is less than original value
 
 New value should not be equal to original value. However there is no need to be less than original value
 Probably this misunderstanding came from samples. Very stupid.
 
    sum(i) + x = prod(i) * x
 => x = sum(i)/(prod(i)-1)
 
 There is no upper bound in `x` 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 Don't do such assumption without concrete proof 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎

 4. Misunderstanding that changing the largest value is optimal
 
 Counter example: [1,1,1,1,1,1,2] => one of `1` should be `7`
 
 This came from crazy misunderstanding of #3. Sigh 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 
 Another reason that it took so much time is potential overflow in multiplication.
 I tried to find if it's necessary to compute result without actually multiplying numbers.
 As part of it, I tried to find a sample which returns YES even if multiplication overflows.
 
 It's impossible to find an input which returns YES even though overflow in production happens.
 If we had below formula, it's obvious that such case does not exist.

  x = sum(i)/(prod(i)-1)
 
 sum(i)<5e10 from constraint. x is upper-bounded by 5e10 as well.
 If prod(i)-1>sum(i), it's obvious that such integer `x` does not exist.
 
 So it was much easier for me to understand the upper-bound if I got this formula earlier.
 Then I didn't need to spend a lot of time... The formula is the key.
 
 Editorials:
  - http://d.hatena.ne.jp/kusano_prog/20110528/1306586411
   - Interesting. This this code is leaving overflow because it doesn't give false positive.
  - http://topcoder.g.hatena.ne.jp/firewood/20110510/1305044277
  - http://topcoder.g.hatena.ne.jp/kuidaored/20110505/1304605599
  - https://topcoder.g.hatena.ne.jp/kita_yuta/20110504/1304506856
  - http://tech.fuqinho.net/?p=48
 
 Summary:
  - There are a lot of confusion. I'm always confused about math problem. I'm too stupid. 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
  - Replacement -> simply put `x` for it
  - Variable is just one value. We should be able to build an equation.
 
 */
class PerfectSequences {
  public:
  string yes="Yes",no="No";
  bool f(vector<int> S, int org) {
    dumpAR(S);
    LL sum=accumulate(S.begin(),S.end(),0LL);
    LL prod=1LL;
    dump(sum);
    FORR(n,S) {
      prod*=1LL*n;
      if(prod>5e10) return false;
    }
    dump2(sum,prod);
    if(prod==1LL) return false;
    if(sum%(prod-1LL)!=0) return false;
    LL x=sum/(prod-1);
    
    dump2(x,0<=x&&x!=org);
    
    return 0<=x&&x!=org;
  }
  string fixIt(vector<int> S) {
//    int zeros=count(S.begin(),S.end(),0);
    int N=SZ(S);
    if(N==1) return yes;
//    if(zeros) return zeros==N-1?yes:no;
    
    bool ok=false;
    REP(i,N) {
      VI SS=S;
      SS.erase(SS.begin()+i);
      ok|=f(SS,*(S.begin()+i));
    }
    return ok?yes:no;
  }
};

// CUT begin
ifstream data("PerfectSequences.sample");

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

bool do_test(vector<int> seq, string __expected) {
    time_t startClock = clock();
    PerfectSequences *instance = new PerfectSequences();
    string __result = instance->fixIt(seq);
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
        vector<int> seq;
        from_stream(seq);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(seq, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522164878;
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
        cout << "PerfectSequences (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
