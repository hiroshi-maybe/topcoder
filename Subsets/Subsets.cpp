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
 
 10/3/2017
 
 9:31-10:08 pause
 17:55-18:15 give up
 
 18:35-19:33 read editorials and add solution:
  - https://apps.topcoder.com/wiki/display/tc/SRM+622
    - backtracking
  - http://kmjp.hatenablog.jp/entry/2014/05/31/1130
    - DP
  - http://torus711.hatenablog.com/entry/20140530/1401459509
    - more naiive backtracking
     - even if input is ns=[1,..,1] ns.size=1000, number of recursive call is nearly at most 1000*1000 = 10^6
 
 if number larger than 1 is added to sets, x*y dominates x+y.
 thus if `sum` < `prod` holds, number of sets is max(`sum`+{number of 1}-`prod`, 0)
 
 Suppose ns = [1,1,1,...,1,2,..,2] (1xp and 2xq, p+q=1000).
 
 p+q=1000
 1*p+2*q>1^p*2^q
 => 2^q-q<1000
 => q<=9
 
 thus even if we brute-force by backtracking, recursive call stops at most 9 for numbers larger than 1.
 note that `ns` should be sorted before hand.
 
 19:34-19:48 add simpler solution
  - count all 1 cases in backtracking to simplify base case
  - remove depth check because analysis shows recursive call stops by sum<=prod check at most 9 calls
 
 22:59-23:18 add simpler and more naiive backtracking
 
 key:
  - backtracking of duplicated elements by jumping to next different value
    - same technique to count permutation with duplicated elements
  - prove upper bound number of recursive calls by analysis in 2^N algorithm
 
 summary:
  - nice set is rare. even 2*2 doesn't satisfy it. I figured out it.
  - I didn't have idea to prove that branch pruning is finished within time limit
 
 */

class Subsets {
public:
  int cnt1;
  VI ns;
  int dfs(int i, int sum, int prod) {
    //    if(i==SZ(ns)||(sum+ns[i]<=prod*ns[i])) return sum>prod;
    //    if(i==SZ(ns)||(sum>0&&sum+ns[i]<prod*ns[i])) return sum>prod;
    // below is simplest condition. sum=0 is the only corner case
    if(i==SZ(ns)||(sum>0&&sum<prod)) return sum>prod;
    int n=ns[i];
    int next=upper_bound(ns.begin(),ns.end(),n)-ns.begin();
    return dfs(i+1,sum+n,prod*n)+dfs(next,sum,prod);
  }
  
  int findSubset(vector<int> ns) {
    sort(ns.begin(),ns.end());
    this->ns=ns;
    return dfs(0,0,1);
  }
};

// simplified original code
class Subsets_procLT1 {
public:
  int cnt1;
  VI ns;
  int dfs(int i, int sum, int prod) {
    int N=SZ(ns);
    int n=ns[i];
    if(i==N||n+sum+cnt1<=prod*n) return max(0, sum+cnt1-prod);
    int next=upper_bound(ns.begin(),ns.end(),ns[i])-ns.begin();
    return dfs(i+1,sum+ns[i],prod*ns[i])+dfs(next,sum,prod);
  }
  
  int findSubset(vector<int> ns) {
    sort(ns.begin(),ns.end());
    this->ns=ns;
    this->cnt1=count(ns.begin(),ns.end(),1);
    
    int start=upper_bound(ns.begin(),ns.end(),1)-ns.begin();
    
    return dfs(start,0,1);
  }
};

// specifically count sets without 1s in backtracking
class Subsets_org {
  public:
  int cnt1;
  VI ns;
  int dfs(int i, int sum, int prod, int depth) {
    if(depth==10) return 0;
    int N=SZ(ns);
    assert(sum>=0);
    if(i==N||(sum>0&&sum+cnt1<=prod)) return sum==0?0:max(0, sum+cnt1-prod);
    int next=upper_bound(ns.begin(),ns.end(),ns[i])-ns.begin();
    return dfs(i+1,sum+ns[i],prod*ns[i],depth+1)+dfs(next,sum,prod,depth);
  }
  
  int findSubset(vector<int> ns) {
    sort(ns.begin(),ns.end());
    this->ns=ns;
    this->cnt1=count(ns.begin(),ns.end(),1);
    
    int start=upper_bound(ns.begin(),ns.end(),1)-ns.begin();
    
    return max(cnt1-1+dfs(start,0,1,0),0);
  }
};

// CUT begin
ifstream data("Subsets.sample");

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

bool do_test(vector<int> numbers, int __expected) {
    time_t startClock = clock();
    Subsets *instance = new Subsets();
    int __result = instance->findSubset(numbers);
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
        vector<int> numbers;
        from_stream(numbers);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numbers, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507048299;
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
        cout << "Subsets (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
