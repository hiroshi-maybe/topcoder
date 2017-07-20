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
 
 7/19/2017
 
 8:48-9:47 give up
 
 20:54 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/08/01/0900
 - http://tsutaj.hatenablog.com/entry/2016/07/19/221019
 
 21:29 
 - how to induce to subproblem
 - research was not enough. X[p-1] should not affect X[p]
 
 21:48 passed system test
 
 Keys:
 - In many problems, we induce to subproblem by moving index of array though, in this problem, solving at X[i] surely affects X[j], j<i. So I should have mutated entire X whenever problem is reducible.
 - Research was not sufficient when I solved this problem. Suppose X=[*,*,2,0,0]. I cannot put "aaaa" because it violates condition of X[3]=0.
 
 Same approach:
 - https://community.topcoder.com/stat?c=problem_solution&rm=329069&rd=16767&pm=14366&cr=40338213
 - https://community.topcoder.com/stat?c=problem_solution&rm=329058&rd=16767&pm=14366&cr=23131657
 - https://community.topcoder.com/stat?c=problem_solution&rm=329064&rd=16767&pm=14366&cr=40100608
 
 */

class BearPasswordAny {
public:
  string findPassword(vector<int> X) {
    string res="";
    int i=SZ(X)-1;
    while(i>=0&&X[i]==0) --i;
    if(i<0) return res;
    int x=0;
    while(i>=0) {
      if(X[i]<0) return "";
      else if(X[i]==0) {
        --i;
        continue;
      }
      
      int n=X[i];
      REP(_,n) {
        res.append(i+1,'a'+x);
        ++x; x%=2;
      }
      for(int o=0; i-o>=0; ++o) {
        int j=i-o;
        X[j]-=n*(i-j+1);
      }
      --i;
    }
    
    return SZ(res)==SZ(X) ? res : "";
  }
};

class BearPasswordAny_giveup {
  public:
  string findPassword(vector<int> X) {
    int N=SZ(X);
    VI temp=X; sort(temp.begin(),temp.end(),greater<int>());
    REP(i,N) if(temp[i]!=X[i]) return "";
    
    int k=0;
    string res="";
    int f=true;
    for(int i=N-1; i>=0; --i) {
      if(X[i]==0) continue;
      if(k==0) {
        res.append(X[i]+i,f?'a':'b'); f=!f;
        k=X[i]+i;
      } else {
        int n=X[i]+i-k;
        if(n<0) return "";
        if(n==0) continue;
        --k;
        
        int m=k-(i+1)+1;
        while(n>=m) {
          res.append(m,f?'a':'b'); f=!f;
          n-=m;
        }
        if(n>0) {
          k=n;
        }
      }
    }
    
    return SZ(res)==N ? res : "";
  }
};

// CUT begin
ifstream data("BearPasswordAny.sample");

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

bool do_test(vector<int> x, string __expected) {
    time_t startClock = clock();
    BearPasswordAny *instance = new BearPasswordAny();
    string __result = instance->findPassword(x);
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
        string __answer;
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
        int T = time(NULL) - 1500479268;
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
        cout << "BearPasswordAny (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
