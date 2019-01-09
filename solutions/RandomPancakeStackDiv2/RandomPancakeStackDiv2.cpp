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
 
 8/30/2017
 
 9:14-11:00 pause
 20:30-21:15 fixed probability calculation and system test passed
 21:16-22:44 add solution by backtracking
 
 editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+656
  - http://kmjp.hatenablog.jp/entry/2015/04/19/0900
 
 24:13 add @kmjp DP solution
  P(j,s+1)+=P[i][s]*1/(N-s)
  res += d[j]*P[i][s]*1/(N-s)
 
 submit solutions:
  - DP
   - https://community.topcoder.com/stat?c=problem_solution&rm=326034&rd=16416&pm=13749&cr=23330633
  - brute force by bitmask
   - https://community.topcoder.com/stat?c=problem_solution&rm=326010&rd=16416&pm=13749&cr=40118296
   - https://community.topcoder.com/stat?c=problem_solution&rm=326033&rd=16416&pm=13749&cr=23144800
  - brute force by backtracking
   - https://community.topcoder.com/stat?c=problem_solution&rm=326021&rd=16416&pm=13749&cr=40122674
 
 Another editorial:
  - http://torus711.hatenablog.com/entry/20150427/1430142353
 
 */

double P[11][11];
class RandomPancakeStackDiv2 {
public:
  VI D;
  int N;
  double expectedDeliciousness(vector<int> D) {
    this->D=D; this->N=SZ(D);
    ZERO(P);
    
    double res=0;
    
    P[N][0]=1.0;
    for(int i=N; i>=0; --i) REP(s,N-i+1) if(P[i][s]) {
      REP(j,i) {
        double p=1.0/(N-s);
        P[j][s+1]+=P[i][s]*p;
        res += P[i][s]*p*D[j];
      }
    }
    
    return res;
  }
};

class RandomPancakeStackDiv2_backtracking {
public:
  VI D;
  int N;
  vector<double> P;
  double dfs(int p, double sum, VI &ord) {
    if(p==N) return sum/P[p];
    
    double res=0.0;
    FOR(i,p,N) {
      swap(ord[i],ord[p]);
      if(p>0&&ord[p]>ord[p-1]) {
        res+=sum/P[p];
      } else {
        res+=dfs(p+1,sum+D[ord[p]],ord);
      }
      swap(ord[i],ord[p]);
    }
    return res;
  }
  
  double expectedDeliciousness(vector<int> D) {
    this->D=D; this->N=SZ(D);
    VI ord; REP(i,N) ord.push_back(i);
    P=vector<double>(N+1);
    P[0]=N;
    for(int i=1; i<N; ++i) P[i]=P[i-1]*(N-i);
    P[N]=P[N-1];

    return dfs(0,0.0,ord);
  }
};

class RandomPancakeStackDiv2_simulation {
public:
  double expectedDeliciousness(vector<int> D) {
    int N=SZ(D);
    VI ord;
    REP(i,N) ord.push_back(i);
    
    long double res=0;
    do {
      // in each case, probability is 1/N!
      long double sum=D[ord[0]];
      FOR(i,1,N) {
        if(ord[i]>ord[i-1]) {
          break;
        }
        sum+=D[ord[i]];
      }
      res += sum;
    } while(next_permutation(ord.begin(),ord.end()));
    
    double p=1.0;
    FOR(i,2,N+1) p*=i;
    
    return res/p;
  }
};

class RandomPancakeStackDiv2_wrong {
  public:
  double expectedDeliciousness(vector<int> D) {
    int N=SZ(D);
    VI ord; REP(i,N) ord.push_back(i);
    
    long double res=0.0;
    do {
      long double sum=D[ord[0]],p=1.0/(long double)N;
      FOR(i,1,N) {
        p*=1.0/(long double)(N-i);
        if(ord[i]>ord[i-1]) break;
        sum+=D[ord[i]];
      }
//      dump2(sum,p);
      res += sum*p;
    } while(next_permutation(ord.begin(),ord.end()));
    
    return res;
  }
};

// CUT begin
ifstream data("RandomPancakeStackDiv2.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> d, double __expected) {
    time_t startClock = clock();
    RandomPancakeStackDiv2 *instance = new RandomPancakeStackDiv2();
    double __result = instance->expectedDeliciousness(d);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> d;
        from_stream(d);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504196061;
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
        cout << "RandomPancakeStackDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
