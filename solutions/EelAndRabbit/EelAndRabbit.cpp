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
 
 12/1/2017
 
 8:20-8:33 analysis
 8:34-8:43 implement and system test passed (323.00 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+580
   - simpler O(N^3) time
  - http://snuke.hatenablog.com/entry/2013/05/26/024648
   - writer's comment
  - http://kmjp.hatenablog.jp/entry/2013/05/26/0900
   - O(N^2) with coordinate compression
  - http://torus711.hatenablog.com/entry/20130525/p1
   - O(N^2) with coordinate compression
  - http://emkcsharp.hatenablog.com/entry/SRM580/EelAndRabbit
   - O(N^3)
  - http://d.hatena.ne.jp/kusano_prog/20130525/1369506104
   - O(N^3)
 
 Summary:
  - I solved by efficient O(N^2) time solution though, O(N^3) is simpler
  - Nice to learn that it's sufficient to check only head which is the point to increase
 
 */

// O(N^3) time
class EelAndRabbit {
public:
  int getmax(vector<int> L, vector<int> T) {
    int N=SZ(L);
    int res=0;
    REP(i,N) REP(j,N) {
      int t1=T[i],t2=T[j];
      int cnt=0;
      REP(k,N) {
        int x1=T[k],x2=T[k]+L[k];
        if((x1<=t1&&t1<=x2)||(x1<=t2&&t2<=x2)) ++cnt;
      }
      res=max(res,cnt);
    }
    return res;
  }
};

// Corrdinate compression, O((2*N)^2) time
class EelAndRabbit_org {
  public:
  int getmax(vector<int> L, vector<int> T) {
    int N=SZ(L);
    
    vector<III> es;
    REP(i,N) {
      es.emplace_back(T[i],-1,i);
      es.emplace_back(T[i]+L[i],1,i);
    }
    sort(es.begin(),es.end());
    
    // t,mask
    vector<pair<int, LL>> xs;
    xs.emplace_back(0,0LL);
    FORR(x,es) {
      int t,lr,i;
      tie(t,lr,i)=x;
      auto prev=xs.back();
      if(lr==-1) {
        // add
        xs.emplace_back(t,prev.second|(1LL<<i));
      } else {
        // rem
        xs.emplace_back(t,prev.second^(1LL<<i));
      }
    }
    
    int res=0;
    REP(j,SZ(xs))REP(i,j) {
      LL m=xs[i].second|xs[j].second;
      res=max(res,__builtin_popcountll(m));
    }
    
    return res;
  }
};

// CUT begin
ifstream data("EelAndRabbit.sample");

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

bool do_test(vector<int> l, vector<int> t, int __expected) {
    time_t startClock = clock();
    EelAndRabbit *instance = new EelAndRabbit();
    int __result = instance->getmax(l, t);
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
        vector<int> l;
        from_stream(l);
        vector<int> t;
        from_stream(t);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(l, t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512145185;
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
        cout << "EelAndRabbit (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
