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
typedef vector <int> VI;
typedef unordered_map <int,int> MAPII;
typedef unordered_set <int> SETI;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline bool SMIN(T &l,const T &r){return l<r?l=r,1:0;}
template<class T> inline bool SMAX(T &l,const T &r){return l>r?l=r,1:0;}
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
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 10/30/2018
 
 9:20-9:56 submit and hacked
 
 11:30-12:33 got AC after 3WA
 
 https://www.topcoder.com/blog/single-round-match-740-editorials/
 http://kmjp.hatenablog.jp/entry/2018/10/23/0900
 
 */

// 9:56 submit and hacked
// 11:30-12:33 AC after 3WA

int dp[31][5000*30+1];
int jump[31][5000*30+1];
class DieDesign {
public:
  vector<int> design(vector<int> A) {
    sort(A.begin(),A.end());
    int N=SZ(A);
    int sum=accumulate(A.begin(),A.end(),0);
    VI B=A; B.push_back(-1);
    sort(B.begin(),B.end());
    B.erase(unique(B.begin(),B.end()),B.end());
    int M=SZ(B);
    VI score(M,0);
    REP(i,M) score[i]=upper_bound(A.begin(),A.end(),B[i])-A.begin();
//    dumpAR(B);
//    dumpAR(score);
    
    MINUS(jump);
    MINUS(dp);
    dp[0][0]=0;
    REP(i,N)REPE(k,sum)REP(j,M) if(dp[i][k]>=0) {
      int x=B[j]+1;
      int a=dp[i+1][k+x],b=dp[i][k]+score[j];
      if(a<b) {
        dp[i+1][k+x]=b;
        jump[i+1][k+x]=j;
      }
    }
    
    int maxwin=-1,s=-1;
    REPE(x,sum) {
      if(maxwin<dp[N][x]) s=x,maxwin=dp[N][x];
    }
    assert(s!=-1);
    int rem=sum-s;
//    dump3(s,rem,sum);
    VI res;
    int i=N;
    while(i>0) {
      int j=jump[i][s],x=B[j]+1;
//      dump4(i,s,j,x);
      res.push_back(x);
      s-=x,--i;
    }
//    dump3(s,dp[0][s],dp[1][90713]);
    assert(s==0);
    assert(SZ(res)==N);
    res[N-1]+=rem;
//    dumpAR(res);
    assert(accumulate(res.begin(),res.end(),0)==sum);
    return res;
  }
};

class DieDesign_wrong {
public:
  vector<int> design(vector<int> A) {
    int N=SZ(A);
    int sum=accumulate(A.begin(),A.end(),0);
    set<int> S(A.begin(),A.end());
    VI res;
    int win=0;
    FORR(a,S) {
      int cnt=min(N,sum/(a+1));
      int rem=sum,x=0;
      VI B(N,0); REP(i,N) if(x<cnt) B[i]=a+1,++x,rem-=a+1;
      if(rem>0) B[N-1]+=rem;
      sort(B.begin(),B.end());
      assert(accumulate(B.begin(),B.end(),0)==sum);
      
      int y=0;
      REP(i,N)REP(j,N) y+=A[i]<B[j];
      if(y>win) res=B,win=y;
      dump2(a,y);
      dumpAR(B);
    }
    return res;
  }
};

// CUT begin
ifstream data("DieDesign.sample");

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

bool do_test(vector<int> pips, vector<int> __expected) {
    time_t startClock = clock();
    DieDesign *instance = new DieDesign();
    vector<int> __result = instance->design(pips);
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
        vector<int> pips;
        from_stream(pips);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(pips, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1540052529;
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
        cout << "DieDesign (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
