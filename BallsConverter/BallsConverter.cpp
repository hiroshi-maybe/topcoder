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
 
 10/6/2018
 
 12:54-13:40 give up
 
 "Uniquely determined" is not easy to handle. How can we transform this? Graph or tree?
 How to make pairs from S doesn't matter. What does that mean?

 13:40-14:12 read editorials and add solution
 
 http://mayokoex.hatenablog.com/entry/2015/04/20/234246
 https://topcoder.g.hatena.ne.jp/jackpersel/20101201/1291207867
 http://rsujskf.blog32.fc2.com/blog-entry-1792.html
 http://tubo28.me/blog/post/2015/04/23/srm489-d1e/
 
 I built binary tree and tried to look for good way to group the ball sets. However it just TLEs. I was in stuck.
 "last ball can be always determined uniquely" <=> Order to apply operation doesn't matter
 
 Suppose we have 3 balls {a,b,c}.
 If we always get the same result regardless of applying operation like... (a-b)-c, (b-c)-a, (c-a)-b, we should be able to get the same result. This is showing associativity property of binary operation.
 If associativity holds, we can extend the thoerem to arbitrary balls easily.
 
 Summary:
  - Two dimension table forms binary operation. I didn't have this interpretation in my mind.
  - Approach to transforming to general problem was correct. However I didn't have good abstraction idea
   - Tree doesn't make sense in this case because three balls case also exists. Binary tree is not general enough
   - I tried two balls case. I should have tried three balls case before jumping to four balls case. My mind was caught by binary tree. Sigh.
  - If some operation happens, we may be able to use some algebraic theorems.
 
 */
const string yes="Good",no="Bad";
class BallsConverter {
  public:
  string theGood(vector<string> convert) {
    int N=SZ(convert);
    vector<VI> T(N,VI(N));
    REP(i,N)REP(j,N) T[i][j]=islower(convert[i][j])?convert[i][j]-'a'+26:convert[i][j]-'A';
    REP(i,N)REP(j,N)REP(k,N) if(T[T[i][j]][k]!=T[i][T[j][k]]) return no;
    return yes;
  }
};

// CUT begin
ifstream data("BallsConverter.sample");

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

bool do_test(vector<string> convert, string __expected) {
    time_t startClock = clock();
    BallsConverter *instance = new BallsConverter();
    string __result = instance->theGood(convert);
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
        vector<string> convert;
        from_stream(convert);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(convert, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1538855647;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BallsConverter (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
