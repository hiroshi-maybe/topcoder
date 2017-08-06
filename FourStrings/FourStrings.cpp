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
 
 9:04-10:23 submit (196.68 pt)
 - A LOT OF BUG. POOOOOR IMPLEMENTATION.
  - wrong index in merge()
 
 14:18-14:45 read editorials
 - https://apps.topcoder.com/wiki/display/tc/SRM+677
 - http://kmjp.hatenablog.jp/entry/2015/12/27/0900
 
 14:45-15:10 add simpler solution by @kmjp
 
 Key:
 - size is small. brute-force is a good option
 - simpler brute force and easy check is a key to quick and easy implementation like @kmjp's solution
 
 Summary:
 - 👍 nice to find a permutation
 - 👎 implementation is too complex
 - 👎 use built-in permutation next_permutation()
  - Note that pemutated set needs to be sorted. Spent 10 minutes to find the bug :(
 */

int Inf = 1e9;

class FourStrings {
public:
  int f(vector<string> SS) {
    int res=Inf;
    string s=SS[0];
    for(int i1=0; i1<=SZ(SS[1]); ++i1) {
      for(int i2=0; i2<=SZ(SS[2]); ++i2) {
        for(int i3=0; i3<=SZ(SS[3]); ++i3) {
          string t = s+SS[1].substr(i1)+SS[2].substr(i2)+SS[3].substr(i3);
          bool ok=true;
          FOR(i,1,4) if(t.find(SS[i])==string::npos) ok=false;
          if(ok)res=min(res,SZ(t));
        }
      }
    }
    return res;
  }
  
  int shortestLength(string a, string b, string c, string d) {
    vector<string> SS = {a,b,c,d};
    sort(SS.begin(),SS.end());
    
    int res=Inf;
    do {
      res = min(res, f(SS));
    } while(next_permutation(SS.begin(),SS.end()));
    return res;
  }
};

class FourStrings_org {
  public:
  
  string merge(string s, string t, int l) {
    REP(i,l) {
//      dump2(s[SZ(s)-l+i],t[i]);
      if(s[SZ(s)-l+i]!=t[i]) return "#";
    }
    return s+t.substr(l);
  }
  
  int f(string s, int p, vector<string> SS) {
    if(p==0) return f(SS[0],p+1,SS);
    if(p==4) return SZ(s);
    string t = SS[p];
    int res=Inf;
    if(t.find(s) != string::npos) res = min(res,f(t,p+1,SS));
    if(s.find(t) != string::npos) res = min(res,f(s,p+1,SS));
    REP(l,min(SZ(s),SZ(t))) {
      string m1=merge(s,t,l);
      if (m1!="#") res=min(res,f(m1,p+1,SS));
      string m2=merge(t,s,l);
      if (m2!="#") res=min(res,f(m2,p+1,SS));
    }
//    dump4(p,s,t,res);
    return res;
  }
  
  int perm(int p, vector<string> SS) {
    if (p==4) return f("",0,SS);
    
    int res=Inf;
    FOR(i,p,4) {
      swap(SS[i],SS[p]);
      res = min(res, perm(p+1,SS));
      swap(SS[i],SS[p]);
    }
    return res;
  }
  
  int shortestLength(string a, string b, string c, string d) {
    vector<string> SS = {a,b,c,d};
    return perm(0,SS);
  }
};

// CUT begin
ifstream data("FourStrings.sample");

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

bool do_test(string a, string b, string c, string d, int __expected) {
    time_t startClock = clock();
    FourStrings *instance = new FourStrings();
    int __result = instance->shortestLength(a, b, c, d);
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
        string a;
        from_stream(a);
        string b;
        from_stream(b);
        string c;
        from_stream(c);
        string d;
        from_stream(d);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, c, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502035472;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FourStrings (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
