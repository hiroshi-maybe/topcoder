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
 
 9/25/2017
 
 8:48-9:20 implemenet
 somehow sample 0 has error
 9:50 fixed by smaller eps (1e-9->1e-12) (213.93 pt)
 1WA for 1e-12 -> 1e-18 passed

 10/1/2017
 
 in order to narrow down 1e12 to 1e-10, it needs iteration of log(1.5,1e22)≈130 times.
 if I run in system test, 130 was not enough. I needed 200 iterations.
   - long double, range=0.0~1e12, 200 iterations (double did not work)
   - long double, range=0.0~1e12, eps=1e-15 (double did not work)

 editorial:
   - ternary search
     - http://kmjp.hatenablog.jp/entry/2014/08/20/1000
     - http://purple-jwl.hatenablog.com/entry/2014/09/22/012145
   - greedy based on optimality
     - https://apps.topcoder.com/wiki/display/tc/SRM+629
     - discussions in twitter
       - https://twitter.com/kuuso1/status/499640796183007234
       - https://twitter.com/masashinakata/status/499770433445441537
 
 15:11-15:16 add greedy solution based on graph analysis.
 
 key:
  - two solutions
    - analyze graph and compute optimal value greedily
    - generally solve by ternary search
 
 summary:
  - great chance to learn about binary/ternary search
   - how to estimate necessary number of iterations
   - lastly take middle one in ternary search
   - fabs() to compute absolute value of floating point number
  - I should remember how graph by absolute value behaves f(x) = ∑|d[i]-a[i]*x|
   - f(x) is minimal for x ∈ { d[i]/a[i] }
   - if a[i] is constant, median of d[i] gives minimal f(x)
     - http://topcoder.g.hatena.ne.jp/kuuso1/20140505

 */

class CandyMaking {
public:
  int N;
  VI vs,ws;
  double diff(double d) {
    double res=0.0;
    REP(i,N) {
      res+=fabs(ws[i]-vs[i]*d);
    }
    return res;
  }
  
  double findSuitableDensity(vector<int> volumes, vector<int> weights) {
    this->N=SZ(volumes);
    this->vs=volumes,this->ws=weights;
    
    double res=1e10;
    REP(i,N) res=min(res,diff(1.0*ws[i]/vs[i]));
    return res;
  }
};

class CandyMaking_ternarysearch_final {
public:
  int N;
  VI vs,ws;
  double diff(double d) {
    double res=0.0;
    REP(i,N) {
      res+=fabs(ws[i]-vs[i]*d);
    }
    return res;
  }
  
  double findSuitableDensity(vector<int> volumes, vector<int> weights) {
    this->N=SZ(volumes);
    this->vs=volumes,this->ws=weights;
    
    double l=0.0, r=1e10;
    
    // 150>>log(1.5,1e10/1e-10)=113
    REP(_,150) {
      double l2=(2*l+r)/3.0;
      double r2=(l+2*r)/3.0;

      double ld=diff(l2),rd=diff(r2);
      // discard further one (in this case larger one)
      if(rd<ld) l=l2;
      else r=r2;
    }
    // take middle one
    return diff((l+r)*0.5);
  }
};

// long double, eps=1e-10, range=0.0~1e12, 200 iterations or eps=1e-15 (system test passed)
class CandyMaking_ternary_wide_range {
public:
  int N;
  vector<long double> vs,ws;
  const long double eps=1e-15;
  long double diff(long double d) {
    double res=0.0;
    REP(i,N) {
      res+=fabs(ws[i]-vs[i]*d);
    }
    return res;
  }
  
  double findSuitableDensity(vector<int> volumes, vector<int> weights) {
    this->N=SZ(volumes);
    vs=vector<long double>(N);
    ws=vector<long double>(N);
    REP(i,N) vs[i]=(long double)volumes[i],ws[i]=(long double)weights[i];
    
    long double l=0.0, r=1e12;
    
//    while(fabs(r-l)>eps) {
    REP(_,200) {
      long double l2=l+(r-l)/3.0;
      long double r2=r-(r-l)/3.0;
      
      long double ld=diff(l2),rd=diff(r2);
      if(abs(rd-ld)<eps) {
        l=l2;
        break;
      }
      if(ld>rd) l=l2;
      else r=r2;
    }
    dump2(l,r);
    //    go=true;
    //    dump2(l,diff(l));
    return diff(l);
  }
};

class CandyMaking_org {
  public:
  int N;
  vector<long double> vs,ws;
  const double eps=1e-18;
  double diff(long double d) {
    long double res=0.0;
    REP(i,N) {
      long double x=ws[i]-vs[i]*d;
      if(x<0) x*=-1;
      res+=x;
    }
    return res;
  }
  
  double findSuitableDensity(vector<int> volumes, vector<int> weights) {
    this->N=SZ(volumes);
    vs=vector<long double>(N);
    ws=vector<long double>(N);
    REP(i,N) vs[i]=(long double)volumes[i],ws[i]=(long double)weights[i];
    
    long double l=0.0, r=1e12;
    
    while(abs(r-l)>eps) {
      long double l2=l+(r-l)/3.0;
      long double r2=r-(r-l)/3.0;
      
      long double ld=diff(l2),rd=diff(r2);
      if(abs(rd-ld)<eps) {
        l=l2;
        break;
      }
      if(ld>rd) l=l2;
      else r=r2;
    }
//    go=true;
//    dump2(l,diff(l));
    return diff(l);
  }
};

// CUT begin
ifstream data("CandyMaking.sample");

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

bool do_test(vector<int> containerVolume, vector<int> desiredWeight, double __expected) {
    time_t startClock = clock();
    CandyMaking *instance = new CandyMaking();
    double __result = instance->findSuitableDensity(containerVolume, desiredWeight);
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
        vector<int> containerVolume;
        from_stream(containerVolume);
        vector<int> desiredWeight;
        from_stream(desiredWeight);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(containerVolume, desiredWeight, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506354520;
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
        cout << "CandyMaking (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
