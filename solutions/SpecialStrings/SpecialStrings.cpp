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
 
 9/20/2017
 
 8:48-9:46 analysis
 9:46-9:53 implementation (380.95 pt)
 9:54 WA for "0"
 10:00 it turns out analysis is wrong
 
 19:10-19:42 read editorials and add solution
  - https://apps.topcoder.com/wiki/display/tc/SRM+634
  - http://kmjp.hatenablog.jp/entry/2014/09/27/1000

 Suppose we have s1="0111111011110111011100111111".
 Next lexicographically larger sequence is s2 below:
 
 s1="0111111011110111011100111111"
 s2="0111111011110111011101111111"
                          ^
 
 If s2 is not special, we can try next 0 column

 s1="0111111011110111011100111111"
 s3="0111111011110111011110111111"
                         ^
 
 if we have more 1s in right columns, it's more likely to be special.
 we can fill 1s and check if it's special

 s1 ="0111111011110111011100111111"
 s3'="0111111011110111011111111111"
                          ^

 If that's not the case, keep looking at next column...
 
 s1 ="0111111011110111011100111111"
 s4 ="0111111011111111111111111111"
                  ^
 
 Ok, this is special. Now this is upper bound of optimal result.
 However there may be more optimal one less than s4.
 We can check if right columns can be 0 one by one.
 
 eventually we'll get optimal one:
 
 s1 ="0111111011110111011100111111"
 res="0111111011111101111111111111"
                  ^ ^
 
 So algorithm follows two steps:
 1. find least significant column where xxxx1111111 is special. It's candidate of result.
 2. try to find smaller sequence by trying 1->0 in left to right.
 
 key:
  - understanding of lexicographically larger sequence
    - replacing more right 0 with 1 makes lexicographically smaller sequence which is larger than original sequence
      - original: "000". "000" < "001" < "010"
  - if "xxx111111" is special, it's an upper bound of optimal result (baseline)
    - try 0 at each column to get as small sequence as possible under the baseline
    - try in left to right direction because change of right column does not break u<v condition in left.
 
 summary:
  - I tried to solve observation that popcount is increasing though, it was due to weak sample
    - no proof that it's always true. thus system test failed
  - I focused on right most 0 and figured out "0000111111" is better than "0000100000"
  - I didn't have idea to test each column from left to right in greedy manner
 
 */

// O(N^4) time
class SpecialStrings {
public:
  bool special(string s) {
    int N=SZ(s);
    FOR(l,1,N) {
      string u=s.substr(0,l),v=s.substr(l);
      if(u>=v) return false;
    }
    return true;
  }
  
  string findNext(string s) {
    int N=SZ(s);
    for(int i=N-1; i>=0; --i) if(s[i]=='0') {
      string t=s;
      FOR(j,i,N) t[j]='1';
      if(!special(t)) continue;
      FOR(j,i+1,N) {
        t[j]='0';
        if(!special(t)) t[j]='1';
      }
      assert(special(t));
      return t;
    }
    
    return "";
  }
};

class SpecialStrings_wrong {
  public:
  string findNext(string s) {
    int N=SZ(s);
    for(int i=N-2; i>=0; --i) if(s[i]=='0') {
      swap(s[i],s[i+1]);
      string u=s.substr(0,i+1),v=s.substr(i+1);
      //      dump2(u,v);
      if(u<v) return s;
      s[i+1]='1';
      u=s.substr(0,i+1),v=s.substr(i+1);
//      dump2(u,v);
      if(u<v) return s;
      return "";
    }
    
    return s=="0"?"1":"";
  }
};

// CUT begin
ifstream data("SpecialStrings.sample");

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

bool do_test(string current, string __expected) {
    time_t startClock = clock();
    SpecialStrings *instance = new SpecialStrings();
    string __result = instance->findNext(current);
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
        string current;
        from_stream(current);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(current, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505922470;
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
        cout << "SpecialStrings (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
