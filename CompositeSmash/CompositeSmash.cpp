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
 
 3/5/2018
 
 14:37-15:00 submit (324.51 pt), but I found a bug
 15:10-15:13 resubmit and ACC
 
 If T is prime factor of N, obviously keep smashing reaches T.
 Another case is T=p^2 when N=p^k, k>=2, p is prime number
 
 We eventually get prime number.
 If there is only one prime factor..
 Before dividing into p and p, we should have a ball which is p^2.
 Thus we always get p^2 as well.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+517
    - dp, greedy and brute-force
  - http://d.hatena.ne.jp/kusano_prog/20110910/1315680440
    - dp
  - http://mainly-coding.blogspot.com/2011/09/topcoder-srm-517.html
    - dp
  - https://topcoder.g.hatena.ne.jp/jackpersel/20110911/1315729474
    - brute-force
  - https://chngng.blogspot.com/2013/10/srm-517-div1-easy-compositesmash.html
    - brute-force
  - http://mayokoex.hatenablog.com/entry/2015/07/28/085405
    - greedy
  - https://topcoder.g.hatena.ne.jp/firewood/20111015/1318653741
    - greedy
 
 */
class CompositeSmash {
  public:
  string yes="Yes",no="No";
  string thePossible(int N, int T) {
    if(N==T) return yes;
    MAPII M;
    for(int p=2; p*p<=N; ++p) {
      while(N%p==0) M[p]++,N/=p;
    }
    if(N>1) M[N]++;
    
    // prime
    if(M.count(T)) return yes;
    if(SZ(M)==1) FORR(kvp,M) {
      int p=kvp.first,cnt=kvp.second;
//      dump4(p,cnt,p*p,T==p*p);
      if(cnt>=2&&T==p*p) return yes;
    }
    
    return no;
  }
};

// CUT begin
ifstream data("CompositeSmash.sample");

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

bool do_test(int N, int target, string __expected) {
    time_t startClock = clock();
    CompositeSmash *instance = new CompositeSmash();
    string __result = instance->thePossible(N, target);
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
        int N;
        from_stream(N);
        int target;
        from_stream(target);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, target, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520289399;
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
        cout << "CompositeSmash (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
