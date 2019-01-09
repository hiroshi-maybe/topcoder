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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/15/2018
 
 8:40-8:48 analysis
 8:49-8:58 submit (375.79 pt), but 1WA
 10:20-10:23 bug fix of m=n case and ACC
 
 I missed [2,2,2,0] case 👎
 If we have k elements of `2`, we have 2^k cases.
 That's because we can assign rabbit or cat to two indices independently.
 If we have 1 like [2,2,2,1,1], we can assign cat or rabbit.
 In following `1`s, they are already determined.
 Thus..

 res = 2^k     if no 1
       2^(k+1) otherwise
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+511
  - http://d.hatena.ne.jp/kusano_prog/20110702/1309631927
  - https://topcoder.g.hatena.ne.jp/jackpersel/20110703/1309682797
  - http://hos0lyric.blog89.fc2.com/blog-entry-36.html
  - http://kg86.hatenablog.com/entry/20130704/1372913735
  - http://mayokoex.hatenablog.com/entry/2015/07/01/122303
  - http://purple-jwl.hatenablog.com/entry/20130322/1363947160
  - https://www.muo.jp/2011/07/topcoder-srm-srm-511-div2-easy.html
  - http://mainly-coding.blogspot.com/2011/07/topcoder-srm-511.html?m=0
  - https://chngng.blogspot.jp/2015/05/srm-511-div1-easy-zoo.html?m=1

 Summary:
  - Approach was straightforward though, I fell in a pitfall of cornercase 👎
  - I should have come up with counting sort
 
 */
class Zoo {
  public:
  long long theCount(vector<int> X) {
    int cnt[41]={0};
    int N=SZ(X);
    REP(i,N) cnt[X[i]]++;
    REP(i,40) {
      int c=cnt[i],c2=cnt[i+1];
      if(c>2) return 0;
      if(c2>c) return 0;
      // 2>=c>=c2
    }
    int x=0;
    while(x<=40&&cnt[x]==2) ++x;
    dumpAR(X);
    dump(x);
    LL y=count(cnt,cnt+41,1)==0?1LL:2LL;
    return y*(1LL<<x);
  }
};

// CUT begin
ifstream data("Zoo.sample");

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

bool do_test(vector<int> answers, long long __expected) {
    time_t startClock = clock();
    Zoo *instance = new Zoo();
    long long __result = instance->theCount(answers);
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
        vector<int> answers;
        from_stream(answers);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(answers, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521128435;
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
        cout << "Zoo (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
