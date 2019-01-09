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
typedef pair<int,int> II;

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

/**
 
 7/22/2017
 
 TCO17 2C
 
 9:00-10:24 give up
 
 Editorial
 - https://twitter.com/kinaba/status/888816107640938496
 
 22:55-23:23 add solution and passed system test
 
 Key
 - ascendant order -> minimum point, descendant order -> maximum point
 - swapping adjacent element increases point by at most one
 - from above, we can do bubble sort by keep swapping until we get expected state
 
 Summary
 - ascendant order -> min, descendant order -> max
  - this was what I figured out during the contest though, one more deep analysis was needed
  - I was trying to do something like binary search though, it didn't work :(
 - swapping adjacent element increases point by at most one! This analysis is the key!
 - observe carefully how state changes by an operation
 - analyze lower bound and upper bound
 - control state change toward expected state
 - observe how state changes by an operation
 
 change state toward expected state <=> keep solving subproblem

 */

// O(N^3) time
class CanidsSeesaw {
public:
  VI W;
  int N;
  int calc(vector<II> F) {
    int sum=0,cnt=0;
    REP(i,N) {
      sum+=F[i].first;
      cnt+=sum>W[i];
    }
    return cnt;
  }
  
  vector<int> construct(vector<int> wolf, vector<int> fox, int k) {
    N=SZ(wolf);
    W=VI(N); W[0]=wolf[0];
    REP(i,N-1) W[i+1]=wolf[i+1]+W[i];
    
    vector<II> F(N);
    REP(i,N) F[i]={fox[i],i};
    sort(F.begin(),F.end());
    
    REP(i,N) {
      int x = calc(F);
      if(x==k) break;
      if(x>k) return {};
      REP(j,N-i-1) {
        swap(F[j],F[j+1]);
        x=calc(F);
        if(x==k) break;
        if(x>k) return {};
      }
    }
    
    if(calc(F)<k) return {};
    VI res;
    FORR(p,F)res.emplace_back(p.second);
    return res;
  }
};

/*
class CanidsSeesaw_wrong {
  public:
  VI W;
  int N;
  int calc(vector<II> F) {
    int sum=0,cnt=0;
    REP(i,N) {
      sum+=G[i];
      cnt+=sum>W[i];
    }
    return cnt;
  }
  
  vector<int> construct(vector<int> wolf, vector<int> fox, int k) {
    N=SZ(wolf);
    W(N); W[0]=wolf[0];
    REP(i,N-1) W[i+1]=wolf[i+1]+W[i];
    
    vector<II> G(N);
    REP(i,N) G[i]={fox[i],i};
    vector<II> B=G;
    sort(G.begin(),G.end());
    sort(B.rbegin(),B.rend());
    
    if(calc(G)>k) return {};
    if(calc(B)<k) return {};

    int i=0,j;
    while(i<N-1) {
      j=i+
    }
    
    if(calc(G)==k) {
      VI res;
      REP(i,N) res.push_back(G.second);
      return res;
    }
    return {};
  }
};*/

// CUT begin
ifstream data("CanidsSeesaw.sample");

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

bool do_test(vector<int> wolf, vector<int> fox, int k, vector<int> __expected) {
    time_t startClock = clock();
    CanidsSeesaw *instance = new CanidsSeesaw();
    vector<int> __result = instance->construct(wolf, fox, k);
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
        vector<int> wolf;
        from_stream(wolf);
        vector<int> fox;
        from_stream(fox);
        int k;
        from_stream(k);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(wolf, fox, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500739206;
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
        cout << "CanidsSeesaw (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
