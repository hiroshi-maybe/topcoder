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
 
 3/14/2018
 
 9:09-9:44 analysis
 10:12 misunderstanding condition 3. f*ck.
 10:13-10:31 (181.98 pt), 1WA
 10:32-11:00 pause
 11:15-11:25 implement and ACC
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+512
  - http://d.hatena.ne.jp/kusano_prog/20111015/1318674447
    - incredibly simple and beautiful ✨
  - http://mayokoex.hatenablog.com/entry/2015/07/03/173826
  - https://chngng.blogspot.jp/2015/05/srm-512-div1-easy-mysteriousrestaurant.html
  - http://hos0lyric.blog89.fc2.com/blog-entry-43.html
  - http://purple-jwl.hatenablog.com/entry/20130321/1363874405
 
 Editorial's description of conversion of optimization problem to decision problem is interesting.
 Well if there are N possible result, we can solve optimization problem in O(N*∑ { T(x) : x∈X, |X|=N })
 This is very generic framework.
 
 23:24-23:31 add simpler solution
 
 Key
  - res is upper-bounded by SZ(P)
  - Skip is not allowed
  - One dish per day (0-6). And dish can be chosen independently.
 
 Summary:
  - I completely misunderstood the condition 3 and got confused
  - Idea to fix day was straightforward though, my analysis was messed up due to misunderstanding of condition 3.
 
 */

class MysteriousRestaurant {
public:
  int f(char c) {
    if(isdigit(c)) return c-'0';
    if(islower(c)) return 36+c-'a';
    return 10+c-'A';
  }
  int maxDays(vector<string> P, int B) {
    int N=SZ(P),M=SZ(P[0]);
    for(int d=N; d>=0; --d) {
      vector<VI> X(7, VI(M, 0));
      REP(i,d) REP(j,M) X[i%7][j]+=f(P[i][j]);
      int sum=0;
      REP(i,7) sum += *min_element(X[i].begin(),X[i].end());
      if(sum<=B) return d;
    }
    return 0;
  }
};

class MysteriousRestaurant_org {
  public:
  int f(char c) {
    if(isdigit(c)) return c-'0';
    if(islower(c)) return 36+c-'a';
    return 10+c-'A';
  }
  int maxDays(vector<string> P, int B) {
    int N=SZ(P),M=SZ(P[0]);
    const int Inf=1e5;
    int res=0;
    REPE(d,N) {
      int cost=B;
//      dump(d);
      REP(i,7) {
        int mincost=Inf;
        int W=(d-i+6)/7;
        REP(j,M) {
          int x=0;
          REP(w,W) x+=f(P[i+7*w][j]);
          SMIN(mincost,x);
        }
        cost-=mincost;
      }
//      dump2(d,cost);
      if(cost>=0) res=d;
      else break;
    }
    return res;
  }
};

// CUT begin
ifstream data("MysteriousRestaurant.sample");

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

bool do_test(vector<string> prices, int budget, int __expected) {
    time_t startClock = clock();
    MysteriousRestaurant *instance = new MysteriousRestaurant();
    int __result = instance->maxDays(prices, budget);
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
        vector<string> prices;
        from_stream(prices);
        int budget;
        from_stream(budget);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(prices, budget, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521043767;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 512 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MysteriousRestaurant (512 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
