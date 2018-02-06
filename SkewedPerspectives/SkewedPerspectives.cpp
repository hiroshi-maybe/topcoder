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
 
 2/5/2018
 
 9:25-9:42 analysis
 9:43-10:05 sample 1 "1bbbbb" does not pass
 10:05-10:20 pause
 11:30-11:43 sounds like dp is needed?
 18:10-18:16 dp is not necessary. Modify code lightly and got ACC.
 
 Two mistakes
  - "1bbbbb" in sample 1 => I assumed 1bb + ??bbbbbb though, simply 1 + bbbbbb works
  - "bbb1" in sample 1 => Only bb + ?bb1 works
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+538
  - http://kmjp.hatenablog.jp/entry/2014/01/05/1000
 
 Key:
  - Pay attention to corner cases and count up
 
 Summary:
  - My analysis was not so accurate though, samples helped me
 
 */

class SkewedPerspectives {
  public:
  string yes="valid",no="invalid";
  int BB,W;
  VI XX;
  bool f(string T) {
    dump(T);
    int N=SZ(T);
    int B=BB;
    int w=1;
    VI D;
    VI X=XX;
    int i=0;
    while(i<N) {
      int b=0;
      while(i<N&&T[i]=='b') ++b,++i;
      if(b==1&&i==1) return false;
      if(b%2==1) {
        // next building
        ++w;
        int cnt=(b+1)/2;
        B-=cnt;
        if(i-2*cnt>=0) {
          D.push_back(i-2*cnt);
        } else {
          D.push_back(1);
        }
        //if(cnt>1) D.push_back(i-(cnt-1)*2);
        //else D.push_back(i-2);
      } else {
        B-=b/2;
      }
      if(B<0) return false;
      
      // normal
      if(i<N) {
        int c=T[i]-'0';
        X[c]--;
        if(X[c]<0) return false;
        ++i;
      }
    }
    if(w>W) return false;
    int r1=accumulate(X.begin(),X.end(),0);
    for(int d : D) {
      int cnt=min(d/2,B);
      d-=2*cnt;
      B-=cnt;
      r1-=d;
      if(r1<0) return false;
    }
    return true;
  }
  vector<string> areTheyPossible(vector<int> X, int B, int W, vector<string> V) {
    this->XX=X,this->BB=B,this->W=W;
    int N=SZ(V);
    vector<string> res(N);
    REP(i,N) res[i]=f(V[i])?yes:no;
    return res;
  }
};

// CUT begin
ifstream data("SkewedPerspectives.sample");

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

bool do_test(vector<int> cubes, int B, int w, vector<string> views, vector<string> __expected) {
    time_t startClock = clock();
    SkewedPerspectives *instance = new SkewedPerspectives();
    vector<string> __result = instance->areTheyPossible(cubes, B, w, views);
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
        vector<int> cubes;
        from_stream(cubes);
        int B;
        from_stream(B);
        int w;
        from_stream(w);
        vector<string> views;
        from_stream(views);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cubes, B, w, views, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517851502;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1050 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SkewedPerspectives (1050 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
