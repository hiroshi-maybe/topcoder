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

LL gcd(LL a, LL b) {
  return b==0?a:gcd(b,a%b);
}

LL lcm(LL a, LL b) {
  return a*b/gcd(a,b);
}

LL gcd(vector<LL> ns) {
  LL res=1;
  if(SZ(ns)==1) return res;
  res=gcd(ns[0],ns[1]);
  FOR(i,2,SZ(ns)) {
    res=gcd(res,ns[i]);
  }
  return res;
}

/*
 
 10/16/2017
 
 9:05-9:55 1WA (203.66 pt)
 18:33-19:34 system test passed
 
 Tried all the LCM leveraging Associative laws lcm(a,b,c) = lcm(a,lcm(b,c))
  - LCM: https://en.wikipedia.org/wiki/Least_common_multiple

 Now I get proof of running time of my original solution.
 If we build LCM by only divisors of X, LCM cannot be larger than X, because LCM is sum set of divisors of X.
 That means size of set of possible LCM is upper-bounded by number of divisors of X.
 X<=10^9. Highly composit number shows that number of divisors of X is less than 1440.
   - HCN: http://wwwhomes.uni-bielefeld.de/achim/highly.txt
 Running time is less than 1440*lg 10^9.
 
 editorial:
  - res = X==lcm { S[i] : S[i] | X }
    - https://apps.topcoder.com/wiki/display/tc/SRM+611
    - http://torus711.hatenablog.com/entry/20140305/p3
    - http://topcoder.g.hatena.ne.jp/agw/20140310
 
 summary:
  - solved though, no proof for running time 👎
  - lcm(a,b)=a*b/gcd(a,b) though, lcm(a,b,c,d)!=a*b*c*d/gcd(a,b,c,d)
   - lcm(2,2,2,3,4,12) = 12 != 2*2*2*3*4*12/gcd(2,2,2,3,4,12) (=566)
   - this misunderstanding brought my first wrong answer
  - I sticked to formula of lcm(a,b)=a*b/gcd(a,b) too much. Even worse I trusted wrong formula 👎
   - at least confirm small example
 
 submit solution:
  - same as editorial:
   - https://community.topcoder.com/stat?c=problem_solution&rm=320878&rd=15844&pm=13040&cr=23304834
   - https://community.topcoder.com/stat?c=problem_solution&rm=320916&rd=15844&pm=13040&cr=40003080
   - https://community.topcoder.com/stat?c=problem_solution&rm=320904&rd=15844&pm=13040&cr=23304831
   - https://community.topcoder.com/stat?c=problem_solution&rm=320886&rd=15844&pm=13040&cr=40002951
 
 */

class LCMSetEasy {
public:
  string yes= "Possible",no="Impossible";
  string include(vector<int> S, int X) {
    LL x=1;
    FORR(n, S) if(X%n==0) x=lcm(x,n);
    
    return x==X?yes:no;
  }
};

// refined my original solution
class LCMSetEasy_set {
public:
  string yes= "Possible",no="Impossible";
  string include(vector<int> S, int X) {
    set<LL> L;
    FORR(n, S) if(X%n==0) {
      set<LL> L2(L);
      L2.emplace(n);
      
      FORR(l, L) {
        LL l2=lcm(l,n);
        L2.emplace(l2);
      }
      L=L2;
    }
    
//    dumpAR(L);
    
    return L.count(X)?yes:no;
  }
};

class LCMSetEasy_org {
public:
  string yes= "Possible",no="Impossible";
  string include(vector<int> S, int X) {
    set<LL> L;
    FORR(n, S) if(X%n==0) {
//      dump(n);
      if(n==X) return yes;
//      map<LL, set<set<LL>>> D2(D.begin(),D.end());
      set<LL> L2(L);
      L2.emplace(n);
      
      FORR(l, L) {
        LL l2=lcm(l,n);
        if(l2==X) return yes;
        if(l2>1LL*X*X) continue; // unnecessary check
        L2.emplace(l2);
      }
      L=L2;
    }
    
    return no;
  }
};

// I thought lcm(a,b,c,d)=a*b*c*d/gcd(a,b,c,d) though, this is NOT true
class LCMSetEasy_wrong {
  public:
  string yes= "Possible",no="Impossible";
  string include(vector<int> S, int X) {
    map<LL, set<set<LL>>> D;
    FORR(n, S) if(X%n==0) {
      dump(n);
      map<LL, set<set<LL>>> D2;
      set<LL> sss={n};
      D2[n].emplace(sss);

      FORR(kvp, D) {
        LL d=kvp.first,d2=d*n;
        dump3(d,n,d*n);
//        if(1LL*X*X>=d) {
//          dump(SZ(kvp.second));
          FORR(ns, kvp.second) {
//            dump(SZ(ns));
            set<LL> ns2=ns;
            ns2.emplace(n);
            D2[d2].emplace(ns2);
          }
//        }
      }
      D=D2;
    }
    
    dump(SZ(D));
    FORR(kvp,D) {
      LL d=kvp.first;
      dump(d);
      if(d%X!=0) continue;
      FORR(ns,kvp.second) {
        vector<LL> ns2(ns.begin(),ns.end());
//        dumpAR(ns2);
        LL gcd2=gcd(ns2);
        dump3(gcd2,gcd2*X,d);
        if(gcd2*X==d) return yes;
      }
    }
    
    return no;
  }
};

// CUT begin
ifstream data("LCMSetEasy.sample");

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

bool do_test(vector<int> S, int x, string __expected) {
    time_t startClock = clock();
    LCMSetEasy *instance = new LCMSetEasy();
    string __result = instance->include(S, x);
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
        vector<int> S;
        from_stream(S);
        int x;
        from_stream(x);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, x, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508169902;
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
        cout << "LCMSetEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
