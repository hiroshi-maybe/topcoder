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
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/*
 
 11/1/2017
 
 8:55-9:07 anslysis
 9:08-9:57 pause
 18:50-19:40 give up
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+600
  - http://emkcsharp.hatenablog.com/entry/SRM600/ORSolitaireDiv2
  - http://torus711.hatenablog.com/entry/20131214/p3
 
 21:50-23:20 brute force... sign...
 
 We want to minimize number of cards to be removed.
 That means we can ignore cards which do NOT contribute to build goal G.
 Card with number which violates goal number bit is such card.
 
 So we can pre-filter those numbers before brute forcing subsets.
 Of courese in-place filter in subset check works too.
 
 Summary:
  - I was looking at only example G=7(111) in which all bits are ON. So I couldn't make clear analysis for a case where chosen number violates goal number with unexpected ON bit.
  - In the first implementation, I wrote a code which brute forces subsets by bit mask. However analysis of invalid number was completely missing. Thus I messed up every thing. I never had chance to get back to right approach 😡💢😢👎
  - I even had an idea to count number of cards which contributes each bit 0..31, which is div1 solution. Anyway missing analysis of unfiltered invalid number messed up everything.
 
 */
class ORSolitaireDiv2 {
public:
  int getMinimum(vector<int> ns, int G) {
    vector<int> ms;
    FORR(n,ns) if((n|G)==G) ms.push_back(n);
//    dump(G);
    int N=SZ(ms);
    int res=N;
    REP(mask,1<<N) {
      int x=0;
      REP(i,N) if((mask&(1<<i))==0) x|=ms[i];
      if(x!=G) res=min(res,__builtin_popcount(mask));
    }
    return res;
  }
};

class ORSolitaireDiv2_wrong {
  public:
  VI uf;
  int find(int x) { return uf[x]==x?x:uf[x]=find(uf[x]); }
  void unite(int x1, int x2) {
    int p1=find(x1),p2=find(x2);
    uf[p1]=p2;
  }
  int getMinimum(vector<int> ns, int G) {
    int N=SZ(ns);
    
    VI S;
    REP(mask,1<<N) {
      int x=0;
      REP(i,N) if(mask&(1<<i)) x|=ns[i];
      if(G==x) { dump(mask); S.emplace_back(mask); }
    }
    dump(SZ(S));
    uf.resize(SZ(S));
    REP(i,SZ(uf)) uf[i]=i;
    REP(i,N) {
      int base=-1;
      REP(j,SZ(S)) if(S[j]&(1<<i)) {
        if(base==-1) base=j;
        else unite(base,j);
      }
    }
    
    dumpAR(uf);
    int res=0;
    REP(i,SZ(S)) if(find(i)==i) res++;
    return res;
  }
};

// CUT begin
ifstream data("ORSolitaireDiv2.sample");

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

bool do_test(vector<int> numbers, int goal, int __expected) {
    time_t startClock = clock();
    ORSolitaireDiv2 *instance = new ORSolitaireDiv2();
    int __result = instance->getMinimum(numbers, goal);
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
        vector<int> numbers;
        from_stream(numbers);
        int goal;
        from_stream(goal);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numbers, goal, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509551725;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ORSolitaireDiv2 (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
