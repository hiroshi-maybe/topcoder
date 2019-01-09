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
 
 10/8/2018
 
 16:18-16:56 give up
 17:24 read editorial and got AC
 
 I had an idea to check 1..N for all C[i].
 However I was not sure if it's valid to determine each C[i] independently.
 
 http://apps.topcoder.com/wiki/display/tc/SRM+495
 
 Important observation is that, possible values for C[i] is some range.
 If we start first valid number from C[0], we should find out minimum possible value for C[i].
 We can figure out maximum possible value from right to left similarly.
 If min value == max value, it's determined. Otherwise it cannot be determined.
 
 Key:
  - Uniquely determined <=> range has single value
  - There is monotonical property
   - If C[0] is smaller, C[i] can be smaller. If C[N-1] is larger, C[i] is larger
   - It's possible to know lower/upper-bound of C[i]
 
 */
int P[1010];
void sieve(int N) {
  REPE(i,N) P[i]=1;
  P[1]=0;
  for(int p=2; p<=N; ++p) if(P[p]==1) {
    for(int q=p*p; q<=N; q+=p) P[q]=0;
  }
}

class ColorfulCards {
  public:
  vector<int> theCards(int N, string C) {
    sieve(N);
    int K=SZ(C);
    VI res(K,-1);
    REP(i,K) {
      VI S;
      FORE(n,1,N) if(P[n]==(C[i]=='R')) {
        bool lok=true;
        int k=n;
        for(int j=i-1; j>=0; --j) {
          --k;
          if(C[j]=='R') {
            while(k>=1&&!P[k]) --k;
          } else {
            while(k>=1&&P[k]) --k;
          }
          if(k<1) {
            lok=false;
            break;
          }
        }
        k=n;
        bool rok=true;
        for(int j=i+1; j<K; ++j) {
          ++k;
          if(C[j]=='R') {
            while(k<=N&&!P[k]) ++k;
          } else {
            while(k<=N&&P[k]) ++k;
          }
          if(k>N) {
            rok=false;
            break;
          }
        }
//        dump3(i,n,k);
//        dump4(i,n,lok,rok);
        if(lok&&rok) S.push_back(n);
      }
      if(SZ(S)==1) res[i]=S.front();
    }
    return res;
  }
};

// CUT begin
ifstream data("ColorfulCards.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(int N, string colors, vector<int> __expected) {
    time_t startClock = clock();
    ColorfulCards *instance = new ColorfulCards();
    vector<int> __result = instance->theCards(N, colors);
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
        string colors;
        from_stream(colors);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, colors, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539040704;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 275 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ColorfulCards (275 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
