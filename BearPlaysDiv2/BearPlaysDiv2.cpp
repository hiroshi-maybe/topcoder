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
 
 8/21/2017
 
 8:41-9:23 passed system test (254.37 pt)
 
 editorials:
  - DFS
    - https://apps.topcoder.com/wiki/display/tc/SRM+664
  - BFS
    - http://kmjp.hatenablog.jp/entry/2015/08/05/0930

 Key:
  - we can keep state by only two numbers because third number is determined from two numbers
  - there is a loop in state transition (not DAG) => graph search rather than DP
 
 Summary:
  - straightforward after figuring out what we should remember
    - it took a while to find it in analysis.
  - we can find that there is a loop in state transition from sample
    - loop -> not DAG -> graph search rether than DP
    - should have judged it in a shorter time
  - missed to update visited table again in implementation phase 😡
 
 Submit solutions:
  - DFS
    - https://community.topcoder.com/stat?c=problem_solution&rm=326728&rd=16513&pm=13939&cr=40235172
    - https://community.topcoder.com/stat?c=problem_solution&rm=326736&rd=16513&pm=13939&cr=40007546
    - https://community.topcoder.com/stat?c=problem_solution&rm=326754&rd=16513&pm=13939&cr=40042734
    - https://community.topcoder.com/stat?c=problem_solution&rm=326735&rd=16513&pm=13939&cr=40066523
 
 */
int viz[1501][1501];
class BearPlaysDiv2 {
  public:
  string ok="possible",ng="impossible";
  string equalPiles(int A, int B, int C) {
    int tot=A+B+C;
    
    if(tot%3!=0) return ng;
    tie(A,B)=order(A,B,C);
//    dump3(A,B,C);
    C=tot-A-B;
    // A<=B<=C
    
    ZERO(viz);
    queue<II> Q;
    Q.emplace(A,B);
    viz[A][B]=true;
    
    while(SZ(Q)) {
      int a,b;
      tie(a,b)=Q.front(); Q.pop();
      int c=tot-a-b;
      
//      dump4(SZ(Q),a,b,c);
      
      int a2=2*a,b2=b,c2=c-a;
      assert(c2>=0);
      tie(a2,b2)=order(a2,b2,c2);
//      dump3(a2,b2,c2);
      if(!viz[a2][b2]) Q.emplace(a2,b2);
      viz[a2][b2]=true;
      
      int a3=a,b3=2*b,c3=c-b;
      assert(c3>=0);
      tie(a3,b3)=order(a3,b3,c3);
      if(!viz[a3][b3]) Q.emplace(a3,b3);
      viz[a3][b3]=true;
    }
    
    return viz[tot/3][tot/3]>0?ok:ng;
  }
  
  II order(int a, int b, int c) {
    if(a>b) swap(a,b);
    if(b>c) swap(b,c);
    
    return {a,b};
  }
};

// CUT begin
ifstream data("BearPlaysDiv2.sample");

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

bool do_test(int A, int B, int C, string __expected) {
    time_t startClock = clock();
    BearPlaysDiv2 *instance = new BearPlaysDiv2();
    string __result = instance->equalPiles(A, B, C);
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        int C;
        from_stream(C);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, C, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503330079;
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
        cout << "BearPlaysDiv2 (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
