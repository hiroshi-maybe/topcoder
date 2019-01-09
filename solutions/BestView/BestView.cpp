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
 
 9/8/2018
 
 15:01-15:03 analysis
 15:04-15:33 AC (133.43 pt)
 
 http://apps.topcoder.com/wiki/display/tc/SRM+436
 
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
bool operator <= (Frac a, Frac b) { return a<b||a==b; }
bool operator >= (Frac a, Frac b) { return a>b||a==b; }

class BestView {
  public:
  int N;
  VI H;
  int f(int p) {
    int l=0,r=0;
    int i=p+1;
    Frac cur(-2e9,1);
    while(i<N) {
      int x=i-p,y=H[i]-H[p];
      Frac a(y,x);
      if(cur<a) ++r,cur=a;
      ++i;
    }
    cur=Frac(2e9,1);
    i=p-1;
    while(i>=0) {
      int x=p-i,y=H[p]-H[i];
      Frac a(y,x);
//      dump3(i,a.n,a.d);
      if(cur>a) ++l,cur=a;
      --i;
    }
    
//    dump4(p,l,r,l+r);
    
    return l+r;
  }
  int f_double(int p) {
    int l=0,r=0;
    int i=p+1;
    double cur=-2e9;
    while(i<N) {
      int x=i-p,y=H[i]-H[p];
      double a=y/x;
      dump4(i,y,x,a);
      if(cur<a) ++r,cur=a;
      ++i;
    }
    cur=2e9;
    i=p-1;
    while(i>=0) {
      int x=p-i,y=H[p]-H[i];
      double a=y/x;
      dump4(i,y,x,a);
      if(cur>a) ++l,cur=a;
      --i;
    }
    
    dump4(p,l,r,l+r);
    
    return l+r;
  }
  int numberOfBuildings(vector<int> H) {
    this->N=SZ(H),this->H=H;
    int res=0;
    REP(i,N) SMAX(res,f(i));
    return res;
  }
};

// CUT begin
ifstream data("BestView.sample");

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

bool do_test(vector<int> heights, int __expected) {
    time_t startClock = clock();
    BestView *instance = new BestView();
    int __result = instance->numberOfBuildings(heights);
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
        vector<int> heights;
        from_stream(heights);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(heights, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536444089;
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
        cout << "BestView (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
