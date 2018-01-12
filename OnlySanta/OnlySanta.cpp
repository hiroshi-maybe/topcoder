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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/10/2018 SRM 727
 
 18:00-18:51 submit and re-submit. System test failed
 20:20-20:33 fixed a bug and system test passed
 
 1/11/2018 add analysis
 
 My analysis:
 
 At first, just simply prepend or append "SANTA". If it doesn't include "SATAN", return it.
 
 a) "SANTA"+S
     ^^ ^^
 
 If S does not contain "N", this meets expectation.
 
 b) S+"SANTA"
         ^^
 
 If S does not cantain subsequence "SAT", this meets expectation.
 
 If it's not case a) or b), S should contain "SAT" and "N".
 
 I classified into below three cases based on position of "N":
 
 c) S = "*S*A*T*N*"
 
 res = "*S*A*T*N*"+"TA" = "*S*A*T*N*TA" ⊋ "SATAN"
                            ^ ^   ^ ^^
 
 d) S = "*S*A*N*T*"
 
 res = "*S*A*N*T*"+"A" = "*S*A*N*T*A" ⊋ "SATAN"
                           ^ ^ ^ ^ ^
 
 e) S = "*S*N*A" + "*T*" = S1 + S2
 
 res = S1 + "N" + S2 + "A" = "*S*N*AN*T*A" ⊋ "SATAN"
                               ^   ^^ ^ ^
 
 f) S = "*N*S*A" + "*T*" = S1 + S2
 
 res = S1+"N"+S2+"A" = "*N*S*AN*T*A" ⊋ "SATAN"
                           ^ ^^ ^ ^
 
 In the contest, I made a mistake to handle case f).
 I mistakenly built S+"NTA" = "*N*S*A*T*NTA".
                                       ^ "A" can be here.
 However this string fails when "A" stays after "T" 👎

 submit solutions:
  - greedy
   - https://community.topcoder.com/stat?c=problem_solution&rm=330856&rd=17055&pm=14776&cr=40561051
   - https://community.topcoder.com/stat?c=problem_solution&rm=330857&rd=17055&pm=14776&cr=23309657
  - DP 😳
   - https://community.topcoder.com/stat?c=problem_solution&rm=330860&rd=17055&pm=14776&cr=40383352
 
 Editorial:
  - http://hamko.hatenadiary.jp/entry/2018/01/11/131554
 
 Simpler analysis from submit solutions
 
 SANTA
 12^34
 
 SATAN
 1234^
 
 If we compare SANTA with SATAN, LCS is "SATA" which is obtained by skipping "N".
 So we can focus on "N".
 
 If there is no "N", problem is easy.
 
 res = "SANTA" + S
 
 If we want to make "SATAN", we need to have "SATA" before "N".
 Giving first "N" by prepending "SANTA" never makes "SATAN".
 
 If there is "N", appending "TA" never makes SATAN, because we can ignore letters following the last "N".
 Note that this is correct because original string S does not have "SATAN".
 
 If there is "SA" before "N", res = S + "TA"
 If there is no "SA" before "N", we can insert "SA" after the last "T" before "N".
 Or simply we can insert "SA" before "N", which guarantees that "SA" appears after "T" before "N".
 
 For example, S="*A*T*A*N*", S+"TA"="*A*T*A*N*TA"
 Inserting "SA" after T makes "*A*TSA*A*N*TA"
                                   ^^   ^ ^^
 Or we can insert before "N": "*A*T*A*SAN*TA"
                                      ^^^ ^^
 
 Key:
  - Find a unique character that we can focus on
   - take LCS and find "N" in this case
  - Once we find a character to be focused, analyze what needs to be coming before or after the character to make "SATAN"
   - If we figure out necessary condition of false case, we can intentionally avoid it
     - Having "SA" before "T" is necessary condition to form "SATAN"
   - We can also add sequences as long as it does not satisfy necessary condition
     - "N" is the last character in "SATAN". So we can append whatever we want after last "N"
 
 Summary:
  - I'm still not sure what is the most efficient approach 🤔
  - However top contestants seem to be taking approach that I added after contest
 
 */

bool subseq(string S, string P) {
  int j=0;
  REP(i,SZ(S)) if(j<SZ(P)&&S[i]==P[j]) ++j;
  return j==SZ(P);
}

class OnlySanta {
public:
  string S;
  void ok(string s) {
    dump(s);
    assert(subseq(s,S));
    assert(subseq(s,"SANTA"));
    assert(!subseq(s,"SATAN"));
  }
  string solve(string S) {
    this->S=S;
    string res;
    int ni=-1;
    REP(i,SZ(S)) if(S[i]=='N') ni=i;
    if(ni==-1) {
      res="SANTA"+S;
      ok(res);
      return res;
    }
    
    if(subseq(S.substr(0,ni),"SA")) {
      res=S+"TA";
      ok(res);
      return res;
    }
    
    res=S.substr(0,ni)+"SA"+S.substr(ni)+"TA";
    ok(res);
    return res;
  }
};

class OnlySanta_org {
  public:
  string S;
  void ok(string s) {
    dump(s);
    assert(subseq(s,S));
    assert(subseq(s,"SANTA"));
    assert(!subseq(s,"SATAN"));
  }
  string solve(string S) {
    this->S=S;
    string res;
    if(count(S.begin(),S.end(),'N')==0) {
      dump(1);
      res="SANTA"+S;
      ok(res);
      return res;
    }
    
    int a=-1,b=-1,c=-1;
    REP(i,SZ(S)) {
      if(S[i]=='S'&&a==-1) a=i;
      if(S[i]=='A'&&a!=-1&&b==-1) b=i;
      if(S[i]=='T'&&a!=-1&&b!=-1&&c==-1) c=i;
    }
    if(c==-1) {
      dump(2);
      res=S+"SANTA";
      ok(res);
      return res;
    }
    
    int d=-1;
    FOR(i,c+1,SZ(S)) if(S[i]=='N') { d=i; break; }
    if(d!=-1) {
      dump(3);
      res=S+"TA";
      ok(res);
      return res;
    }
    
    FOR(i,b+1,c) if(S[i]=='N') { d=i; break; }
    if(d!=-1) {
      dump(4);
      res=S+"A";
      ok(res);
      return res;
    }
    
    FOR(i,a+1,b) if(S[i]=='N') { d=i; break; }
    if(d!=-1) {
      dump(5);
      res=S.substr(0,b+1)+"N"+S.substr(b+1)+"A";
      ok(res);
      return res;
    }
    
    dump(6);
//    res=S+"NTA"; System test failed in the contest 🐞
    res=S.substr(0,b+1)+"N"+S.substr(b+1)+"A";
    ok(res);
    return res;
  }
};

// CUT begin
ifstream data("OnlySanta.sample");

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

bool do_test(string S, string __expected) {
    time_t startClock = clock();
    OnlySanta *instance = new OnlySanta();
    string __result = instance->solve(S);
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
        string S;
        from_stream(S);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515636008;
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
        cout << "OnlySanta (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
