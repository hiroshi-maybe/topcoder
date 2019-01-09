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
 
 9/24/2017
 
 13:12-13:54 system test passed (468.82 pt)
 
 editorials:
  - http://kmjp.hatenablog.jp/entry/2014/08/24/1000
  - https://apps.topcoder.com/wiki/display/tc/SRM+630
 
 key:
  - find smallest string that satisfies suffix array of inptu string
  - give smallest characters from SA[0], SA[1], ..., SA[N-1]
  - S[SA[i+1]]==S[SA[i]] only when S[SA[i+1]..] > S[SA[i]..]
 
 summary:
  - submit solution passed system test though, no proof of correctness of the algorithm 😵
    - intuitively I wanted to minimize impact to suffix order. thus tried smaller string at most one character
  - generating smallest string and comparing with given one is new pattern.
  - suffix array gives hint of position of smaller characters. in such a case, filling from smallest number to larger is sometimes useful approach.
 
 submit solutions:
  - solution in editorials:
    - https://community.topcoder.com/stat?c=problem_solution&rm=323312&rd=16061&pm=13287&cr=22913297
  - change one character (same as my original solution)
    - https://community.topcoder.com/stat?c=problem_solution&rm=323325&rd=16061&pm=13287&cr=40035551
    - https://community.topcoder.com/stat?c=problem_solution&rm=323310&rd=16061&pm=13287&cr=14898211
 
 16:46-17:17 add proved solution in editorial
 
 */

class SuffixArrayDiv2 {
public:
  const string yes="Exists",no="Does not exist";
  VI sarray(string s) {
    int N=SZ(s);
    vector<pair<string,int>> xs;
    REP(i,N) xs.emplace_back(s.substr(i),i);
    sort(xs.begin(),xs.end());
    VI res;
    REP(i,N) res.push_back(xs[i].second);
    return res;
  }
  
  string smallest(VI sa) {
    int N=SZ(sa);

    // order of each index
    VI ord(N);
    REP(i,N) ord[sa[i]]=i;
    
    string s(N,'#');
    s[sa[0]]='a';
    FOR(i,1,N) {
      int j=sa[i-1],k=sa[i];
      if(k==N-1) s[k]=s[j]+1;
      else if(j==N-1||ord[j+1]<ord[k+1]) s[k]=s[j];
      else s[k]=s[j]+1;
    }
//    dump(s);
    assert(sarray(s)==sa);
    return s;
  }
  
  string smallerOne(string S) {
    return S>smallest(sarray(S))?yes:no;
  }
};

class SuffixArrayDiv2_oneEditDistance {
  public:
  const string yes="Exists",no="Does not exist";
  VI sa;
  VI sarray(string s) {
    int N=SZ(s);
    vector<pair<string,int>> xs;
    REP(i,N) xs.emplace_back(s.substr(i),i);
    sort(xs.begin(),xs.end());
    VI res;
    REP(i,N) res.push_back(xs[i].second);
    return res;
  }
  string smallerOne(string S) {
    string test(10,'z'+1);
    cout<<"|"<<test<<"|"<<endl;
    int N=SZ(S);
    this->sa=sarray(S);
    
    REP(i,N) if(S[i]!='a') {
      string t=S;
      t[i]-=1;
      VI sb=sarray(t);
      if(sa==sb) return yes;
    }
    return no;
  }
};

// CUT begin
ifstream data("SuffixArrayDiv2.sample");

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

bool do_test(string s, string __expected) {
    time_t startClock = clock();
    SuffixArrayDiv2 *instance = new SuffixArrayDiv2();
    string __result = instance->smallerOne(s);
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
        string s;
        from_stream(s);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506283938;
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
        cout << "SuffixArrayDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
