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
 
 8/10/2017
 
 8:40-8:55 design
 8:55-9:02 implement and submit (327.61 pt)
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+673
  - http://kmjp.hatenablog.jp/entry/2015/11/20/0900
  - http://kg86.hatenablog.com/entry/2016/01/18/142726
 
 24:31-24:35 add simpler at most 3 times loop solution
 24:36-24:43 add simple position check solution
 
 Key:
  - we can prove that sort happens at most 3 times
 
 Summary:
  - nice to figure out that result is at most 3
  - implementation is a bit verbose though, robust enough
  - revised solutions are beautiful 👍
 
 */

class BearSlowlySorts {
public:
  int minMoves(vector<int> W) {
    VI T=W; sort(T.begin(),T.end());
    int maxn = *max_element(W.begin(),W.end());
    int minn = *min_element(W.begin(),W.end());
    
    int maxi = find(W.begin(),W.end(),maxn)-W.begin();
    int mini = find(W.begin(),W.end(),minn)-W.begin();
    
    int N=SZ(W);

    if(mini==0&&maxi==N-1) return W==T ? 0 : 1;
    if(mini==0&&maxi!=N-1) return 1;
    if(mini!=0&&maxi==N-1) return 1;
    if(maxi==0&&mini==N-1) return 3;
    return 2;
  }
};

class BearSlowlySorts_loop {
public:
  int minMoves(vector<int> W) {
    VI T=W;
    sort(T.begin(),T.end());
    
    VI X=W, Y=W;
    int i=0;
    for(; i<3&&X!=T&&Y!=T; ++i) {
      if(i&1) {
        sort(X.begin()+1,X.end());
        sort(Y.begin(),Y.end()-1);
      } else {
        sort(Y.begin()+1,Y.end());
        sort(X.begin(),X.end()-1);
      }
    }
    return i;
  }
};

class BearSlowlySorts_org {
  public:
  int Inf=1e9;
  int N;
  VI T;
  int dfs(VI w, int LR, int prevLR) {
    if (T==w) return 0;
    
    VI w2=w;
    int res=Inf;
    if(LR==0&&prevLR!=LR) {
      sort(w2.begin(),w2.begin()+N-1);
      res=min(res,dfs(w2,1,0)+1);
    }
    if(LR==1&&prevLR!=LR) {
      sort(w.begin()+1,w.end());
      res=min(res,dfs(w,0,1)+1);
    }
    return res;
  }
  
  int minMoves(vector<int> W) {
    N=SZ(W);
    T=W;
    sort(T.begin(),T.end());
    int res=dfs(W,0,-1);
    res=min(res,dfs(W,1,-1));
    
    return res;
  }
};

// CUT begin
ifstream data("BearSlowlySorts.sample");

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

bool do_test(vector<int> w, int __expected) {
    time_t startClock = clock();
    BearSlowlySorts *instance = new BearSlowlySorts();
    int __result = instance->minMoves(w);
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
        vector<int> w;
        from_stream(w);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(w, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502379591;
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
        cout << "BearSlowlySorts (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
