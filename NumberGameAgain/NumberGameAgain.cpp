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
 
 9/15/2017
 
 8:30-9:13 system test passed (275.15 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+640
    - sweep line
  - http://kmjp.hatenablog.jp/entry/2014/12/12/1030
    - close to my solution though, handling F[i] as binary of p columns
  - http://roiti46.hatenablog.com/entry/2015/05/19/032959
    - almost same as my solution
 
 key:
  - 2*k and 2*k+1 forms children in binary tree like binary heap by array
 
 summary:
  - analysis is not so hard
  - it took time to fix design bug and implementation
    - missed to remove all the subranges in each height
    - overflow
 
 */
class NumberGameAgain_perfectBinaryTree {
  public:
  LL ub;
  pair<vector<pair<LL,LL>>,int> subtree(LL x) {
    int h=1;
    LL l=x,r=x;
    vector<pair<LL,LL>> rs; rs.emplace_back(l,r);
    while((l<<1)<ub) {
      l=l<<1;
      r=(r<<1)+1;
      ++h;
      rs.emplace_back(l,r);
    }
    return {rs,h};
  }

  long long solve(int K, vector<long long> F) {
    this->ub=(1LL<<K);
    LL res=(1LL<<K)-2;
    sort(F.begin(),F.end());
    REP(i,SZ(F)) if(F[i]>0) {
      pair<vector<pair<LL,LL>>,int> sub=subtree(F[i]);
      vector<LL> xs;
      FOR(j,i+1,SZ(F)) FORR(p,sub.first) if(F[j]>0) {
        LL l=p.first,r=p.second;
        if(l<=F[j]&&F[j]<=r) xs.push_back(F[j]),F[j]=0;
      }
      int h=sub.second;
//      dump2(F[i],h);
//      dumpAR(xs);
      res -= (1LL<<h)-1;
    }
    
    return res;
  }
};

class NumberGameAgain {
public:
  long long solve(int K, vector<long long> F) {
    LL ub=(1LL<<K)-1;
    sort(F.begin(),F.end());
    vector<pair<LL, int>> rs;
    rs.emplace_back(2,1); rs.emplace_back(1LL<<K,-1);
    
    FORR(x,F) {
      LL l=x,r=x;
      while(l<=ub) {
        rs.emplace_back(l,-1);
        rs.emplace_back(r+1,1);
        l*=2; r=2*r+1;
      }
    }
    sort(rs.begin(), rs.end());
    LL res=0;
    LL end=0; int cnt=0;
    FORR(r,rs) {
//      dump3(cnt,r.first,r.second);
      if(cnt>0) res+=r.first-end;
      cnt+=r.second;
      end=r.first;
    }
    return res;
  }
};

// CUT begin
ifstream data("NumberGameAgain.sample");

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

bool do_test(int k, vector<long long> table, long long __expected) {
    time_t startClock = clock();
    NumberGameAgain *instance = new NumberGameAgain();
    long long __result = instance->solve(k, table);
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
        int k;
        from_stream(k);
        vector<long long> table;
        from_stream(table);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, table, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505489407;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "NumberGameAgain (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
