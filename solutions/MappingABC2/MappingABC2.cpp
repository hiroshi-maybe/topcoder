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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;
constexpr int MOD = 1e9+7;

/**
 
 7/5/2017
 
 9:05 start
 9:30 need to remove duplicated pattern..
 9:50 time up

 20:18 http://kmjp.hatenablog.jp/entry/2017/01/23/0930
 20:48 https://community.topcoder.com/stat?c=problem_solution&rd=16850&rm=329617&cr=40173510&pm=14496
 21:22 passed samples and system test
 
 */

// O(N^4) time
class MappingABC2 {
public:
  int countStrings(vector<int> t) {
    int N=SZ(t);
    
    LL res=0;
    REP(ai,N) FOR(bi,ai+1,N) FOR(ci,bi+1,N) {
      int mask[55];
      FORR(n,t) mask[n]=(1|2|4);
      REP(i,N) {
        if(i<ai)       mask[t[i]]&=(2|4);
        else if(i==ai) mask[t[i]]&=1;
        else if(i< bi) mask[t[i]]&=(1|4);
        else if(i==bi) mask[t[i]]&=2;
        else if(i< ci) mask[t[i]]&=(1|2);
        else if(i==ci) mask[t[i]]&=4;
        else           mask[t[i]]&=(1|2|4);
      }
      
      LL cnt=1;
      FORR(n,t) {
        if (mask[n]==-1) continue;
        /*
        if (mask[n]==0) { cnt=0; break; }
        if (mask[n]==1||mask[n]==2||mask[n]==4) cnt*=1;
        if (mask[n]==(1|2)||mask[n]==(1|4)||mask[n]==(2|4)) cnt*=2;
        if (mask[n]==(1|2|4)) cnt*=3;*/
        cnt *= __builtin_popcount(mask[n]);
        cnt %= MOD;
        mask[n]=-1;
      }
      
      res += cnt;
      res %= MOD;
    }
    
    return res;
  }
};

// my wrong answer
class MappingABC2_wrong {
  public:
  int countStrings(vector<int> t) {
    SETI S;
    FORR(n,t) S.insert(n);
    int SN=SZ(S);
    if (SN<3) return 0;
    
    dumpAR(t);
    dump(SN);
    
    LL res=0;
    for(int n1=1; n1<=50; ++n1) {
      for(int n2=1; n2<=50; ++n2) {
        if (n1==n2) continue;
        for(int n3=1; n3<=50; ++n3) {
          if(n1==n3||n2==n3) continue;
          
          if(ok(n1,n2,n3,t)) {
            int x = pow(3.0,SZ(S)-3)-1;
//            dump4(n1,n2,n3,x);
            res += x;
            res %= MOD;
          }
        }
      }
    }
    
    return (int)res;
  }
  
  bool ok(int n1, int n2, int n3, VI &ns) {
    assert(n1!=n2&&n2!=n3&&n3!=n1);
    int i1=55,i3=-1;
    
    REP(i,SZ(ns)) {
      if(ns[i]==n1) i1=min(i,i1);
      if(ns[i]==n3) i3=max(i,i3);
    }
    
    if (i1==55||i1==-1||i3<i1) return false;
    
    REP(i,SZ(ns)) {
      if (ns[i]==n2&&i1<i&&i<i3) return true;
    }
    return false;
  }
};

// CUT begin
ifstream data("MappingABC2.sample");

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

bool do_test(vector<int> t, int __expected) {
    time_t startClock = clock();
    MappingABC2 *instance = new MappingABC2();
    int __result = instance->countStrings(t);
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
        vector<int> t;
        from_stream(t);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499270425;
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
        cout << "MappingABC2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
