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
 
 8/28/2017
 
 18:05-18:51 give up
 
 18:52-19:37 read editorials:
 - http://kmjp.hatenablog.jp/entry/2015/05/13/1000
  - http://kmjp.hatenablog.jp/entry/2015/05/13/0930
  - http://mayokoex.hatenablog.com/entry/2015/09/26/123718
 - http://codeforces.com/blog/entry/17856
  - writer's solution seems to be a bit different
    - Keep [AAAAOOOOO] window repeated
    - if window hits info[x], move last movable A to info[x].
 
 21:36-23:24 add solution
 
 key:
  - N is large. it's hard to iterate N.
  - |I| is small. it's easier to look at I from left to right
   - determined element is pretty sparse
  - if interval of free elements >=2*K, we'll have x cycle (x>=0) of repeated sequence
   - we need AT LEAST 2*K elements before I[x]
    - K to fix repeated sequence in cycle
    - buffer K to prevent I[x]'s apple
  - assignment is deterministic in greedy way from left to right
 
 summary:
  - kind of sweep line idea
  - guessed cycle though, I didn't have good idea to assign greedily
  - one of the most tough implementation problem
 
 */

class ApplesAndOrangesHard {
  public:
  int res=0,K;
  SETI is;
  deque<int> D;
  
  void assign(int cur) {
    D.push_back(cur); ++res;
    if(D.front()<=cur-K) D.pop_front();
    if(SZ(D)>K/2) {
      for(int i=SZ(D)-1; i>=0; --i) if(is.count(D[i])==0) {
        D.erase(D.begin()+i); --res;
        break;
      }
    }
  }
  
  int maximumApples(int N, int K, vector<int> I) {
    this->K=K;
    REP(i,SZ(I)) is.emplace(--I[i]);
    sort(I.begin(),I.end());
    I.push_back(N); // sentinel
    int cur=0;
    REP(j,SZ(I)) {
      int i=I[j];
      
      // at least 2*K elements before `i`
      if(cur<=i-2*K) {
        // this my original implementation is wrong because we don't have enough interval to fix repeated sequence
        // while((i-K-cur)%K>0) assign(cur++);
        // int cycle=(i-cur-1-K)/K;
        
        REP(_,K)assign(cur++);
        int cycle=(i-cur-1)/K;
        
        res += cycle*SZ(D);
        cur += cycle*K;
        FORR(k,D) k+=cycle*K;
      }
      for(; cur<=i&&cur<N; ++cur) assign(cur);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ApplesAndOrangesHard.sample");

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

bool do_test(int N, int K, vector<int> info, int __expected) {
    time_t startClock = clock();
    ApplesAndOrangesHard *instance = new ApplesAndOrangesHard();
    int __result = instance->maximumApples(N, K, info);
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
        int K;
        from_stream(K);
        vector<int> info;
        from_stream(info);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, info, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503968715;
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
        cout << "ApplesAndOrangesHard (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
