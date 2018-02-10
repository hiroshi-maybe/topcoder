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
 
 2/9/2018
 
 9:21-9:43 analysis
 9:44-9:59 implement and submit (494.69 py), but MLE
 10:00-10:42 Did boring memory optimization and ACC
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+534
  - http://kmjp.hatenablog.jp/entry/2014/01/06/0930
  - https://topcoder.g.hatena.ne.jp/firewood/20120225/1330153505
 
 Key:
  - At most 26 values in [1,10000]
  - 26^5 32 bit integer ≈ 50MB memory
 
 Summary:
  - boring memory optimization
 
 */
const int MOD=1000000007;

int memo[26][26][26][26][26];
VI X[5];
class EllysFiveFriends {
public:
  VI seq(int n) {
    set<int> S;
    S.emplace(n);
    while(n>0) {
      if(n%2==1) S.emplace(n-1);
      S.emplace(n/2);
      n/=2;
    }
    VI res(S.rbegin(),S.rend());
    dumpAR(res);
    return res;
  }
  int f(VI P) {
    int &res=memo[P[0]][P[1]][P[2]][P[3]][P[4]];
    if(res>=0) return res;
    bool done=true;
    REP(i,5) done&=(P[i]==SZ(X[i])-1);
    if(done) return res=1;
    
    //    dumpAR(P);
    res=0;
    REP(i,5) {
      int i1=i,i2=(i+1)%5;
      int p1=P[i1],p2=P[i2];
      int a=X[i1][p1],b=X[i2][p2];
      if(a==0||b==0) continue;
      if(a%2==1&&b%2==1) {
        P[i1]++,P[i2]++;
        res=((LL)res+f(P))%MOD;
        P[i1]=p1,P[i2]=p2;
      }
      int d1=1,d2=1;
      if(X[i1][p1+1]==a/2) d1=1;
      else if(X[i1][p1+2]==a/2) d1=2;
      if(X[i2][p2+1]==b/2) d2=1;
      else if(X[i2][p2+2]==b/2) d2=2;
      
      P[i1]+=d1,P[i2]+=d2;
      res=((LL)res+f(P))%MOD;
      P[i1]=p1,P[i2]=p2;
    }
    return res;
  }
  int getZero(vector<int> ns) {
    REP(i,5) X[i]=seq(ns[i]);
    MINUS(memo);
    return f({0,0,0,0,0});
  }
};

/*
map<VI,LL> memo;
class EllysFiveFriends {
public:
  LL f(VI X) {
    if(memo.count(X)) return memo[X];
    LL &res=memo[X];
    bool done=true;
    REP(i,5) done&=X[i]==0;
    if(done) return res=1LL;
    
    res=0;
    REP(i,5) {
      int i1=i,i2=(i+1)%5;
      int a=X[i1],b=X[i2];
      if(X[i1]==0||X[i2]==0) continue;
      if(X[i1]%2==1&&X[i2]%2==1) {
        X[i1]-=1,X[i2]-=1;
        res+=f(X),res%=MOD;
        X[i1]=a,X[i2]=b;
      }
      X[i1]/=2,X[i2]/=2;
      res+=f(X),res%=MOD;
      X[i1]=a,X[i2]=b;
    }
    return res;
  }
  int getZero(vector<int> ns) {
    memo.clear();
    return f({ns[0],ns[1],ns[2],ns[3],ns[4]});
  }
};*/

// CUT begin
ifstream data("EllysFiveFriends.sample");

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

bool do_test(vector<int> numbers, int __expected) {
    time_t startClock = clock();
    EllysFiveFriends *instance = new EllysFiveFriends();
    int __result = instance->getZero(numbers);
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
        vector<int> numbers;
        from_stream(numbers);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numbers, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1518196886;
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
        cout << "EllysFiveFriends (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
