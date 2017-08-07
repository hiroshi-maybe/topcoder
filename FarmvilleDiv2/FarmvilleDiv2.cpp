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

/**
 
 8/7/2017
 
 8:35-9:32 submit (100.74 pt)
  - due to misunderstanding of sample, I could not understand problem 🏥💢
 
 15:57 failed system test
 15:59 fixed a bug and passed systemt test.
  - existing loop ignoring remaining time
 
 editorial:
 - https://apps.topcoder.com/wiki/display/tc/SRM+676
 
 */
class FarmvilleDiv2 {
public:
  int minTime(vector<int> T, vector<int> C, int B) {
    int N=SZ(T);
    vector<III> TT;
    REP(i,N) TT.emplace_back(C[i],T[i],i);
    sort(TT.begin(),TT.end());
    
    int res=0;
    FORR(x,TT) {
      int c,t,i;
      tie(c,t,i) = x;
      int d=min(t,B/c);
      t-=d;
      B-=c*d;
      res+=t;
    }
    return res;
  }
};

/*
class FarmvilleDiv2_wrong {
  public:
  int minTime(vector<int> T, vector<int> C, int B) {
    int N=SZ(T);
    vector<III> TT;
    REP(i,N) TT.emplace_back(T[i],C[i],i);
    while(B>0) {
      III p=*max_element(TT.begin(),TT.end());
      int t,c,i;
      tie(t,c,i) = p;
      if (t<=0) return 0;
      if (B<c) return t;
      B-=c;
      TT[i]={t-1,c,i};
    }
    III p=*max_element(TT.begin(),TT.end());
    return get<0>(p);
  }
};*/

// CUT begin
ifstream data("FarmvilleDiv2.sample");

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

bool do_test(vector<int> time, vector<int> cost, int budget, int __expected) {
    time_t startClock = clock();
    FarmvilleDiv2 *instance = new FarmvilleDiv2();
    int __result = instance->minTime(time, cost, budget);
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
        vector<int> time;
        from_stream(time);
        vector<int> cost;
        from_stream(cost);
        int budget;
        from_stream(budget);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(time, cost, budget, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502120104;
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
        cout << "FarmvilleDiv2 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
