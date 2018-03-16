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

string n2bin(long long n) {
  assert(n>=0);
  string res="";
  while(n>0) res+=(n%2LL?'1':'0'),n/=2LL;
  return string(res.rbegin(), res.rend());
}

/*
 
 3/15/2018
 
 9:02-9:47 analysis
 9:52 (428.86 pt) 1WA
 9:55-10:15 give up
 
 I tried three approaches though, no luck 😞
  - dp => I couldn't encode remaining numbers to reasonable number of states
  - greedy => I couldn't find optimal strategy from initial state
  - Nim => Tried to reduce to Nim by looking at duplciated bits. Samples passed though, it didn't pass system test
 
 18:30-19:56 Read editorials. I finally figured out why c1'=c1-used
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+511
  - http://d.hatena.ne.jp/simezi_tan/20110703/1309636474
  - http://hos0lyric.blog89.fc2.com/blog-entry-36.html
  - http://kenkoooo.hatenablog.com/entry/2015/08/21/152631
   - Player NEVER loses if picked card is inclusive in memory. This is the key.
  - https://topcoder.g.hatena.ne.jp/jackpersel/20110703/1309682798
  - http://d.hatena.ne.jp/kusano_prog/20110702/1309632228
  - http://mayokoex.hatenablog.com/entry/2015/07/01/124313
  - http://kmjp.hatenablog.jp/entry/2014/02/14/0900
  - http://purple-jwl.hatenablog.com/entry/20130322/1363947177
  - http://mainly-coding.blogspot.com/2011/07/topcoder-srm-511.html
  - https://chngng.blogspot.jp/2014/04/srm-511-div1-middle-fivehundredeleven.html
 
 23:43-24:16 Write down analysis to ensure that I'm understanding the solution.
 
 In turn game, dp is very popular to solve the problem.
 However number of state to be remembered should be reasonable enough to fit in runtime and memory.
 Challenge of this problem is what should be remembered to know unused cards.
 In naiive implementation, we need 2^50 states to represent set of selected cards.
 It's clearly impossible to define it.

 Two states that we would need is "memory" and number of used cards.
 Memory is dependent on used cards. We can see if we can "restore" unused cards from memory.
 
 Suppose we have memory "M" with selected `k` cards.
 M = OR { X[i] : i∈S, S is set of selected cards }
 Note that |S| = k, S ⊆ X
 
 Out of X, we can figure out candidate of S by set operation.
 Suppose C ⊆ X s.t. c∈C submask(c,M). Then |C|>=k holds.
 Then S ⊆ C ⊆ X, |S|=k, |X|=N.
 
 What we want to know is two sets C' and D:
 C' = C - S, D = { d : !submask(d,M), d∈X }
 
 Since C' is subset of C, c'∈C' satisfies submask(c',M).
 C' does not contribute to update M.
 We can also find D as well by iterating and testing elements of X.
 Wow we figured out unused cards.
 
 We can try C' and D in game DP.
 
 24:17-24:25 implement and ACC
 
 Key:
  - Because of dependency of used cards on memory, we can figure out what is unused card, which is exactly we want to know to do dynamic programming!!!!
 
 Summary:
  - This was beautiful problem. Code is simple. However analysis needs creativity
  - I had an idea of dp though, my analysis ability was not confident to dig into dp 👎
   - My understanding of Nim was not sufficient. So I couldn't stop myself to go into this approach
   - As long as I cannot figure out that it seems to be hard to solve by Nim, I cannot tackle DP approach.
 
 */

int memo[512][51];
class FiveHundredEleven {
public:
  int N;
  VI X;
  string p1="Fox Ciel",p2="Toastman";
  int f(int M, int k) {
    int &res=memo[M][k];
    if(res>=0) return res;
    if(M==511) return true;
    if(k==N) return false;
    
    res=0;
    int c=0;
    REP(i,N) c+=(M|X[i])==M;
    // there exists C'
    if(c-k) res|=!f(M,k+1);
    REP(i,N) if((M|X[i])!=M) res|=!f(M|X[i],k+1);
    return res;
  }
  string theWinner(vector<int> X) {
    this->X=X,this->N=SZ(X);
    MINUS(memo);
    return f(0,0)?p1:p2;
  }
};

class FiveHundredEleven_wrong {
  public:
  string p1="Fox Ciel",p2="Toastman";
  string theWinner(vector<int> X) {
    int a=0,N=SZ(X);
    FORR(x,X) a|=x;
    if(a!=511) return N%2==0?p2:p1;
    int p=0;
    LL viz=0;
    dumpAR(X);
    REP(i,N) dump(n2bin(X[i]));
    REP(i,N) {
      int mask=0;
      REP(j,N) if(i!=j) mask|=X[i]&X[j];
      if(mask==0) ++p,viz|=1LL<<i;
    }
    int b=0;
    REPE(i,8) {
      int cnt=0;
      REP(j,N) if(((viz>>j)&1)==0) cnt+=(X[j]>>i)&1;
//      dump2(i,cnt);
      b^=cnt;
    }
    dump3(p,N,b);
    if(p==N) return N%2==0?p1:p2;
    REP(_,p) b^=1;
    return b==0?p2:p1;
  }
};

// CUT begin
ifstream data("FiveHundredEleven.sample");

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

bool do_test(vector<int> cards, string __expected) {
    time_t startClock = clock();
    FiveHundredEleven *instance = new FiveHundredEleven();
    string __result = instance->theWinner(cards);
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
        vector<int> cards;
        from_stream(cards);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cards, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521129734;
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
        cout << "FiveHundredEleven (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
