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
 
 9/18/2017
 
 9:00-9:40 ok, brute force 3 division + binary search seem to work
 9:41-10:04 implement
 10:05-10:08 debug and submit and system test passed (374.10 pt)
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2014/10/15/0930
  - https://apps.topcoder.com/wiki/display/tc/SRM+636
    - more efficient solution with additional binary search
  - http://purple-jwl.hatenablog.com/entry/2014/10/16/230204
 
 key:
  - 2d cumulative sum + brute force + binary search
 
 summary:
  - beautiful problem with combination of three technique
  - Reached solution by noticing brute force of one dimension is feasible
 
 9/24/2017
 
 9:50-11:16 add more binary search solution in official editorial
 Note that cumulative sum should be used in HALF-OPEN HALF-CLOSED query.
 
 */

// O(M^3*lg^3 N*lg M*N) time
int sum[80][80];
class ChocolateDividingHard {
public:
  int M,N;
  vector<string> B;

  // (i1,i2): inclusive, (i2,j2): exclusive
  int area(int i1, int j1, int i2, int j2) {
    return sum[i2][j2]-sum[i2][j1]-sum[i1][j2]+sum[i1][j1];
  }
  
  bool okarea(int i1, int i2, int i3, int j1, int clen, int T) {
    int a1=area(   0,j1,i1+1,j1+clen);
    int a2=area(i1+1,j1,i2+1,j1+clen);
    int a3=area(i2+1,j1,i3+1,j1+clen);
    int a4=area(i3+1,j1,   M,j1+clen);
    return a1>=T&&a2>=T&&a3>=T&&a4>=T;
  }
  
  bool ok(int T) {
    REP(i1,M)FOR(i2,i1+1,M)FOR(i3,i2+1,M) {
      int x=0,j=0;
      while(j<N&&x<=4) {
        int good=N-j,bad=0;
        while(abs(good-bad)>1) {
          int mid=(good+bad)/2;
          (okarea(i1,i2,i3,j,mid,T)?good:bad)=mid;
        }
        if(okarea(i1,i2,i3,j,good,T)) {
          ++x;
          j+=good;
        } else break;
      }
      if(x>=4) return true;
    }
    return false;
  }
  
  int findBest(vector<string> B) {
    ZERO(sum);
    this->B=B;
    this->M=SZ(B),this->N=SZ(B[0]);
    REP(i,M)REP(j,N) {
      sum[i+1][j+1]=sum[i+1][j]+sum[i][j+1]-sum[i][j]+B[i][j]-'0';
    }
    int good=0, bad=9*M*N+1;
    while(abs(good-bad)>1) {
      int mid=(good+bad)/2;
      (ok(mid)?good:bad)=mid;
    }
    return good;
  }
};

// O(M^3*N*lg M*N) time
int cum[80][80];
class ChocolateDividingHard_org {
  public:
  int M,N;
  vector<string> B;
  
  int area(int i, int j, int i2, int j2) {
    return cum[i2+1][j2+1]-cum[i2+1][j]-cum[i][j2+1]+cum[i][j];
  }
  
  bool ok(int T, int i1, int i2, int i3) {
    int gs=0,prevj=-1;
    REP(j,N) {
      int a1=area(   0,prevj+1, i1,j);
      int a2=area(i1+1,prevj+1, i2,j);
      int a3=area(i2+1,prevj+1, i3,j);
      int a4=area(i3+1,prevj+1,M-1,j);
      
      if(a1>=T&&a2>=T&&a3>=T&&a4>=T) {
        ++gs;
        prevj=j;
      }
    }
    return gs>=4;
  }
  
  int findBest(vector<string> B) {
    ZERO(cum);
    this->B=B;
    this->M=SZ(B),this->N=SZ(B[0]);
    REP(i,M) REP(j,N) {
      cum[i+1][j+1]=B[i][j]-'0'+cum[i+1][j]+cum[i][j+1]-cum[i][j];
    }
    
    int res=-1;
    REP(i1,M)FOR(i2,i1+1,M)FOR(i3,i2+1,M) {
      int good=0,bad=9*M*N+1;
      while(abs(good-bad)>1) {
        int mid=(good+bad)/2;
        if(ok(mid,i1,i2,i3)) good=mid;
        else bad=mid;
      }
      res=max(res,good);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ChocolateDividingHard.sample");

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

bool do_test(vector<string> chocolate, int __expected) {
    time_t startClock = clock();
    ChocolateDividingHard *instance = new ChocolateDividingHard();
    int __result = instance->findBest(chocolate);
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
        vector<string> chocolate;
        from_stream(chocolate);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(chocolate, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505750408;
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
        cout << "ChocolateDividingHard (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
