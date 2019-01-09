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
 
 3/26/2018
 
 9:09-9:48 analysis. dp?
 10:00 re-analyze (res is upper-bounded by 2 (!=50))
 10:07 submit (200.05 pt)
 10:10 resubmit
 10:51-10:53 fix a bug when L is coming last and ACC :(
 
 I was totally messed up due to wrong analysis 👎👎👎👎
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/Member+SRM+503
  - http://d.hatena.ne.jp/kusano_prog/20110416/1302987086
  - https://topcoder.g.hatena.ne.jp/kita_yuta/20110420/1303306268
  - http://kg86.hatenablog.com/entry/20130529/1369842289
  - http://expnotes9.blog.fc2.com/blog-date-201401.html
  - http://peryaudo.hatenablog.com/entry/20110417/1303048038
 
 DP solution: https://community.topcoder.com/stat?c=problem_solution&rm=307795&rd=14432&pm=11204&cr=13351270

 22:15-22:25 Add solution with min and max
 
 The most important observation is that result is at most 2.
 If we are solving by greedy, finding this is mandatory. Otherwise, dp is the only option.
 In my case it took 50 mins to find it. This is the reason that I could not do well.
 It's obvious that result is at most 50. However I couldn't go further quickly 😞
 The reason is that the last sample #3 lead me wrong assumption.
 What I should be able to do was confirming more LR pairs case.
 We cannot say that just two intervals are enough. I should have confirmed one more larger case.
 It's important to look into such a case to ensure that my analysis is correct in terms of induction.
 
 Key:
  - Result is at most 2
 
 Summary:
  - It took almost one hour to figure out that result is at most 2 👎👎👎👎
  - From sample #3 I misunderstood that number of L affects how we can assign R 👎👎👎👎👎👎👎👎
  - Pay more attention to samples if the result value is very small
  - Sample may be intentionally weak. Play around bigger samples!!!!!!!!!!!!!!
 
 */

class ToastXToast {
public:
  int bake(vector<int> L, vector<int> R) {
    int minL=*min_element(L.begin(),L.end()),maxL=*max_element(L.begin(),L.end());
    int minR=*min_element(R.begin(),R.end()),maxR=*max_element(R.begin(),R.end());
    
    if(minL>minR) return -1;
    if(maxL>maxR) return -1;
    if(maxL<minR) return 1;
    return 2;
  }
};

class ToastXToast_org {
  public:
  int bake(vector<int> L, vector<int> R) {
    vector<II> X;
    REP(i,SZ(L)) X.emplace_back(L[i],-1);
    REP(i,SZ(R)) X.emplace_back(R[i],1);
    sort(X.begin(),X.end());
    if(X.front().second==1) return -1;
    if(X.back().second==-1) return -1;
    int st=0,i=0;
    int N=SZ(X);
    while(i<N) {
      if(st==0&&X[i].second==1) st=1;
      if(st==1&&X[i].second==-1) st=2;
      if(st==2&&X[i].second==1) st=3;
      ++i;
    }
//    REP(i,N) cout <<(X[i].second==1?'R':'L');
//    cout <<endl;
//    dump(st);
    if(st==2||st==0) return -1;
    return st==1?1:2;
  }
};

// CUT begin
ifstream data("ToastXToast.sample");

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

bool do_test(vector<int> undertoasted, vector<int> overtoasted, int __expected) {
    time_t startClock = clock();
    ToastXToast *instance = new ToastXToast();
    int __result = instance->bake(undertoasted, overtoasted);
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
        vector<int> undertoasted;
        from_stream(undertoasted);
        vector<int> overtoasted;
        from_stream(overtoasted);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(undertoasted, overtoasted, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522080564;
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
        cout << "ToastXToast (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
