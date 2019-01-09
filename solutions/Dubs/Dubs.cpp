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
 
 7/23/2017
 
 8:32-8:57 passed system test (309.70 pt)
 
 spent some time to figure out x00 case was missing :(
 
 f(L,R) = f(0,R)-f(0,L-1)
 
 suppose n = x*100 + y
 f(0,n) = x*9 + y/11 + x(if x>0)

 12:35 add simpler solution of O(1) original one

 12:36 read editorial
 - https://apps.topcoder.com/wiki/display/tc/SRM+692
 
 searching z such that z = x*100 + y <= n
 <=> x*100 <= n-y
 <=> x <= (n-y)/100
 count(x) = ceil((n-y)/100)!!

 - take care of negative case like (21-22)/100 => we want 0 => use ceil()
  - (n-y)/100 > -1 is guaranteed. (n-y)/100 > -99/100
  - ceil((21-22)/100)=ceil(-0.01)=0
  - ceil((123-22)/100)=ceil(1.01)=2 (22 and 122)
  - ceil((122-22)/100)=ceil(1.00)=2 (22 and 122)
  - ceil(n/k) = floor((n+k)/k)
 
 13:20 other solutions
 - same as mine
  - https://community.topcoder.com/stat?c=problem_solution&rm=328874&rd=16747&pm=14278&cr=40096705
 
 Key
 - original solution is neat though, should understand how to solve by math help
 - how many multiples of k in range 0..n? => ceil(n/k)
 
 */

// O(10)=O(1) time
class Dubs {
public:
  LL f(LL n) {
    LL res=0;
    REP(k,10) res += (n-11*k+100)/100;
    
    return res;
  }
  
  long long count(long long L, long long R) {
    return f(R)-f(L-1);
  }
};

// O(1) time
class Dubs_org2 {
public:
  long long count(long long L, long long R) {
    --L; L=max(L,0LL);
    LL x1=R/100,y1=R%100,x2=L/100,y2=L%100;
    LL r = 10*x1+y1/11, l = 10*x2+y2/11;
    return r-l;
  }
};

// O(1) time
class Dubs_org {
  public:
  long long count(long long L, long long R) {
    --L; L=max(L,0LL);
    LL x1=R/100LL,y1=10*((R/10)%10)+R%10,x2=L/100,y2=10*((L/10)%10)+L%10;
    
    LL r = 9*x1+y1/11, l = 9*x2+y2/11;
    if(x1>0) r+=x1;
    if(x2>0) l+=x2;
    
    return r-l;
  }
};

// CUT begin
ifstream data("Dubs.sample");

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

bool do_test(long long L, long long R, long long __expected) {
    time_t startClock = clock();
    Dubs *instance = new Dubs();
    long long __result = instance->count(L, R);
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
        long long L;
        from_stream(L);
        long long R;
        from_stream(R);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500823911;
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
        cout << "Dubs (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
