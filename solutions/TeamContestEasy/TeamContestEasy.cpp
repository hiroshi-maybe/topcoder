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
 
 12/13/2017
 
 8:44-9:08 analysis
 9:08-9:28 submit (229.25 pt)
 
 Since we want to know WORST rank of my team, we need to make as many teams which is stronger than mine.
 
 Member of smallest strength in a team does not contribute strength.
 To make team stronger, we can ignore those (N-3)/3 members.
 
 In 2*(N-3)/3 members, I maintained pointer of stronger member `r`.
 If we can find weaker member `l` s.t. strength(l)+strength(r)>`me`, my rank increases by 1.
 This algorithm works in O(N^2) time
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+573
  - http://kmjp.hatenablog.jp/entry/2013/03/23/1000
  - http://torus711.hatenablog.com/entry/20130315/p4
  - http://purple-jwl.hatenablog.com/entry/20130315/1363336183
 
 Making more pairs whose sum is greater than X is typical greedy problem by two pointers.
 
 Sort numbers and keep two pointers `l` for smallest and `r` for greatest number
 1) ns[l] + ns[r] <= X
   pair two worst to keep better number
 2) ns[l] + ns[r] > X
   pair ns[l] and ns[r]. Since ns[l]<=ns[l+1], no need to keep ns[r] for following pairs
 
 12/15/2017
 
 Add simpler solution in editorial
 
 Key:
  - Drop smallest numbers greedily
  - Making more pairs whose sum is greater than X is typical problem
 
 Summary:
  - Too slow to analyze greedy algorithm
   - Confused about higher rank => better rank or worse rank? What rank is higher means that strength is lower
   - It took a bit long time to figure out that I can drop smallest (N-3)/3 values
  - My original two pointer did not work. Analysis of design is not sufficient.
 
 */

class TeamContestEasy {
public:
  int worstRank(vector<int> X) {
    int a=X[0],b=X[1],c=X[2];
    if(b<c) swap(b,c);
    if(a<b) swap(a,b);
    if(b<c) swap(b,c);
    int A=a+b;
    sort(X.begin()+3,X.end());

    int res=0;
    int N=SZ(X);
    int l=2+N/3,r=N-1;
    while(l<r) {
      if(X[l]+X[r]>A) {
        ++res;
        ++l,--r;
      } else {
        l+=2;
      }
    }
    return res+1;
  }
};

class TeamContestEasy_org {
  public:
  int worstRank(vector<int> X) {
    int a=X[0],b=X[1],c=X[2];
    if(b<c) swap(b,c);
    if(a<b) swap(a,b);
    if(b<c) swap(b,c);
    int A=a+b;
    VI ns;
    FOR(i,3,SZ(X)) ns.push_back(X[i]);
    sort(ns.begin(),ns.end());
    vector<II> ps;
    int M=SZ(ns);
    int cnt=1;
    FOR(i,M/3+1,M) {
      if(ns[i]!=ns[i-1]) {
        ps.emplace_back(ns[i-1],cnt);
        cnt=0;
      }
      ++cnt;
      if(i==M-1) ps.emplace_back(ns[i],cnt);
    }
    
    int res=0;
    int N=SZ(ps);
    
//    dump(A);
//    REP(i,N) dump2(ps[i].first,ps[i].second);
    
    REP(r,N) REP(l,r+1) if(ps[l].first+ps[r].first>A) {
      int a=ps[l].first==ps[r].first?ps[l].second/2:min(ps[l].second,ps[r].second);
//      dump3(ps[l].first,ps[r].first,a);
      res+=a;
      ps[l].second-=a,ps[r].second-=a;
    }
//    dump(res);
    return res+1;
  }
};

// CUT begin
ifstream data("TeamContestEasy.sample");

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

bool do_test(vector<int> strength, int __expected) {
    time_t startClock = clock();
    TeamContestEasy *instance = new TeamContestEasy();
    int __result = instance->worstRank(strength);
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
        vector<int> strength;
        from_stream(strength);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(strength, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513183456;
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
        cout << "TeamContestEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
