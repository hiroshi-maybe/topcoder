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
 
 4/14/2018 SRM 733
 
 9:02-9:13 submit (219.01 pt) but system test failed due to pricision error
 
 4/16/2018
 
 Create frac library
 
 4/18/2018
 
 11:10-12:20, 13:30-14:15 add solution with fraction library
 17:05-17:10 add simpler solution
 
 Editorials:
  - https://www.topcoder.com/blog/srm-733-results/
  - https://www.topcoder.com/blog/single-round-match-733-editorials/
  - https://kimiyuki.net/blog/2018/04/15/srm-733-easy/
  - http://kmjp.hatenablog.jp/entry/2018/04/15/0900
  - https://togetter.com/li/1218180

 There are two traps in this problem.
  1. doulbe causes pricision issue
  2. comparison may cause overflow in even long long
 
 #1 => So foolish as to use double in integer computation problem.
 
 Sample 6)
 
 One sample that causes precision error is below sample 6:
 
 X={9995,10000,9994,9996,10000}
 
 A=f(0,1,2,4) = |9995/10000-9994/10000|
 B=f(0,1,3,4) = |9995/10000-9996/10000|
 
 A==B is true. {0,1,2,4} is lexicographically smaller.
 However code with `double` gives B<A == true.
 
 Sample 7)
 
 Another sample that causes precision error is below sample 7:
 
 X={4,3,2,10000,10000}
 
 A=f(0,3,1,4) = |4/10000-3/10000|
 B=f(1,3,2,4) = |3/10000-2/10000|

 A==B is true. {0,3,1,4} is lexicographically smaller.
 However code with `double` gives B<A == true.
 
 #2 => Always estimate maximal value in even intermediate calculation.
 
 My library needs (1e4)^4 = 1e16 integer which fits in 1e18.
 
 Key:
  - Obviously double gives precision error
  - Pay attention to overflow during the computation
 
 Summary:
  - Search was trivial. I did not pay attention to precision error
  - It took most of time to figure out overflow in the frac library
 
 */

struct Frac {
public:
  // numerator / denominator
  int n,d;
  Frac(int nn, int dd) {
    assert(dd>0);
    bool neg=nn<0;
    nn=neg?-nn:nn;
    long long g=gcd(nn,dd);
    this->n=nn/g;
    if(neg) this->n=-1*this->n;
    this->d=dd/g;
  }
  Frac abs() {
    Frac res(n<0?-n:n,d);
    return res;
  }
  void debug() {
    printf("%d/%d\n",n,d);
  }
private:
  long long gcd(long long a, long long b) {
    return b==0?a:gcd(b,a%b);
  }
};
Frac operator + (Frac a, Frac b) { return Frac((long long)a.n * b.d + (long long)b.n * a.d, (long long)a.d * b.d); }
Frac operator - (Frac a, Frac b) { return a + Frac(-b.n, b.d); }
Frac operator * (Frac a, Frac b) { return Frac((long long)a.n * b.n, (long long)a.d * b.d); }
Frac operator / (Frac a, Frac b) { return a * Frac(b.d, b.n); }
bool operator < (Frac a, Frac b) { return a.n *(long long) b.d < b.n *(long long) a.d; }
bool operator > (Frac a, Frac b) { return b < a; }
bool operator == (Frac a, Frac b) { return a.n == b.n && a.d == b.d; }

// O(N^5) time where N<5
class MinimizeAbsoluteDifferenceDiv1 {
public:
  vector<int> findTuple(vector<int> X) {
    Frac minx=Frac(1e4,1);
    VI res={5,5,5,5};
    REP(i,5)REP(j,5)if(i!=j)REP(k,5)if(i!=k&&j!=k)REP(l,5)if(i!=l&&j!=l&&k!=l) {
      VI A={i,j,k,l};
      Frac x=Frac(X[i],X[j])-Frac(X[k],X[l]); x=x.abs();
      if(x==minx) SMIN(res,A);
      if(x<minx) minx=x,res=A;
    }
    return res;
  }
};

class MinimizeAbsoluteDifferenceDiv1_complex {
public:
  vector<int> findTuple(vector<int> X) {
    Frac minx=Frac(1e4,1);
    set<VI> S;
    REP(i,5) {
      VI Y;
      REP(j,5) if(i!=j) Y.push_back(j);
      VI ord(4); REP(j,4) ord[j]=j;
      do {
        int a=X[Y[ord[0]]],b=X[Y[ord[1]]],c=X[Y[ord[2]]],d=X[Y[ord[3]]];
        Frac x1(a,b),x2(c,d);
        Frac p=(x1-x2).abs();
        VI is={Y[ord[0]],Y[ord[1]],Y[ord[2]],Y[ord[3]]};
        
        if(p<minx) {
          S.clear();
          S.emplace(is);
          minx=p;
        } else if(p==minx) {
          S.emplace(is);
        }
      } while(next_permutation(ord.begin(),ord.end()));
    }
    return *S.begin();
  }
};
class MinimizeAbsoluteDifferenceDiv1_org {
  public:
  vector<int> findTuple(vector<int> X) {
    /*
    double opt = abs(1.0*X[0]/X[3]-1.0*X[1]/X[4]);
    double ng = abs(1.0*X[1]/X[3]-1.0*X[2]/X[4]);
    
    cout<<opt<<"<"<<ng<<(opt<ng)<<endl;
//    cout << (opt>ng)<<endl;
    */
    double minx=1e9;
    set<VI> S;
    REP(i,5) {
      VI Y;
      REP(j,5) if(i!=j) Y.push_back(j);
      VI ord(4); REP(j,4) ord[j]=j;
      do {
        double a=X[Y[ord[0]]],b=X[Y[ord[1]]],c=X[Y[ord[2]]],d=X[Y[ord[3]]];
        double p=abs(a/b-c/d);
        VI is={Y[ord[0]],Y[ord[1]],Y[ord[2]],Y[ord[3]]};
        if(p<minx) {
          S.clear();
          S.emplace(is);
          minx=p;
        } else if(p==minx) {
          S.emplace(is);
        }
      } while(next_permutation(ord.begin(),ord.end()));
    }
    return *S.begin();
//    return {0,1,2,3};
  }
};

// CUT begin
ifstream data("MinimizeAbsoluteDifferenceDiv1.sample");

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

bool do_test(vector<int> x, vector<int> __expected) {
    time_t startClock = clock();
    MinimizeAbsoluteDifferenceDiv1 *instance = new MinimizeAbsoluteDifferenceDiv1();
    vector<int> __result = instance->findTuple(x);
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
        vector<int> x;
        from_stream(x);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1523721730;
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
        cout << "MinimizeAbsoluteDifferenceDiv1 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
