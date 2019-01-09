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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/27/2018
 
 17:24-18:10 give up and take a look at editorials
 
 1/28/2018
 
 10:00-11:00 Try greedy solution. System test passed.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+545
  - http://d.hatena.ne.jp/kusano_prog/20120608/1339143743
  - http://mayokoex.hatenablog.com/entry/2016/05/02/210059
  - http://torus711.hatenablog.com/entry/20121211/p2
  - https://chngng.blogspot.jp/2013/06/
  - http://topcoder.g.hatena.ne.jp/agw/20120610/1339314294
  - http://quiz.fuqinho.net/blog/2012/06/11/srm-545-striirec-div1-275-slash-div2-550/

 Sample 4 is nice one to play around.
 
 N=9, minInv=20, minS="fcdebiha"
 
 1) i=0, minS[0]=f
  f*****, inversion ranges in [5,33] => 33>=20 ✅
 2) i=1, minS[1]=c
  fc****, inversion ranges in [7,28] => 28>=20 ✅
 3) i=2, minS[2]=d
  fcd***, inversion ranges in [9,24] => 24>=20 ✅
 4) i=3, minS[2]=e
  fcde**, inversion ranges in [11,21] => 21>=20 ✅
 5) i=3, minS[2]=b
  fcdeb*, inversion ranges in [12,18] => 18<20 ❌
  fcdeg*, inversion ranges in [13,19] => 19<20 ❌
  fcdeh*, inversion ranges in [14,20] => 20>=20 ✅
 
 Picking larger character gives higher inversion. However we want to minimize string.
 We need to pick up optimal character to satisfy those two conditions.
 Key is that choice of letter determines possible range of inversion changes.
 It's easier to predict inversions by choice of character in current index.
 Pick up smaller character so that possible highest inversion does not get smaller than `minInv`
 
 Key:
  - DP doesn't work. Try greedy
  - By choice of character, possible range of inversion changes
  - To satisfy two minimum conditions, observe range of possible value of either one
  - We can pick up smallest as long as highest value does not exceed minimum constraint
 
 Summary:
  - Greedy never came up with me 👎👎👎👎👎👎
   - I misunderstood that bit manipulation is used to solve due to N<=20 constraint
   - Bit DP is trivial. However state table does not fit in memory...
   - Tried brute-force though, it just exceeds time constraint
  - More sophisticated analysis is needed in brute-force analysis
  - If DP doesn't fit, some options may work
   - Try to reduce state in heuristic manner like SRM 547 div2 hard RelativelyPrimeSubset
   - Greedy
  - In greedy analysis technique
   - Try most ideal and extreme case and relax it
   - Observe how search space shrinks
 
 */
class StrIIRec {
  public:
  string recovstr(int N, int minInv, string minS) {
    string res="";
    int viz[20]={};
    int l=0;
    bool any=false;
    REP(i,N) {
      int c=-1;
      int rest=N-i-1;
      REP(j,N) if(!viz[j]) {
        if (!any&&i<SZ(minS)&&(minS[i]-'a')>j) continue;
        int d=0;
        REP(k,j) d+=!viz[k];
        int rr=l+d+rest*(rest-1)/2;
        if(rr>=minInv) {
          c=j;
          l+=d;
          if(!any&&(i>=SZ(minS)||minS[i]-'a'<j)) any=true;
          break;
        }
      }
      dump2(i,c);
      if(c==-1) return "";
      viz[c]=true;
      res+='a'+c;
    }
    return res;
  }
};

// CUT begin
ifstream data("StrIIRec.sample");

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

bool do_test(int n, int minInv, string minStr, string __expected) {
    time_t startClock = clock();
    StrIIRec *instance = new StrIIRec();
    string __result = instance->recovstr(n, minInv, minStr);
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
        int n;
        from_stream(n);
        int minInv;
        from_stream(minInv);
        string minStr;
        from_stream(minStr);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, minInv, minStr, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517102645;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "StrIIRec (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
