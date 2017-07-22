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

SETI E[101];

/**
 
 7/21/2017
 
 9:06-9:26 analysis. keep degree 2 for each vertex.
 9:41 (259.87 pt) 
 10:19 failed system test :(
 10:27 passed system teests. sounds like we can remove only w1?
 
 19:43 analyze problem
 
 Yes, only w1 can be removed. suppose w2 connecting [i] and [i+2] is removed.
 Then [i+1] is the only vertex to connect to right vertices.
 
 [i]-w2-[i+2]
  |    / w1
 [i+1] -w2-
 
 That means we can remove any w1 edge as long as it satisfies below conditions in a greedy manner
 - weight is positive
 - edge is not the first one or last one
 
 It turns out no need to sort and check graph degrees :(
 - https://community.topcoder.com/stat?c=problem_solution&rm=328948&rd=16748&pm=14332&cr=22744380
 - https://community.topcoder.com/stat?c=problem_solution&rm=328950&rd=16748&pm=14332&cr=23331631
 - https://community.topcoder.com/stat?c=problem_solution&rm=328956&rd=16748&pm=14332&cr=40443867
 
 Summary
 - It took some of time to understand biconnected graph
 - Analysis! Analysis! Analysis!
  - Analysis was not enough. Should have understood that w2 cannot be removed even if indegree > 2.
 
 20:10 add expected simpler solution
 
 */

// O(N) time
class BiconnectedDiv2 {
public:
  int minimize(vector<int> w1, vector<int> w2) {
    int res=w1.front()+w1.back();
    FOR(i,1,SZ(w1)-1) if(w1[i]<0) res+=w1[i];
    FORR(w,w2) res+= w;
    return res;
  }
};

// O(N*lg N) time
class BiconnectedDiv2_org {
public:
  int minimize(vector<int> w1, vector<int> w2) {
    //    int V=SZ(w1)+1;
    REP(i,100) E[i].clear();
    vector<tuple<int,int,int>> ws;
    int sum=0;
    REP(i,SZ(w1)) {
      ws.emplace_back(w1[i],i,i+1), sum+=w1[i];
      E[i].insert(i+1);
      E[i+1].insert(i);
    }
    REP(i,SZ(w2)) {
//      ws.emplace_back(w2[i],i,i+2)
      sum+=w2[i];
      E[i].insert(i+2);
      E[i+2].insert(i);
    }
    sort(ws.rbegin(),ws.rend());
    
//    dump(sum);
    FORR(e, ws) {
      int u,v,w;
      tie(w,u,v) = e;
      if(w<=0) continue;
      if(SZ(E[u])>2&&SZ(E[v])>2) {
        //        dump3(u,v,w);
        sum -= w;
        E[u].erase(v);
        E[v].erase(u);
      }
    }
    
    return sum;
  }
};

class BiconnectedDiv2_wrong {
  public:
  int minimize(vector<int> w1, vector<int> w2) {
//    int V=SZ(w1)+1;
    REP(i,100) E[i].clear();
    vector<tuple<int,int,int>> ws;
    int sum=0;
    REP(i,SZ(w1)) {
      ws.emplace_back(w1[i],i,i+1), sum+=w1[i];
      E[i].insert(i+1);
      E[i+1].insert(i);
    }
    REP(i,SZ(w2)) {
      ws.emplace_back(w2[i],i,i+2), sum+=w2[i];
      E[i].insert(i+2);
      E[i+2].insert(i);
    }
    sort(ws.rbegin(),ws.rend());
    
    dump(sum);
    FORR(e, ws) {
      int u,v,w;
      tie(w,u,v) = e;
      if(w<=0) continue;
      if(SZ(E[u])>2&&SZ(E[v])>2) {
//        dump3(u,v,w);
        sum -= w;
        E[u].erase(v);
        E[v].erase(u);
      }
    }
    
    return sum;
  }
};

// CUT begin
ifstream data("BiconnectedDiv2.sample");

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

bool do_test(vector<int> w1, vector<int> w2, int __expected) {
    time_t startClock = clock();
    BiconnectedDiv2 *instance = new BiconnectedDiv2();
    int __result = instance->minimize(w1, w2);
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
        vector<int> w1;
        from_stream(w1);
        vector<int> w2;
        from_stream(w2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(w1, w2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500653186;
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
        cout << "BiconnectedDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
