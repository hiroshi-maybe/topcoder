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
 
 4/9/2018
 
 19:08-19:33 analysis
 19:50 I found a lot of corner cases...
 20:25 finish first implementation
 
 22:30 1WA
 23:43 ACC 7WA? Pretty boring problem to take care of tons of corner cases.
 
 4/10/2018
 
 Read editorial and add simpler solution inspired by @kmjp
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+500
  - http://kmjp.hatenablog.jp/entry/2014/04/20/1030
   - cleanest solution in editorials
  - http://topcoder.g.hatena.ne.jp/JAPLJ/20110320/1300569561
   - Inclusion exclusion principle as my solution
  - http://d.hatena.ne.jp/kusano_prog/20110403/1301846155
  - http://kyuridenamida.hatenablog.com/entry/2011/03/20/045304
 
 Official editorial is avoiding corner case by computing sequence up to `500000000`.
 Another trick in the editorial is storing vector in the set. That uses a lot of memory though.
 
 Key:
  - Prime factorization works
  - To minimize corner cases, just computing sequence up to `500000000` is easy
 
 Summary:
  - Tons of corner cases. I don't like this kind of problem 👎
 
 */

map<int,int> facts(int x) {
  map<int,int> res;
  for(int p=2; p*p<=x; ++p) if(x%p==0) {
    while(x%p==0) res[p]++, x/=p;
  }
  if(x>1) res[x]++;
  return res;
}

class GeometricProgressions {
public:
  int count(int b1, int q1, int n1, int b2, int q2, int n2) {
    int B[2]={b1,b2},Q[2]={q1,q2},N[2]={n1,n2};
    vector<II> zero={make_pair(0,1)};
    set<vector<II>> S;
    REP(i,2) {
      if(B[i]==0) {
        S.emplace(zero);
        continue;
      }
      map<int,int> cur=facts(B[i]),q=facts(Q[i]);
      REP(j,N[i]) {
        vector<II> x;
        FORR(kvp,cur) x.emplace_back(kvp.first,kvp.second);
        S.emplace(x);
        
        if(Q[i]==0&&j>0) {
          S.emplace(zero);
          continue;
        }
        if(Q[i]==1) continue;
        FORR(kvp,q) cur[kvp.first]+=kvp.second;
      }
    }
    return SZ(S);
  }
};

class GeometricProgressions_org {
  public:
  MAPII facts(int x) {
    MAPII res;
    for(int p=2; p*p<=x; ++p) if(x%p==0) {
      while(x%p==0) res[p]++, x/=p;
    }
    if(x>1) res[x]++;
    return res;
  }
  
  int f(int p, int i, int ubj, map<int, II> &M1, map<int, II> &M2) {
    LL A=M1[p].first*i+M1[p].second;
//    dump4(p,i,ubj,A);
    if(M2[p].first==0) return M2[p].second==A?-1:-2;
    LL x=A-M2[p].second;
    if(x<0||(x%M2[p].first!=0)) return -2;
    LL y=x/M2[p].first;
    if(y>=ubj) return -2;
    return y;
  }
  int count(int b1, int q1, int n1, int b2, int q2, int n2) {
    if(q1==1) n1=1;
    if(q2==1) n2=1;
    if(q1==0) n1=n1>1?2:1;
    if(q2==0) n2=n2>1?2:1;

    dump3(b1,q1,n1);
    dump3(b2,q2,n2);
    
    if(b1==0&&b2==0) return 1;
    if(b1==0) return q2==0&&n2>1?2:n2+1;
    if(b2==0) return q1==0&&n1>1?2:n1+1;
//    if(q1==0&&q2==0) return (b1==b2?1:2)+1;
    
    map<int, II> M1, M2;
    MAPII bs=facts(b1);
    FORR(kvp,bs) M1[kvp.first].second=kvp.second;
    MAPII as=facts(q1);
    FORR(kvp,as) M1[kvp.first].first=kvp.second;
    MAPII bs2=facts(b2);
    FORR(kvp,bs2) M2[kvp.first].second=kvp.second;
    MAPII as2=facts(q2);
    FORR(kvp,as2) M2[kvp.first].first=kvp.second;

    if((q1==0||q1==1)&&(q2==0||q2==1)) {
      SETI S;
      S.emplace(b1),S.emplace(b2);
      if(n1>1) S.emplace(b1*q1);
      if(n2>1) S.emplace(b2*q2);
      return SZ(S);
    }
    
    if(q1==0) {
      FORR(kvp,bs2) {
        int p=kvp.first;
        if(M2.count(p)==0) return n2+1;
        int n=M2[p].first*n2+M2[p].second;
        if(n<kvp.second) return n2+1;
      }
      return n2+n1;
    }
    if(q2==0) {
      FORR(kvp,bs) {
        int p=kvp.first;
        if(M1.count(p)==0) return n1+1;
        int n=M1[p].first*n1+M1[p].second;
        if(n<kvp.second) return n1+1;
      }
      return n1+n2;
    }
    
    SETI S;
    FORR(kvp,M1) S.emplace(kvp.first);
    FORR(kvp,M2) S.emplace(kvp.first);
    
    dumpAR(S);
    
    int res=0;
    REP(i,n1) if(SZ(S)) {
      SETI SS;
      FORR(s,S) {
        int x=f(s, i, n2, M1, M2);
        if(x!=-1) SS.emplace(x);
//        if(!x) { dump2(i,s); dump4(M1[s].first,M1[s].second,M2[s].first,M2[s].second); }
      }
//      dumpAR(SS);
      bool ok=SZ(SS)==1&&*(SS.begin())!=-2;
//      if(ok) dump2(i,ok);
      res+=ok;
    }
    dump(res);
    return n1 + n2 - res;
  }
};

// CUT begin
ifstream data("GeometricProgressions.sample");

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

bool do_test(int b1, int q1, int n1, int b2, int q2, int n2, int __expected) {
    time_t startClock = clock();
    GeometricProgressions *instance = new GeometricProgressions();
    int __result = instance->count(b1, q1, n1, b2, q2, n2);
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
        int b1;
        from_stream(b1);
        int q1;
        from_stream(q1);
        int n1;
        from_stream(n1);
        int b2;
        from_stream(b2);
        int q2;
        from_stream(q2);
        int n2;
        from_stream(n2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(b1, q1, n1, b2, q2, n2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1523297697;
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
        cout << "GeometricProgressions (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
