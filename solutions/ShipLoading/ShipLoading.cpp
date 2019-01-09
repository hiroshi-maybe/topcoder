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
 
 8/31/2018
 
 20:40-21:04 AC (158.90 pt)
 
 Editorials:
  - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm415
  - http://topcoder.g.hatena.ne.jp/nitoyon/20081012/1223809946
  - http://area.hateblo.jp/entry/2013/04/06/211847
 
 O(M*N) solution or O(N*lg 10^6) time is more efficient and smart.
 
 @rng_58's solution is not even using sort. I tried to understand it. However I could not.
 
 */

const int INF=1e5;

class ShipLoading {
public:
  int minimumTime(vector<int> W, vector<string> B) {
    VI A;
    int n=0;
    REP(i,SZ(B)) {
      string s=B[i];
      REP(j,SZ(s)) {
        if(s[j]==' ') A.push_back(n),n=0;
        else n=10*n+s[j]-'0';
      }
    }
    if(n)A.push_back(n);
    
    sort(A.rbegin(),A.rend());
    int N=SZ(A),M=SZ(W);
    VI cnt(M,0);
    REP(i,N) {
      int w=A[i];
      int jj=-1;
      int ub=INF;
      REP(j,M) if(W[j]>=w&&cnt[j]<ub) {
        jj=j,ub=cnt[j];
      }
      if(jj==-1) return -1;
      cnt[jj]++;
    }
    return *max_element(cnt.begin(),cnt.end());
  }
};

// O(M^2*N) time
// 8:40-21:04 AC (158.90 pt)
class ShipLoading_org {
  public:
  int minimumTime(vector<int> W, vector<string> B) {
    VI A;
    int n=0;
    REP(i,SZ(B)) {
      string s=B[i];
      REP(j,SZ(s)) {
        if(s[j]==' ') A.push_back(n),n=0;
        else n=10*n+s[j]-'0';
      }
    }
    if(n) A.push_back(n);
    sort(W.rbegin(),W.rend()),sort(A.rbegin(),A.rend());
    if(SZ(A)==0) return 0;
    if(W.front()<A.front()) return -1;
    int N=SZ(W),M=SZ(A);
    VI viz(M,0);
    int res=0;
    while(true) {
      int cur=0;
      bool added=false;
      REP(i,M) if(!viz[i]) {
        FOR(j,cur,N) if(W[j]>=A[i]) {
          ++cur;
          viz[i]=true;
          added=true;
          break;
        }
      }
      if(!added) break;
      ++res;
    }
    return res;
  }
};

// CUT begin
ifstream data("ShipLoading.sample");

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

bool do_test(vector<int> cranes, vector<string> boxes, int __expected) {
    time_t startClock = clock();
    ShipLoading *instance = new ShipLoading();
    int __result = instance->minimumTime(cranes, boxes);
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
        vector<int> cranes;
        from_stream(cranes);
        vector<string> boxes;
        from_stream(boxes);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cranes, boxes, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535773156;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ShipLoading (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
