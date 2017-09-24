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
 
 9/23/2017
 
 14:07-14:19 designed with imos method though, figured out that number of cats matters too.
 14:35-14:49 redesigned and submit (1WA) (231.89 pt)
 16:22-16:31 boundary bug fix. system test passed.
 
 key:
  - greedily put cats from left-most position one by one
 
 summary:
  - again it took a while to analyze problem correctly 👎
    - first analysis was completely wrong
    - always pay attention to counter example
    - time loss due to wrong analysis is quite expensive
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+631
  - http://kmjp.hatenablog.jp/entry/2014/08/31/0930
 
 */
class CatsOnTheLineDiv2 {
public:
  const string yes="Possible",no="Impossible";
  string getAnswer(vector<int> P, vector<int> C, int t) {
    int N=SZ(P);
    vector<II> xs;
    REP(i,N) xs.emplace_back(P[i],i);
    sort(xs.begin(),xs.end());
    
    int prev=-1e8;
    FORR(p,xs) {
      int l=max(prev,p.first-t),r=min(p.first+t+1, l+C[p.second]);
      if(r-l<C[p.second]) return no;
      prev=r;
    }
    return yes;
  }
};

class CatsOnTheLineDiv2_wrong {
  public:
  const string yes="Possible",no="Impossible";
  string getAnswer(vector<int> P, vector<int> C, int t) {
    int N=SZ(P);
    vector<II> rs;
    REP(i,N) {
      rs.emplace_back(P[i]-t,-1);
      rs.emplace_back(P[i]+t,1);
      dump2(P[i]-t,P[i]+t);
    }
    sort(rs.begin(),rs.end());
    
    int im=0,tot=0,prev=rs.front().first;
    FORR(p,rs) {
      if(p.second==1) {
        --im;
      } else {
        ++im;
      }
      assert(im>=0);
      if(im==0&&p.second==1) {  dump2(prev,p.first); tot+=p.first-prev+1; }
      else if(im==1&&p.second==-1) prev=p.first;
    }
    
    int sum=accumulate(C.begin(),C.end(),0);
    dump2(sum,tot);
    return tot>=sum?yes:no;
  }
};

// CUT begin
ifstream data("CatsOnTheLineDiv2.sample");

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

bool do_test(vector<int> position, vector<int> count, int time, string __expected) {
    time_t startClock = clock();
    CatsOnTheLineDiv2 *instance = new CatsOnTheLineDiv2();
    string __result = instance->getAnswer(position, count, time);
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
        vector<int> position;
        from_stream(position);
        vector<int> count;
        from_stream(count);
        int time;
        from_stream(time);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(position, count, time, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506200808;
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
        cout << "CatsOnTheLineDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
