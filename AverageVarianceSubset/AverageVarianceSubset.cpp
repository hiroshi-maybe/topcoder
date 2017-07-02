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

/*
 
 7/1/2017
 
 22:36 start
 23:10 time up
 
 7/2/2017
 
 8:20 analyzing https://community.topcoder.com/stat?c=problem_solution&rm=329959&rd=16881&pm=14568&cr=23202843

 // i/j: left/right index
 // k: number of elements in a subset
 
 f[i][j][k]: number of subsets
 f[i][j][k] = ∑ f[i][l][k-1] (l=i..<j)
 
 g[i][j][k]: sum of `s[x]` in all the subsets
 g[i][j][k] = ∑ g[i][l][k-1]+s[j]*f[i][l][k-1] (l=i..<j)
 
 h[i][j][k]: sum of `s[x]^2` in all the subsets
 h[i][j][k] = ∑ h[i][l][k-1]+s[j]*s[j]*f[i][l][k-1] (l=i..<j)
 
 p[i][j][k]: `sum of s[x]`^2 in all the subsets
 p[i][j][k] = ∑ p[i][l][k-1]+s[j]*s[j]*f[i][l][k-1]+2*s[j]*g[i][l][k-1] (l=i..<j)
 
 Sum(k) = x[1]+x[2]+..+x[k] = ∑x[i](i=1..k)
 Sum(k+1)^2 = Sum(k)^2 + x[k+1]^2 + 2*x[k+1]*Sum(k)
 
 9:49 understood and added solution
 
 */

typedef long long ll;
typedef double ld;
class AverageVarianceSubset {
  public:
  ld f[51][51][51];
  ld g[51][51][51];
  ld h[51][51][51];
  ld p[51][51][51];
  
  double average(vector<int> s, int R) {
    typedef double ld; int n=s.size();
    sort(s.begin(),s.end());
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    memset(h,0,sizeof(h));
    memset(p,0,sizeof(p));
    ld ans=0,sm=0;
    for(int i=0;i<n;i++)
    {
      f[i][i][1]=1;
      g[i][i][1]=s[i];
      h[i][i][1]=(ld)s[i]*s[i];
      p[i][i][1]=(ld)s[i]*s[i];
      for(int j=i+1;j<n&&s[j]-s[i]<=R;j++)
      {
        for(int k=2;k<=j-i+1;k++)
        {
          for(int l=i;l<j;l++)
          {
            f[i][j][k]+=f[i][l][k-1];
            g[i][j][k]+=g[i][l][k-1]+s[j]*(ld)f[i][l][k-1];
            h[i][j][k]+=h[i][l][k-1]+(ld)s[j]*s[j]*f[i][l][k-1];
            p[i][j][k]+=p[i][l][k-1]+(ld)s[j]*s[j]*f[i][l][k-1]+(ld)s[j]*g[i][l][k-1]*2;
          }
        }
      }
    }
    for(int i=0;i<n;i++)
    {
      for(int j=i;j<n&&s[j]-s[i]<=R;j++)
      {
        for(int k=1;k<=j-i+1;k++)
        {
          if(!f[i][j][k]) continue;
          sm+=f[i][j][k];
          ans+=(h[i][j][k]-p[i][j][k]/k)/k; // (E[X^2]-E[X]^2)/k
        }
      }
    }
    //(a+b+c)^2=a^2+b^2+c^2+2ab+2ac+2bc
    return ans/sm;
  }
};

// CUT begin
ifstream data("AverageVarianceSubset.sample");

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

bool do_test(vector<int> s, int R, double __expected) {
    time_t startClock = clock();
    AverageVarianceSubset *instance = new AverageVarianceSubset();
    double __result = instance->average(s, R);
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
        vector<int> s;
        from_stream(s);
        int R;
        from_stream(R);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498973756;
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
        cout << "AverageVarianceSubset (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
