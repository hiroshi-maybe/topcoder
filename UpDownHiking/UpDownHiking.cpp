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
 
 7/14/2017
 
 8:22-8:37 (200.79 pt)
 
 - It took more time because my first approach to enumerate altitude instead of days didn't work :(
 - I used ceil() though, input should be `double` :(
 
 18:18 add height enumeration solution by ceil
 
 18:25-18:30 add binary search solution
 - https://community.topcoder.com/stat?c=problem_solution&rm=329292&rd=16803&pm=14398&cr=40181036
 - https://community.topcoder.com/stat?c=problem_solution&rm=329293&rd=16803&pm=14398&cr=23143666
 - (x+A-1)/A == ceil(x/A) in integer x
 
 */

// O(lg N*A)
class UpDownHiking {
public:
  int maxHeight(int N, int A, int B) {
    int good=1, bad=2500;
    while(abs(good-bad)>1) {
      int mid=(good+bad)>>1;
      int d = (mid+A-1)/A + (mid+B-1)/B;
      
      if(d<=N) good=mid;
      else bad=mid;
    }
    
    return good;
  }
};

// O(N*A)
class UpDownHiking_height {
public:
  int maxHeight(int N, int A, int B) {
    int res=1;
    for(double h=1.0; h<=2500; ++h) {
      if (ceil(h/(double)A)+ceil(h/(double)B)<=N) res=h;
    }
    
    return res;
  }
};

// O(N)
class UpDownHiking_org {
  public:
  int maxHeight(int N, int A, int B) {
    int res=0;
    REP(a,N) {
      res = max(res, min(A*a, B*(N-a)));
    }
    
    return res;
  }
};

// CUT begin
ifstream data("UpDownHiking.sample");

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

bool do_test(int N, int A, int B, int __expected) {
    time_t startClock = clock();
    UpDownHiking *instance = new UpDownHiking();
    int __result = instance->maxHeight(N, A, B);
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
        int N;
        from_stream(N);
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500045714;
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
        cout << "UpDownHiking (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
