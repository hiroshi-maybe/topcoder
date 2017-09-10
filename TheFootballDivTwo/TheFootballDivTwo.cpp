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
 
 9/10/2017
 
 9:52-10:45 give up
 
 editorials:
  - http://kmjp.hatenablog.jp/entry/2015/01/22/1000
  - http://tatanaideyo.hatenablog.com/entry/2015/01/29/034637
    - nice box and ball metaphors to understand
  - https://apps.topcoder.com/wiki/display/tc/SRM+646
    ```
    The proof for both assumptions: As long as there are `n` victories and `n` defeats, then the match selection would be correct. This means that no team needs to be matched against itself. There are at least two teams. For a team to be matched against itself, we need to assign both a victory and a defeat to it. There will always be at least one other team assigned a victory and one other team assigned a defeat. So we can do an exchange.
    ```
  - http://mayokoex.hatenablog.com/entry/2015/03/25/200445
  - http://codeforces.com/blog/entry/15822
 
 13:20-14:08 read editorials and add solution
 
 For N teams, we'll have N game. That means 3*N scores are given to N teams.
 Each team can have at most score 6.
 As long as we follow this rule, we can determine final score of each team.
 Pair of teams in a match doesn't matter. We are interested in ONLY who gets 3/6 scores.
 
 Our team gets 6 scores optimally. We can make 4 groups based on their scores.
 We define M = m + 6 as a criteria to classify teams.
 
 G0 = { team :   M < score(team)        } those teams are always above
 G1 = { team :       score(team) <= M-6 } those teams are always below
 G2 = { team : M-6 < score(team) <= M-3 } those teams will be above by by 2 wins
 G3 = { team : M-3 < score(team) <= M   } those teams will be above by by 1 win
 
 We give 3*N-6 scores (`rem`) in {G0(6), G1(6), G2(3), G3(6), G2(3)} order
 
 1) rem -= 6*|G0| rank += |G0|
 2) rem -= 6*|G1|
 3) rem -= 3*|G2|
 4) rem -= 6*|G3| rank += |G3|
 rank += rem/3
 
 res = rank + 1
 
 actually we can look at how to give `wins` instead of `scores` to simplify.
 
 wins = N-2-2*(|G0|+|G1|)-|G3|
 rank = |G0|
 
 if(wins>=2*|G2|)
  rank += |G2| + (wins-2*|G2|) // G2 and G3 teams to go above
 else if(wins>0)
  rank += ceil(wins/2) // G2 to go above
 
 key:
  - we are interested in who gets 3/6 scores. no need to be worried about actual pair of teams in matches
    - if scores are determined, we'll know rank of our team.
  - team can be classified to 4 groups
  - we have 3*N-6 score pool. design make it zero by giving pooled scores optimally
 
 summary:
  - found out that keep pairing highest and lowest greedily doesn't work though, I didn't reach further greedy idea
  - we are interested in final rank => look at how many teams potentially go above or below
    - give wins at most 2 to N teams. this condition surfices.
    - pair of teams in match doesn't matter
  - nice analysis focused problem
 
 */
class TheFootballDivTwo {
  public:
  int find(int m, vector<int> ss, vector<int> ns) {
    int M=m+6;
    int N=accumulate(ns.begin(),ns.end(),0)+1;
    int rem=3*(N-2);
    
    int G[4]={0};
    REP(i,SZ(ns)) {
      int n=ns[i],s=ss[i];
      if(s>M) G[0]+=n;
      else if(s<=M-6) G[1]+=n;
      else if(s<=M-3) G[2]+=n;
      else G[3]+=n;
    }
//    dump2(M,rem);
//    dump4(G[0],G[1],G[2],G[3]);
    
    int res=G[0];
    if(rem<=6*G[0]) return res+1;
    rem -= 6*G[0];
    
    if(rem<=6*G[1]) return res+1;
    rem -= 6*G[1];
    
    if(rem<=3*G[2]) return res+1;
    rem -= 3*G[2];
    
    if(rem<=6*G[3]) return res+(rem+5)/6+1;
    rem -= 6*G[3];
    
    return res+rem/3+1;
  }
};

// CUT begin
ifstream data("TheFootballDivTwo.sample");

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

bool do_test(int yourScore, vector<int> scores, vector<int> numberOfTeams, int __expected) {
    time_t startClock = clock();
    TheFootballDivTwo *instance = new TheFootballDivTwo();
    int __result = instance->find(yourScore, scores, numberOfTeams);
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
        int yourScore;
        from_stream(yourScore);
        vector<int> scores;
        from_stream(scores);
        vector<int> numberOfTeams;
        from_stream(numberOfTeams);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(yourScore, scores, numberOfTeams, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505072059;
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
        cout << "TheFootballDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
