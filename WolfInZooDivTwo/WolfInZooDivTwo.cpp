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

// note that the last empty element is trimmed
vector<string> split(const string &s, char c) {
  vector<string> res;
  
  istringstream ss(s);
  string token;
  while(getline(ss,token,c)) {
    res.push_back(token);
  }
  
  return res;
}

/*
 
 12/3/2017
 
 16:36-17:15 analysis
 17:16-17:49 time up. Sample 2 doesn't pass.
 
 12/4/2017
 
 18:00-18:22 Taking a look at editorial and design recurrence relation.
 18:51 system test passed
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+578
  - http://emkcsharp.hatenablog.com/entry/SRM578/WolfInZooDivTwo
  - http://kmjp.hatenablog.jp/entry/2013/05/03/1030
 
 If we put wolf at position i, then it may unlock several overlapping intervals.
 We need to make sure that interval rule is satisified at the end of interval.
 If not, we MUST put a wolf not to violate rule.

 In order to figure out that the interval is filled, there should be at least one wolf in the interval.
 If we remember the last position of wolf, it's sufficient to make a decision.
 
 f(i,last) = f(i+1,last) if last>= max { l : l=interval.left, interval.right = i }
           + f(i+1,   i)
 f(N,   _) = 1
 
 res = f(0,-1)
 
 Key:
  - Make a decision with end of intervals to make sure rule is not violated
  - Remembering the last position of wolf so far is sufficient and necessary to make a choice
 
 Summary:
  - Not bad to focus on intervals though, analysis of a case [x,x] was missing
  - Also my own idea was not tricky. I didn't have clear proof of correctness
   - I got WA in the large sample 2
 
 Iterative DP: https://community.topcoder.com/stat?c=problem_solution&rm=317290&rd=15498&pm=12533&cr=23155968
 
 */

// O(N^2) time
constexpr int MOD = 1e9+7;
int MAXL[305];
LL memo[301][301];
class WolfInZooDivTwo {
public:
  int N;
  LL f(int i, int last) {
    LL &res=memo[i][last];
    if(res>=0) return res;
    if(i==N) return 1LL;
    
    res=0;
    bool ok=last-1>=MAXL[i];
    
    if(ok) res+=f(i+1, last);
    res+=f(i+1,i+1),res%=MOD;
    
    return res;
  }
  
  VI parse(vector<string> SS) {
    string S="";
    FORR(s,SS) S+=s;
    vector<string> ss=split(S,' ');
    VI res;
    REP(i,SZ(ss)) res.push_back(stoi(ss[i]));
    return res;
  }
  int count(int N, vector<string> _L, vector<string> _R) {
    this->N=N;
    MINUS(MAXL);
    VI LL=parse(_L),RR=parse(_R);
    assert(SZ(LL)==SZ(RR));
    MINUS(memo);
    REP(i,SZ(LL)) {
      int l=LL[i],r=RR[i];
      MAXL[r]=max(MAXL[r],l);
    }
    
    return f(0,0);
  }
};

// This didn't pass sample #2
// It's hard to figure out what it wrong though, at least test case with interval [x,x] does not pass.
int sum[301];
int E[301];
class WolfInZooDivTwo_wrong {
  public:
  int N;
  LL memo[301][51];
  LL f(int i, int b) {
    if(b<0) return 0;
    if(i==N) {
      assert(b==0);
      return 1LL;
    }
    LL &res=memo[i][b];
    if(res>=0) return res;
    res=0;
    int b1=min(b+sum[i],sum[i])-E[i],b2=b-E[i];
    LL x1=f(i+1, b1);
    LL x2=f(i+1, b2);
    dump4(i,b,b1,b2);
    res=(x1+x2)%MOD;
    
    dump3(i,b,res);
    return res;
  }
  
  VI parse(vector<string> SS) {
    string S="";
    FORR(s,SS) S+=s;
    vector<string> ss=split(S,' ');
    VI res;
    REP(i,SZ(ss)) res.push_back(stoi(ss[i]));
    return res;
  }
  int count(int N, vector<string> LL, vector<string> RR) {
    this->N=N;
    VI L=parse(LL),R=parse(RR);
    assert(SZ(L)==SZ(R));
    MINUS(memo);
    ZERO(sum); ZERO(E);
    REP(i,SZ(L)) {
      int l=L[i],r=R[i];
      for(int x=l; x<=r; ++x) {
        ++sum[x];
      }
      ++E[r];
    }
    
    return f(0,0);
  }
};

// CUT begin
ifstream data("WolfInZooDivTwo.sample");

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

bool do_test(int N, vector<string> L, vector<string> R, int __expected) {
    time_t startClock = clock();
    WolfInZooDivTwo *instance = new WolfInZooDivTwo();
    int __result = instance->count(N, L, R);
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
        vector<string> L;
        from_stream(L);
        vector<string> R;
        from_stream(R);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, L, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512347793;
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
        cout << "WolfInZooDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
