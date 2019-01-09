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
 
 8/1/2017
 
 8:25-8:52 passed system test (329.20 pt)
 
 I'm surprised that `for(auto& x:arr)` behavior is different in below cases:
 `for(auto& x: "abc") cout << x << endl; => 'a','b','c',''(empty character at the tail 😡)
 `string xx="abc"; for(auto& x: xx) cout << x << endl; => 'a','b','c'(no empty character 😇)
 
 If this didn't happen, I could have submitted earlier.
 
 My solution
  - check sequence whose length is from 1 to N until the sequence does not appear in S
  - the first found one is the solution
 
 24:00- read editorial
 BFS search by queue
  - http://pekempey.hatenablog.com/entry/2016/02/23/152917
  - https://docs.google.com/document/d/1Pvo2HS88n1en_1nKZ6XaRnm_9RmwdyUfc3WKhncZ754/edit
 DFS search by backtracking
  - https://apps.topcoder.com/wiki/display/tc/SRM+682
 
 1. Loose upper bound
 
 substring of a string whose length is N is N*(N+1)/2
 
 possible substrings = 2000*(2000+1)/2 ≈ 2x10^6
 corresponding sequence length = 4^12 ≈ 4x10^6
 
 So solution should be found at most length 12
 
 2. Tight upper bound
 
 Suppose S has all the patterns whose length is n.
 4^6 = 4096 > 2000 >= S. In worst case, 4^6 sequences overlap by 5 like S[0..5]=seq[0], S[1..6]=seq[1].
 In such a case length of S is still 4096+5 = 4101. Thus solution should be found at most length 6.
 
 total number of candidate is ∑{4^i: i=1..6} ≈ 5460
 
 24:46-24:52 add BFS solution
 
 Other solutions
 - DFS
  - https://community.topcoder.com/stat?c=problem_solution&rm=328093&rd=16652&pm=14163&cr=40380304
 - BFS
  - https://community.topcoder.com/stat?c=problem_solution&rm=328109&rd=16652&pm=14163&cr=40121353
 - generate sequences by bitmask
  - https://community.topcoder.com/stat?c=problem_solution&rm=328113&rd=16652&pm=14163&cr=23178685
 
 Key
  - analyze upper bound of search space so that we can do simple brute force.
  - technique to generate n-ary sequence seems to be useful in other problems
 
 Summary
  - luckily my solution to store substrings though, it could hit MLE. It's not right way.
  - tight upper bound analysis helps have better sense of search space. Train it too. Some top solutions are sometimes using constant upper bound. That is coming from deep problem size analysis.
 
 */

string DNA="ACGT";
class TopBiologist {
public:
  
  bool test(string s, string S) {
    int l=SZ(s);
    REP(i,SZ(S)) if(S.substr(i,l)==s) return false;
    return true;
  }
  
  string findShortestNewSequence(string S) {
    queue<string> Q;
    Q.push("");
    while(SZ(Q)) {
      string cur=Q.front(); Q.pop();
      if(S.find(cur)==string::npos) return cur;
      FORR(c,DNA) Q.push(cur+c);
    }
    return "";
  }
};

unordered_set<string> SS[2001];
class TopBiologist_org {
  public:
  
  bool test(string s, string S) {
    int l=SZ(s);
    REP(i,SZ(S)) if(S.substr(i,l)==s) return false;
    return true;
  }
  
  string findShortestNewSequence(string S) {
    int N=SZ(S);
    REP(i,N+1) SS[i].clear();
    SS[0].insert("");
    for(int l=1; l<=N; ++l) {
      for(int i=0; i+l<=N; ++i) {
//        dump2(l,S.substr(i,l));
        SS[l].insert(S.substr(i,l));
      }
//      dump2(l,SZ(SS[l]));
//      dumpAR(SS[l]);
      FORR(s,SS[l-1]) FORR(c,DNA) if(SS[l].count(s+c)==0) {
        assert(test(s+c,S));
        return s+c;
      }
    }
    
    return "";
  }
};

// CUT begin
ifstream data("TopBiologist.sample");

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

bool do_test(string sequence, string __expected) {
    time_t startClock = clock();
    TopBiologist *instance = new TopBiologist();
    string __result = instance->findShortestNewSequence(sequence);
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
        string sequence;
        from_stream(sequence);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(sequence, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501601116;
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
        cout << "TopBiologist (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
