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
 
 2/4/2018
 
 18:17-18:26 analysis
 18:27-18:33 implement and ACC (390.60 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+539
  - http://d.hatena.ne.jp/anta1/20120815/1345026885
  - http://mayokoex.hatenablog.com/entry/2016/04/05/000916
  - http://kg86.hatenablog.com/entry/20130418/1366292316
  - http://hamko.hatenadiary.jp/entry/2017/03/03/175057
  - http://rkx1209.hatenablog.com/entry/2012/11/02/003117
  - http://lepton.hatenablog.jp/entry/20120405/1333605737
 
 23:15-23:25 add solution with greedy interval merge
 
 Key:
  - Do imos after summing interval ranges
 
 Summary:
  - I solved quickly even though only 7.6(%) in div2/59(%) in div1 contesntants solved it 👍
 
 */

// Greedy (merge interval), O(N*2^N) time
class Over9000Rocks {
public:
  int countPossibilities(vector<int> L, vector<int> U) {
    int N=SZ(L);
    vector<II> xs;
    REP(mask,1<<N) if(mask) {
      int l=0,r=0;
      REP(i,N) if(mask&(1<<i)) l+=L[i],r+=U[i];
      l=max(l,9001);
//      dump2(l,r);
      if(r<l) continue;
      xs.emplace_back(l,r);
    }
    sort(xs.begin(),xs.end());
    int res=0,l=-1,r=-2;
    FORR(p,xs) {
      if(r<p.first) {
        res+=r-l+1;
        l=p.first,r=p.second;
      } else {
        r=max(r,p.second);
      }
    }
    res+=r-l+1;
    return res;
  }
};

// imos, O(N*2^N) time
class Over9000Rocks_org {
  public:
  int countPossibilities(vector<int> L, vector<int> U) {
    int N=SZ(L);
    map<int,int> imos;
    REP(mask,1<<N) if(mask) {
      int l=0,r=0;
      REP(i,N) if(mask&(1<<i)) l+=L[i],r+=U[i];
      l=max(l,9001);
//      dump2(l,r);
      if(r<l) continue;
      imos[l]++;
      imos[r+1]--;
    }
    int res=0,sum=0,l=-1;
    FORR(kvp,imos) {
      int sum2=sum+kvp.second;
      if(sum==0&&sum2>0) l=kvp.first;
      if(sum>0&&sum2==0) res+=kvp.first-l;
      sum=sum2;
    }
    return res;
  }
};

// CUT begin
ifstream data("Over9000Rocks.sample");

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

bool do_test(vector<int> lowerBound, vector<int> upperBound, int __expected) {
    time_t startClock = clock();
    Over9000Rocks *instance = new Over9000Rocks();
    int __result = instance->countPossibilities(lowerBound, upperBound);
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
        vector<int> lowerBound;
        from_stream(lowerBound);
        vector<int> upperBound;
        from_stream(upperBound);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(lowerBound, upperBound, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517797064;
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
        cout << "Over9000Rocks (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
