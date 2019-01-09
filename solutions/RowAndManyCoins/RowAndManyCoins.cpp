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
 
 2/26/2018
 
 9:15-22:07 ACC (230.95 pt)
 
 I went back and forth between normal dp and grundy number.
 DP solution passed system test.
 However I had no proof why player loses when game is divided to W state and L state...
 
 2/27/2018
 
 9:30-11:30 Read editorials and add proof of greedy strategy.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+522
  - http://d.hatena.ne.jp/kusano_prog/20111027/1319746061
   - impressive proof with induction
  - http://rsujskf.blog32.fc2.com/blog-entry-2146.html
  - http://d.hatena.ne.jp/anta1/20120820/1345397834
  - http://purple-jwl.hatenablog.com/entry/20121027/1351319549
  - https://topcoder.g.hatena.ne.jp/firewood/20111027/1319732512
 
 If A is at the edge like A@@@@@@ or @@@@@A, obviously Alice always wins.
 
 Suppose both edges are 'B' like BBAAABABAB
 
 If Alice takes from edges, she can take up to A or B
 1) BBAAABABAB -> @@@@@@ABAB
 2) BBAAABABAB -> @@@@@@@BAB
 
 In case #1, Alice loses. In case #2, still B is in both edges.
 So problem was reduced to same problem with smaller size.
 
 If Alice doesn't touch edges, she makes two sub problems with two new edges.
 1) BBAAABABAB -> BBAAAB@BAB, "B*B" and "B*B"
 2) BBAAABABAB -> BBAAAB@@AB, "B*B" and "A*B"
 3) BBAAABABAB -> BBA@@@ABAB, "B*A" and "A*B"
 
 Suppose Bob always wins in form "B*B" and see if it's true or not by induction.
 
 In base case, "B", "BAB" or "BB", obviously Bob wins.
 
 In case #1 and #2, Bob can leave "B*B". This is subproblem of original "B*B" case for Alice.
 By induction, it eventually reaches base case. Bob wins.
 
 In case #3, Bob can leave "B*A" and "B".
 If Alice removes "B", Bob wins by keeping B at the edge.
 If Alice doesn't touch "B", we have "B*B"+"B*A"+"B","B*A"+"A*A"+"B", or "B*A"+"B*B"+"B" (symmetry of first one)
 Single "B" contributes to only Bob's win. If we don't care this "B", we get "B*B"+"B*A" and "B*A"+"A*A".
 In either case, Bob can make "B*B" or "B*A".
 "B*B" case is subproblem. It eventually reaches base case by induction. Thus Bob wins.

 "B*A" case is also subproblem of case #3. This eventually reaches "BA" + "B"xN.
 In this base case, Alice has no way to win. Even if she keeps single "A", Bob removes it in next step.
 
 Key:
  - By induction, optimal strategy can be proved to win
 
 Summary:
  - I went back and forth between normal dp and grundy number 👎
  - Good strategy may be found. Don't go rush to dp or grundy number 👎👎
  - Nice to learn that optimal strategy can be proved by induction if that exists.
 
 */
class RowAndManyCoins {
public:
  string p1="Alice",p2="Bob";
  int N;
  string S;
  string getWinner(string S) {
    this->S=S,this->N=SZ(S);
    return S.front()=='A'||S.back()=='A'?p1:p2;
  }
};

int memo[51][51][2];
class RowAndManyCoins_org {
public:
  string p1="Alice",p2="Bob";
  int N;
  string S;
  int f(int l, int r, int p) {
    int &res=memo[l][r][p];
    if(res>=0) return res;
    if(r-l<=1) {
      assert(l<r);
      int rem=S[l]=='B';
      res=rem==p;
//      dump4(l,r,p,res);
      return res;
    }
    
    FORE(ll,l,r)FORE(rr,ll+1,r) {
      int cnt=0,x=0;
      if(l<ll) cnt++,x=!f(l,ll,1^p);
      if(rr<r) cnt++,x=!f(rr,r,1^p);
      if(cnt==0) continue;
      if(cnt==x) {
        res=1;
//        dump2(ll,rr);
//        dump4(l,r,p,res);
        return res;
      }
    }
//    dump4(l,r,p,0);
    return res=false;
  }
  string getWinner(string S) {
    this->S=S,this->N=SZ(S);
    MINUS(memo);
    return f(0,N,0)==0?p2:p1;
  }
};

class RowAndManyCoins_wrong {
  public:
  string p1="Alice",p2="Bob";
  int N;
  string S;
  int f(int l, int r, int p) {
    int &res=memo[l][r][p];
    if(res>=0) return res;
    if(r-l<=1) {
      assert(l<r);
      int rem=S[l]=='B';
      res=rem!=p?0:1;
      dump4(l,r,p,res);
      return res;
    }
    SETI S;
    FORE(ll,l,r)FORE(rr,ll+1,r) {
      int x=0;
      if(l<ll) x^=f(l,ll,1^p);
      if(rr<r) x^=f(rr,r,1^p);
      S.emplace(x);
    }
    res=0;
    while(S.count(res)) ++res;
    dump4(l,r,p,res);
    return res;
  }
  string getWinner(string S) {
    this->S=S,this->N=SZ(S);
    MINUS(memo);
    return f(0,N,0)==0?p2:p1;
  }
};

// CUT begin
ifstream data("RowAndManyCoins.sample");

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

bool do_test(string cells, string __expected) {
    time_t startClock = clock();
    RowAndManyCoins *instance = new RowAndManyCoins();
    string __result = instance->getWinner(cells);
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
        string cells;
        from_stream(cells);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cells, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519708502;
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
        cout << "RowAndManyCoins (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
