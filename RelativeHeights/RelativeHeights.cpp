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
 
 7/12/2017
 
 SRM 718 div2
 
 18:00-18:27 couldn't solve in contest.
 Brute-force solution came up with me though,
 couldn't figure out how to count up unique combination of orders.
 (turned out just using ordered set `set<vector<int>>` works)
 
 19:20-19:32 found greedy solution
 19:40 passed samples and system test
 
 https://community.topcoder.com/stat?c=problem_solution&rm=330357&rd=16933&pm=14644&cr=40168949
 https://community.topcoder.com/stat?c=problem_solution&rm=330348&rd=16933&pm=14644&cr=40234236
 
 22:56-23:10 add brute-force solution
 
 */

// hashtable, O(N^2) time
class RelativeHeights {
public:
  int countWays(vector<int> h) {
    int N=SZ(h);
    vector<pair<int,int>> ps(N);
    REP(i,N) ps[i]={h[i],i};
    sort(ps.begin(),ps.end(),std::greater<pair<int,int>>());
    VI rank(N);
    REP(i,N) rank[ps[i].second]=i;
    
    set<VI> S;
    REP(i,N) {
      VI profs;
      REP(j,N) {
        if(i==j) continue;
        if(rank[j]>rank[i]) profs.push_back(rank[j]-1);
        else profs.push_back(rank[j]);
      }
      
      S.insert(profs);
    }
    return S.size();
  }
};

// greedy, O(N*lg N) time
class RelativeHeights_org {
public:
  int countWays(vector<int> h) {
    int N=SZ(h);
    vector<pair<int,int>> ps(N);
    REP(i,N) ps[i]={h[i],i};
    sort(ps.begin(),ps.end());
    VI rank(N);
    REP(i,N) rank[ps[i].second]=i;

    int res=1;
    FOR(i,1,N) {
      if(abs(rank[i]-rank[i-1])!=1) ++res;
    }
    
    return res;
  }
};

class RelativeHeights_wrong {
  public:
  int countWays(vector<int> h) {
    int N=SZ(h);
    vector<pair<int,int>> ps(N);
    REP(i,N) ps[i]={h[i],i};
    sort(ps.begin(),ps.end());
    VI rank(N);
    REP(i,N) rank[ps[i].second]=i;
    
    REP(i,N) {
      VI rs(N-1);
      REP(j,N) {
        if(j==i) continue;
        if(rank[j]>rank[i]) rs[j]=rank[i]-1;
        else rs[j] = rank[i];
      }
    }
    
    return 0;
  }
};

// CUT begin
ifstream data("RelativeHeights.sample");

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

bool do_test(vector<int> h, int __expected) {
    time_t startClock = clock();
    RelativeHeights *instance = new RelativeHeights();
    int __result = instance->countWays(h);
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
        vector<int> h;
        from_stream(h);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(h, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499907607;
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
        cout << "RelativeHeights (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
