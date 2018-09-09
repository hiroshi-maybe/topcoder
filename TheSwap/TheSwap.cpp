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
 
 9/8/2018
 
 16:03-16:07 analysis
 16:27 (160.36 pt)
 16:44 give up
 
 N=8799, K=2 => res=9987
 
 http://apps.topcoder.com/wiki/display/tc/SRM+437
 https://chngng.blogspot.com/2015/05/srm-437-div1-easy-theswap.html
 http://rsujskf.blog32.fc2.com/blog-entry-224.html
 
 If there are multiple largest digits, there is no optimal strategy to select specific one.
 Suppose we have number "bc...aa..." (a>b>c)
 
 If K=1, swap(b,second a) is better than swap(b,first a)
 
 "ac...ab..." > "ac...ba..."
 
 However if K=2, swap(b,first a) and swap(c,second a) is the best.
 Thus we cannot say that swapping `b` with first or second `a` is optimal.
 Search by DP is necessary.
 
 17:23 read editorial and add solution
 
 */

class TheSwap {
public:
  map<II,int> memo;
  VI enc(int N) {
    VI D;
    while(N>0) D.push_back(N%10),N/=10;
    reverse(D.begin(),D.end());
    return D;
  }
  int dec(VI &D) {
    int res=0;
    REP(i,SZ(D)) res=10*res+D[i];
    return res;
  }
  int f(int n, int k) {
    if(k==0) return n;
    if(memo.count({n,k})) return memo[{n,k}];
    int &res=memo[{n,k}];
    res=-1;
    VI D=enc(n);
    int M=SZ(D);
    REP(j,M)REP(i,j) {
      if(i==0&&D[j]==0) continue;
      swap(D[i],D[j]);
      SMAX(res,f(dec(D),k-1));
      swap(D[i],D[j]);
    }
    return res;
  }
  
  int findMax(int N, int K) {
    memo.clear();
    return f(N,K);
  }
};

class TheSwap_wrong {
  public:
  int findMax(int N, int K) {
    VI D;
    while(N>0) D.push_back(N%10),N/=10;
    reverse(D.begin(),D.end());
//    dumpAR(D);
    int k=K,M=SZ(D),p=0;
    if(count(D.begin(),D.end(),0)==M-1) return -1;
    while(k>0&&p<M-1) {
      int q=p;
      FOR(i,p+1,M) {
        if(D[i]==0) continue;
        if(q!=p&&D[q]==D[i]) {
          q=i;
        } else if(D[q]<D[i]) q=i;
      }
      if(p!=q) {
        dump2(p,q);
        --k,swap(D[q],D[p]);
      }
      ++p;
//      dumpAR(D);
    }
    if(k>0) {
      REP(i,M-1) if(D[i]==D[i+1]) k=0;
      if(k%2==1) {
        swap(D[M-1],D[M-2]);
      }
    }
    
    int res=0;
    REP(i,M) res=10*res+D[i];
    return res;
  }
};

// CUT begin
ifstream data("TheSwap.sample");

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

bool do_test(int n, int k, int __expected) {
    time_t startClock = clock();
    TheSwap *instance = new TheSwap();
    int __result = instance->findMax(n, k);
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
        int n;
        from_stream(n);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536447818;
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
        cout << "TheSwap (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
