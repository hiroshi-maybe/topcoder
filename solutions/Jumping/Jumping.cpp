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
 
 9/21/2017
 
 8:42-9:27 (223.10 pt)
 10:23 1WA
 18:47-18:57 found issue in design and fixed. system test passed.
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2014/09/19/0930
    - check if J forms polygon
  - https://apps.topcoder.com/wiki/display/tc/SRM+633
    - maintain radius intervals
 
 suppose sx = max { S[i] }.
 If sx is larger than rest of total sides, polygon cannot be formed.
  sx > ∑(S[i]) - ss
  <=> sx <= ∑ S[i]/2
 
 key:
  - cordinate of non-integer is valid. This is actually geometry problem
  - transform problem to polygon detection
 
 summary:
  - I found out how to apply triangle inequality by myself though, it took a lot of time
  - Sample was not strong. I applied triangle inequality in wrong way. I got 1WA.
  - explanation by polygon simplifies analysis. It didn't come up with me.
 
 22:30-22:41 add simpler polygon solution inspired by @kmjp's editorial
 
 */

class Jumping {
public:
  const string yes="Able",no="Not able";
  string ableToGet(int x, int y, vector<int> J) {
    double T=sqrt(x*x+y*y);
    vector<double> JJ={T};
    FORR(x,J) JJ.push_back(x);
    double sum=accumulate(JJ.begin(),JJ.end(),0);
    double ss = (double)(*max_element(JJ.begin(),JJ.end()));
    double rest=sum-ss;
    
    return rest<ss?no:yes;
  }
};

class Jumping_org {
  public:
  const string yes="Able",no="Not able";
  string ableToGet(int x, int y, vector<int> J) {
    double T=sqrt(x*x+y*y);
    int N=SZ(J);
    if(N==1) return (double)J[0]==T?yes:no;
    double sum=0;
    REP(i,N) sum+=(double)J[i];
    if(sum<T) return no;
    REP(i,N) {
      double rest=sum-J[i];
      if(T+rest<J[i]) return no;
    }
    return yes;
  }
};

// CUT begin
ifstream data("Jumping.sample");

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

bool do_test(int x, int y, vector<int> jumpLengths, string __expected) {
    time_t startClock = clock();
    Jumping *instance = new Jumping();
    string __result = instance->ableToGet(x, y, jumpLengths);
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
        int x;
        from_stream(x);
        int y;
        from_stream(y);
        vector<int> jumpLengths;
        from_stream(jumpLengths);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, jumpLengths, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506008511;
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
        cout << "Jumping (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
