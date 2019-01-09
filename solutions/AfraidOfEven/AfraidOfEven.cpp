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
 
 10/5/2018
 
 13:23-14:00 give up
 14:40-15:05 read submit solutions and figured out my mistake.
 
 Mistake of runtime analysis. Multiplying 2^a and 2^b for S[0] and S[1] is just 32*32. Not 2^32*2^32 😡
 
 https://topcoder.g.hatena.ne.jp/jackpersel/20101021/1287676048
 http://topcoder.g.hatena.ne.jp/chokudai/20101023/1287848612
 http://rsujskf.blog32.fc2.com/blog-entry-1641.html
 http://expnotes9.blog.fc2.com/page-4.html
 
 I had no idea about how to upper-bound result elements. However actually it's possible to analyze by focusing on parity of difference.
 
 There are two cases:
 1) difference is even
 
 In this case, A[i] cannot be even because in such a case, (A[i]-A[i-1])/2 gives lexicographically smaller sequence.
 Thus this case holds only when given array with all odd elements is already expected sequence.
 
 2) difference is odd
 
 In this case, even and odd elements show up alaternatively.
 Thus, S[0] and S[2] are odd, or S[1] and S[3] are odd.
 S[i]<=1000 holds. Thus S[i]-S[i-1]<=1000. The largest odd element is 999(<=1000).
 The largest element is upper-bounded by 1996 (S={2,999,1996})
 
 Summary:
  - Critical mistake of runtime analysis...
  - Parity of give element is fixed. Dig parity more deeply. In this case, parity of difference matters.
 
 */
class AfraidOfEven {
  public:
  vector<LL> T;
  bool ok(vector<LL> A) {
    int N=SZ(A);
    REP(i,N) {
      if(A[i]%T[i]!=0) return false;
      LL a=A[i]/T[i];
      if(a&(a-1)) return false;
    }
    return true;
  }
  vector<int> restoreProgression(vector<int> S) {
    int N=SZ(S);
    REP(i,N) this->T.push_back(S[i]);
    LL s0=S[0],s1=S[1];
    REP(i,32) {
      LL a0=s0<<i;
      REP(j,32) {
        vector<LL> A(N);
        LL a1=s1<<j;
        A[0]=a0,A[1]=a1;
        LL d=a1-a0;
        FOR(k,2,N) A[k]=A[k-1]+d;
        if(ok(A)) {
          VI res(N); REP(i,N) res[i]=A[i];
          return res;
        }
      }
      
    }
    return vector<int>();
  }
};

// CUT begin
ifstream data("AfraidOfEven.sample");

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

bool do_test(vector<int> seq, vector<int> __expected) {
    time_t startClock = clock();
    AfraidOfEven *instance = new AfraidOfEven();
    vector<int> __result = instance->restoreProgression(seq);
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
        vector<int> seq;
        from_stream(seq);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(seq, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1538771002;
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
        cout << "AfraidOfEven (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
