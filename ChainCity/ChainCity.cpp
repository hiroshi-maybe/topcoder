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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/12/2017
 
 SRM 718
 
 21:57-22:32 rough idea of greedy strategy
 22:53 give up
 
 8/15/2017
 
 18:55-19:30 retried and give up again
 
 19:30-20:00 read editorials
  - https://www.topcoder.com/blog/single-round-match-718-editorials/
  - http://kmjp.hatenablog.jp/entry/2017/07/14/0930
 
 K>=2 that means at least we need to put two transporters. Warp always shortens distance (maximum distance in any two points). There is no strictly better way to get smaller distance without going through transporter. Note that traveler meets it though, warp may or may not happen in longest distance x which represents diameter x.
 Suppose x/2 is `max { d(i) : distance to closest transporter from P[i] }`.
 Then diameter = x. There are two cases for distance x and y where x>y:
    1) d(T1,P[i])=x, d(T1,P[j])=x, d(T2,P[k])=y, d(T2,P[l])=y => diameter = 2*x = d(P[i],P[j]) no use of transporter
    2) d(T1,P[i])=x, d(T1,P[j])=y, d(T2,P[k])=x, d(T2,P[l])=y => diameter = 2*x = d(P[i],P[k]) using transporter
 In case 1, warp does not happen in x path. In case 2, warp happens.
 
 So in either case, distance to closest transporter from each point matters. It determines diameter. Smaller x => more transporters. Thus binary search comes up.
 
 22:51-23:12 add solution (no bug in implementation 👍)

 Submit solution:
 - https://community.topcoder.com/stat?c=problem_solution&rm=330357&rd=16933&pm=14643&cr=40168949
  - almost same as my implementation
 
 Key:
  - diameter is determined by distance from each point to its closest trasnporter
  - we always put more than one transporter. we don't need to be worried about distance without transporter
    - we can always focus on distance to closest warp regardless of warp
  - x is larger => distance to transporter is larger => less transporters
 
 Summary:
  - to understand two points are keys. I couldn't figure out them 👎
   - always valid to focus on distance to closest transporter
   - more transporter => transporter is closer => diameter is smaller
  - no bug in implementation after reading editorial explanation 👍
 
 */
class ChainCity {
  public:
  VI D;
  VI cum;
  int K;
  int findMin(vector<int> D, int _K) {
    K=_K;
    int N=SZ(D);
    if(K==N+1) return 0;
    
    cum=VI(N+1,0);
    REP(i,N) cum[i+1]=cum[i]+D[i];
    int good=INT_MAX, bad=0;
    
    while(abs(good-bad)>1) {
      int mid = bad+(good-bad)/2;
      if(ok(mid)) good=mid;
      else bad=mid;
    }
    
    return good;
  }
  
  bool ok(int d) {
    int cnt=1;
    int base=0;
    
    REP(i,SZ(cum)) {
      if(cum[i]-cum[base]>d) {
        ++cnt;
        base=i;
      }
    }
    return cnt<=K;
  }
};

// CUT begin
ifstream data("ChainCity.sample");

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

bool do_test(vector<int> dist, int k, int __expected) {
    time_t startClock = clock();
    ChainCity *instance = new ChainCity();
    int __result = instance->findMin(dist, k);
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
        vector<int> dist;
        from_stream(dist);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(dist, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499921831;
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
        cout << "ChainCity (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
